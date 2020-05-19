#include "led.h"
#include "SEGGER_RTT.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK miniSTM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	 //使能PA,PD端口时钟
	
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz

// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //LED0-->PA.8 端口配置
// GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
// GPIO_SetBits(GPIOA,GPIO_Pin_8);						 //PA.8 输出高

// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->PD.2 端口配置, 推挽输出
// GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
// GPIO_SetBits(GPIOD,GPIO_Pin_2); 						 //PD.2 输出高 
	
// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->Pc2 端口配置, 推挽输出
// GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
// GPIO_SetBits(GPIOC,GPIO_Pin_2); 						 //输出高 
	
	//LED
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PB5 端口配置, 推挽输出
 GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_ResetBits(GPIOB,GPIO_Pin_5); 						 //输出高 

	//rs485 RE
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	    		 //LED1-->Pc2 端口配置, 推挽输出
 GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 RS485_RX_EN();



	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	    		 //LED1-->Pc2 端口配置, 推挽输出
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GPIO_ResetBits(GPIOC,GPIO_Pin_3); 						 //输出高 
	
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	    		 //LED1-->Pc2 端口配置, 推挽输出
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GPIO_ResetBits(GPIOC,GPIO_Pin_1); 						 //输出高 

//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试-----
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;//Pc3
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
//	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化
	
}











//设置TIM4的开关
//sta:0，关闭;1,开启;
void TIM4_Set(u8 sta)
{
	if(sta)
	{
       
		TIM_SetCounter(TIM4,0);//计数器清空
		TIM_Cmd(TIM4, ENABLE);  //使能TIMx	
	}
	else 
		TIM_Cmd(TIM4, DISABLE);//关闭定时器4	   
}


//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM4_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //时钟使能
	
	//定时器TIM4初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

	TIM_Cmd(TIM4, ENABLE);  //使能TIMx				
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );	
}

u8 lock_channel=0;
//定时器3中断服务程序
void TIM4_IRQHandler(void)   //TIM4中断
{
	SEGGER_RTT_printf(0, "TIM4_IRQHandler\n"); 
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //检查TIM4更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //清除TIMx更新中断标志 
		//LED1=!LED1;
		//Uart1_Rx =0 ;
		SEGGER_RTT_printf(0, "lock_channel= %d\n",lock_channel);
		if(lock_channel <=25)
		{
			switch(lock_channel)
			{
				case 1://power on
					SEGGER_RTT_printf(0, "lock_channel=%d\n",lock_channel);
					GPIO_SetBits(GPIOC,GPIO_Pin_1); 						 //输出高 gong yang:off
					delay_ms(20);  
					GPIO_ResetBits(GPIOC,GPIO_Pin_1); 						 //输出高  on
					delay_ms(20);  
				
					break;
				case 2://
					SEGGER_RTT_printf(0, "lock_channel=%d\n",lock_channel);
					GPIO_SetBits(GPIOC,GPIO_Pin_3); 						 //输出高 gong yang:off
					delay_ms(20);  
					GPIO_ResetBits(GPIOC,GPIO_Pin_3); 						 //输出高  on
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





