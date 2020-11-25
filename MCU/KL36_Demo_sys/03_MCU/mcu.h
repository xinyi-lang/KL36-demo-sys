//======================================================================
//文件名称：mcu.h（mcu头文件）
//制作单位：SD-Arm(sumcu.suda.edu.cn)
//更新记录：20181201-20200221
//概要说明：包含cpu.h、芯片头文件，这样后级只要包含mcu.h即可
//======================================================================
#ifndef  MCU_H  //防止重复定义（MCU_H 开头）
#define  MCU_H
 //（1）包含芯片头文件
#include "MKL36Z4.h"
#include "system_MKL36Z4.h"

//（2）包含cpu头文件
#include "cpu.h"
void **  component_fun;   //用于存放函数指针数组地址。

//（3）总中断宏定义
#define ENABLE_INTERRUPTS        __enable_irq()             // 开总中断()
#define DISABLE_INTERRUPTS       __disable_irq()            // 关总中断()

//【BIOS工程宏定义修改处】1
#define MCU_IRQ_MAX           32     // 可设置中断最大个数
#define MCU_IRQ_PRIOR_MAX     3      // 可设置最大中断优先级
#define NOP 				     __asm ("NOP")              // 无操作
#define DisableIRQ(irq)          NVIC_DisableIRQ(irq)       // 禁止irq中断
#define EnableIRQ(irq)           NVIC_EnableIRQ(irq)        // 打开irq中断
#define SetPriority(irq, prio)   NVIC_SetPriority(irq, prio)  // 设置irq中断优先级

//（4）MCU基本信息相关宏常数
//【BIOS工程宏定义修改处】2
//                                        "1234567890123456789"
#define MCU_TYPE              "AHL-GEC-KL36-V2.8   "  //MCU型号（19字节）
//                                         "123456789"
#define BIOS_TYPE               "20200222 "       //BIOS版本号（19字节）
#define MCU_SECTORSIZE        1024              //扇区大小（B）
#define MCU_SECTOR_NUM        64                //MCU扇区总数
#define MCU_STACKTOP          0x20001800        //栈顶地址
#define MCU_FLASH_ADDR_START  0x00000000        //MCU的FLASH起始地址
#define MCU_FLASH_ADDR_LENGTH 0x00010000        //MCU的FLASH长度（64KB）
#define MCU_RAM_ADDR_START    0x1FFFF800	    //MCU的RAM起始地址
#define MCU_RAM_ADDR_LENGTH   0x00002000	    //MCU的RAM长度（8KB）


//(5)复位相关
//【BIOS工程宏定义修改处】3
#define IS_PIN_RESET_OCCURED      BGET(RCM_SRS0_PIN_SHIFT,RCM_SRS0)    // 按键复位
#define IS_POWERON_RESET          BGET(RCM_SRS0_POR_SHIFT, RCM_SRS0)   // 上电复位
#define IS_WDOG_RESET_OCCURED     BGET(RCM_SRS0_WDOG_SHIFT, RCM_SRS0)  // 看门狗复位
#define CLEAR_PIN_RESET_FLAG      NOP  //写1清引脚复位标志位

//(6)定义系统使用的时钟频率
//【BIOS工程宏定义修改处】4
#define  MCU_SYSTEM_CLK       SystemCoreClock              // 芯片系统时钟频率(HZ)
#define  MCU_SYSTEM_CLK_KHZ   SystemCoreClock/1000         // 芯片系统时钟频率(KHz)
#define  MCU_BUS_CLK_KHZ      MCU_SYSTEM_CLK_KHZ/2         // 芯片总线时钟频率(KHz)
#define  MCU_SYSTEM_CLK_MS    (SystemCoreClock / 1000)     // 1ms所需时钟频率(HZ)
#define  MCU_SYSTEM_CLK_US    (MCU_SYSTEM_CLK_MS / 1000)   // 1us所需时钟频率(HZ)

#endif  //防止重复定义（MCU_H 结尾）
