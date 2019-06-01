#include "main.h"

extern pid_typedef x_pid;
extern pid_typedef y_pid;

int main()
{
//	u16 speed;
// 	speed=50;
	SystemInit();
	usart_init();
	write_angle(2,50,700);
	write_angle(1,50,450);
	nvic_init();
	pid_init();
	
	while(1)
	{
		
		//read_servo(1);
	}
}

