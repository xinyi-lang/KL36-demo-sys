//=====================================================================
//文件名称：spi.c
//功能概要：spi底层驱动构件源文件
//制作单位：苏州大学嵌入式系统与物联网研究所(sumcu.suda.edu.cn)
//版    本：  2019-05-09  V2.0
//适用芯片：KL25、KL26、KL36
//=====================================================================
#include "spi.h"


//=====================================================================
//函数名称：spi_init。
//功能说明：SPI初始化
//函数参数：No：模块号，可用参数可参见gec.h文件
//       MSTR：SPI主从机选择，0选择为从机,1选择为主机。
//       BaudRate：波特率，可取12000、6000、4000、3000、1500、1000，单位：bps
//       CPOL：CPOL=0：高有效SPI时钟（低无效）；CPOL=1：低有效SPI时钟（高无效）
//       CPHA：CPHA=0相位为0； CPHA=1相位为1；
//函数返回：无
//=====================================================================
void spi_init(uint8_t No,uint8_t MSTR,uint16_t BaudRate,\
uint8_t CPOL,uint8_t CPHA)
{
    uint8_t BaudRate_Mode;
    uint8_t BaudRate_High;
    uint8_t BaudRate_Low;
    if(No<0||No>1)   No=0;    //如果SPI号参数错误则强制选择 0号模块
    if(No==0)                         //初始化SPI0功能
    {
        BSET(SIM_SCGC4_SPI0_SHIFT,SIM_SCGC4);   //打开SPI0模块时钟。
        //引脚复用为SPI0功能
        PORTC_PCR4=(0|PORT_PCR_MUX(0x02));        //选择PTC4的SS功能
        PORTC_PCR5=(0|PORT_PCR_MUX(0x02));        //选择PTC5的SCK功能
        PORTC_PCR6=(0|PORT_PCR_MUX(0x02));        //选择PTC6的MOSI功能
        PORTC_PCR7=(0|PORT_PCR_MUX(0x02));        //选择PTC7的MIOS功能
        wdog_feed();
        
        SPI0_C1=0x00;                           //SPI控制寄存器1清零
        BSET(SPI_C1_SPE_SHIFT,SPI0_C1);         //使能SPI模块
        
        //MSTR=1为主机模式；
        //MSTR=0为从机模式（因MSTR初始值为0，无需更改）
        (MSTR==1)?BSET(SPI_C1_MSTR_SHIFT,SPI0_C1):\
        BSET(SPI_C1_SPIE_SHIFT,SPI0_C1);
        
        //时钟极性配置，CPOL=0，平时时钟为高电平，反之CPOL=1，平时时钟为低电平
        (0==CPOL)?BCLR(SPI_C1_CPOL_SHIFT,SPI0_C1):\
        BSET(SPI_C1_CPOL_SHIFT,SPI0_C1);
        
        //时钟相位CPHA
        (0 == CPHA)?BCLR(SPI_C1_CPHA_SHIFT,SPI0_C1):\
        BSET(SPI_C1_CPHA_SHIFT,SPI0_C1);
        wdog_feed();
        ////SSOE为1,MODFEN为1，配置本模块为自动SS输出
        BSET(SPI_C1_SSOE_SHIFT,SPI0_C1);
        //对SPI0的C1寄存器配置为主机模式、从机选择自动模式并使能SPI0模块。
        SPI0_C2=0x00;
        if(MSTR == 1 )  //主机模式
        BSET(SPI_C2_MODFEN_SHIFT,SPI0_C2);
        SPI0_BR = 0x00U;//波特率寄存器清零
        //重新设置波特率
        BaudRate_High=0;
        BaudRate_Low=0;
        BaudRate_Mode=24000/BaudRate;
        wdog_feed();
        if(BaudRate_Mode <= 8)
        {
            SPI0_BR = (BaudRate_Mode - 1) << 4;
        }
        else
        {
            
            while(BaudRate_Mode / 2 > 8)
            {
                wdog_feed();
                BaudRate_Low++;
                BaudRate_Mode=BaudRate_Mode/2;
            }
            BaudRate_High=--BaudRate_Mode;
            SPI0_BR=BaudRate_High<<4;//数值赋给SPI0_BR的SPPR的D6D5D4位
            SPI0_BR|=BaudRate_Low;//赋值给SPI0_BR的SPR的 D2D1D0位
        }
    }
    else         //初始化SPI1功能
    {
        wdog_feed();
        BSET(SIM_SCGC4_SPI1_SHIFT,SIM_SCGC4);   //打开SPI1模块时钟。
        //引脚复用为SPI1功能
        PORTD_PCR4=(0|PORT_PCR_MUX(0x02));        //选择PTD4的SS功能
        PORTD_PCR5=(0|PORT_PCR_MUX(0x02));        //选择PTD5的SCK功能
        PORTD_PCR6=(0|PORT_PCR_MUX(0x02));        //选择PTD6的MOSI功能
        PORTD_PCR7=(0|PORT_PCR_MUX(0x02));        //选择PTD7的MIOS功能
        wdog_feed();
        SPI1_C1=0x00;                     //SPI控制寄存器1清零
        BSET(SPI_C1_SPE_SHIFT,SPI1_C1);   //使能SPI模块
        //MSTR=1为主机模式；
        //MSTR=0为从机模式（因MSTR初始值为0，无需更改）
        (MSTR==1)?BSET(SPI_C1_MSTR_SHIFT,SPI1_C1):\
        BSET(SPI_C1_SPIE_SHIFT,SPI1_C1);
        
        //时钟极性配置，CPOL=0，平时时钟为高电平，反之CPOL=1，平时时钟为低电平
        (0 == CPOL)?BCLR(SPI_C1_CPOL_SHIFT,SPI1_C1):\
        BSET(SPI_C1_CPOL_SHIFT,SPI1_C1);
        
        //CPHA=0时钟信号的第一个边沿出现在8周期数据传输的第一个周期的中央；
        //CPHA=1时钟信号的第一个边沿出现在8周期数据传输的第一个周期的起点。
        (0 == CPHA)?BCLR(SPI_C1_CPHA_SHIFT,SPI1_C1): \
        BSET(SPI_C1_CPHA_SHIFT,SPI1_C1);
        wdog_feed();
        BSET(SPI_C1_SSOE_SHIFT,SPI1_C1);//SSOE为1,MODFEN为1，配置本模块为自动SS输出
        //对SPI0的C1寄存器配置为主机模式、从机选择自动模式并使能SPI0模块。
        
        //        BSET(SPI_C1_SPIE_SHIFT,SPI1_C1);  //开本模块的SPI中断
        SPI1_C2 = 0x00U;
        if(MSTR == 1 )  //主机模式
        BSET(SPI_C2_MODFEN_SHIFT,SPI1_C2);
        SPI1_BR = 0x00U;
        //重新设置波特率
        BaudRate_High=0;
        BaudRate_Low=0;
        BaudRate_Mode=24000/BaudRate;   //取除数用于寄存器中数据计算
        wdog_feed();
        if(BaudRate_Mode <= 8)
        {
            SPI0_BR = (BaudRate_Mode - 1) << 4;
        }
        else
        {
            while(BaudRate_Mode / 2 > 8)
            {
                wdog_feed();
                BaudRate_Low++;
                BaudRate_Mode=BaudRate_Mode/2;
            }
            BaudRate_High=--BaudRate_Mode;
            SPI0_BR=BaudRate_High<<4;//数值赋给SPI0_BR的SPPR的D6D5D4位
            SPI0_BR|=BaudRate_Low;//赋值给SPI0_BR的SPR的 D2D1D0位
        }
    }
}

//=====================================================================
//函数名称：spi_send1.
//功能说明：SPI发送一字节数据。
//函数参数：No：模块号，可用参数可参见gec.h文件
//       data：     需要发送的一字节数据。
//函数返回：0：发送失败；1：发送成功。
//=====================================================================
uint8_t spi_send1(uint8_t No,uint8_t data)
{
    uint32_t i;
    SPI_MemMapPtr baseadd=SPI_baseadd(No);
    while(!(SPI_S_REG(baseadd)&SPI_S_SPTEF_MASK));//等待发送缓冲区空闲
    SPI_DL_REG(baseadd)=data;//数据寄存器接收数据
    for(i=0;i<0xFFF0;i++)        //在一定时间内发送不能完成，则认为发送失败。
    {
        if(SPI_S_REG(baseadd)&SPI_S_SPTEF_MASK)//判断发送缓冲区是否接到数据
        {
            return(1);
        }
    }
    return(0);
}

//=====================================================================
//函数名称：spi_sendN
//功能说明：SPI发送数据。
//函数参数：No：模块号，可用参数可参见gec.h文件
//       n:     要发送的字节个数。范围为(1~255)
//       data[]:所发数组的首地址。
//函数返回：无。
//=====================================================================
void spi_sendN(uint8_t No,uint8_t n,uint8_t data[])
{
    SPI_MemMapPtr baseadd=SPI_baseadd(No);
    uint32_t k;
    for(k=0;k<n;k++)
    {
        //状态寄存器的SPTEF位不空
        while(!(SPI_S_REG(baseadd)&SPI_S_SPTEF_MASK));
        SPI_DL_REG(baseadd)=data[k];
        SPI_S_REG(baseadd) !=  SPI_S_SPTEF_MASK;    //清除SPTEF位
    }
}

//=====================================================================
//函数名称：spi_receive1.
//功能说明：SPI接收一个字节的数据
//函数参数：No：模块号，可用参数可参见gec.h文件
//函数返回：接收到的数据。
//=====================================================================
uint8_t spi_receive1(uint8_t No)
{
    SPI_MemMapPtr baseadd=SPI_baseadd(No);
    while(!(SPI_S_REG(baseadd)& SPI_S_SPRF_MASK));    //检测SPI是否收到了数据。
    return SPI_DL_REG(baseadd);
}

//=====================================================================
//函数名称：spi_receiveN.
//功能说明：SPI接收数据。当n=1时，就是接受一个字节的数据……
//函数参数：No：模块号，可用参数可参见gec.h文件
//        n:    要发送的字节个数。范围为(1~255),
//       data[]:接收到的数据存放的首地址。
//函数返回：1：接收成功,其他情况：失败。
//=====================================================================
uint8_t spi_receiveN(uint8_t No,uint8_t n,uint8_t data[])
{
    SPI_MemMapPtr baseadd=SPI_baseadd(No);
    uint32_t m=0;
    while(m<n)
    {
        if(SPI_S_REG(baseadd)&SPI_S_SPRF_MASK)
        {
            data[m]=SPI_DL_REG(baseadd);
            m++;
        }
    }
    return(1);
}

//=====================================================================
//函数名称：spi_enable_re_int
//功能说明：打开SPI接收中断。
//函数参数：No：模块号，可用参数可参见gec.h文件
//函数返回：无。
//=====================================================================
void spi_enable_re_int(IRQn_Type SPI_No)
{
	NVIC_EnableIRQ(SPI_No+10);
}

//=====================================================================
//函数名称：spi_disable_re_int
//功能说明：关闭SPI接收中断。
//函数参数：No：模块号，可用参数可参见gec.h文件
//函数返回：无。
//=====================================================================
void spi_disable_re_int(IRQn_Type SPI_No)
{
	NVIC_DisableIRQ(SPI_No+10);
}

