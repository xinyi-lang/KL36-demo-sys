//======================================================================
//文件名称：user.h（user头文件）
//制作单位：SD-Arm(sumcu.suda.edu.cn)
//更新记录：20181201-20200221
//概要说明：包含gpio.h文件，实现对具体应用编程，而不是对引脚状态等编程
//======================================================================
#ifndef USER_H   //防止重复定义（USER_H 开始）
#define USER_H

//（1）【不动】文件包含
#include "mcu.h"
#include "gpio.h"
#include "uart.h"
#include "systick.h"
#include "flash.h"
#include "wdog.h"
#include "emuart.h"
#include "printf.h"


//（2）【改动】指示灯端口及引脚定义—根据实际使用的引脚改动

#define  LIGHT_RED      (PTA_NUM|5)   //红灯
#define  LIGHT_GREEN    (PTA_NUM|12)  //绿灯
#define  LIGHT_BLUE     (PTA_NUM|13)  //蓝灯
#define  LIGHT_ON       0   //灯亮（灯状态宏定义，由硬件接法决定）
#define  LIGHT_OFF      1   //灯暗

//（3）【改动】UART可用模块定义
#define UART_Debug  UART_2  //用于程序更新，无法被使用
#define UART_User    UART_0  //用户串口
#define UART_User_Handler    UART0_IRQHandler  //用户串口中断函数

//（4）【改动】SysTick可用模块定义
#define SYSTICK_USER_Handler SysTick_Handler   //用户系统定时器中断函数


//（5）Flash操作宏定义，定义实验所用的测试数据，方便用户修改
//#define Offset 0                         //擦除、写入、（逻辑地址）读取、保护实验所使用扇区内偏移地址
//#define CNT 30                           //擦除、写入、（逻辑地址）读取、保护实验所使用字节数
//#define Content "Welcome to Soochow University!"//擦除、写入、读取（逻辑地址）、保护实验内容
//#define SectorNum   62       //扇区号
//#define Address   (0xF800)  //62扇区起始地址，KL36开发板一个扇区空间大小为2KB，62*2^10= 0x0000F800
//#define CNTvar 0           //（物理地址）读取的字节数

#endif    //防止重复定义（USER_H 结尾）


