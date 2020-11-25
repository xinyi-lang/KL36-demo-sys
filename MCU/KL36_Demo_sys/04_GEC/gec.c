///======================================================================
//文件名称：gec.c文件
//制作单位：SD-Arm(sumcu.suda.edu.cn)
//更新记录：20181201-20200221
//概要说明：供以后驻留函数接口等使用
//                最小软件系统可暂且不用
//======================================================================

#include "gec.h"


//======================================================================
//函数名称：BIOS_API_Init
//函数返回：无
//参数说明：无
//功能概要：（1）BIOS区域驱动构件函数指针初始化
//       （2）User中断向量表涉及BIOS两个中断向量的更改
//======================================================================
void  BIOS_API_Init()
{
#if (GEC_USER_SECTOR_START!=0)
	uint32_t user[MCU_SECTORSIZE/4];
	void ** bios=MCU_FLASH_ADDR_START;
//（1）驱动构件函数指针初始化
     component_fun=(void **)(GEC_COMPONENT_LST_START*MCU_SECTORSIZE);//对于旧版本BIOS需手动赋值
//（2）改变User中断向量表中BIOS_UART中断、BIOS_TIMER中断向量
     flash_read_physical((uint8_t *)user,GEC_USER_SECTOR_START*MCU_SECTORSIZE,MCU_SECTORSIZE);
     if((user[BIOS_UART_UPDATE_IRQn] != (uint32_t)bios[BIOS_UART_UPDATE_IRQn]) //判断USER中串口更新中断和定时器中断是否为BIOS对应中断地址
     	  || (user[BIOS_TIMER_IRQn] != (uint32_t)bios[BIOS_TIMER_IRQn]))    //若都是，则不作操作；否则修改为BIOS对应中断地址
	 {
    	 flash_erase(GEC_USER_SECTOR_START);

		 //改USER中断向量表的BIOS程序写入串口的中断处理程序地址
		 user[BIOS_UART_UPDATE_IRQn]=(uint32_t)bios[BIOS_UART_UPDATE_IRQn];
		 //改USER中断向量表的BIOS程序定时器的中断处理程序地址
		 user[BIOS_TIMER_IRQn]=(uint32_t)bios[BIOS_TIMER_IRQn];

		 flash_write_physical(GEC_USER_SECTOR_START*MCU_SECTORSIZE,MCU_SECTORSIZE,(uint8_t *)user);
	 }
//（3）中断向量表指针重定向
	 SCB->VTOR = (uint32_t)GEC_USER_SECTOR_START*MCU_SECTORSIZE;//指向USER程序FLASH中的中断向量表
	 printf("  【USER提示】：进入USER的主程序...\r\n");
	 wdog_feed();
#endif
}

