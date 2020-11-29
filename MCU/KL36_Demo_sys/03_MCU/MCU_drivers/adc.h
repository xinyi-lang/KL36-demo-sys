//=====================================================================
//文件名称：adc.h
//功能概要：ADC底层驱动构件头文件
//制作单位：苏州大学嵌入式系统与物联网研究所(sumcu.suda.edu.cn)
//版    本：2017-04-19  V1.0;
//适用芯片：KL25、KL26、KL36
//=====================================================================

#ifndef _ADC_H           //防止重复定义（ 开头）
#define _ADC_H

#include "mcu.h"   
#include "string.h"

//用于定义硬件滤波次数
#define SAMPLE4   0
#define SAMPLE8   1
#define SAMPLE16  2
#define SAMPLE32  3

//（3）ADC引脚定义-WYH
//通道选择
#define MUXSEL_A     0    //选择端口的A通道
#define MUXSEL_B     1    //选择端口的B通道

//ADC通道定义              通道号|通道组<<8
//单端引脚定义
//ADC_PIN1、ADC_PIN2可以合成一个差分引脚
#define ADC_PIN0  (0|MUXSEL_A<<8)     //所在引脚：GEC_10（PTE_NUM|20），ADC0_DP0/SE0
#define ADC_PIN1  (4|MUXSEL_A<<8)     //所在引脚：GEC_8（PTE_NUM|21）， ADC0_DM0/SE4a
//ADC_PIN3、ADC_PIN4可以合成一个差分引脚
#define ADC_PIN2  (1|MUXSEL_A<<8)     //所在引脚：GEC_45（PTE_NUM|16），ADC0_DP1/SE1
#define ADC_PIN3  (5|MUXSEL_A<<8)     //所在引脚：GEC_44（PTE_NUM|17），ADC0_DM1/SE5a
//ADC_PIN5、ADC_PIN6可以合成一个差分引脚
#define ADC_PIN4  (2|MUXSEL_A<<8)     //所在引脚：GEC_12（PTE_NUM|18），ADC0_DP2/SE2
#define ADC_PIN5  (6|MUXSEL_A<<8)     //所在引脚：GEC_11（PTE_NUM|19），ADC0_DM2/SE6a
//以下只能单端输入
#define ADC_PIN6   (7|MUXSEL_A<<8)    //所在引脚：GEC_7（PTE_NUM|23），ADC0_DM3/SE7a
#define ADC_PIN7   (4|MUXSEL_B<<8)    //所在引脚：GEC_6（PTE_NUM|29），ADC0_SE4b
#define ADC_PIN8   (6|MUXSEL_B<<8)    //所在引脚：GEC_21（PTD_NUM|5），ADC0_SE6b
#define ADC_PIN9  (7|MUXSEL_B<<8)    //所在引脚：GEC_15（PTD_NUM|6），ADC0_SE7b
#define ADC_PIN10  (11|MUXSEL_A<<8)   //所在引脚：GEC_38（PTC_NUM|2），ADC0_SE11
#define ADC_PIN11  (14|MUXSEL_A<<8)   //所在引脚：GEC_40（PTC_NUM|0），ADC0_SE14
#define ADC_PIN12  (15|MUXSEL_A<<8)   //所在引脚：GEC_39（PTC_NUM|1），ADC0_SE15
#define ADC_PIN13  (13|MUXSEL_A<<8)   //所在引脚：GEC_46（PTB_NUM|3），ADC0_SE13
#define ADC_PIN14  (12|MUXSEL_A<<8)   //所在引脚：GEC_47（PTB_NUM|2），ADC0_SE12
#define ADC_PIN15  (9 |MUXSEL_A<<8)   //所在引脚：GEC_48（PTB_NUM|1），ADC0_SE9
#define ADC_PIN16  (8 |MUXSEL_A<<8)   //所在引脚：GEC_49（PTB_NUM|0），ADC0_SE8
#define ADC_PIN17  (26|MUXSEL_A<<8)   //芯片自带温度传感器 引脚未引出

//============================================================================
//函数名称：adc_init
//功能概要：初始化一个AD通道组
//参数说明：A_SENSOR_No：可用模拟量传感器通道，具体可参见user.h文件和gec.h文件
//         diff：采样模式，0为单端，1为差分
//============================================================================
void adc_init(uint16_t A_SENSOR_No,uint8_t diff);

//============================================================================
//函数名称：adc_read
//功能概要：进行一个通道的一次A/D转换
//参数说明：A_SENSOR_No：可用模拟量传感器通道，具体可参见user.h文件和gec.h文件
//============================================================================
uint16_t adc_read(uint16_t A_SENSOR_No);

//============================================================================
//函数名称：TempRegression
//功能概要：将读到的环境温度AD值转换为实际温度
//参数说明：tmpAD：通过adc_read函数得到的AD值
//函数返回：实际温度值
//============================================================================
float TempRegression(uint16_t tmpAD);

//============================================================================
//函数名称：TempTrans
//功能概要：将读到的mcu温度AD值转换为实际温度
//参数说明：mcu_temp_AD：通过adc_read函数得到的AD值
//函数返回：实际温度值
//============================================================================
float TempTrans(uint16_t mcu_temp_AD);

#endif

//===========================================================================
//声明：
//（1）我们开发的源代码，在本中心提供的硬件系统测试通过，真诚奉献给社会，不足之处，
//    欢迎指正。
//（2）对于使用非本中心硬件系统的用户，移植代码时，请仔细根据自己的硬件匹配。
//
//苏州大学嵌入式社区，http://sumcu.suda.edu.cn；0512-65214835


