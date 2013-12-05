#include "Balancer_running.h"

void balancer_init( Balancer* self ){
	self->gyro_offset = 0;
	self->color_white = 0;
	self->color_black = 0;
}

void balance_running( Balancer *self ){
	S8 pwm_l,pwm_r;	// モータの回転角
	S8 cmd_forward = 0;	// 前進
	S8 cmd_turn = 100;	// 旋回

	balance_control(
				(F32)cmd_forward,
				(F32)cmd_turn,
				(F32)ecrobot_get_gyro_sensor(NXT_PORT_S1),
				(F32)self->gyro_offset,
				(F32)nxt_motor_get_count(NXT_PORT_C),
				(F32)nxt_motor_get_count(NXT_PORT_B),
				(F32)ecrobot_get_battery_voltage(),
				&pwm_l,
				&pwm_r);

}

void set_gyro_offset(Balancer *self , U32 gyro_offset){
	self->gyro_offset = gyro_offset;
}

void set_color_white(Balancer *self , int color_white){
	self->color_white = color_white;
}

void set_color_black(Balancer *self ,int color_black){
	self->color_black = color_black;
}
