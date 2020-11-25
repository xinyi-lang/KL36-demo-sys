//======================================================================
//文件名称：cpu.h（cpu头文件）
//制作单位：SD-ARM(sumcu.suda.edu.cn)
//更新记录：20181201-20200502
//概要说明：包含cpu相关的头文件，这样mcu.h只要包含cpu.h就可以了
//======================================================================
#ifndef   CPU_H    //防止重复定义（开头）
#define  CPU_H

#include "core_cm0plus.h"
#include "core_cmFunc.h"
#include "core_cmInstr.h"

//（1）位操作宏函数（置位、清位、获得寄存器一位的状态）
#define BSET(bit,Register)  ((Register)|= (1<<(bit)))    //置寄存器的一位
#define BCLR(bit,Register)  ((Register) &= ~(1<<(bit)))  //清寄存器的一位
#define BGET(bit,Register)  (((Register) >> (bit)) & 1)  //获得寄存器一位的状态

//（2）不优化类型基本类型别名宏定义
typedef volatile uint8_t       vuint8_t;         // 不优化无符号数
typedef volatile uint16_t     vuint16_t;
typedef volatile uint32_t     vuint32_t;
typedef volatile uint64_t     vuint64_t;
typedef volatile int8_t         vint8_t;         // 不优化有符号数
typedef volatile int16_t       vint16_t;
typedef volatile int32_t       vint32_t;
typedef volatile int64_t       vint64_t;

#endif          //防止重复定义（结尾）