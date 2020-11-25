//==========================================================================
//文件名称：systick.c
//功能概要：systick 构件源文件
//版权所有：苏州大学嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2017-11-08   V1.0
//==========================================================================

#include "systick.h"

//===========================================================================
//函数名称：systick_init
//函数返回：无
//参数说明：int_ms:中断的时间间隔(1~5000ms)
//功能概要：初始化SysTick模块，设置中断的时间间隔
//简要说明：使用内核时钟，其频率SYSTEM_CLK_KHZ在common.h中宏定义
//===========================================================================
void systick_init( uint8_t int_ms)
{
    SysTick->CTRL = 0;   //设置前先关闭systick。CTRL控制及状态寄存器
    SysTick->VAL  = 0;   //清除计数器。VAL 计数器
    if((int_ms<1)||(int_ms>5592))
    {
       int_ms = 10;
    }
    SysTick->LOAD = MCU_SYSTEM_CLK_KHZ*int_ms/16;
    //设定 SysTick优先级为3(SHPR3寄存器的最高字节=0xC0)
    NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL);
    //设置时钟源,允许中断,使能该模块,开始计数
    SysTick->CTRL |= ( SysTick_CTRL_ENABLE_Msk|SysTick_CTRL_TICKINT_Msk );
}


