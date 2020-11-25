#include "emuart.h"

//帧头为0xa5,0x06；帧尾为0xb6,0x07
static uint8_t emuartFrameHead[2] = {0xa5,0x06};  //帧头
static uint8_t emuartFrameTail[2] = {0xb6,0x07};  //帧尾
static uint8_t emuartTerminStr[13] ="StOpUeMySeLf";  //uecom终结组帧字符串
static uint8_t UART_NO=2;      //emuart使用的串口

//======================内部函数声明====================================
//在函数定义处有详细说明
void sendFrame(uint16_t length,uint8_t *data);
uint16_t crc16(uint8_t *ptr,uint16_t len);

//======================内部函数声明结束==================================

//=====================================================================
//函数名称：emuart_init
//函数返回： 无
//参数说明： uartNo：emuart使用的串口； baud：emuart的波特率。
//功能概要：初始化emuart
//更新记录：20180602，wb；
//=====================================================================
void emuart_init(uint8_t uartNo,uint32_t baud)
{
	uart_init(uartNo,baud);
	uart_enable_re_int(uartNo);
	UART_NO = uartNo;
}

//=====================================================================
//函数名称：emuart_send1
//函数返回： 无
//参数说明： a：待发送的一个字节数据
//功能概要：通过emuart发送一个字节数据
//更新记录：20180602，wb；
//=====================================================================
void emuart_send1(uint8_t a)
{
	sendFrame(1,&a);
}

//=====================================================================
//函数名称：emuart_sendN
//函数返回： 无
//参数说明： len：待发送数组的长度；buff：待发送数据缓冲区
//功能概要：通过emuart发送一个字节数组
//更新记录：20180602，wb；
//=====================================================================
void emuart_sendN(uint8_t len ,uint8_t* buff)
{
	sendFrame(len,buff);
}

//=====================================================================
//函数名称：emuart_send_string
//函数返回： 无
//参数说明： buff：待发送的字符串
//功能概要：通过emuart发送一个字符串
//更新记录：20180602，wb；
//=====================================================================
void emuart_send_string(uint8_t * buff)
{
	uint16_t len=0;
	while(buff[len])len++;
	sendFrame(len,buff);
}

//===========================================================================
//函数名称：emuart_recv
//功能概要：组建数据帧，将待组帧数据加入到数据帧中。本函数应被放置于中断中。
//参数说明：ch：串口中断接收到的一个字节的串口数据；data：存放接收到的数据。
//函数返回：0：未接收到数据；非0：接收到一帧长度组帧成功，且返回值为接收到的数据长度
//备注：十六进制数据帧格式
//        帧头       + 数据长度         + 有效数据   +CRC校验码 +  帧尾
//        emuartFrameHead(2字节)  +  len(2字节)   + 有效数据(N字节 N=len[0]*256+len[1])
//        +CRC校验(2字节)+  emuartFrameTail(2字节)
//
//===========================================================================
uint16_t emuart_recv(uint8_t ch, uint8_t *data)
{
	static uint16_t index = 0;
	static uint16_t length = 0;
	static uint8_t markPos=0;
	uint16_t ret_val;
	uint16_t i;
	uint8_t CRC1[2];
	uint16_t crc;


	//（1）若未接收到数据或者未遇到帧头，则退出并返回0  帧头长度为两个字节
	if((index == 0 && ch != emuartFrameHead[0]) ||
			(index == 1 && ch != emuartFrameHead[1]))
	{
		index = 0;
		length = 0;
		ret_val = 0;     //接收数据错误
		goto uecom_recv_exit;
	}
	//（2）正确接收到了帧头，继续执行，将数据存入data数组
	data[index++] = ch;
	//（3）当获取到第四个数据时，求出有效数据长度
	if(index == 4)
	{
		length = ((uint16_t)data[2]<<8) + data[3];
	}

	//（4）如果接收到的数据达到一帧长度（帧长度=有效数据长度+8），进行CRC校验，如果校验通过将进行数据的处理。
	if(length != 0 && index >= length+8)
	{
		//（4.1）对有效数据进行CRC校验
		crc = crc16(data+4,length);
		CRC1[0] =(uint8_t)( (crc>>8)&0xff);
		CRC1[1] = crc&0xff;
		//（4.2）当未获取到帧尾或CRC校验出错，则出错返回0
		if(data[index-2]!=emuartFrameTail[0] || data[index-1]!= emuartFrameTail[1]//未遇到帧尾
||	CRC1[0] != data[index-4] || CRC1[1] != data[index-3])//CRC检验错误
		{
			//出错返回
			index = 0;
			length = 0;
			ret_val = 0;
			goto uecom_recv_exit;
		}
		//（4.3）将前4个字节移出buf数组，令buf数组全为有效数据，并返回有效数据
		for(i=0;i<length;i++)
		{
			data[i] = data[i+4];
		}
		index = 0;
		ret_val = length; //返回有效数据长度
		data[length] = 0; //令数组长度为0
		//（4.4）收到的数据若为上位机搜寻emuart设备的字符串，则进行响应
		if(length == 21 &&
			!strcmp(data,"[Are you an emuart??]"))
		{
			emuart_send_string("[Yes,I am an emuart!!]");
			ret_val = 0;
		}
		length = 0; //令有效数据长度为0
		goto uecom_recv_exit;
	}
	ret_val = 0;
uecom_recv_exit:
    return ret_val;
}

//======以下为内部函数====================================================
//=====================================================================
//函数名称：sendFrame
//函数返回： 无
//参数说明：length：待发送数据的长度；data：待发送数据缓冲区。
//功能概要：通过emuart发送指定长度的字节数组。
//更新记录：20180602，wb；
//=====================================================================
void sendFrame(uint16_t length,uint8_t *data)
{
	uint16_t crc,len;
	//计算得到CRC校验码
	crc = crc16(data,length);
	//发送帧头
	uart_send1(UART_NO,emuartFrameHead[0]);
	uart_send1(UART_NO,emuartFrameHead[1]);
	//发送帧长
	uart_send1(UART_NO,length>>8);
	uart_send1(UART_NO,length);
	//发送帧数据
	uart_sendN(UART_NO,length,data);
    //发送校验码
	uart_send1(UART_NO,crc>>8);
	uart_send1(UART_NO,crc);
	//发送帧尾
	uart_send1(UART_NO,emuartFrameTail[0]);
	uart_send1(UART_NO,emuartFrameTail[1]);
}



//=====================================================================
//函数名称：crc16
//功能概要：将数据进行16位的CRC校验，返回校验后的结果值
//参数说明：ptr:需要校验的数据缓存区
//     len: 需要检验的数据长度
//函数返回：计算得到的校验值
//=====================================================================
uint16_t crc16(uint8_t *ptr,uint16_t len)
{
	uint16_t i,j,tmp,crc16;

	crc16 = 0xffff;
	for(i = 0;i < len;i++)
	{
		crc16 = ptr[i]^crc16;
		for(j = 0;j< 8;j++)
		{
			tmp = crc16 & 0x0001;
			crc16 = crc16>>1;
			if(tmp)
				crc16 = crc16^0xa001;
		}
	}
	return crc16;
}
