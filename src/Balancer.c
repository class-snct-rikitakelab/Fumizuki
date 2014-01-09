#include "Balancer.h"

<<<<<<< HEAD
void balancer_init( Balancer *self ){
	self->gyro_offset = 0;
=======
void balancer_init(Balancer *self){
	self->gyro_offset = 0; 
>>>>>>> 9b3817fe6a16ca223e7edbf1f76593e2934c7bf5
	self->color_white = 0;
	self->color_black = 0;
}

<<<<<<< HEAD
void balance_runnning( Balancer *self ){
	S8 pwm_l,pwm_r;	// ãƒ¢ãƒ¼ã‚¿ã®å›žè»¢è§’
	S8 cmd_forward = 0;	// å‰é€²
	S8 cmd_turn = 100;	// æ—‹å›ž
=======
void balance_running(Balancer *self){
	S8 pwm_l,pwm_r;	// ƒ‚[ƒ^‚Ì‰ñ“]Šp
	S8 cmd_forward = 0;
	S8 cmd_turn = 100;
>>>>>>> 9b3817fe6a16ca223e7edbf1f76593e2934c7bf5

	balance_control(
				(F32)cmd_forward,
				(F32)cmd_turn,
				(F32)ecrobot_get_gyro_sensor(NXT_PORT_S1),
<<<<<<< HEAD
				(F32)self->gyrooffset,
=======
				(F32)self->gyro_offset,
>>>>>>> 9b3817fe6a16ca223e7edbf1f76593e2934c7bf5
				(F32)nxt_motor_get_count(NXT_PORT_C),
				(F32)nxt_motor_get_count(NXT_PORT_B),
				(F32)ecrobot_get_battery_voltage(),
				&pwm_l,
				&pwm_r);

}

<<<<<<< HEAD
void set_gyro_offset(Balancer *self , U32 gyro_offset){
	*self->gyro_offset = gyro_offset;
}

void set_color_white(Balancer *self , int color_white){
	*self->color_white = color_white;
}

void set_color_black(Balancer *self ,int color_black){
	*self->color_black = color_black
}
=======
void set_gyro_offset(Balancer *self,U32 gyro_offset){
	self->gyro_offset = gyro_offset;
}

void set_color_white(Balancer *self,int color_white){
	self->color_white = color_white;
}

void set_color_black(Balancer *self,int color_black){
	self->color_black = color_black;
}
>>>>>>> 9b3817fe6a16ca223e7edbf1f76593e2934c7bf5
