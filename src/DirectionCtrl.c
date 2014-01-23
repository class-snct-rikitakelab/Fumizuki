#include "DirectionCtrl.h"
#include "../../Factory.h"

#include "../../EncoderPart/DirectionEncoder.h" //need to be rectoring

#define CYCLE_TIME 0.004


//fake implementation
int DirectionCtrl_run(DirectionCtrl *this_DirectionCtrl,int target_direction)
{
	static	float	hensa = 0;
	static	int		turn = 0;

	static const float dKp = 0.5;
	static const float dKi = 0.00	;
	static const float dKd =	0.0;

	static float i_hensa = 0;
	static float d_hensa = 0;
	static float bf_hensa = 0;

	hensa =  DirectionEncoder_get_direction(&directionEncoder) - target_direction;

	i_hensa = i_hensa + (hensa * CYCLE_TIME);
	d_hensa = (bf_hensa - hensa )/CYCLE_TIME;
	bf_hensa = hensa;

	turn = dKp*hensa + dKi*i_hensa + dKd*d_hensa;
	turn = cutoff(turn,100);
	
	return turn;

}

int DirectionCtrl_do_direction_ctrl(DirectionCtrl *this_DirectionCtrl)
{
	return 0;
}
