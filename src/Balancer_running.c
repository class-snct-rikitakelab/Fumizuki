#include "Balancer_running.h"

void balancer_init( Balancer* self ){
	self->gyro_offset = 0;
	self->color_white = 0;
	self->color_black = 0;
	self->cmd_forward = 30;
	self->cmd_turn    = 0;
}

void balance_running( Balancer *self ){
	S8 pwm_l,pwm_r;	// モータの回転角

	balance_control(
				(F32)self->cmd_forward,
				(F32)self->cmd_turn,
				(F32)ecrobot_get_gyro_sensor(NXT_PORT_S1),
				(F32)self->gyro_offset,
				(F32)nxt_motor_get_count(NXT_PORT_C),
				(F32)nxt_motor_get_count(NXT_PORT_B),
				(F32)ecrobot_get_battery_voltage(),
				&pwm_l,
				&pwm_r);
	nxt_motor_set_speed(NXT_PORT_C, pwm_l, 1);
	nxt_motor_set_speed(NXT_PORT_B, pwm_r, 1);

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

void calc_cmd_turn_on_off(Balancer* self){
	int target_value = (self->color_white + self->color_black) / 2 ;	// 白と黒の中間値を出す
	// 現在の輝度値が目標値より大きければ+50、そうでなければ-50の旋回値を与える
	if(target_value > ecrobot_get_light_sensor(NXT_PORT_S3)){
		self->cmd_turn = 50;
	}else
	{
		self->cmd_turn = -50;
	}
	
}

void calc_cmd_turn_pid(Balancer* self){
	float deviation=0,i_deviation=0,d_deviation=0,bf_deviation=0;
	float kp=2.0,ki=0.0,kd=1.0;
	int target_value = (self->color_white + self->color_black) / 2 ;

	deviation = target_value - ecrobot_get_light_sensor(NXT_PORT_S3);

	i_deviation = i_deviation + (deviation * 0.004);
	d_deviation = (bf_deviation - deviation)/0.004;
	bf_deviation = deviation;

	self->cmd_turn = kp*deviation + ki*i_deviation + kd*d_deviation;

	if(self->cmd_turn>127)self->cmd_turn=127;
	else if(self->cmd_turn<-127)self->cmd_turn=-127;

}
