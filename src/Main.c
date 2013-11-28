#include"Main.h"

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "balancer.h" // <-　バランサーを使うときはこれを呼び出さないとしぬっぽい？

// グローバル変数
static U32	avg_cnt = 0;
static U32	cal_start_time;	
static U32	gyrooffset = 0;	// ジャイロオフセット
int flg = 0;	// フラグ

S8 pwm_l,pwm_r;	// モータの回転角
S8 cmd_forward = 0;
S8 cmd_turn = 100;

// 関数プロトタイプ	
void caribration();

//カウンタの宣言
DeclareCounter(SysTimerCnt);

/*タスク*/
DeclareCounter(ActionTask);

//初期処理
void ecrobot_device_initialize(void){
	ecrobot_set_light_sensor_active(NXT_PORT_S3);
}

//後始末処理
void ecrobot_device_terminate(void){
	ecrobot_set_motor_speed(NXT_PORT_B, 0);
	ecrobot_set_motor_speed(NXT_PORT_C, 0);
}


/*--------------------------------------------------------------------------*/
/* OSEK hooks                                                               */
/*--------------------------------------------------------------------------*/
void StartupHook(void){}
void ShutdownHook(StatusType ercd){}
void PreTaskHook(void){}
void PostTaskHook(void){}
void ErrorHook(StatusType ercd){}


/*--------------------------------------------------------------------------*/
/* Function to be invoked from a category 2 interrupt                       */
/*--------------------------------------------------------------------------*/
void user_1ms_isr_type2(void){
	StatusType ercd;
	/*
	 *  Increment OSEK Alarm System Timer Count
     */
	ercd = SignalCounter( SysTimerCnt );
	if( ercd != E_OK ){
		ShutdownOS( ercd );
	}
}


TASK(ActionTask){
	ecrobot_status_monitor("OSEK Hell_World!");

	if(flg == 0){
		caribration();
		flg = 1;
	}

	balance_control(
				(F32)cmd_forward,
				(F32)cmd_turn,
				(F32)ecrobot_get_gyro_sensor(NXT_PORT_S1),
				(F32)gyrooffset,
				(F32)nxt_motor_get_count(NXT_PORT_C),
				(F32)nxt_motor_get_count(NXT_PORT_B),
				(F32)ecrobot_get_battery_voltage(),
				&pwm_l,
				&pwm_r);

	nxt_motor_set_speed(NXT_PORT_C , pwm_l , 1);
	nxt_motor_set_speed(NXT_PORT_B , pwm_r , 1);


	TerminateTask();	// <- 忘れるとセグフォがおきてしぬ 
}

void caribration(){
	//gyro_offset
	// ボタンが押されるまで待機
	while (1){
		if( ecrobot_get_touch_sensor(NXT_PORT_S4) )	break;
	}
	
	// 音を鳴らす
	ecrobot_sound_tone(880, 512, 10);
	/* ジャイロセンサの値を計算するための開始時間をセットする */
	cal_start_time = ecrobot_get_systick_ms();

	while((ecrobot_get_systick_ms() - cal_start_time) < 1000U){
		/* ジャイロセンサの設定をする */
		gyrooffset += ecrobot_get_gyro_sensor(NXT_PORT_S1);
		avg_cnt++;
	}

	gyrooffset /= avg_cnt;
	ecrobot_sound_tone(440U, 500U, 10);

	systick_wait_ms(1500);
	
}
