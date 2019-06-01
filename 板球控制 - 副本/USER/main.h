#include "stm32f10x.h"

#include "usart.h"
#include "pid.h"
#include "servo.h"
#include "key.h"
#include "math.h"

typedef struct
{
	float actual;
	float set;
	float error;
	float last_error;
	float next_error;
	float integral;
	float max;
	float min;
	float p;
	float i;
	float d;
	float d_error;
}pid_typedef;

typedef struct
{
	float rol;
	float pitch;
	float rol_set;
	float pitch_set;
}ball_typedef;
float Pid_Cal(pid_typedef* pid,float Actual);

