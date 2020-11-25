//===========================================================================
//文件名称：flash.h
//功能概要：Flash底层驱动构件头文件
//版权所有：SD-Arm(sumcu.suda.edu.cn)
//版本更新：20181201-20200221
//芯片类型：KL36
//===========================================================================
#ifndef FLASH_H //防止重复定义（FLASH_H  开头)
#define FLASH_H

#include "mcu.h"
#include "string.h"

//【User程序添加处1】
#define USE_BIOS_FLASH    (1) //1代表函数继承自BIOS，0代表使用自带函数

#if(USE_BIOS_FLASH==0)
//======================================================================
//函数名称：flash_init
//函数返回：无
//参数说明：无
//功能概要：flash初始化
//======================================================================
void flash_init(void);

//======================================================================
//函数名称：flash_erase_sector
//函数返回：函数执行执行状态：0=正常；1=异常。
//参数说明：sect：目标扇区号（范围取决于实际芯片，见mcu.h）
//功能概要：擦除flash存储器的sect扇区
//======================================================================
uint8_t flash_erase(uint16_t sect);

//======================================================================
//函数名称：flash_write
//函数返回：函数执行状态：0=正常；1=异常。
//参数说明：sect：扇区号（范围取决于实际芯片，见mcu.h）
//        offset:写入扇区内部偏移地址（要求为0,4，8,12，......）
//        N：写入字节数目（要求为4，8,12,......）
//        buf：源数据缓冲区首地址
//功能概要：将buf开始的N字节写入到flash存储器的sect扇区的 offset处
//======================================================================
uint8_t flash_write(uint16_t sect,uint16_t offset,uint16_t N,uint8_t *buf);

//======================================================================
//函数名称：flash_read_logic
//函数返回：无
//参数说明：sect：扇区号（范围取决于实际芯片，见mcu.h）
//        offset:扇区内部偏移地址（要求为0,4，8,12，......）
//        N：读字节数目（要求为4，8,12,......）
//        dest：读出数据存放处（传地址，目的是带出所读数据，RAM区）
//功能概要：读取flash存储器的sect扇区的 offset处开始的N字节，到RAM区dest处
//========================================================================
void flash_read_logic(uint8_t *dest,uint16_t sect,uint16_t offset,uint16_t N);

//========================================================================
//函数名称：flash_read_physical
//函数返回：无
//参数说明：addr：目标地址，要求为4的倍数（例如：0x00000004）
//        N：读字节数目（0~1020,要求为4，8,12,......）
//        dest：读出数据存放处（传地址，目的是带出所读数据，RAM区）
//功能概要：读取flash指定地址的内容
//========================================================================
void flash_read_physical(uint8_t *dest,uint32_t addr,uint16_t N);

//========================================================================
//函数名称：flash_protect
//函数返回：无
//参数说明：sect：待保护区域的扇区号入口值，实际保护M~M+3,其中M=0,4,8,......,124
//功能概要：flash保护操作
//说        明：每调用本函数一次，保护4个扇区（M~M+3）
//========================================================================
void flash_protect(uint16_t sect);

//========================================================================
//函数名称：flash_isempty
//函数返回：1=目标区域为空；0=目标区域非空。
//参数说明：所要探测的flash区域初始地址及范围
//功能概要：flash判空操作
//========================================================================
uint8_t flash_isempty(uint16_t sect,uint16_t N);

//========================================================================
//函数名称：flash_unprotect
//函数返回：无
//参数说明：所要解保护的扇区
//功能概要：flash扇区解保护操作
//========================================================================
void flash_unprotect(uint16_t sect);

//========================================================================
//函数名称：flashCtl_isSectorProtected
//函数返回：1=扇区被保护；0=扇区未被保护
//参数说明：所要检测的扇区
//功能概要：判断flash扇区是否被保护
//=========================================================================
uint8_t flash_isSectorProtected(uint16_t sect);

//========================================================================
//函数名称：flash_read_physical
//函数返回：无
//参数说明：   destaddr：目标地址
//        N：写字节数目（0~1020,要求为4，8,12,......）
//        buf：写入数据存放处
//功能概要：读取flash指定地址的内容
//========================================================================
uint8_t flash_write_physical(uint32_t destaddr,uint16_t N,uint8_t *buf);



// Flash控制器宏定义 ，内部使用
#define CCIF    (1<<7)
#define ACCERR  (1<<5)
#define FPVIOL  (1<<4)
#define MGSTAT0 (1<<0)


//Flash命令宏定义，内部使用
#define RD1SEC    0x01   // 读整个扇区
#define PGMCHK    0x02   // 写入检查
#define RDRSRC    0x03   // 读目标数据
#define PGM4      0x06   // 写入长字
#define ERSBLK    0x08   // 擦除整块Flash
#define ERSSCR    0x09   // 擦除Flash扇区
#define RD1ALL    0x40   // 读所有的块
#define RDONCE    0x41   // 只读一次
#define PGMONCE   0x43   // 只写一次
#define ERSALL    0x44   // 擦除所有块
#define VFYKEY    0x45   // 验证后门访问钥匙

//======================================================================
//【User程序添加处2】
#elif (USE_BIOS_FLASH == 1)
#define flash_init       		  ((void (*)(void))(component_fun[23]))
#define flash_erase      		  ((uint8_t (*)(uint16_t sectorNo))(component_fun[24]))
#define flash_write               ((uint8_t (*)(uint16_t sectNo,uint16_t offset,uint16_t cnt,uint8_t buf[]))(component_fun[25]))
#define flash_write_physical      ((uint8_t (*)(uint32_t addr,uint16_t cnt,uint8_t buf[]))(component_fun[26]))
#define flash_read_logic 		  ((void (*)(uint8_t *dest,uint16_t sect,uint16_t offset,uint16_t N))(component_fun[27]))
#define flash_read_physical 	  ((void (*)(uint8_t *dest,uint32_t addr,uint16_t N))(component_fun[28]))
#define flash_protect    		  ((void (*)(uint16_t size))(component_fun[29]))
#define flash_isempty    		  ((uint8_t (*)(uint8_t *buff,uint16_t N))(component_fun[30]))
#define flash_unprotect    		  ((void (*)(uint16_t sect))(component_fun[31]))
#define flash_isSectorProtected   ((uint8_t (*)(uint16_t sect))(component_fun[32]))

#endif

#endif // FLASH_H（FLASH_H  结尾)

//======================================================================
//声明：
//（1）我们开发的源代码，在本中心提供的硬件系统测试通过，真诚奉献给社会，
//    不足之处，欢迎指正。
//（2）对于使用非本中心硬件系统的用户，移植代码时，请仔细根据自己的硬件匹配。
//
//苏州大学嵌入式系统与物联网研究所,0512-65214835  http://sumcu.suda.edu.cn

