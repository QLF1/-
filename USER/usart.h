#include "stm32f10x.h"
#define DataLen 5
#define Header '!'
#define ID1 1
#define ID2 2

void usart_init(void);
void nvic_init(void);
void usart1_senddata(u8 buf[],u8 len);

