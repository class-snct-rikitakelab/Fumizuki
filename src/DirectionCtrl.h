#ifndef __DirectionControl
#define __DirectionControl

#include "../../lib/CommonFunction.h"

typedef struct {
	
}DirectionCtrl;


int DirectionCtrl_do_direction_ctrl(DirectionCtrl *this_DirectionCtrl);


int DirectionCtrl_run(DirectionCtrl *this_DirectionCtrl,int target_direction);


#endif
