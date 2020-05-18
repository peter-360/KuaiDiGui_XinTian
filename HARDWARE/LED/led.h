#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
	/// 不精确的延时
static void RS485_delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
} 

//#define LED0 PAout(8)	// PA8
#define LED1 PBout(5)	// PD2	

/*控制收发引脚*/
//进入接收模式,必须要有延时等待485处理完数据
#define RS485_RX_EN()			RS485_delay(1000); GPIO_ResetBits(GPIOA,GPIO_Pin_11);  RS485_delay(1000);
//进入发送模式,必须要有延时等待485处理完数据
#define RS485_TX_EN()			RS485_delay(1000); GPIO_SetBits(GPIOA,GPIO_Pin_11);  RS485_delay(1000);

void LED_Init(void);//初始化



void TIM4_Int_Init(u16 arr,u16 psc);
void TIM4_Set(u8 sta);

		 				    
#endif
