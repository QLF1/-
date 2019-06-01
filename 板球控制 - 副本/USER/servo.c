#include "main.h"


//求校验和
u8 checksum(u8 buf[])
{
	uint8_t i;
  uint16_t temp = 0;
  for (i = 2; i < buf[3] + 2; i++) {
    temp += buf[i];
  }
  temp = ~temp;
  i = (uint8_t)temp;
  return i;
}
//设置id
void set_servo_id(u8 old_id,u8 new_id)
{
	u8 buf[7];
	buf[0]=buf[1]=LOBOT_SERVO_FRAME_HEADER;
	buf[2]=old_id;
	buf[3]=4;
	buf[4]=LOBOT_SERVO_ID_WRITE;
	buf[5]=0;
	buf[6]=checksum(buf);
	servo_send(buf,7);
}
//设置转动角度
void write_angle(u8 id,u16 time, u16 position)
{
	u8 buf[10];
	//if (position<0)
		//position=0;
	if(position>1000)
		position=1000;
	buf[0]=buf[1]=LOBOT_SERVO_FRAME_HEADER;
	buf[2]=id;
	buf[3]=7;
	buf[4]=LOBOT_SERVO_MOVE_TIME_WRITE;
	buf[5]=position&0xff;
	buf[6]=position>>8;
	buf[7]=time&0x0f;
	buf[8]=time>>8;
	buf[9]=checksum(buf);
	servo_send(buf,10);
}

//接收舵机反馈数据
u16 rx_buf[7];
void read_servo(u8 id)
{ 
	u16 time=10000;
	u8 tx_buf[7];
	u8 i;
	tx_buf[0]=tx_buf[1]==LOBOT_SERVO_FRAME_HEADER;
	tx_buf[2]=id;
	tx_buf[3]=7;
	tx_buf[4]=LOBOT_SERVO_MOVE_TIME_READ;
	tx_buf[5]=0;
	tx_buf[6]=checksum(tx_buf);
	servo_send(tx_buf,10);
	while(time--);
	for(i=0;i<7;i++)
	{
		rx_buf[i]=USART_ReceiveData(USART1);
	}
	
}
