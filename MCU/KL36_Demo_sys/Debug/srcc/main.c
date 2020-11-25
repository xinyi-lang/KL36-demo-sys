//====================================================================
//文件名称：main.c（应用工程主函数）
//框架提供：SD-Arm（sumcu.suda.edu.cn）
//版本更新：2017.08, 2020.05
//功能描述：见本工程的<01_Doc>文件夹下Readme.txt文件
//====================================================================
#define GLOBLE_VAR
#include "includes.h"      //包含总头文件

//----------------------------------------------------------------------
//声明使用到的内部函数
//main.c使用的内部函数声明处

//----------------------------------------------------------------------
//主函数，一般情况下可以认为程序从此开始运行（实际上有启动过程见书稿）
int main(void)
{
    //（1）======启动部分（开头）==========================================
    //（1.1）声明main函数使用的局部变量
    uint32_t mMainLoopCount;  //主循环使用的记录主循环次数变量
    uint8_t  mFlag;           //主循环使用的临时变量
    uint8_t  mSec;	         //记当前秒的值
    uint8_t  i;
    //（1.2）【不变】关总中断
    DISABLE_INTERRUPTS;
    wdog_stop();
    
    //（1.3）给主函数使用的局部变量赋初值
    mFlag=1;              //主循环使用的临时变量：蓝灯状态标志
    
    //（1.4）给全局变量赋初值
   	//"时分秒"缓存初始化(00:00:00)
   	gTime[0] = 0;       //时
   	gTime[1] = 0;	  	//分
   	gTime[2] = 0;	  	//秒
   	mSec = gTime[2];	//记住当前秒的值
    //（1.5）用户外设模块初始化
    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);    //初始化蓝灯
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);    //初始化蓝灯
    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);    //初始化蓝灯
    LCD_Init();
    
    LCD_aotu(2,2,238,318,0);
    LCD_ShowString(92,20,RED,GRAY,(char *)"GPIO-LED");
    LCD_ShowString(60,40,RED,GRAY,(char *)"PC not connected");
    LCD_aotu(2,80,236,120,0);
    LCD_ShowString(6,92,BLACK,GRAY,(char *)"light:");
    uart_init(UART_User, 115200);
    uart_init(UART_Debug, 115200);
    flash_init();
    systick_init(10);      //设置systick为10ms中断
    //（1.6）使能模块中断
    uart_enable_re_int(UART_User);
    //（1.7）【不变】开总中断
    ENABLE_INTERRUPTS;

    //（1）======启动部分（结尾）==========================================
    
    //（2）======主循环部分（开头）=========================================
    for(;;)     //for(;;)（开头）
    {
        //（2.1）主循环次数变量+1
        mMainLoopCount++;
        //（2.2）未达到主循环次数设定值，继续循环
        if (mMainLoopCount<=0x1fffff)  continue;
        //（2.3）达到主循环次数设定值，执行下列语句，进行灯的亮暗处理
        //（2.3.1）清除循环次数变量
        mMainLoopCount=0; 
        if(gchflag==1){
        	LCD_ShowString(60,40,BLACK,GRAY, (char *)"                 ");
       		if(gcRecvBuf[0]==8&&strncmp((char *)(gcRecvBuf+1),"red",3) == 0)
				{
					gpio_set(LIGHT_RED,LIGHT_ON);   
					gpio_set(LIGHT_BLUE,LIGHT_OFF);
					gpio_set(LIGHT_GREEN,LIGHT_OFF);
					LCD_ShowString(70,92,BLACK,GRAY,(char *)"          ");
        			LCD_ShowString(70,92,RED,GRAY,(char *)"red ");
        			for (i=30;i>2;i=i-2)LCD_DrawCircle(120,205,i,RED);
					uart_send_string(UART_User,"红灯:亮\r\n");
					gchflag=0;
				}
				if(gcRecvBuf[0]==9&&strncmp((char *)(gcRecvBuf+1),"blue",4) == 0)
				{
					gpio_set(LIGHT_BLUE,LIGHT_ON);  
					gpio_set(LIGHT_RED,LIGHT_OFF);
					gpio_set(LIGHT_GREEN,LIGHT_OFF);
					LCD_ShowString(70,92,BLACK,GRAY,(char *)"          ");
        			LCD_ShowString(70,92,BLUE,GRAY,(char *)"blue");
        			for (i=30;i>2;i=i-2)LCD_DrawCircle(120,205,i,BLUE);
					uart_send_string(UART_User,"蓝灯:亮\r\n");
					gchflag=0;
				}
				if(gcRecvBuf[0]==10&&strncmp((char *)(gcRecvBuf+1),"green",5) == 0)
				{
					//设置绿灯“亮”,蓝灯红灯：“暗”
					gpio_set(LIGHT_GREEN,LIGHT_ON); 
					gpio_set(LIGHT_RED,LIGHT_OFF);
					gpio_set(LIGHT_BLUE,LIGHT_OFF);
					LCD_ShowString(70,92,BLACK,GRAY,(char *)"          ");
        			LCD_ShowString(70,92,GREEN,GRAY,(char *)"green");
        			for (i=30;i>2;i=i-2)LCD_DrawCircle(120,205,i,GREEN);
					uart_send_string(UART_User,"绿灯:亮\r\n");
					gchflag=0;
				}
				if(gcRecvBuf[0]==9&&strncmp((char *)(gcRecvBuf+1),"cyan",4) == 0)
				{
					//设置青灯“亮”
					gpio_set(LIGHT_BLUE,LIGHT_ON);   
					gpio_set(LIGHT_GREEN,LIGHT_ON);
					gpio_set(LIGHT_RED,LIGHT_OFF);
					LCD_ShowString(70,92,BLACK,GRAY,(char *)"          ");
        			LCD_ShowString(70,92,CYAN,GRAY,(char *)"cyan");
        			for (i=30;i>2;i=i-2)LCD_DrawCircle(120,205,i,CYAN);
					uart_send_string(UART_User,"青灯（蓝绿合成）:亮\r\n");
					gchflag=0;
				}
				if(gcRecvBuf[0]==11&&strncmp((char *)(gcRecvBuf+1),"violet",6) == 0)
				{
					gpio_set(LIGHT_RED,LIGHT_ON);   
            		gpio_set(LIGHT_BLUE,LIGHT_ON);   
            		gpio_set(LIGHT_GREEN,LIGHT_OFF);
            		LCD_ShowString(70,92,BLACK,GRAY,(char *)"          ");
        			LCD_ShowString(70,92,VIOLET,GRAY,(char *)"violet");
        			for (i=30;i>2;i=i-2)LCD_DrawCircle(120,205,i,VIOLET);
            		uart_send_string(UART_User,"紫灯（红蓝合成）:亮\r\n");
            		gchflag=0;
				}
				if(gcRecvBuf[0]==11&&strncmp((char *)(gcRecvBuf+1),"yellow",6) == 0)
				{
					gpio_set(LIGHT_RED,LIGHT_ON);   
           			gpio_set(LIGHT_GREEN,LIGHT_ON);
           			gpio_set(LIGHT_BLUE,LIGHT_OFF);
           			LCD_ShowString(70,92,BLACK,GRAY,(char *)"          ");
        			LCD_ShowString(70,92,YELLOW,GRAY,(char *)"yellow");
        			for (i=30;i>2;i=i-2)LCD_DrawCircle(120,205,i,YELLOW);
            		uart_send_string(UART_User,"黄灯（红绿合成）:亮\r\n");
            		gchflag=0;
				}
				if(gcRecvBuf[0]==10&&strncmp((char *)(gcRecvBuf+1),"white",5) == 0)
				{
					//设置白灯“亮”
					gpio_set(LIGHT_RED,LIGHT_ON);
            		gpio_set(LIGHT_BLUE,LIGHT_ON);
            		gpio_set(LIGHT_GREEN,LIGHT_ON);
            		LCD_ShowString(70,92,BLACK,GRAY,(char *)"          ");
        			LCD_ShowString(70,92,WHITE,GRAY,(char *)"white");
        			for (i=30;i>2;i=i-2)LCD_DrawCircle(120,205,i,WHITE);
            		uart_send_string(UART_User,"白灯（红蓝绿合成）:亮\r\n");
            		gchflag=0;
				}
				 if(gcRecvBuf[0]==8&&strncmp((char *)(gcRecvBuf+1),"off",3) == 0 )
				{
					//关灯
					gpio_set(LIGHT_RED,LIGHT_OFF);
            		gpio_set(LIGHT_BLUE,LIGHT_OFF);
            		gpio_set(LIGHT_GREEN,LIGHT_OFF);
            		LCD_ShowString(70,92,BLACK,GRAY,(char *)"          ");
        			LCD_ShowString(70,92,BLACK,GRAY,(char *)"light off");
        			for (i=30;i>2;i=i-2)LCD_DrawCircle(120,205,i,GRAY);
            		uart_send_string(UART_User,"关灯\r\n");
            		gchflag=0;
				}	   
       }
        

    }     //for(;;)结尾
    //（2）======主循环部分（结尾）========================================
}

//======以下为主函数调用的子函数存放处=====================================

//====================================================================
/*
知识要素：
（1）main.c是一个模板，该文件所有代码均不涉及具体的硬件和环境，通过调用构件
实现对硬件的干预。
（2）本文件中标有【不变】的地方为系统保留，此类代码与具体项目无关，不宜删除。
（3）本文件中对宏GLOBLE_VAR进行了定义，所以在包含"includes.h"头文件时，会定
义全局变量，在其他文件中包含"includes.h"头文件时，
编译时会自动增加extern
*/



