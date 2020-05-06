#include "led.h"
#include "exti.h" 
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include <stdarg.h>
#include <string.h>
#include "timer.h"

//ALIENTEK Mini STM32¿ª·¢°å·¶Àý´úÂë3
//´®¿ÚÊµÑé   
//¼¼ÊõÖ§³Ö£ºwww.openedv.com
//¹ãÖÝÊÐÐÇÒíµç×Ó¿Æ¼¼ÓÐÏÞ¹«Ë¾

#define CMD_BUFFER_LEN 100
void usart1Printf(char *fmt, ...)
{
    char buffer[CMD_BUFFER_LEN - 1];
    u8 i = 0;
    u8 len;

    va_list arg_ptr; //Define convert parameters variable
    va_start(arg_ptr, fmt); //Init variable
    len = vsnprintf(buffer, CMD_BUFFER_LEN+1, fmt, arg_ptr); //parameters list format to buffer
    
    while ((i < CMD_BUFFER_LEN) && (i < len) && (len > 0))
    {
        USART_SendData(USART1, (u8) buffer[i++]);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    }
    va_end(arg_ptr);
}



void spear_rtt_send_datas(uint8_t* str, uint8_t len)
{
	SEGGER_RTT_printf(0, "rtt-temp====="); 
	//SEGGER_RTT_printf(0, "spear_rtt_send_datas="); 
	while(len--)
	{
		SEGGER_RTT_printf(0, "%02x ",*str); 
		str++;
	}
	SEGGER_RTT_printf(0, "\n"); 
	
}

//0
void spear_uart_send_data(uint8_t ch)
{
	/* ·¢ËÍÒ»¸ö×Ö½ÚÊý¾Ýµ½USART */
	USART_SendData(USART1,ch);
	/* µÈ´ý·¢ËÍÊý¾Ý¼Ä´æÆ÷Îª¿Õ */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	
}
//1
void spear_uart_send_datas(uint8_t* str, uint8_t len)
{
	while(len--)
	{
		//delay_ms(50);  
		//while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 
		USART_SendData(USART1, *str);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); 
		str++;
	}
}

//2
void UartSendString(char* Str)
{
	while(*Str)
	{
		//while(!UART_GetFlagStatus(UART_FLAG_TXFE));
		USART_SendData(USART1, *Str);
		while(!USART_GetFlagStatus(USART1,USART_FLAG_TC));
		Str++;
		//while(SdkEvalComUARTBusy() == SET);//203400
	}
}





void Process_InputData(uint8_t* data_buffer, uint16_t Nb_bytes)
{

//	printf("*********Process_InputData*************\r\n");
//	usart1Printf("data_buffer=%x %d",data_buffer[0],Nb_bytes);
	//USART1_Puts("----\r\n");
	//SEGGER_RTT_printf(0,"----\r\n");
	//spear_uart_send_datas((uint8_t*)"123\r\n",5);
//	usart1Printf("-------\r\n");
	//USART1_Puts("-----\r\n");


	USART_SendData(USART1, *data_buffer);
	

	
	//if(spear_uart_process_data(*data_buffer))//packege start
	{
		////send event to 
		//spear_sched_set_evt(NULL, 0,user_cmd_process_event_handle);
	 
	 //os_timer_create(&TimersUartRcv, "TimersUartRcv", 1, 10, false, user_cmd_process_event_handle);//10ms
	 //os_timer_start(&TimersUartRcv);
	 

	 //user_cmd_process_event_handle(pxTimer);
	 //user_cmd_process_event_handle(& rx_char, 1);
	}

}
void HCHO_Test(uint8_t recv_data)
{
	printf("recv_data=%x\r\n",recv_data);
}

///command struct
typedef struct
{
	//uint8_t type;
	uint8_t opcode;
	
	uint8_t board_addr;
	uint8_t lock_addr;//-------
	uint8_t gu_ding;//---
	
	uint8_t bcc;
}command1_struct;

/////start process the data in

command1_struct m_data;

uint8_t ComputXor(uint8_t *InData, uint16_t Len)
{
	uint8_t Sum = 0;
	uint16_t i;
	for(i = 0; i < Len; i++)
	{
		Sum ^= InData[i];	
	}
	return Sum;
}


void data_parse()
{
	uint8_t bcc_temp;
	uint8_t tx_Buffer[256]={0};        //?????
	uint8_t length = 0;             //??
	uint8_t gpio_level;
	
	uint8_t Uart1_Buffer_T[256]={0};        //?????
	uint8_t Uart1_Rx_T = 0;             //??
	
	SEGGER_RTT_printf(0, "-parse-Uart1_Rx = %d\n",Uart1_Rx);      //RTT´òÓ¡
	Uart1_Rx_T = Uart1_Rx - 8;
	SEGGER_RTT_printf(0, "-Uart1_Rx_T = %d\n",Uart1_Rx_T);      //RTT´òÓ
	memcpy(Uart1_Buffer_T,Uart1_Buffer+4,Uart1_Rx_T);
	if(5==Uart1_Rx_T)
	{
		m_data.opcode = Uart1_Buffer_T[0];
		m_data.board_addr = Uart1_Buffer_T[1];
		m_data.lock_addr = Uart1_Buffer_T[2];//
		m_data.gu_ding = Uart1_Buffer_T[3];//
		m_data.bcc = Uart1_Buffer_T[4];

		bcc_temp = ComputXor(Uart1_Buffer_T,4);
		SEGGER_RTT_printf(0, "bcc_temp = %x\n",bcc_temp);
		if(bcc_temp == m_data.bcc)
		{
			switch(m_data.opcode)
			{
				case 0x8A:
					//----1------
					if(m_data.gu_ding  == 0x11)//process
					{
						switch(m_data.lock_addr)
						{
							case 0x01:
								GPIO_SetBits(GPIOC,GPIO_Pin_1); 						 //Êä³ö¸ß gong yang:off
								delay_ms(200);  
								GPIO_ResetBits(GPIOC,GPIO_Pin_1); 						 //Êä³ö¸ß  on
								delay_ms(200);  

							
								gpio_level= GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0);
								
								SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
								break;
							
							case 0x02:
								GPIO_SetBits(GPIOC,GPIO_Pin_3); 						 //Êä³ö¸ß gong yang:off
								delay_ms(200);  
								GPIO_ResetBits(GPIOC,GPIO_Pin_3); 						 //Êä³ö¸ß  on
								delay_ms(200);  

							
								gpio_level= GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2);
								
								SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
								break;
							default:
								break;

						}
						
						memcpy(tx_Buffer,"star",4);
						tx_Buffer[4]= m_data.opcode;
						tx_Buffer[5]= m_data.board_addr;
						tx_Buffer[6]= m_data.lock_addr;
						
						if(0x01 == gpio_level)
							tx_Buffer[7]= 0x11;//lock state todo open
						else
							tx_Buffer[7]= 0x00;//lock state todo close
						
						bcc_temp = ComputXor(tx_Buffer+4,4);
						tx_Buffer[8]= bcc_temp;
						memcpy(tx_Buffer+9,"end",3);
						
						tx_Buffer[12]='\0';
						
						spear_uart_send_datas(tx_Buffer,12);
						spear_rtt_send_datas(tx_Buffer,12);

						SEGGER_RTT_printf(0, "ok,m_data.opcode=%02x\n",m_data.opcode);
					}
					else
					{
						SEGGER_RTT_printf(0, "error-2,m_data.opcode=%02x\n",m_data.opcode);
					}
					break;
				case 0x80:
					if(m_data.gu_ding  == 0x33)//process
					{
						if(0x00== m_data.lock_addr)//----4------
						{
							
							
							
							//spear_uart_send_datas
						}
						else//----3------
						{
							switch(m_data.lock_addr)
							{
								case 0x01:
									gpio_level= GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2);
									
									SEGGER_RTT_printf(0, "gpio_level = %x\n",gpio_level);
									break;
								case 0x08:
									 GPIO_ResetBits(GPIOC,GPIO_Pin_2); 						 //Êä³ö¸ß  on
								default:
									break;

							}
							
							memcpy(tx_Buffer,"star",4);
							tx_Buffer[4]= m_data.opcode;
							tx_Buffer[5]= m_data.board_addr;
							tx_Buffer[6]= m_data.lock_addr;
							
							if(0x01 == gpio_level)
								tx_Buffer[7]= 0x11;//lock state todo open
							else
								tx_Buffer[7]= 0x00;//lock state todo close

							
							bcc_temp = ComputXor(tx_Buffer+4,4);
							tx_Buffer[8]= bcc_temp;
							memcpy(tx_Buffer+9,"end",3);
							
							tx_Buffer[12]='\0';
							
							spear_uart_send_datas(tx_Buffer,12);
							spear_rtt_send_datas(tx_Buffer,12);

							SEGGER_RTT_printf(0, "ok,m_data.opcode=%02x\n",m_data.opcode);
						}
						
					}
					else
					{
						SEGGER_RTT_printf(0, "error-2,m_data.opcode=%02x\n",m_data.opcode);
					}
					break;
					

				default:
					break;
			}
			
			SEGGER_RTT_printf(0, "m_data.bcc = %x\n",m_data.bcc);
		}
		else
		{
			SEGGER_RTT_printf(0, "error-1-m_data.bcc = %x\n",m_data.bcc);
		}
		
	}
	else if(3==Uart1_Rx_T)
	{
		m_data.opcode = Uart1_Buffer_T[0];
		m_data.board_addr = Uart1_Buffer_T[1];

		m_data.bcc = Uart1_Buffer_T[2];
		
		bcc_temp = ComputXor(Uart1_Buffer_T,2);
		SEGGER_RTT_printf(0, "bcc_temp = %x\n",bcc_temp);
		if(bcc_temp == m_data.bcc)
		{
			switch(m_data.opcode)
			{
				case 0x90://--------2---------
					SEGGER_RTT_printf(0, "ok,m_data.opcode=%02x\n",m_data.opcode);
					break;
				case 0x91://--------2.1---------
					SEGGER_RTT_printf(0, "ok,m_data.opcode=%02x\n",m_data.opcode);
					break;
				case 0x92://--------2.2---------
					SEGGER_RTT_printf(0, "ok,m_data.opcode=%02x\n",m_data.opcode);
					break;
				case 0x93://--------2.3---------
					SEGGER_RTT_printf(0, "ok,m_data.opcode=%02x\n",m_data.opcode);
					break;
				case 0x70://--------2.4---------
					SEGGER_RTT_printf(0, "ok,m_data.opcode=%02x\n",m_data.opcode);
					break;
				case 0x71://--------2.5---------
					SEGGER_RTT_printf(0, "ok,m_data.opcode=%02x\n",m_data.opcode);
					break;					
				default:
					break;
			}
			
			SEGGER_RTT_printf(0, "m_data.bcc = %x\n",m_data.bcc);
		}
		else
		{
			SEGGER_RTT_printf(0, "error-1-m_data.bcc = %x\n",m_data.bcc);
		}
	
	}

}




 int main(void)
 {	
	u8 t;
	u8 len=3;	
 
	delay_init();	    	 //ÑÓÊ±º¯Êý³õÊ¼»¯	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// ÉèÖÃÖÐ¶ÏÓÅÏÈ¼¶·Ö×é2
	//uart_init(9600,HCHO_Test);	 //´®¿Ú³õÊ¼»¯Îª9600
	SdkEvalComIOConfig(Process_InputData);
	LED_Init();		  	 //³õÊ¼»¯ÓëLEDÁ¬½ÓµÄÓ²¼þ½Ó¿Ú 
	 EXTIX_Init();		//Íâ²¿ÖÐ¶Ï³õÊ¼»¯
	TIM3_Int_Init(99,7199);//10KhzµÄ¼ÆÊýÆµÂÊ£¬¼ÆÊýµ½100Îª10ms  
	TIM3_Set(0);			//¹Ø±Õ¶¨Ê±Æ÷3
//	RS485_RX_EN();
//	//printf("1-len=%d\r\n",len);
//	delay_ms(1300);
//	printf("--------------\r\n");
	SEGGER_RTT_printf(0,"*****************************************************************\n");

	//USART1_Puts("1234567\r\n");
	 
	 
	while(1)
	{
		if((1== packerflag))
		{
			RS485_TX_EN();
			SEGGER_RTT_printf(0, "\n");
			SEGGER_RTT_printf(0, "-main-Uart1_Rx = %d\n",Uart1_Rx);      //RTT´òÓ¡
			SEGGER_RTT_printf(0, "---rcv-datas---"); 
			spear_rtt_send_datas(Uart1_Buffer,Uart1_Rx);
			
			//spear_uart_send_datas(Uart1_Buffer,Uart1_Rx); //debug


			data_parse();
			RS485_RX_EN();
			
			memset(Uart1_Buffer,0,13);//max =4+5+4 =13
			Uart1_Rx   = 0 ;
			packerflag = 0;
			//Uart1_index_flag_end =0;

			
		}

	}	 
}


//		if(USART_RX_STA&0x8000)
//		{					   
//			len=USART_RX_STA&0x3fff;//µÃµ½´Ë´Î½ÓÊÕµ½µÄÊý¾Ý³¤¶È
//			printf("\r\nÄú·¢ËÍµÄÏûÏ¢Îª:\r\n");
//			for(t=0;t<len;t++)
//			{
//				USART1->DR=USART_RX_BUF[t];
//				while((USART1->SR&0X40)==0);//µÈ´ý·¢ËÍ½áÊø
//			}
//			printf("\r\n\r\n");//²åÈë»»ÐÐ
//			USART_RX_STA=0;
//		}else
//		{
//			times++;
//			if(times%5000==0)
//			{
//				printf("\r\nALIENTEK MiniSTM32¿ª·¢°å ´®¿ÚÊµÑé\r\n");
//				printf("ÕýµãÔ­×Ó@ALIENTEK\r\n\r\n\r\n");
//			}
//			if(times%200==0)printf("ÇëÊäÈëÊý¾Ý,ÒÔ»Ø³µ¼ü½áÊø\r\n");  
//			if(times%30==0)LED0=!LED0;//ÉÁË¸LED,ÌáÊ¾ÏµÍ³ÕýÔÚÔËÐÐ.
//			delay_ms(10);   
//		}

