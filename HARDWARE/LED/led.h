#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
	/// ����ȷ����ʱ
static void RS485_delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
} 

//#define LED0 PAout(8)	// PA8
#define LED1 PBout(5)	// PD2	


#define GI_1  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)//��ȡ����1
#define GO_1 PCout(1)	//

#define GI_2  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)//��ȡ����1
#define GO_2 PCout(3)	//

#define GI_4  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)//��ȡ����0
#define GO_4 PAout(3)	//




//bo ma kai guan
#define DSW_1 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10)
#define DSW_2 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11)
#define DSW_3 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12)
#define DSW_4 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)
#define DSW_5 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4)
#define DSW_6 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3)
#define DSW_7 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)
#define DSW_8 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)


/*�����շ�����*/
//�������ģʽ,����Ҫ����ʱ�ȴ�485����������
#define RS485_RX_EN()			RS485_delay(1000); GPIO_ResetBits(GPIOA,GPIO_Pin_11);  RS485_delay(1000);
//���뷢��ģʽ,����Ҫ����ʱ�ȴ�485����������
#define RS485_TX_EN()			RS485_delay(1000); GPIO_SetBits(GPIOA,GPIO_Pin_11);  RS485_delay(1000);

void LED_Init(void);//��ʼ��



void TIM4_Int_Init(u16 arr,u16 psc);
void TIM4_Set(u8 sta);

extern u8 key_mode;

		 				    
#endif
