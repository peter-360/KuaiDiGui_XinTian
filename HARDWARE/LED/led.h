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
