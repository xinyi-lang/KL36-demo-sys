
#include "NumToStr.h"

//=====================================================================
//函数名称：NumToStr_int
//函数返回：转换完成后所得到的字符串首地址，以'\0'结尾
//参数说明：x：待转换为字符串的数字；
//         buf：字符串转换完成后存储的位置；
//功能概要：将整数转为字符串
//=====================================================================
uint8_t *NumToStr_int(int32_t x,char *buf)
{
	char *str,*p;
	int temp,sign;
	
	sign= 0;              //标记符号
	str = buf;
     p = str;
	  //负数的话取绝对值并改变标记
	  if (x < 0)
	  {
			 x = 0 - x;
			 sign = 1;
	  }
	  //把数从低位放进字符串
	  do
	  {
			 temp = x % 10;    //取x的最后一位
			 *p = temp + '0';
			 p++;
	  }while ((x /= 10) != 0);
	  //是负数的时候添加‘-’
	  if (sign == 1)
	  {
			*(p++) = '-';
	  }
	  //给字符串的末尾添加 \0
	  *p = '\0';
	  p--;
	  //字符串逆置
	  while(str < p)
	  {
		   *str = *str + *p;
		   *p = *str - *p;
		   *str = *str - *p;
		   str++;
		   p--;
	  }
	  return buf;
}

//================================================================
//函数名称：NumToStr_float
//函数返回：转换完成后所得到的字符串首地址，以'\0'结尾
//参数说明：x：待转换的双精度浮点数；
//          m：转换后保留小数的位数；
//          buf：字符串转换完成后存储的位置；
//功能概要：将浮点数转为字符串
//=================================================================
char *NumToStr_float(float x,int num,char *buf)
{
    int    sumI,sign,temp,count; 
    float  sumF;
    char *p;
    char *pp;
    char *str;
    //
    str = buf;
    p = str;
    //
    sign = 0;
    count = 0;
    //
    if(x < 0)
    {
        sign = 1;
        x = 0 - x;
    }
    sumI = (int)x;    //sumI is the part of int
    sumF = x - sumI;  //sumF is the part of float
    do
    {
        temp = sumI % 10;
        *(str++) = temp + '0';
    }while((sumI = sumI /10) != 0);
    if(sign == 1)
    {
        *(str++) = '-';
    }
    pp = str;
    pp--;
    while(p < pp)
    {
        *p = *p + *pp;
        *pp = *p - *pp;
        *p = *p -*pp;
        p++;
        pp--;
    }
    *(str++) = '.';     //point
    do
    {
        temp = (int)(sumF*10);
        *(str++) = temp + '0';

        if((++count) == num)
            break;

        sumF = sumF*10 - temp;

    }while(!(sumF > -0.000001 && sumF < 0.000001));
    *str = '\0';
    return buf;
}
