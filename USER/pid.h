#ifndef __PID_H
#define __PID_H

void pid_init(void);
float MIN(float set,float actual,float buff1,float buff2);
float ABS(float a,float b);

#endif
