#include "main.h"

//������ʱ����
void delay(u32 time)
{
	while(time--);
}

//������ʼ�� 
void key_init(void)
{
	GPIO_InitTypeDef gpio_init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	gpio_init.GPIO_Pin=GPIO_Pin_10;
	gpio_init.GPIO_Mode=GPIO_Mode_IPU;
	gpio_init.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&gpio_init);
}

u8 key_push(void)
{
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)==0)
	{
		delay(50000);
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)==0)
		{
			return 1; 
		}
		return 0;
	}
	return 0;
}
//���ݰ�������ѡ��ģʽ
void select_mode(u8 keytime)
{
	
}

