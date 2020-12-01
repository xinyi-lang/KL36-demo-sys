//=====================================================================
//文件名称：isr.c（中断处理程序源文件）
//框架提供：SD-ARM（sumcu.suda.edu.cn）
//版本更新：20170801-20191020
//功能描述：提供中断处理程序编程框架
//=====================================================================
#include "includes.h"
//声明使用到的内部函数
//isr.c使用的内部函数声明处
void SecAdd1(uint8_t *p);
//======================================================================
//中断服务程序名称：UART_User_Handler
//触发条件：UART_User串口收到一个字节触发
//功    能：收到一个字节，直接返回该字节
//备    注：进入本程序后，可使用uart_get_re_int函数可再进行中断标志判断
//          （1-有UART接收中断，0-没有UART接收中断）
//======================================================================
void UART_User_Handler(void)
{
    uint8_t ch;
	uint8_t flag,mFlag;
    uint32_t i;
    uint8_t flashRead[2048];


	DISABLE_INTERRUPTS;      //关总中断
	//------------------------------------------------------------------
	//接收一个字节
	//（1）接收一个字节
	ch = uart_re1(UART_User, &flag);   //调用接收一个字节的函数，清接收中断位
    
	if(flag==0)  goto UARTA_IRQHandler_Exit;     //若没有成功接收数据，直接退出
	//（2）调用组帧程序，对接收到的数据组帧
	gcRecvLen = emuart_recv(ch,gcRecvBuf);         //组帧程序仅当组帧完成时返回非0帧长
//	uart_send1(UART_User,ch);
	if(gcRecvLen == 0) goto UARTA_IRQHandler_Exit;//未组帧直接退出
    if(gcRecvBuf[0]==8&&strncmp((char *)(gcRecvBuf+1),"LED",3) == 0)
    {
    	gchflag=1;	
    }
    if(gcRecvBuf[0]==8&&strncmp((char *)(gcRecvBuf+1),"ADC",3) == 0)
    {
    	gadflag=1;	
    }
    if(gcRecvBuf[0]==10&&strncmp((char *)(gcRecvBuf+1),"KL36?",5) == 0)
    {
    	uart_send_string(UART_User,"I am an KL36");                   //与上位机握手，确立通信关系
    	LCD_ShowString(60,40,BLACK,GRAY,(char *)"                     ");
        LCD_ShowString(60,40,YELLOW,GRAY,(char *)"KL36 is connecting");
    }
    if(gcRecvBuf[0]==7&&strncmp((char *)(gcRecvBuf+1),"ok",2) == 0)
    {
    	LCD_ShowString(60,40,BLACK,GRAY, (char *)"                     ");
        LCD_ShowString(60,40,YELLOW,GRAY,(char *)"KL36 is ready");
    }

//	if(gcRecvBuf[0]!=0xFF)
//    {
//
//		   switch(gcRecvBuf[0])
//		   {
//		        case'r':
//
//					flash_read_logic(flashRead,gcRecvBuf[1],(gcRecvBuf[2]<<8)|gcRecvBuf[3],gcRecvBuf[4]);
//					mFlag=1;
//					for(i=0;i<gcRecvBuf[4];i++)   //判空
//					{
//					   if(flashRead[i]!=0xFF)
//					   {
//						   mFlag=0;
//						   break;
//
//					   }
//					}
//
//					if(mFlag==1)
//						uart_send_string(UART_User," selected area is empty\n");
//					else
//						uart_sendN(UART_User,gcRecvBuf[4],flashRead);
//
////					uart_sendN(UART_User,gcRecvBuf[4],gcRecvBuf);
//
//					//还原标志变量及接收数组
//					memset(gcRecvBuf,0xFF,gcRecvBuf[5]);
//					mFlag=1;
//
//					 break;
//
//				case'a':
//
//					flash_read_physical(flashRead,(gcRecvBuf[1]<<24)|(gcRecvBuf[2]<<16)|(gcRecvBuf[3]<<8)|gcRecvBuf[4],gcRecvBuf[5]);
////					uart_sendN(UART_User,gcRecvBuf[5],flashRead);
//					mFlag=1;
//					for(i=0;i<gcRecvBuf[5];i++)   //判空
//					{
//					   if(flashRead[i]!=0xFF)
//					   {
//						   mFlag=0;
//						   break;
//
//					   }
//					}
//					if(mFlag==1)
//						uart_send_string(UART_User," selected area is empty\n");
//					else
//					    uart_sendN(UART_User,gcRecvBuf[5],flashRead);
//
//
//					//还原标志变量及接收数组
//					memset(gcRecvBuf,0xFF,gcRecvBuf[5]);
//					mFlag=1;
//
//				 break;
//				case 'w':
//					mFlag=flash_erase(gcRecvBuf[1]);
//					mFlag=flash_write(gcRecvBuf[1], (gcRecvBuf[2]<<8)|gcRecvBuf[3],gcRecvBuf[4],&gcRecvBuf[5]);
//
//					if(mFlag==0)
//						uart_send_string(UART_User,"Write OK！!\n");
//					else
//						uart_send_string(UART_User,"Write error！!\n");
//
////					uart_sendN(UART_User,gcRecvBuf[5],gcRecvBuf);
//
//					memset(gcRecvBuf,0xFF,gcRecvBuf[5]);
//					mFlag=1;
//
//				 break;
//				case 'e':
//					mFlag=flash_erase(gcRecvBuf[1]);
////					uart_sendN(UART_User,gcRecvBuf[5],gcRecvBuf);
//
//					if(mFlag==0)
//						uart_send_string(UART_User,"erase OK！!\n");
//					else
//						uart_send_string(UART_User,"erase error！!\n");
//
//
//					//还原标志变量及接收数组
//					memset(gcRecvBuf,0xFF,gcRecvBuf[5]);
//					mFlag=1;
//				 break;
//
//				 default:
//					 uart_send_string(UART_User,"default test!\n");
//					 break;
//		   }
//
//    }
	UARTA_IRQHandler_Exit:
	gcRecvLen = 0;  //恢复接收状态

	//------------------------------------------------------------------
	ENABLE_INTERRUPTS;       //开总中断
}

//=====================================================================
//函数名称：SYSTICK_USER_Handler（SysTick定时器中断处理程序）
//参数说明：无
//函数返回：无
//功能概要：（1）每10ms中断触发本程序一次；（2）达到一秒时，调用秒+1
//           程序，计算“时、分、秒”
//特别提示：（1）使用全局变量字节型数组gTime[3]，分别存储“时、分、秒”
//          （2）注意其中静态变量的使用
//=====================================================================
//void SYSTICK_USER_Handler()

void SysTick_Handler()
{
	static uint8_t SysTickCount = 0;
	SysTickCount++;    //Tick单元+1
	wdog_feed();      //看门狗“喂狗”
	if (SysTickCount >= 100)
	{
		SysTickCount = 0;
		SecAdd1(gTime);
	}
}



//===========================================================================
//函数名称：SecAdd1
//函数返回：无
//参数说明：*p:为指向一个时分秒数组p[3]
//功能概要：秒单元+1，并处理时分单元（00:00:00-23:59:59)
//===========================================================================
void SecAdd1(uint8_t *p)
{
	*(p+2)+=1;         //秒+1
	if(*(p+2)>=60)     //秒溢出
	{
		*(p+2)=0;       //清秒
		*(p+1)+=1;      //分+1
		if(*(p+1)>=60)  //分溢出
		{
			*(p+1)=0;    //清分
			*p+=1;       //时+1
			if(*p>=24)   //时溢出
			{
				*p=0;      //清时
			}
		}
	}
}

/*
 知识要素：
 1.本文件中的中断处理函数调用的均是相关设备封装好的具体构件，在更换芯片
 时，只需保证设备的构件接口一致，即可保证本文件的相关中断处理函数不做任何
 更改，从而达到芯片无关性的要求。
 */
