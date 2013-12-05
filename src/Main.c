#include"Main.h"

typedef enum{
	MODE_INIT,
	MODE_RUN
}RUN_MODE;

typedef enum{
	INIT_GYRO,
	INIT_WHITE,
	INIT_BLACK,
	INIT_WAIT_GYRO,
	INIT_WAIT_WHITE,
	INIT_WAIT_BLACK
}INIT_MODE;

RUN_MODE run_mode = MODE_INIT;
INIT_MODE init_mode = INIT_WAIT_GYRO;



// グローバル変数
static U32	avg_cnt = 0;

static U32	gyrooffset = 0;	// ジャイロオフセット

// 関数プロトタイプ	
void caribration();

//カウンタの宣言
DeclareCounter(SysTimerCnt);

/*タスク*/
DeclareCounter(ActionTask);

//初期処理
void ecrobot_device_initialize(void){
	ecrobot_set_light_sensor_active(NXT_PORT_S3);
	balancer_init(&balancer);
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

	switch(run_mode){
		case (MODE_INIT):
			caribration();
			break;
		case (MODE_RUN):
			break;
	}

	/*

	*/

	TerminateTask();	// <- 忘れるとセグフォがおきてしぬ 
}

void caribration(){

	static U32	cal_start_time;	

	switch(init_mode){
	case (INIT_GYRO):
		ecrobot_sound_tone(880, 512, 10);
		cal_start_time = ecrobot_get_systick_ms();
		while((ecrobot_get_systick_ms() - cal_start_time) < 1000U){
			gyrooffset += ecrobot_get_gyro_sensor(NXT_PORT_S1);
			avg_cnt++;
		}
		gyrooffset /= avg_cnt;
		ecrobot_sound_tone(440U, 500U, 10);

		//set_gyro_offset(&balancer,gyrooffset);
		systick_wait_ms(500);
		init_mode= INIT_WAIT_WHITE;
		break;

	case (INIT_WHITE):
		set_color_white(&balancer,ecrobot_get_light_sensor(NXT_PORT_S3));
		ecrobot_sound_tone(440U, 500U, 10);
		init_mode = INIT_WAIT_BLACK;
		systick_wait_ms(500);
		break;
	case (INIT_BLACK):
		set_color_white(&balancer,ecrobot_get_light_sensor(NXT_PORT_S3));
		ecrobot_sound_tone(440U, 500U, 10);
		run_mode = MODE_RUN;
		systick_wait_ms(500);
		break;

	case (INIT_WAIT_GYRO):
		if( ecrobot_get_touch_sensor(NXT_PORT_S4) == TRUE )init_mode=INIT_GYRO;
		break;
	case (INIT_WAIT_WHITE):
		if( ecrobot_get_touch_sensor(NXT_PORT_S4) == TRUE ){
			init_mode=INIT_WHITE;
		}
		break;
	case (INIT_WAIT_BLACK):
		if( ecrobot_get_touch_sensor(NXT_PORT_S4) == TRUE ){
			init_mode=INIT_BLACK;
		}
		break;
}

}
