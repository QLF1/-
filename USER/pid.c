#include "main.h"

 ball_typedef ball_status;
 pid_typedef x_pid;
 pid_typedef x_pid_buff;
 pid_typedef y_pid;
 pid_typedef y_pid_buff;
 float X_Buff_Set1=25;
 float X_Buff_Set2=35;
 float Y_Buff_Set1=25;
 float Y_Buff_Set2=35;
 float X_Set=34;
 float Y_Set=34;

void pid_init(void)
{
	x_pid.actual = 0;
	x_pid.set = X_Set;
	x_pid.error = 0;
	x_pid.last_error = 0;
	x_pid.integral = 0;
	x_pid.max=1000;
	x_pid.min=-1000;
	x_pid.p = 8;
	x_pid.i = 0;
	x_pid.d = 80;
	
	y_pid.set = Y_Set;
	y_pid.actual = 0;
	y_pid.error = 0;
	y_pid.last_error = 0;
	y_pid.integral = 0;
	y_pid.max=1000;
	y_pid.min=-1000;
	y_pid.p = 8;
	y_pid.i = 0;
	y_pid.d = 100;
	
	x_pid_buff.set = 0;
	x_pid_buff.actual = 0;
	x_pid_buff.error = 0;
	x_pid_buff.last_error = 0;
	x_pid_buff.integral = 0;
	x_pid_buff.max=1000;
	x_pid_buff.min=-1000;
	x_pid_buff.p = 8;
	x_pid_buff.i = 0;
	x_pid_buff.d = 20;
	
	y_pid_buff.set = 0;
	y_pid_buff.actual = 0;
	y_pid_buff.error = 0;
	y_pid_buff.last_error = 0;
	y_pid_buff.integral = 0;
	y_pid_buff.max=1000;
	y_pid_buff.min=-1000;
	y_pid_buff.p = 7;
	y_pid_buff.i = 0;
	y_pid_buff.d = 30;
	
	
}

//pid»·
float Pid_Cal(pid_typedef* pid,float Actual)
{
	pid->error=Actual-pid->set;
	pid->integral +=pid->error;
	pid->d_error=pid->error-pid->last_error;
	
	if(pid->integral>pid->max)
		pid->integral=pid->max;
	if(pid->integral<pid->min)
		pid->integral=pid->min;
	
	if(	pid->d_error!=0)
	{
		pid->actual = pid->p*pid->error+pid->i*pid->integral+pid->d*(pid->error-pid->last_error);
		pid->last_error=pid->error;
	}
	if((pid->d_error==0)&&(ABS(pid->error,0)<2))
	{
		pid->actual = pid->p*pid->error+pid->i*pid->integral;
		//+pid->d*(pid->error-pid->last_error
		pid->last_error=pid->error;

	}
	
	return pid->actual;
}


float ABS(float a,float b)
{
	if(a>b)
		return a-b;
	else if(b>a)
		return b-a;
	else
		return a;
}

float test_a;
float MIN(float set,float actual,float buff1,float buff2)
{
	float a,b,c;
	a=ABS(set,actual);
	test_a=a;
	b=ABS(actual,buff1);
	c=ABS(actual,buff2);
	
	if((a<b)&&(a<c))
		return set;
	if((b<a)&&(b<c))
		return buff1;
	if((c<b)&&(c<a))
		return buff2;
	else
		return set;
}
