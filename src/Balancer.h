#ifndef BALANCER
#define BALANCER

typedef struct{
	U32 gyro_offset;	
	int color_white;
	int color_black;
}BALANCER;

void balancer_init(Balancer* self);
void balance_runnning(Balancer* self );
void set_gyro_offset(Balancer* self , U32 gyro_offset);
void set_color_white(Balancer* self ,int color_white);
void set_color_black(Balancer* self ,int color_black);

#endif