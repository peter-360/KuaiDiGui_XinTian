#include "led.h"
#include "SEGGER_RTT.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK mini�SSTM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PA,PD�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz

// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //LED0-->PA.8 �˿�����
// GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8
// GPIO_SetBits(GPIOA,GPIO_Pin_8);						 //PA.8 �����

// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->PD.2 �˿�����, �������
// GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
// GPIO_SetBits(GPIOD,GPIO_Pin_2); 						 //PD.2 ����� 
	
// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->Pc2 �˿�����, �������
// GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
// GPIO_SetBits(GPIOC,GPIO_Pin_2); 						 //����� 
	
	//LED
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PB5 �˿�����, �������
 GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_ResetBits(GPIOB,GPIO_Pin_5); 						 //����� 

	//rs485 RE
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	    		 //LED1-->Pc2 �˿�����, �������
 GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 RS485_RX_EN();



	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	    		 //LED1-->Pc2 �˿�����, �������
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GPIO_ResetBits(GPIOC,GPIO_Pin_3); 						 //����� 
	
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	    		 //LED1-->Pc2 �˿�����, �������
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GPIO_ResetBits(GPIOC,GPIO_Pin_1); 						 //����� 

//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��������SWDģʽ����-----
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;//Pc3
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
//	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��
	
}











//����TIM4�Ŀ���
//sta:0���ر�;1,����;
void TIM4_Set(u8 sta)
{
	if(sta)
	{
       
		TIM_SetCounter(TIM4,0);//���������
		TIM_Cmd(TIM4, ENABLE);  //ʹ��TIMx	
	}
	else 
		TIM_Cmd(TIM4, DISABLE);//�رն�ʱ��4	   
}


//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM4_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM4��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIMx				
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );	
}

u8 lock_channel=0;
//��ʱ��3�жϷ������
void TIM4_IRQHandler(void)   //TIM4�ж�
{
	SEGGER_RTT_printf(0, "TIM4_IRQHandler\n"); 
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //���TIM4�����жϷ������
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
		//LED1=!LED1;
		//Uart1_Rx =0 ;
		SEGGER_RTT_printf(0, "lock_channel= %d\n",lock_channel);
		if(lock_channel <=25)
		{
			switch(lock_channel)
			{
				case 1://power on
					SEGGER_RTT_printf(0, "lock_channel=%d\n",lock_channel);
					GPIO_SetBits(GPIOC,GPIO_Pin_1); 						 //����� gong yang:off
					delay_ms(20);  
					GPIO_ResetBits(GPIOC,GPIO_Pin_1); 						 //�����  on
					delay_ms(20);  
				
					break;
				case 2://
					SEGGER_RTT_printf(0, "lock_channel=%d\n",lock_channel);
					GPIO_SetBits(GPIOC,GPIO_Pin_3); 						 //����� gong yang:off
					delay_ms(20);  
					GPIO_ResetBits(GPIOC,GPIO_Pin_3); 						 //�����  on
					delay_ms(20);  

					break;
		
				default:
					break;
			}
			TIM4_Set(1);			//TIM 
		}
		else
		{
			TIM4_Set(0);			//TIM 
			lock_channel=0;
			key_mode = 1;
		}
		lock_channel++;
	}
}





