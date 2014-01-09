#ifndef BALANCER
#define BALANCER
#include "Main.h"

typedef struct{
	U32 gyro_offset;	
	int color_white;	
	int color_black;	
	S8  cmd_forward;
	S8  cmd_turn;
}Balancer;

void balancer_init(Balancer* self);
void balance_running(Balancer* self );
void set_gyro_offset(Balancer* self ,U32 gyro_offset);
void set_color_white(Balancer* self ,int color_white);
void set_color_black(Balancer* self ,int color_black);
void calc_cmd_turn_on_off(Balancer* self);
void calc_cmd_turn_pid(Balancer* self);

#endif
