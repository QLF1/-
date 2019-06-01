#include "main.h"
/*
	usart1控制舵机
	USART2采用dma接收摄像头数据
*/

u8 dma_rx_buf[9];
u8 dma_tx_buf[9];


void usart_init(void)
{
	GPIO_InitTypeDef gpio_init;
	USART_InitTypeDef usart_init;
	DMA_InitTypeDef DMA_initStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2|RCC_APB1Periph_USART3,ENABLE); //开启时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	//PA 9 Tx
	gpio_init.GPIO_Pin = GPIO_Pin_9;
	gpio_init.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_init);
	
	//PA 10 Rx
	gpio_init.GPIO_Pin = GPIO_Pin_10;
	gpio_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_init);

	//usart1 配置
	usart_init.USART_BaudRate = 115200;
	usart_init.USART_WordLength = USART_WordLength_8b;
	usart_init.USART_StopBits = USART_StopBits_1;
	usart_init.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usart_init.USART_Parity = USART_Parity_No;
	usart_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	USART_Init(USART1,&usart_init);
	USART_Cmd(USART1,ENABLE);
	
	//PA 2 Tx
	gpio_init.GPIO_Pin = GPIO_Pin_2;
	gpio_init.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_init.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&gpio_init);
	
	//PA 3 Rx
	gpio_init.GPIO_Pin = GPIO_Pin_3;
	gpio_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio_init.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&gpio_init);

	//usart2 配置
	usart_init.USART_BaudRate = 115200;
	usart_init.USART_WordLength = USART_WordLength_8b;
	usart_init.USART_StopBits = USART_StopBits_1;
	usart_init.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usart_init.USART_Parity = USART_Parity_No;
	usart_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART2,&usart_init);
	USART_Cmd(USART2,ENABLE);
	
	//USART2dma接收配置
	DMA_initStruct.DMA_BufferSize = 9;
	DMA_initStruct.DMA_DIR =  DMA_DIR_PeripheralSRC;
	DMA_initStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_initStruct.DMA_MemoryBaseAddr = (u32)&dma_rx_buf;						//强制转化
	DMA_initStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_initStruct.DMA_MemoryInc =  DMA_MemoryInc_Enable;
	DMA_initStruct.DMA_Mode =  DMA_Mode_Circular;
	DMA_initStruct.DMA_PeripheralBaseAddr = (u32)&USART2->DR;						//强制转化
	DMA_initStruct.DMA_PeripheralDataSize =  DMA_PeripheralDataSize_Byte;
	DMA_initStruct.DMA_PeripheralInc =  DMA_PeripheralInc_Disable;
	DMA_initStruct.DMA_Priority = DMA_Priority_High;
	DMA_Init(DMA1_Channel6,&DMA_initStruct);
	
	DMA_ITConfig(DMA1_Channel6,DMA_IT_TC,ENABLE);
	DMA_Cmd(DMA1_Channel6,ENABLE);
	USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);
	
}

//中断初始化
void nvic_init(void)
{
	NVIC_InitTypeDef nvic_stucture;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	//dma中断配置
	nvic_stucture.NVIC_IRQChannel = DMA1_Channel6_IRQn;
	nvic_stucture.NVIC_IRQChannelSubPriority = 1;
	nvic_stucture.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_stucture.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_stucture);
}

//usart1发送函数
void usart1_senddata(u8 buf[],u8 len)
{
		while (len--) 
		{
			while ((USART1->SR & 0x40) == 0);
			USART_SendData(USART1,*buf++);
		}
}

extern  ball_typedef ball_status;
extern  pid_typedef x_pid;
extern  pid_typedef x_pid_buff;
extern  pid_typedef y_pid;
extern  pid_typedef y_pid_buff;

extern  float X_Buff_Set1;
extern  float X_Buff_Set2;
extern  float Y_Buff_Set1;
extern  float Y_Buff_Set2;

float test1;
u16 test2;
u16 angle2=700;
u16 angle1=450;
float Y_set;
//usart2DMA接收中断服务函数，接收摄像头数据
void DMA1_Channel6_IRQHandler(void)
{
		float X,X_set;
		float Y;
		if(dma_rx_buf[0]==Header)
		{
			//摄像头数据解码
			if(dma_rx_buf[3]==0x2E)
				ball_status.pitch=(dma_rx_buf[1]-48)*10+(dma_rx_buf[2]-48)+((float)dma_rx_buf[4]-48)/10;
			else
				ball_status.pitch=dma_rx_buf[1]-48+((float)dma_rx_buf[3]-48)/10;
			if(dma_rx_buf[7]==0x2E)
				ball_status.rol=(dma_rx_buf[5]-48)*10+(dma_rx_buf[6]-48)+((float)dma_rx_buf[8]-48)/10;
			else
				ball_status.rol=dma_rx_buf[5]-48+((float)dma_rx_buf[7]-48)/10;
			
			/****************Y轴******************/
			Y_set=MIN(y_pid.set,ball_status.rol,Y_Buff_Set1,Y_Buff_Set2);
			if((Y_set==Y_Buff_Set1)||(Y_set==Y_Buff_Set2))
			{
				y_pid_buff.set=Y_set;
				Y=Pid_Cal(&y_pid_buff,ball_status.rol);
				if(ABS(ball_status.rol,Y_Buff_Set1)<5)
					Y=Pid_Cal(&y_pid,ball_status.rol);
				if(ABS(ball_status.rol,Y_Buff_Set2)<5)
					Y=Pid_Cal(&y_pid,ball_status.rol);
			}
			else
			{
				Y=Pid_Cal(&y_pid,ball_status.rol);
			}
			/*******************X轴******************/
			X_set=MIN(x_pid.set,ball_status.pitch,X_Buff_Set1,X_Buff_Set2);
			if((X_set==X_Buff_Set1)||(X_set==Y_Buff_Set2))
			{
				x_pid_buff.set=X_set;
				X=Pid_Cal(&x_pid_buff,ball_status.pitch);
				if(ABS(ball_status.pitch,X_Buff_Set1)<5)
					X=Pid_Cal(&x_pid,ball_status.pitch);
				if(ABS(ball_status.pitch,X_Buff_Set2)<5)
					X=Pid_Cal(&x_pid,ball_status.pitch);
			}
			else
			{
				X=Pid_Cal(&x_pid,ball_status.pitch);
			}
			
			//发送控制数据
			X = -X + 470;
			Y = Y + 700;
			if(Y>900)
				Y=900;
			if(Y<600)
				Y=600;
			if(X>755)
				X=755;
			if(X<270)
				X=270;
			test1=Y;
			write_angle(ID2,1,(u16)Y);
			write_angle(ID1,1,(u16)X);
			//write_angle(2,50,angle2);
			//write_angle(1,50,angle1);
		}		
	
	DMA_ClearITPendingBit(DMA_IT_TC);
}


void USART1_IRQHandler(void)
{
	if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==SET)
	{
		
	}
	USART_ClearFlag(USART1,USART_FLAG_RXNE);
}
