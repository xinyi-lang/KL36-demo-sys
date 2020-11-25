//===========================================================================
//文件名称：gpio.h
//功能概要：GPIO底层驱动构件头文件
//版权所有：SD-Arm(sumcu.suda.edu.cn)
//版本更新：20181201-20200221
//芯片类型：KL36
//===========================================================================
#ifndef  GPIO_H       //防止重复定义（GPIO_H  开头)
#define  GPIO_H

#include "mcu.h"     //包含公共要素头文件
#include "string.h"

// 端口号地址偏移量宏定义
#define PTA_NUM    (0<<8)
#define PTB_NUM    (1<<8)
#define PTC_NUM    (2<<8)
#define PTD_NUM    (3<<8)
#define PTE_NUM    (4<<8)
// GPIO引脚方向宏定义
#define GPIO_INPUT  (0)
#define GPIO_OUTPUT (1)
// GPIO引脚中断类型宏定义
#define LOW_LEVEL    (8)      //低电平触发
#define HIGH_LEVEL   (12)     //高电平触发
#define RISING_EDGE  (9)      //上升沿触发
#define FALLING_EDGE (10)     //下降沿触发
#define DOUBLE_EDGE  (11)     //双边沿触发

//【User程序添加处1】
#define USE_BIOS_GPIO    (0) //1代表函数继承自BIOS，0代表使用自带函数

#if (USE_BIOS_GPIO==0)
//=====================================================================
//函数名称：gpio_init
//函数返回：无
//参数说明：port_pin：(端口号)|(引脚号)（如：(PTB_NUM)|(9) 表示为B口9号脚）
//         dir：引脚方向（0=输入，1=输出,可用引脚方向宏定义）
//         state：端口引脚初始状态（0=低电平，1=高电平）
//功能概要：初始化指定端口引脚作为GPIO引脚功能，并定义为输入或输出，若是输出，
//         还指定初始状态是低电平或高电平
//=====================================================================
void gpio_init(uint16_t port_pin, uint8_t dir, uint8_t state);

//=====================================================================
//函数名称：gpio_set
//函数返回：无
//参数说明：port_pin：(端口号)|(引脚号)（如：(PTB_NUM)|(9) 表示为B口9号脚）
//          state：希望设置的端口引脚状态（0=低电平，1=高电平）
//功能概要：当指定端口引脚被定义为GPIO功能且为输出时，本函数设定引脚状态
//=====================================================================
void gpio_set(uint16_t port_pin, uint8_t state);

//=====================================================================
//函数名称：gpio_get
//函数返回：指定端口引脚的状态（1或0）
//参数说明：port_pin：(端口号)|(引脚号)（如：(PTB_NUM)|(9) 表示为B口9号脚）
//功能概要：当指定端口引脚被定义为GPIO功能且为输入时，本函数获取指定引脚状态
//=====================================================================
uint8_t gpio_get(uint16_t port_pin);

//=====================================================================
//函数名称：gpio_reverse
//函数返回：无
//参数说明：port_pin：(端口号)|(引脚号)（如：(PTB_NUM)|(9) 表示为B口9号脚）
//功能概要：当指定端口引脚被定义为GPIO功能且为输出时，本函数反转引脚状态
//=====================================================================
void gpio_reverse(uint16_t port_pin);

//=====================================================================
//函数名称：gpio_pull
//函数返回：无
//参数说明：port_pin：(端口号)|(引脚号)（如：(PTB_NUM)|(9) 表示为B口9号脚）
//       pullselect：下拉/上拉（0=下拉，1=上拉）
//功能概要：当指定端口引脚被定义为GPIO功能且为输入时，本函数设置引脚下拉/上拉
//=====================================================================
void gpio_pull(uint16_t port_pin, uint8_t pullselect);

//=====================================================================
//函数名称：gpio_enable_int
//函数返回：无
//参数说明：port_pin：(端口号)|(引脚号)（如：(PTB_NUM)|(9) 表示为B口9号脚）
//          irqtype：引脚中断类型，由宏定义给出，再次列举如下：
//                  LOW_LEVEL    8      //低电平触发
//                  HIGH_LEVEL   12     //高电平触发
//                  RISING_EDGE  9      //上升沿触发
//                  FALLING_EDGE 10     //下降沿触发
//                  DOUBLE_EDGE  11     //双边沿触发
//功能概要：当指定端口引脚被定义为GPIO功能且为输入时，本函数开启引脚中断，并
//          设置中断触发条件。
//注          意： KL25芯片，只有PORTA、PORTD口具有GPIO类中断功能
//         KW01芯片，只有PORTA、PORTC、PORTD口具有GPIO类中断功能
//         KL36芯片，只有PORTA、PORTC、PORTD口具有GPIO类中断功能
//=====================================================================
void gpio_enable_int(uint16_t port_pin,uint8_t irqtype);

//=====================================================================
//函数名称：gpio_disable_int
//函数返回：无
//参数说明：port_pin：(端口号)|(引脚号)（如：(PTB_NUM)|(9) 表示为B口9号脚）
//功能概要：当指定端口引脚被定义为GPIO功能且为输入时，本函数关闭引脚中断
//注          意： KL25芯片，只有PORTA、PORTD口具有GPIO类中断功能
//         KW01芯片，只有PORTA、PORTC、PORTD口具有GPIO类中断功能
//         KL36芯片，只有PORTA、PORTC、PORTD口具有GPIO类中断功能
//=====================================================================
void gpio_disable_int(uint16_t port_pin);

//=====================================================================
//函数名称：gpio_get_int
//函数返回：引脚GPIO中断标志（1或0）1表示引脚有GPIO中断，0表示引脚没有GPIO中断。
//参数说明：port_pin：(端口号)|(引脚号)（如：(PTB_NUM)|(9) 表示为B口9号脚）
//功能概要：当指定端口引脚被定义为GPIO功能且为输入时,获取中断标志。
//注          意： KL25芯片，只有PORTA、PORTD口具有GPIO类中断功能
//           KW01芯片，只有PORTA、PORTC、PORTD口具有GPIO类中断功能
//           KL36芯片，只有PORTA、PORTC、PORTD口具有GPIO类中断功能
//=====================================================================
uint8_t gpio_get_int(uint16_t port_pin);

//=====================================================================
//函数名称：gpio_clear_int
//函数返回：无
//参数说明：port_pin：(端口号)|(引脚号)（如：(PTB_NUM)|(9) 表示为B口9号脚）
//功能概要：当指定端口引脚被定义为GPIO功能且为输入时,清除中断标志。
//注          意： KL25芯片，只有PORTA、PORTD口具有GPIO类中断功能
//           KW01芯片，只有PORTA、PORTC、PORTD口具有GPIO类中断功能
//           KL36芯片，只有PORTA、PORTC、PORTD口具有GPIO类中断功能
//=====================================================================
void gpio_clear_int(uint16_t port_pin);

//=====================================================================
//函数名称：gpio_clear_allint
//函数返回：无
//参数说明：无
//功能概要：清除所有端口的GPIO中断
//注          意： KL25芯片，只有PORTA、PORTD口具有GPIO类中断功能
//           KW01芯片，只有PORTA、PORTC、PORTD口具有GPIO类中断功能
//           KL36芯片，只有PORTA、PORTC、PORTD口具有GPIO类中断功能
//=====================================================================
void gpio_clear_allint(void);

//=====================================================================
//函数名称：gpio_drive_strength
//函数返回：无
//参数说明：port_pin：(端口号)|(引脚号)（如：(PTB_NUM)|(9) 表示为B口9号脚）
//       control：控制引脚的驱动能力，1=高驱动，0=正常驱动
//          （引脚被配置为数字输出时，引脚控制寄存器的DSE=1：高驱动， DSE=0：正常驱动）
//功能概要：（引脚驱动能力：指引脚输入或输出电流的承受力，一般用mA单位度量
//        ，正常驱动能力5mA,高驱动能力18mA。）当引脚被配置为数字输出时,
//        对引脚的驱动能力进行设置，只有PTB0,PTB1,PTD6,PTD7同时具有高驱
//        动能力和正常驱动能力,这些引脚可用于直接驱动LED或给MOSFET（金氧
//        半场效晶体管）供电，该函数只适用于上述4个引脚。
//=====================================================================
void gpio_drive_strength(uint16_t port_pin, uint8_t control);
//=======================函数定义区结束=====================================
//【User程序添加处2】
#elif (USE_BIOS_GPIO==1)
#define gpio_init  			 ((void (*)(uint16_t port_pin,uint8_t dir,uint8_t state))(component_fun[37]))
#define gpio_set  			 ((void (*)(uint16_t port_pin, uint8_t state))(component_fun[38]))
#define gpio_get  			 ((uint8_t (*)(uint16_t port_pin))(component_fun[39]))
#define gpio_reverse  		 ((void (*)(uint16_t port_pin))(component_fun[40]))
#define gpio_pull  			 ((void (*)(uint16_t port_pin, uint8_t pullselect))(component_fun[41]))
#define gpio_enable_int  	 ((void (*)(uint16_t port_pin,uint8_t irqtype))(component_fun[42]))
#define gpio_disable_int  	 ((void (*)(uint16_t port_pin))(component_fun[43]))
#define gpio_drive_strength  ((void (*)(uint16_t port_pin, uint8_t control))(component_fun[44]))
#endif

#endif  //防止重复定义（GPIO_H 结尾)
