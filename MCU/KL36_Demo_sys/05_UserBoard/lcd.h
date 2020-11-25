#ifndef __LCD_H
#define __LCD_H

#include "mcu.h"
#include "gpio.h"
#include "spi.h"
#include "NumToStr.h"

/******************************************************
接线方式
VCC=3.3V
GND=GND
PD5=RES
PD4=DC
PD1=CLK
PD2=MOSI
BLK,MISO可以不接
******************************************************/

#define LCD_RS    (PTD_NUM|2)    //LCD复位
#define LCD_DC    (PTD_NUM|1)    //LCD数据/命令
#define LCD_SCK   (PTC_NUM|5)    //LCD时钟
#define LCD_SDI   (PTC_NUM|6)    //LCD主出从入
#define LCD_CS    (PTD_NUM|0)    //模拟SPI的CS

#define LCD_SPI  SPI_0

//定义LCD的尺寸（240*320像素）
#define LCD_W 240    
#define LCD_H 320

//=====================================================================
//函数名称：Lcd_Init。
//函数返回：无
//参数说明：无
//功能概要：LCD初始化
//修改记录：王宜怀，2018年7月23日，利用常数数组，简化LCD_Init编程
//=====================================================================
void LCD_Init(void);    //LCD初始化

//=====================================================================
//函数名称：LCD_Clear
//函数返回：无
//参数说明：background:背景颜色（使用本文件后画笔颜色宏定义）
//功能概要：LCD清屏
//=====================================================================
void LCD_Clear(uint16_t background);    //LCD清屏

//=====================================================================
//函数名称：LCD_DrawPoint
//函数返回：无
//参数说明：x,y:点坐标(240*320),
//       color:颜色（使用本文件后画笔颜色宏定义）
//功能概要：在指定位置画一个点
//=====================================================================
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color);    //画点

//=====================================================================
//函数名称：LCD_DrawPoint_big
//函数返回：无
//参数说明：x,y:点坐标(240*320)
//       color:颜色（使用本文件后画笔颜色宏定义）
//功能概要：在指定位置画一个大点,大点的范围实际是一个以x-1,y-1为左上解，x+1,y+1为右下角的小矩形
//       包含9个点（3*3）的大点。
//=====================================================================
void LCD_DrawPoint_big(uint16_t x,uint16_t y,uint16_t color);    //画一个大点

//=====================================================================
//函数名称：Draw_Circle
//函数返回：无
//参数说明：x,y:中心点坐标(240*320),
//       r:圆的半径,
//       color:颜色（使用本文件后画笔颜色宏定义）
//功能概要：在指定位置画一个指定大小的圆
//=====================================================================
void LCD_DrawCircle(uint16_t x,uint16_t y,uint8_t r,uint16_t color);  //画圆

//=====================================================================
//函数名称：LCD_DrawLine
//函数返回：无
//参数说明：x1,y1:起点坐标(240*320),x2,y2:终点坐标(240*320),
//       color:颜色（使用本文件后画笔颜色宏定义）
//功能概要：在指定两点间画一条指定颜色的直线
//=====================================================================
void LCD_DrawLine(uint16_t x1,uint16_t y1,
	 uint16_t x2, uint16_t y2,uint16_t color);    //画线

//=====================================================================
//函数名称：LCD_DrawRectangle
//函数返回：无
//参数说明：x1,y1:左上角点坐标(240*320),x2,y2:右下角点坐标(240*320),
//       color:颜色（使用本文件后画笔颜色宏定义）
//功能概要：在指定左上角与右下角画一个指定线条颜色的矩形
//=====================================================================
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, 
     uint16_t x2, uint16_t y2,uint16_t color);    //画矩形

//=====================================================================
//函数名称：LCD_DrawSurface
//函数返回：无
//参数说明：x1,y1:起点坐标(240*320),x2,y2:终点坐标(240*320),
//       color:颜色（使用本文件后画笔颜色宏定义）
//功能概要：指定颜色填充矩形区域
//=====================================================================
void LCD_DrawSurface(uint16_t x1,uint16_t y1,
     uint16_t x2,uint16_t y2,uint16_t color);    //填充矩形区域

//函数名称：LCD_ShowCharactor
//函数返回：无
//参数说明：x,y:起点坐标(240*320),index：汉字在字库中的索引,fontcolor:字体颜色,
//       groundbackcolor:背景颜色，p:字库起始地址
//功能概要：在指定位置显示一个汉字(16*16大小),汉字需要自行从字库提取
//=====================================================================
void LCD_ShowCharactor(uint16_t  x,uint16_t y,uint16_t fontcolor,
	 uint16_t groundbackcolor,const char *p);    //显示16*16汉字


//函数名称：LCD_ShowString
//函数返回：无
//参数说明：x,y:起点坐标(240*320),p:字符串起始地址（可以包含中文，但应包含在汉字字模中）
//       color:颜色（使用本文件后画笔颜色宏定义）
//功能概要：在指定位置显示字符串，可指定显示画笔颜色和背景颜色。
//                   中文大小为（16*16）,英文大小为（8*16）
//=====================================================================
void LCD_ShowString(uint16_t  x,uint16_t y,uint16_t fontcolor,
	 uint16_t groundbackcolor,const char *p);

//=====================================================================
//函数名称：LCD_aotu
//函数返回：无
//参数说明：x,y:左上坐标(240*320),x1,y1:右下角坐标(240*320)
//功能概要：在指定位置显示一个凹凸按钮
//=====================================================================
void LCD_aotu(uint16_t x,uint16_t y,uint16_t x1,uint16_t y1,uint8_t s); //凹凸按钮

// ------------------  汉字字模的数据结构定义 ------------------------ //
typedef struct typFNT_GB16                 // 汉字字模数据结构
{
       signed char Index[2];               // 汉字内码索引
       char Msk[32];                              // 点阵码数据
} typFNT_GB16;

//=====================================================================
//struct _HEADCOLOR
//scan: 扫描模式
//Bit7: 0:自左至右扫描，1:自右至左扫描。
//Bit6: 0:自顶至底扫描，1:自底至顶扫描。
//Bit5: 0:字节内象素数据从高位到低位排列，1:字节内象素数据从低位到高位排列。
//Bit4: 0:WORD类型高低位字节顺序与PC相同，1:WORD类型高低位字节顺序与PC相反。
//Bit3~2: 保留。
//Bit1~0: [00]水平扫描，[01]垂直扫描，[10]数据水平,字节垂直，[11]数据垂直,字节水平。
//gray: 灰度值
// 1:单色，2:四灰，4:十六灰，8:256色，12:4096色，16:16位彩色，24:24位彩色，32:32位彩色。
//w: 图像的宽度。
//h: 图像的高度。
//is565: 在4096色模式下为0表示使用[16bits(WORD)]格式，此时图像数据中每个WORD表示一个象素；
//为1表示使用[12bits(连续字节流)]格式，此时连续排列的每12Bits代表一个象素。
//在16位彩色模式下为0表示R G B颜色分量所占用的位数都为5Bits，为1表示R G B颜色分量所占用的位数
//分别为5Bits,6Bits,5Bits。
//在18位彩色模式下为0表示"6Bits in Low Byte"，为1表示"6Bits in High Byte"。
//在24位彩色和32位彩色模式下is565无效。
//rgb: 描述R G B颜色分量的排列顺序，rgb中每2Bits表示一种颜色分量，[00]表示空白，[01]表示
//Red，[10]表示Green，[11]表示Blue。
//=====================================================================
typedef struct _HEADCOLOR
{
   unsigned char scan;
   unsigned char gray;
   unsigned short w;
   unsigned short h;
   unsigned char is565;
   unsigned char rgb;
}HEADCOLOR;


void LCD_WR_DATA8(uint8_t da); //发送数据-8位参数
void Address_set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);

//画笔颜色


#define WHITE       0xFFFF
#define BLACK       0x0000
#define BLUE        0x001F
#define BRED        0XF81F
#define GRED        0XFFE0
#define GBLUE       0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN       0XBC40  //棕色
#define BRRED       0XFC07  //棕红色
#define GRAY        0X8430  //灰色
#define VIOLET      0XF81F  //紫色

//GUI颜色
#define DARKBLUE      0X01CF   //深蓝色
#define LIGHTBLUE     0X7D7C   //浅蓝色
#define GRAYBLUE      0X5458   //灰蓝色
//以上三色为PANEL的颜色

#define LIGHTGREEN    0X841F  //浅绿色
#define LGRAY         0XC618  //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE     0XA651  //浅灰蓝色(中间层颜色)
#define LBBLUE        0X2B12  //浅棕蓝色(选择条目的反色)

//=====================================================================
// ------------------  ASCII字模的数据表 ------------------------
// 码表从0x20~0x7e
//去掉了前32个无法表示的字符
//=====================================================================
const static char  nAsciiDot[] =              // ASCII
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // (空）
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x18,0x3C,0x3C,0x3C,0x18,0x18,  //!（感叹号）
	0x18,0x00,0x18,0x18,0x00,0x00,0x00,0x00,

	0x00,0x66,0x66,0x66,0x24,0x00,0x00,0x00,  //"（双引号）
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x36,0x36,0x7F,0x36,0x36,  //#（井号）
	0x36,0x7F,0x36,0x36,0x00,0x00,0x00,0x00,

	0x18,0x18,0x3E,0x63,0x43,0x03,0x3E,0x60,  //$（美元符）
	0x61,0x63,0x3E,0x18,0x18,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x43,0x63,0x30,0x18,  //%（百分号）
	0x0C,0x06,0x63,0x61,0x00,0x00,0x00,0x00,

	0x00,0x00,0x1C,0x36,0x36,0x1C,0x6E,0x3B,  //&（与）
	0x33,0x33,0x33,0x6E,0x00,0x00,0x00,0x00,

	0x00,0x0C,0x0C,0x0C,0x06,0x00,0x00,0x00,  //'（单引号）
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x30,0x18,0x0C,0x0C,0x0C,0x0C,  //(（左括号）
	0x0C,0x0C,0x18,0x30,0x00,0x00,0x00,0x00,

	0x00,0x00,0x0C,0x18,0x30,0x30,0x30,0x30,  //)（右括号）
	0x30,0x30,0x18,0x0C,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x66,0x3C,0xFF,  //*（星号）
	0x3C,0x66,0x00,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x7E,  //+（加号）
	0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  //,（逗号）
	0x00,0x18,0x18,0x18,0x0C,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,  //-（减号）
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  //.（点）
	0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x40,0x60,0x30,0x18,  ///（左斜杠）
	0x0C,0x06,0x03,0x01,0x00,0x00,0x00,0x00,

	0x00,0x00,0x3E,0x63,0x63,0x73,0x6B,0x6B,  //0（数字0）
	0x67,0x63,0x63,0x3E,0x00,0x00,0x00,0x00,

	0x00,0x00,0x18,0x1C,0x1E,0x18,0x18,0x18,  //1（数字1）
	0x18,0x18,0x18,0x7E,0x00,0x00,0x00,0x00,

	0x00,0x00,0x3E,0x63,0x60,0x30,0x18,0x0C,  //2（数字2）
	0x06,0x03,0x63,0x7F,0x00,0x00,0x00,0x00,

	0x00,0x00,0x3E,0x63,0x60,0x60,0x3C,0x60,  //3（数字3）
	0x60,0x60,0x63,0x3E,0x00,0x00,0x00,0x00,

	0x00,0x00,0x30,0x38,0x3C,0x36,0x33,0x7F,  //4（数字4）
	0x30,0x30,0x30,0x78,0x00,0x00,0x00,0x00,

	0x00,0x00,0x7F,0x03,0x03,0x03,0x3F,0x70,  //5（数字5）
	0x60,0x60,0x63,0x3E,0x00,0x00,0x00,0x00,

	0x00,0x00,0x1C,0x06,0x03,0x03,0x3F,0x63,  //6（数字6）
	0x63,0x63,0x63,0x3E,0x00,0x00,0x00,0x00,

	0x00,0x00,0x7F,0x63,0x60,0x60,0x30,0x18,  //7（数字7）
	0x0C,0x0C,0x0C,0x0C,0x00,0x00,0x00,0x00,

	0x00,0x00,0x3E,0x63,0x63,0x63,0x3E,0x63,  //8（数字8）
	0x63,0x63,0x63,0x3E,0x00,0x00,0x00,0x00,

	0x00,0x00,0x3E,0x63,0x63,0x63,0x7E,0x60,  //9（数字9）
	0x60,0x60,0x30,0x1E,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,  //:（冒号）
	0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,  //;（分号）
	0x00,0x18,0x18,0x0C,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x60,0x30,0x18,0x0C,0x06,  //<（小于号）
	0x0C,0x18,0x30,0x60,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x00,  //=（等于号）
	0x00,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x06,0x0C,0x18,0x30,0x60,  //>（大于号）
	0x30,0x18,0x0C,0x06,0x00,0x00,0x00,0x00,

	0x00,0x00,0x3E,0x63,0x63,0x30,0x18,0x18,  //?（问号）
	0x18,0x00,0x18,0x18,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x3E,0x63,0x63,0x7B,0x7B,  //@（艾特符）
	0x7B,0x3B,0x03,0x3E,0x00,0x00,0x00,0x00,

	0x00,0x00,0x08,0x1C,0x36,0x63,0x63,0x7F,  //A（字母A）
	0x63,0x63,0x63,0x63,0x00,0x00,0x00,0x00,

	0x00,0x00,0x3F,0x66,0x66,0x66,0x3E,0x66,  //B（字母B）
	0x66,0x66,0x66,0x3F,0x00,0x00,0x00,0x00,

	0x00,0x00,0x3C,0x66,0x43,0x03,0x03,0x03,  //C（字母C）
	0x03,0x43,0x66,0x3C,0x00,0x00,0x00,0x00,

	0x00,0x00,0x1F,0x36,0x66,0x66,0x66,0x66,  //D（字母D）
	0x66,0x66,0x36,0x1F,0x00,0x00,0x00,0x00,

	0x00,0x00,0x7F,0x66,0x46,0x16,0x1E,0x16,  //E（字母E）
	0x06,0x46,0x66,0x7F,0x00,0x00,0x00,0x00,

	0x00,0x00,0x7F,0x66,0x46,0x16,0x1E,0x16,  //F（字母F）
	0x06,0x06,0x06,0x0F,0x00,0x00,0x00,0x00,

	0x00,0x00,0x3C,0x66,0x43,0x03,0x03,0x7B,  //G（字母G）
	0x63,0x63,0x66,0x5C,0x00,0x00,0x00,0x00,

	0x00,0x00,0x63,0x63,0x63,0x63,0x7F,0x63,  //H（字母H）
	0x63,0x63,0x63,0x63,0x00,0x00,0x00,0x00,

	0x00,0x00,0x3C,0x18,0x18,0x18,0x18,0x18,  //I（字母I）
	0x18,0x18,0x18,0x3C,0x00,0x00,0x00,0x00,

	0x00,0x00,0x78,0x30,0x30,0x30,0x30,0x30,  //J（字母J）
	0x33,0x33,0x33,0x1E,0x00,0x00,0x00,0x00,

	0x00,0x00,0x67,0x66,0x36,0x36,0x1E,0x1E,  //K（字母K）
	0x36,0x66,0x66,0x67,0x00,0x00,0x00,0x00,

	0x00,0x00,0x0F,0x06,0x06,0x06,0x06,0x06,  //L（字母L）
	0x06,0x46,0x66,0x7F,0x00,0x00,0x00,0x00,

	0x00,0x00,0x63,0x77,0x7F,0x7F,0x6B,0x63,  //M（字母M）
	0x63,0x63,0x63,0x63,0x00,0x00,0x00,0x00,

	0x00,0x00,0x63,0x67,0x6F,0x7F,0x7B,0x73,  //N（字母N）
	0x63,0x63,0x63,0x63,0x00,0x00,0x00,0x00,

	0x00,0x00,0x1C,0x36,0x63,0x63,0x63,0x63,  //O（字母O）
	0x63,0x63,0x36,0x1C,0x00,0x00,0x00,0x00,

	0x00,0x00,0x3F,0x66,0x66,0x66,0x3E,0x06,  //P（字母P）
	0x06,0x06,0x06,0x0F,0x00,0x00,0x00,0x00,

	0x00,0x00,0x3E,0x63,0x63,0x63,0x63,0x63,  //Q（字母Q）
	0x63,0x6B,0x7B,0x3E,0x30,0x70,0x00,0x00,

	0x00,0x00,0x3F,0x66,0x66,0x66,0x3E,0x36,  //R（字母R）
	0x66,0x66,0x66,0x67,0x00,0x00,0x00,0x00,

	0x00,0x00,0x3E,0x63,0x63,0x06,0x1C,0x30,  //S（字母S）
	0x60,0x63,0x63,0x3E,0x00,0x00,0x00,0x00,

	0x00,0x00,0x7E,0x7E,0x5A,0x18,0x18,0x18,  //T（字母T）
	0x18,0x18,0x18,0x3C,0x00,0x00,0x00,0x00,

	0x00,0x00,0x63,0x63,0x63,0x63,0x63,0x63,  //U（字母U）
	0x63,0x63,0x63,0x3E,0x00,0x00,0x00,0x00,

	0x00,0x00,0x63,0x63,0x63,0x63,0x63,0x63,  //V（字母V）
	0x63,0x36,0x1C,0x08,0x00,0x00,0x00,0x00,

	0x00,0x00,0x63,0x63,0x63,0x63,0x63,0x6B,  //W（字母W）
	0x6B,0x7F,0x36,0x36,0x00,0x00,0x00,0x00,

	0x00,0x00,0x63,0x63,0x36,0x36,0x1C,0x1C,  //X（字母X）
	0x36,0x36,0x63,0x63,0x00,0x00,0x00,0x00,

	0x00,0x00,0x66,0x66,0x66,0x66,0x3C,0x18,  //Y（字母Y）
	0x18,0x18,0x18,0x3C,0x00,0x00,0x00,0x00,

	0x00,0x00,0x7F,0x63,0x61,0x30,0x18,0x0C,  //Z（字母Z）
	0x06,0x43,0x63,0x7F,0x00,0x00,0x00,0x00,

	0x00,0x00,0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,  //[（左中括号）
	0x0C,0x0C,0x0C,0x3C,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x01,0x03,0x07,0x0E,0x1C,  //\（右斜杠）
	0x38,0x70,0x60,0x40,0x00,0x00,0x00,0x00,

	0x00,0x00,0x3C,0x30,0x30,0x30,0x30,0x30,  //]（右中括号）
	0x30,0x30,0x30,0x3C,0x00,0x00,0x00,0x00,

	0x08,0x1C,0x36,0x63,0x00,0x00,0x00,0x00,  //^（乘方等符）
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  //_（下划线）
	0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,

	0x0C,0x0C,0x18,0x00,0x00,0x00,0x00,0x00,  //`（点符）
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x1E,0x30,0x3E,  //a（字母a）
	0x33,0x33,0x33,0x6E,0x00,0x00,0x00,0x00,

	0x00,0x00,0x07,0x06,0x06,0x1E,0x36,0x66,  //b（字母b）
	0x66,0x66,0x66,0x3B,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x3E,0x63,0x03,  //c（字母c）
	0x03,0x03,0x63,0x3E,0x00,0x00,0x00,0x00,

	0x00,0x00,0x38,0x30,0x30,0x3C,0x36,0x33,  //d（字母d）
	0x33,0x33,0x33,0x6E,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x3E,0x63,0x7F,  //e（字母e）
	0x03,0x03,0x63,0x3E,0x00,0x00,0x00,0x00,

	0x00,0x00,0x1C,0x36,0x26,0x06,0x0F,0x06,  //f（字母f）
	0x06,0x06,0x06,0x0F,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x6E,0x33,0x33,  //g（字母g）
	0x33,0x33,0x33,0x3E,0x30,0x33,0x1E,0x00,

	0x00,0x00,0x07,0x06,0x06,0x36,0x6E,0x66,  //h（字母h）
	0x66,0x66,0x66,0x67,0x00,0x00,0x00,0x00,

	0x00,0x00,0x18,0x18,0x00,0x1C,0x18,0x18,  //i（字母i）
	0x18,0x18,0x18,0x3C,0x00,0x00,0x00,0x00,

	0x00,0x00,0x60,0x60,0x00,0x70,0x60,0x60,  //j（字母j）
	0x60,0x60,0x60,0x60,0x66,0x66,0x3C,0x00,

	0x00,0x00,0x07,0x06,0x06,0x66,0x36,0x1E,  //k（字母k）
	0x1E,0x36,0x66,0x67,0x00,0x00,0x00,0x00,

	0x00,0x00,0x1C,0x18,0x18,0x18,0x18,0x18,  //l（字母l）
	0x18,0x18,0x18,0x3C,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x37,0x7F,0x6B,  //m（字母m）
	0x6B,0x6B,0x6B,0x6B,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x3B,0x66,0x66,  //n（字母n）
	0x66,0x66,0x66,0x66,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x3E,0x63,0x63,  //o（字母o）
	0x63,0x63,0x63,0x3E,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x3B,0x66,0x66,  //p（字母p）
	0x66,0x66,0x66,0x3E,0x06,0x06,0x0F,0x00,

	0x00,0x00,0x00,0x00,0x00,0x6E,0x33,0x33,  //q（字母q）
	0x33,0x33,0x33,0x3E,0x30,0x30,0x78,0x00,

	0x00,0x00,0x00,0x00,0x00,0x3B,0x6E,0x46,  //r（字母r）
	0x06,0x06,0x06,0x0F,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x3E,0x63,0x06,  //s（字母s）
	0x1C,0x30,0x63,0x3E,0x00,0x00,0x00,0x00,

	0x00,0x00,0x08,0x0C,0x0C,0x3F,0x0C,0x0C,  //t（字母t）
	0x0C,0x0C,0x6C,0x38,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x33,0x33,0x33,  //u（字母u）
	0x33,0x33,0x33,0x6E,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x66,0x66,0x66,  //v（字母v）
	0x66,0x66,0x3C,0x18,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x63,0x63,0x63,  //w（字母w）
	0x6B,0x6B,0x7F,0x36,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x63,0x36,0x1C,  //x（字母x）
	0x1C,0x1C,0x36,0x63,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x00,0x63,0x63,0x63,  //y（字母y）
	0x63,0x63,0x63,0x7E,0x60,0x30,0x1F,0x00,

	0x00,0x00,0x00,0x00,0x00,0x7F,0x33,0x18,  //z（字母z）
	0x0C,0x06,0x63,0x7F,0x00,0x00,0x00,0x00,

	0x00,0x00,0x70,0x18,0x18,0x18,0x0E,0x18,  //{（左大括号）
	0x18,0x18,0x18,0x70,0x00,0x00,0x00,0x00,

	0x00,0x00,0x18,0x18,0x18,0x18,0x00,0x18,  //|（竖线）
	0x18,0x18,0x18,0x18,0x00,0x00,0x00,0x00,

	0x00,0x00,0x0E,0x18,0x18,0x18,0x70,0x18,  //}（右大括号）
	0x18,0x18,0x18,0x0E,0x00,0x00,0x00,0x00,

	0x00,0x00,0x6E,0x3B,0x00,0x00,0x00,0x00,  //~（波浪号）
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

	0x00,0x00,0x00,0x00,0x08,0x1C,0x36,0x63,  //（空格）
	0x63,0x63,0x7F,0x00,0x00,0x00,0x00,0x00,
};

 //=====================================================================
  // 汉字字模表
  // 汉字库: 宋体（16*16） 横向取模右高位,数据排列:从左到右从上到下
  // 汉字表：
  //     金葫芦【】
  //=====================================================================
#define ChineseCharacterLength (sizeof(GB_16)/sizeof(typFNT_GB16))   //记录汉字的个数
  const static typFNT_GB16  GB_16[] =          // 数据表
  {
  "金", 0x80,0x00,0x80,0x00,0x40,0x01,0x20,0x02,
        0x10,0x04,0x08,0x0A,0xF4,0x77,0x83,0x20,
        0x80,0x00,0xF8,0x0F,0x80,0x00,0x88,0x08,
        0x90,0x04,0xA0,0x12,0xFE,0x3F,0x00,0x00,

  "葫", 0x20,0x02,0x20,0x22,0xFF,0x7F,0x20,0x02,
        0x10,0x3E,0x90,0x22,0xFE,0x23,0x10,0x3E,
        0x50,0x22,0xFC,0x22,0x44,0x3E,0x44,0x22,
        0x44,0x22,0x7C,0x22,0x44,0x29,0x80,0x10,

  "芦", 0x10,0x04,0x10,0x24,0xFF,0x7F,0x10,0x04,
        0x80,0x10,0xFC,0x3F,0x04,0x10,0x04,0x10,
        0xFC,0x1F,0x04,0x10,0x04,0x00,0x04,0x00,
        0x04,0x00,0x02,0x00,0x02,0x00,0x01,0x00,
        
  "严", 0xFC,0x3F,0x40,0x02,0x48,0x12,0x50,0x12,
        0x50,0x0A,0x40,0x02,0xF8,0x3F,0x08,0x00,
        0x08,0x00,0x08,0x00,0x08,0x00,0x04,0x00,
        0x04,0x00,0x02,0x00,0x00,0x00,0x00,0x00,

  "信", 0x10,0x01,0x10,0x02,0xE8,0x3F,0x08,0x00,
        0xCC,0x1F,0x0A,0x00,0xC8,0x1F,0x08,0x00,
        0xC8,0x1F,0x48,0x10,0x48,0x10,0x48,0x10,
        0xC8,0x1F,0x48,0x10,0x00,0x00,0x00,0x00,

  "义", 0x40,0x08,0x88,0x08,0x88,0x08,0x10,0x04,
        0x10,0x04,0x20,0x02,0x20,0x02,0x40,0x01,
        0x80,0x00,0x40,0x01,0x20,0x02,0x10,0x04,
        0x08,0x08,0x06,0x30,0x00,0x00,0x00,0x00,

  };


#endif

