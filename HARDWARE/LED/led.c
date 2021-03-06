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
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC\
												|RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE);	 //使能PA,PD端口时钟
	

// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //LED0-->PA.8 端口配置
// GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
// GPIO_SetBits(GPIOA,GPIO_Pin_8);						 //PA.8 输出高

// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->PD.2 端口配置, 推挽输出
// GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
// GPIO_SetBits(GPIOD,GPIO_Pin_2); 						 //PD.2 输出高 
	
// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->Pc2 端口配置, 推挽输出
// GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
// GPIO_SetBits(GPIOC,GPIO_Pin_2); 						 //输出高 
	
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	//a13 a14 a15    b3 b4
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
	//LED
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PB5 端口配置, 推挽输出
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GPIO_ResetBits(GPIOB,GPIO_Pin_5); 						 //输出高 

	//rs485 RE
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	    		 //LED1-->Pc2 端口配置, 推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	RS485_RX_EN();
	
	//LED2_LOCK
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	    		 //LED1-->PB5 端口配置, 推挽输出
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GPIO_ResetBits(GPIOB,GPIO_Pin_3); 						 //输出高 


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	    		 //LED1-->PB5 端口配置, 推挽输出
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GPIO_ResetBits(GPIOB,GPIO_Pin_7); 						 //输出高 


//	//i group1
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
// 	GPIO_Init(GPIOC, &GPIO_InitStructure);//
//	//i group2
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;//
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
// 	GPIO_Init(GPIOC, &GPIO_InitStructure);//

// ...
	
	
	//o group1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_1=0; 						 //输出高 
	
	//o group2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_2=0;	 						 //输出高 

	//o group3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_3=0;	 						 //输出高 
	//o group4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_4=0;	 						 //输出高 
	//o group5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_5=0;	 						 //输出高 
	//o group6
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_6=0;	 						 //输出高 
	//o group7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_7=0;	 						 //输出高 	
	//o group8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_8=0;	 						 //输出高 	
	//o group9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_9=0;	 						 //输出高 
	//o group10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_10=0;	 						 //输出高 
	//o group11
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_11=0;	 						 //输出高 
	//o group12
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_12=0;	 						 //输出高 
	//o group13
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_13=0;	 						 //输出高 
	//o group14
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_14=0;	 						 //输出高 
	//o group15
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_15=0;	 						 //输出高 
	//o group16
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_16=0;	 						 //输出高 
	//o group17
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_17=0;	 						 //输出高 

	//o group18
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_18=0;	 						 //输出高 

	//o group19
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_19=0;	 						 //输出高 

	//o group20
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_20=0;	 						 //输出高 

	//o group21
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_21=0;	 						 //输出高 

	//o group22
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_22=0;	 						 //输出高 

	//o group23
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_23=0;	 						 //输出高 

	//o group24
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	    		 //端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	GO_24=0;	 						 //输出高 




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
u8 lock_channel_mode2=0;
//定时器3中断服务程序
void TIM4_IRQHandler(void)   //TIM4中断
{
	uint8_t gpio_level;
	SEGGER_RTT_printf(0, "TIM4_IRQHandler\n"); 
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //检查TIM4更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //清除TIMx更新中断标志 
		//LED1=!LED1;
		//Uart1_Rx =0 ;
		
		if(3== key_mode)
		{
			SEGGER_RTT_printf(0, "mode3-lock_channel= %d\n",lock_channel);
			if(lock_channel <=25)
			{
				switch(lock_channel)
				{
					SEGGER_RTT_printf(0, "lock_channel=%d\n",lock_channel);
					case 1://power on
						GO_1=1; 					//open
						LED2_CTL = 1;
						delay_ms(100);  
						GO_1=0;						//close
						
						
					
						break;
					case 2://
						GO_2=1;							 //open
						LED2_CTL = 1;
						delay_ms(100);  
						GO_2=0;	 						 //close
						
					
						break;
			
		
					case 3:
						GO_3=1;							 //open
						LED2_CTL = 1;
						delay_ms(100);  
						GO_3=0;	 						 //close
						

						break;
					case 4:
						GO_4=1;							 //open
						LED2_CTL = 1;
						delay_ms(100);  
						GO_4=0;	 						 //close
						


						break;
					case 5:
						GO_5=1;							 //open
						LED2_CTL = 1;
						delay_ms(100);  
						GO_5=0;	 						 //close
						

						break;
					case 6:
						GO_6=1;							 //open
						LED2_CTL = 1;
						delay_ms(100);  
						GO_6=0;	 						 //close
						

						break;
					case 7:
						GO_7=1;							 //open
						LED2_CTL = 1;
						delay_ms(100);  
						GO_7=0;	 						 //close
						


						break;
					case 8:
						GO_8=1;							 //open
						LED2_CTL = 1;
						delay_ms(100);  
						GO_8=0;	 						 //close
						

						break;
					case 9:
						GO_9=1;							 //open
						LED2_CTL = 1;
						delay_ms(100);  
						GO_9=0;	 						 //close
						

						break;
					case 10:
						GO_10=1;							 //open
						LED2_CTL = 1;
						delay_ms(100);  
						GO_10=0;	 						 //close
						


						break;
					case 11:
						GO_11=1;							 //open
						LED2_CTL = 1;
						delay_ms(100);  
						GO_11=0;	 						 //close
						

						break;
					case 12:
						GO_12=1;							 //open
						LED2_CTL = 1;
						delay_ms(100);  
						GO_12=0;	 						 //close
						
					
						break;
					case 13:
						GO_13=1;							 //open
						LED2_CTL = 1;
						delay_ms(100);  
						GO_13=0;	 						 //close
						

						break;
					case 14:
						GO_14=1;							 //open
						LED2_CTL = 1;
						delay_ms(100);  
						GO_14=0;	 						 //close
						

						break;
					case 15:
						GO_15=1;							 //open
						LED2_CTL = 1;
						delay_ms(100);  
						GO_15=0;	 						 //close
						

						break;
					case 16:
						GO_16=1;							 //open
						LED2_CTL = 1;
						delay_ms(100);  
						GO_16=0;	 						 //close
						

						break;
					case 17:
						GO_17=1;							 //open
						LED2_CTL = 1;
						delay_ms(100);  
						GO_17=0;	 						 //close
						

						break;
					case 18:
						GO_18=1;							 //open
						LED2_CTL = 1;
						delay_ms(100);  
						GO_18=0;	 						 //close
						

						break;
					case 19:
						GO_19=1;							 //open
						LED2_CTL = 1;
						delay_ms(100);  
						GO_19=0;	 						 //close
						
					
						break;
					case 20:
						GO_20=1;							 //open
						LED2_CTL = 1;
						delay_ms(100);  
						GO_20=0;	 						 //close
						

						break;
					case 21:
						GO_21=1;							 //open
						LED2_CTL = 1;
						delay_ms(100);  
						GO_21=0;	 						 //close
						

						break;
					case 22:
						GO_22=1;							 //open
						LED2_CTL = 1;
						delay_ms(100);  
						GO_22=0;	 						 //close
						

						break;
					case 23:
						GO_23=1;							 //open
						LED2_CTL = 1;
						delay_ms(100);  
						GO_23=0;	 						 //close
						

						break;
					case 24:
						GO_24=1;							 //open
						LED2_CTL = 1;
						delay_ms(100);  
						GO_24=0;	 						 //close
						

						break;
					
					
					default:
						break;
				}
				LED2_CTL = 0;
				lock_all_off();
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
		
		
		if(2== key_mode)
		{
			SEGGER_RTT_printf(0, "mode3-lock_channel_mode2= %d\n",lock_channel_mode2);
			if(lock_channel_mode2 <=25)
			{
				//SEGGER_RTT_printf(0, "lock_channel_mode2=%d\n",lock_channel_mode2);
				switch(lock_channel_mode2)
				{
					case 1://power on

						gpio_level= GI_1;
						SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
						if(0== gpio_level)
						{
							GO_1=1;	 						 //输出高 gong yang:off
							delay_ms(30);  
							GO_1=0; 						 //输出高  on
						}
					
						break;
					case 2://
						gpio_level= GI_2;
						SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
						if(0== gpio_level)
						{
							GO_2=1;							 //输出高 gong yang:off
							delay_ms(30);  
							GO_2=0;	 						 //输出高  on
						}							
						break;
						
					case 3://
						gpio_level= GI_3;
						SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
						if(0== gpio_level)
						{
							GO_3=1;							 //输出高 gong yang:off
							delay_ms(30);  
							GO_3=0;	 						 //输出高  on
						}							
						break;
						
					case 4://
						gpio_level= GI_4;
						SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
						if(0== gpio_level)
						{
							GO_4=1;							 //输出高 gong yang:off
							delay_ms(30);  
							GO_4=0;	 						 //输出高  on
						}							
						break;
						
					case 5://
						gpio_level= GI_5;
						SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
						if(0== gpio_level)
						{
							GO_5=1;							 //输出高 gong yang:off
							delay_ms(30);  
							GO_5=0;	 						 //输出高  on
						}							
						break;
						
					case 6://
						gpio_level= GI_6;
						SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
						if(0== gpio_level)
						{
							GO_6=1;							 //输出高 gong yang:off
							delay_ms(30);  
							GO_6=0;	 						 //输出高  on
						}							
						break;	
						
					case 7://
						gpio_level= GI_7;
						SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
						if(0== gpio_level)
						{
							GO_7=1;							 //输出高 gong yang:off
							delay_ms(30);  
							GO_7=0;	 						 //输出高  on
						}							
						break;
						
					case 8://
						gpio_level= GI_8;
						SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
						if(0== gpio_level)
						{
							GO_8=1;							 //输出高 gong yang:off
							delay_ms(30);  
							GO_8=0;	 						 //输出高  on
						}							
						break;
						
					case 9://
						gpio_level= GI_9;
						SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
						if(0== gpio_level)
						{
							GO_9=1;							 //输出高 gong yang:off
							delay_ms(30);  
							GO_9=0;	 						 //输出高  on
						}							
						break;	
						
					case 10://
						gpio_level= GI_10;
						SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
						if(0== gpio_level)
						{
							GO_10=1;							 //输出高 gong yang:off
							delay_ms(30);  
							GO_10=0;	 						 //输出高  on
						}							
						break;			
						
					case 11://power on

						gpio_level= GI_11;
						SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
						if(0== gpio_level)
						{
							GO_11=1;	 						 //输出高 gong yang:off
							delay_ms(30);  
							GO_11=0; 						 //输出高  on
						}
					
						break;
					case 12://
						gpio_level= GI_12;
						SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
						if(0== gpio_level)
						{
							GO_12=1;							 //输出高 gong yang:off
							delay_ms(30);  
							GO_12=0;	 						 //输出高  on
						}							
						break;
						
					case 13://
						gpio_level= GI_13;
						SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
						if(0== gpio_level)
						{
							GO_13=1;							 //输出高 gong yang:off
							delay_ms(30);  
							GO_13=0;	 						 //输出高  on
						}							
						break;
						
					case 14://
						gpio_level= GI_14;
						SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
						if(0== gpio_level)
						{
							GO_14=1;							 //输出高 gong yang:off
							delay_ms(30);  
							GO_14=0;	 						 //输出高  on
						}							
						break;
						
					case 15://
						gpio_level= GI_15;
						SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
						if(0== gpio_level)
						{
							GO_15=1;							 //输出高 gong yang:off
							delay_ms(30);  
							GO_15=0;	 						 //输出高  on
						}							
						break;
						
					case 16://
						gpio_level= GI_16;
						SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
						if(0== gpio_level)
						{
							GO_16=1;							 //输出高 gong yang:off
							delay_ms(30);  
							GO_16=0;	 						 //输出高  on
						}							
						break;	
						
					case 17://
						gpio_level= GI_17;
						SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
						if(0== gpio_level)
						{
							GO_17=1;							 //输出高 gong yang:off
							delay_ms(30);  
							GO_17=0;	 						 //输出高  on
						}							
						break;
						
					case 18://
						gpio_level= GI_18;
						SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
						if(0== gpio_level)
						{
							GO_18=1;							 //输出高 gong yang:off
							delay_ms(30);  
							GO_18=0;	 						 //输出高  on
						}							
						break;
						
					case 19://
						gpio_level= GI_19;
						SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
						if(0== gpio_level)
						{
							GO_19=1;							 //输出高 gong yang:off
							delay_ms(30);  
							GO_19=0;	 						 //输出高  on
						}							
						break;	
						
					case 20://
						gpio_level= GI_20;
						SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
						if(0== gpio_level)
						{
							GO_20=1;							 //输出高 gong yang:off
							delay_ms(30);  
							GO_20=0;	 						 //输出高  on
						}							
						break;

						
					case 21://power on

						gpio_level= GI_21;
						SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
						if(0== gpio_level)
						{
							GO_21=1;	 						 //输出高 gong yang:off
							delay_ms(30);  
							GO_21=0; 						 //输出高  on
						}
					
						break;
					case 22://
						gpio_level= GI_22;
						SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
						if(0== gpio_level)
						{
							GO_22=1;							 //输出高 gong yang:off
							delay_ms(30);  
							GO_22=0;	 						 //输出高  on
						}							
						break;
						
					case 23://
						gpio_level= GI_23;
						SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
						if(0== gpio_level)
						{
							GO_23=1;							 //输出高 gong yang:off
							delay_ms(30);  
							GO_23=0;	 						 //输出高  on
						}							
						break;
						
					case 24://
						gpio_level= GI_24;
						SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
						if(0== gpio_level)
						{
							GO_24=1;							 //输出高 gong yang:off
							delay_ms(30);  
							GO_24=0;	 						 //输出高  on
						}							
						break;
						
					default:
						break;

				}
				lock_all_off();
				TIM4_Set(1);			//TIM 
			}
			else
			{
				lock_channel_mode2=0;
			}
			lock_channel_mode2++;
		}
		
		
		if(1== key_mode)
		{
			lock_channel =0;
			lock_channel_mode2 =0;
			TIM4_Set(0);
		}
		
	}
}





