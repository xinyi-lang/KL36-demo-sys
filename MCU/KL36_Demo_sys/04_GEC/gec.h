//======================================================================
//文件名称：gec.h（GEC芯片引脚头文件）
//制作单位：苏大arm技术中心(sumcu.suda.edu.cn)
//更新记录：2018.12：1.0，2019.2：A.12
//概要说明：本文件为GEC引脚的功能索引
//======================================================================

#ifndef GEC_H    //防止重复定义（开始）
#define GEC_H

#include "mcu.h"
#include "flash.h"
#include "printf.h"
#include "wdog.h"

void  BIOS_API_Init();



#define GEC_USER_SECTOR_START        (26)    //26=从BIOS启动,0=自启动0
#define GEC_COMPONENT_LST_START  (19)    //函数列表开始扇区号
#define BIOS_UART_UPDATE_IRQn        (30)   //BIOS程序写入串口的中断号
#define BIOS_TIMER_IRQn                     (35)   //BIOS程序定时器的中断号
//===========================================================
//（0）GEC引脚名与内部MCU（KL36）引脚对应关系
//有关名称
#define  GND          0XFFFF    //地
#define  P5V          0XFFFE    //5V电源
#define  P3V3         0XFFFD    //3V3电源
#define  GNSS_ANT     0XFFFC    //北斗/GPS天线引脚名称
#define  MAIN_ANT     0XFFFB    //主通信模组引脚名称
#define  DBG_TXD      0XFFFA    //主通信模组调试串口输出引脚名称
#define  DBG_RXD      0XFFF9    //主通信模组调试串口输入引脚名称
#define  SWD_DIO      0XFFF8    //SWD数据输入引脚名称
#define  SWD_CLK      0XFFF7    //SWD时钟信号引脚名称
//端口号地址偏移量宏定义
#define PTA_NUM     (0<<8)
#define PTB_NUM     (1<<8)
#define PTC_NUM     (2<<8)
#define PTD_NUM     (3<<8)
#define PTE_NUM     (4<<8)
//GEC引脚定义
#define  GEC_1     GND
#define  GEC_2     PTE_NUM|25
#define  GEC_3     PTE_NUM|31
#define  GEC_4     PTE_NUM|30
#define  GEC_5     PTE_NUM|24
#define  GEC_6     PTE_NUM|29
#define  GEC_7     PTE_NUM|23
#define  GEC_8     PTE_NUM|21     //UART_0_RX
#define  GEC_9     GND
#define  GEC_10    PTE_NUM|20     //UART_0_TX

#define  GEC_11    PTE_NUM|19
#define  GEC_12    PTE_NUM|18
#define  GEC_13    PTE_NUM|17     //UART_2_RX
#define  GEC_14    PTE_NUM|16     //UART_2_TX
#define  GEC_15    PTD_NUM|6
#define  GEC_16    PTD_NUM|7
#define  GEC_17    GND
#define  GEC_18    GNSS_ANT
#define  GEC_19    GND
#define  GEC_20    GND

#define  GEC_21    PTD_NUM|5
#define  GEC_22    PTD_NUM|4
#define  GEC_23    PTD_NUM|3
#define  GEC_24    PTD_NUM|2
#define  GEC_25    PTD_NUM|1
#define  GEC_26    GND
#define  GEC_27    PTD_NUM|0
#define  GEC_28    PTC_NUM|7
#define  GEC_29    PTC_NUM|6
#define  GEC_30    PTC_NUM|5

#define  GEC_31    PTC_NUM|4
#define  GEC_32    GND
#define  GEC_33    MAIN_ANT
#define  GEC_34    GND
#define  GEC_35    GND
#define  GEC_36    P3V3
#define  GEC_37    PTC_NUM|3
#define  GEC_38    PTC_NUM|2       //GPIOC_13/I2CB_SDA
#define  GEC_39    PTC_NUM|1      //GPIOC_14/I2CB_SCL
#define  GEC_40    PTC_NUM|0

#define  GEC_41    PTB_NUM|19
#define  GEC_42    PTB_NUM|18
#define  GEC_43    GND
#define  GEC_44    PTB_NUM|17
#define  GEC_45    PTB_NUM|16
#define  GEC_46    PTB_NUM|3      //GPIOB_14/I2CA的SDA引脚
#define  GEC_47    PTB_NUM|2       //GPIOB_15/I2CA的SCL引脚
#define  GEC_48    PTB_NUM|1
#define  GEC_49    PTB_NUM|0
#define  GEC_50    DBG_TXD

#define  GEC_51    GND
#define  GEC_52    GND
#define  GEC_53    DBG_RXD
#define  GEC_54    PTA_NUM|13
#define  GEC_55    PTA_NUM|12
#define  GEC_56    PTA_NUM|5
#define  GEC_57    PTA_NUM|4   //NMI（保留）
#define  GEC_58    SWD_DIO
#define  GEC_59    PTA_NUM|2
#define  GEC_60    GND

#define  GEC_61    PTA_NUM|1
#define  GEC_62    SWD_CLK
#define  GEC_63    GND
#define  GEC_64    P3V3
#define  GEC_65    GND
#define  GEC_66    P5V
#define  GEC_67    P5V
#define  GEC_68    GND

//（1）GPIO引脚
//GPIOA模块（具有中断功能）对应KL36的A口-WYH-190213核对
#define  GPIOA_0    GEC_54   //PTA_NUM|13
#define  GPIOA_1    GEC_55   //PTA_NUM|12
#define  GPIOA_2    GEC_56   //PTA_NUM|5
#define  GPIOA_3    GEC_59   //PTA_NUM|2
#define  GPIOA_4    GEC_61   //PTA_NUM|1
//GPIOB模块（具有中断功能）-对应KL36的C口、D口WYH-190213核对
#define  GPIOB_0    GEC_15   //PTD_NUM|6
#define  GPIOB_1    GEC_16   //PTD_NUM|7

#define  GPIOB_2    GEC_21   //PTD_NUM|5
#define  GPIOB_3    GEC_22   //PTD_NUM|4
#define  GPIOB_4    GEC_23   //PTD_NUM|3
#define  GPIOB_5    GEC_24   //PTD_NUM|2
#define  GPIOB_6    GEC_25   //PTD_NUM|1

#define  GPIOB_7    GEC_27   //PTD_NUM|0
#define  GPIOB_8    GEC_28   //PTC_NUM|7
#define  GPIOB_9    GEC_29   //PTC_NUM|6
#define  GPIOB_10   GEC_30   //PTC_NUM|5
#define  GPIOB_11   GEC_31   //PTC_NUM|4

#define  GPIOB_12   GEC_37   //PTC_NUM|3
#define  GPIOB_13   GEC_38   //PTC_NUM|2
#define  GPIOB_14   GEC_39   //PTC_NUM|1
#define  GPIOB_15   GEC_40   //PTC_NUM|0

//GPIOC模块（无中断功能）-对应KL36的E口、B口WYH-190213核对
#define  GPIOC_0    GEC_2     //PTE_NUM|25
#define  GPIOC_1    GEC_3     //PTE_NUM|31
#define  GPIOC_2    GEC_4
#define  GPIOC_3    GEC_5
#define  GPIOC_4    GEC_6
#define  GPIOC_5    GEC_7
#define  GPIOC_6    GEC_11
#define  GPIOC_7    GEC_12
#define  GPIOC_8    GEC_41
#define  GPIOC_9    GEC_42
#define  GPIOC_10   GEC_44
#define  GPIOC_11   GEC_45
#define  GPIOC_12   GEC_46
#define  GPIOC_13   GEC_47
#define  GPIOC_14   GEC_48
#define  GPIOC_15   GEC_49


//（2）UART引脚
//UART模块定义
#define UART_0  0  //TX引脚： GEC_10；RX引脚： GEC_8
#define UART_1  1  //未引出（请勿使用）
#define UARTC  2  //TX引脚： GEC_14；RX引脚： GEC_13

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


//（4）SPI模块引脚-WYH
//SS引脚： GEC_31（PTC_NUM|4）；SCK引脚： GEC_30（PTC_NUM|5）；
//MOSI引脚： GEC_29（PTC_NUM|6）；MISO引脚： GEC_28（PTC_NUM|7）
#define SPIA  0
//SS引脚： GEC_22（PTD_NUM|4）；SCK引脚： GEC_21（PTD_NUM|5）
//MOSI引脚： GEC_15（PTD_NUM|6）；MISO引脚： GEC_16(PTD_NUM|7)
#define SPIB  1

//（5）I2C模块引脚-WYH
//I2C模块定义
#define I2CA  0   //SDA引脚：GEC_46（PTB_NUM|3）；SCL引脚： GEC_47（PTB_NUM|2）
#define I2CB  1   //SDA引脚：GEC_38（PTC_NUM|2）；SCL引脚： GEC_39（PTC_NUM|1）

//TPM0用作PWM、INCAP、OUTCMP
//（6）脉宽调制PWM引脚-WYH
#define  PWM_PIN0  GEC_39  //GEC_39（PTC_NUM|1）
#define  PWM_PIN1  GEC_38  //GEC_38（PTC_NUM|2）
#define  PWM_PIN2  GEC_37  //GEC_37（PTC_NUM|3）
#define  PWM_PIN3  GEC_23  //GEC_23（PTD_NUM|3）
#define  PWM_PIN4  GEC_22  //GEC_22（PTD_NUM|4）
#define  PWM_PIN5  GEC_21  //GEC_21（PTD_NUM|5）
//（7）输入捕捉INCAP引脚-WYH
#define  INCAP_PIN0  GEC_39  //GEC_39（PTC_NUM|1）
#define  INCAP_PIN1  GEC_38  //GEC_38（PTC_NUM|2）
#define  INCAP_PIN2  GEC_37  //GEC_37（PTC_NUM|3）
#define  INCAP_PIN3  GEC_23  //GEC_23（PTD_NUM|3）
#define  INCAP_PIN4  GEC_22  //GEC_22（PTD_NUM|4）
#define  INCAP_PIN5  GEC_21  //GEC_21（PTD_NUM|5）
//（8）输出比较OUTCMP引脚-WYH
#define  OUTCMP_PIN0  GEC_39  //GEC_39（PTC_NUM|1）
#define  OUTCMP_PIN1  GEC_38  //GEC_38（PTC_NUM|2）
#define  OUTCMP_PIN2  GEC_37  //GEC_37（PTC_NUM|3）
#define  OUTCMP_PIN3  GEC_23  //GEC_23（PTD_NUM|3）
#define  OUTCMP_PIN4  GEC_22  //GEC_22（PTD_NUM|4）
#define  OUTCMP_PIN5  GEC_21  //GEC_21（PTD_NUM|5）

//（9）TSI通道定义与引脚说明
#define TSI_PIN0   13   //所在引脚：GEC_40（PTC_NUM|0）
#define TSI_PIN1   12   //所在引脚：GEC_41（PTB_NUM|19）
#define TSI_PIN2   11   //所在引脚：GEC_42（PTB_NUM|18）
#define TSI_PIN3   10   //所在引脚：GEC_44（PTB_NUM|17）
#define TSI_PIN4    9   //所在引脚：GEC_45（PTB_NUM|16）
#define TSI_PIN5    8   //所在引脚：GEC_46（PTB_NUM|3）
#define TSI_PIN6    7   //所在引脚：GEC_47（PTB_NUM|2）
#define TSI_PIN7    6   //所在引脚：GEC_48（PTB_NUM|1）
#define TSI_PIN8    0   //所在引脚：GEC_49（PTB_NUM|0）
#define TSI_PIN9    3   //所在引脚：GEC_59（PTA_NUM|2）
#define TSI_PIN10   2   //所在引脚：GEC_61（PTA_NUM|1）

//不需硬件对应的模块
//（10）定时器定义
//timer
#define TIMERA  0   //LPTMR
//TPM
#define TIMERB  1   //TPM1


//（11）DMA通道定义
#define DMA_CH0  0  //通道0  对应UART_0
#define DMA_CH1  1  //通道1  对应UART_0
#define DMA_CH2  2  //通道2  对应UART_0
#define DMA_CH3  3  //通道3  对应UART_0


#endif  //防止重复定义（结尾）

