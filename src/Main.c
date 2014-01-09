#include"Main.h"

<<<<<<< HEAD


// enum 動作状態
typedef enum{
	MODE_INIT,
	MODE_RUN
} RUN_MODE;

RUN_MODE run_mode = MODE_INIT;

// 初期化の中の状態
typedef enum{
	INIT_WAIT_GYRO,
	INIT_GYRO,
	INIT_WAIT_WHITE,
	INIT_WHITE,
	INIT_WAIT_BLACK,
	INIT_BLACK
} INIT_MODE;


INIT_MODE init_mode = INIT_WAIT_GYRO;

// グローバル変数
static U32	avg_cnt = 0;
static U32 gyrooffset;
Balancer balancer;
=======
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
>>>>>>> 9b3817fe6a16ca223e7edbf1f76593e2934c7bf5

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
<<<<<<< HEAD
		case MODE_INIT:
			caribration();
			break;
		case MODE_RUN:
			ecrobot_debug1(balancer.color_white, balancer.color_black , 0);
			calc_cmd_turn(&balancer);
			balance_running(&balancer);
			break;
		default:
=======
		case (MODE_INIT):
			caribration();
			break;
		case (MODE_RUN):
			ecrobot_debug1(balancer.color_white,balancer.color_black,0);
>>>>>>> 9b3817fe6a16ca223e7edbf1f76593e2934c7bf5
			break;
	}
	/*

<<<<<<< HEAD
	*/
=======
	/*

	*/

>>>>>>> 9b3817fe6a16ca223e7edbf1f76593e2934c7bf5
	TerminateTask();	// <- 忘れるとセグフォがおきてしぬ 
}

void caribration(){
<<<<<<< HEAD
	static U32	cal_start_time;	

	switch(init_mode){
		case INIT_WAIT_GYRO:	// ボタンが押されるまでジャイロオフセットの初期化には遷移しない
			if( ecrobot_get_touch_sensor(NXT_PORT_S4) ) init_mode = INIT_GYRO;
			break;

		case INIT_GYRO:			// ジャイロオフセットの初期化
			// 音を鳴らす
			ecrobot_sound_tone(880, 512, 10);
			// ジャイロセンサの値を計算するための開始時間をセットする 
			cal_start_time = ecrobot_get_systick_ms();

			while((ecrobot_get_systick_ms() - cal_start_time) < 1000U){
				// ジャイロセンサの設定をする 
				gyrooffset += ecrobot_get_gyro_sensor(NXT_PORT_S1);
				avg_cnt++;
			}

			gyrooffset /= avg_cnt;

			set_gyro_offset(&balancer , gyrooffset);
			ecrobot_sound_tone(440U, 500U, 10);		
			systick_wait_ms(500);

			init_mode = INIT_WAIT_WHITE;
			break;

		case INIT_WAIT_WHITE:	// ボタンが押されるまで白のキャリブレーションには遷移しない
			if( ecrobot_get_touch_sensor(NXT_PORT_S4) ) init_mode = INIT_WHITE;
			break;

		case INIT_WHITE:		// 白のキャリブレーション
			ecrobot_sound_tone(880, 512, 10);	// 音を出す
			set_color_white(&balancer , ecrobot_get_light_sensor(NXT_PORT_S3) );
			init_mode = INIT_WAIT_BLACK;
			systick_wait_ms(500);
			break;

		case INIT_WAIT_BLACK:	// ボタンが押されるまで黒のキャリブレーションには遷移しない
			if( ecrobot_get_touch_sensor(NXT_PORT_S4) ) init_mode = INIT_BLACK;
			break;

		case INIT_BLACK:
			ecrobot_sound_tone(880, 512, 10);
			set_color_black(&balancer , ecrobot_get_light_sensor(NXT_PORT_S3) );
			run_mode = MODE_RUN;
			systick_wait_ms(500);
			break;

	}
	
	/*
	//gyro_offset
	// ボタンが押されるまで待機
	if( ecrobot_get_touch_sensor(NXT_PORT_S4) )	 ;
	
	
	// 音を鳴らす
	ecrobot_sound_tone(880, 512, 10);
	// ジャイロセンサの値を計算するための開始時間をセットする 
	cal_start_time = ecrobot_get_systick_ms();

	while((ecrobot_get_systick_ms() - cal_start_time) < 1000U){
		// ジャイロセンサの設定をする 
		gyrooffset += ecrobot_get_gyro_sensor(NXT_PORT_S1);
		avg_cnt++;
	}
=======
>>>>>>> 9b3817fe6a16ca223e7edbf1f76593e2934c7bf5

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

<<<<<<< HEAD
	*/
=======
>>>>>>> 9b3817fe6a16ca223e7edbf1f76593e2934c7bf5
}
