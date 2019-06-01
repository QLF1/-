#include "can_config.h"



/*can初始化*/
void can_config(void)
{
	CAN_InitTypeDef can_init_structure;
	GPIO_InitTypeDef gpio_init_structure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);
	
	 CAN_DeInit(CAN1);
	
	/*can结构体初始化*/
	can_init_structure.CAN_ABOM = ENABLE;
	can_init_structure.CAN_AWUM = ENABLE;
	can_init_structure.CAN_TTCM = DISABLE;
	can_init_structure.CAN_NART = DISABLE;
	can_init_structure.CAN_RFLM = DISABLE;
	can_init_structure.CAN_TXFP = DISABLE;
	can_init_structure.CAN_Mode = CAN_Mode_Normal;
	can_init_structure.CAN_SJW = CAN_SJW_2tq;
	can_init_structure.CAN_BS1 = CAN_BS1_6tq;
	can_init_structure.CAN_BS2 = CAN_BS1_2tq;
	can_init_structure.CAN_Prescaler = 4000;
	CAN_StructInit(&can_init_structure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA, ENABLE);			//开启时钟和复用时钟
	GPIO_DeInit(GPIOA);
	//GPIO_PinRemapConfig(GPIO_Remap1_CAN1,ENABLE);																		//重映射
	
	/*接收端口PA11*/
	gpio_init_structure.GPIO_Pin = GPIO_Pin_11;
	gpio_init_structure.GPIO_Mode = GPIO_Mode_IPU;			//输入上拉
	gpio_init_structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_init_structure);
	
	/*发送端口PA12*/
	gpio_init_structure.GPIO_Pin = GPIO_Pin_12;
	gpio_init_structure.GPIO_Mode = GPIO_Mode_AF_PP;		//复用推挽输出
	gpio_init_structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_init_structure);
}

/*优先级设置*/
void nvic_config(void)
{
	NVIC_InitTypeDef nvic_init_structure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	nvic_init_structure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	nvic_init_structure.NVIC_IRQChannelPreemptionPriority = 1;
	nvic_init_structure.NVIC_IRQChannelSubPriority = 1;
	nvic_init_structure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&nvic_init_structure);
}

/*过滤器初始化*/
void can_filter_config(void)
{
	CAN_FilterInitTypeDef can_filterstructure;
	
	can_filterstructure.CAN_FilterNumber = 0;											//选择过滤器组
	can_filterstructure.CAN_FilterMode = CAN_FilterMode_IdMask;			//过滤器模式
	can_filterstructure.CAN_FilterScale = CAN_FilterScale_32bit;
	can_filterstructure.CAN_FilterMaskIdHigh = 0xf700;
	can_filterstructure.CAN_FilterIdLow = 0xffff;
	can_filterstructure.CAN_FilterIdHigh = ((u32)0xffff0000<<3)&0x2080000>>16;			//扩展id，标准id201
	can_filterstructure.CAN_FilterIdLow = (u32)0x0<<3|CAN_ID_STD|CAN_RTR_DATA;
	can_filterstructure.CAN_FilterFIFOAssignment = CAN_FilterFIFO0;
	can_filterstructure.CAN_FilterActivation = ENABLE;
	
	CAN_FilterInit(&can_filterstructure);
	
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);			//开启中断
}

