#ifndef BALANCER_RUNNING
#define BALANCER_RUNNING

#include "balancer.h"


typedef struct{
	int gyro_offset;
	int color_white;
	int color_black;
}Balancer;

void balancer_init(Balancer *self);
void balance_running(Balancer *self);
void set_gyro_offset(Balancer *self,int gyro_offset);
void set_color_white(Balancer *self,int color_white);
void set_color_black(Balancer *self,int color_black);

#endif
