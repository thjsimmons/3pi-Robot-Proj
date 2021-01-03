#include "TrackNavigatorLogic.h"

void TrackNavigatorLogic::optimizeTrackReponse() {
	// We gave the TrackNavigatorLogic the purpose of managing the PID control
	// in reponse to sign number, i.e. the navigator's pidController changes coefficients to handle different tracks:
	// The navigator associates a reccommended speed with each of the tracks in addition
	// to prioritizing different PID terms.
	// TODO: actually tune the PID coefficients using the Ziegler-Nichols method:
	switch(this->get_trackNumber()){
		case 1: //straight away
			this->PID.setPIDCoefficents(0.1, 0.0001, 3/2);
			this->set_rec_speed(250);
			break;
		case 2: //sharp angular
			this->PID.setPIDCoefficents(0.1, 0.0001, 3/2);
			this->set_rec_speed(220);
			
			break;
		case 3: //fast undulating
			this->PID.setPIDCoefficents(0.2, 0.0001, 3/2);
			this->set_rec_speed(240);
			break;
		case 4: //slow undulating
			this->PID.setPIDCoefficents(0.1, 0.0001, 3/2);
			this->set_rec_speed(240);
			break;
		default: // The default case is the straight away case
			this->PID.setPIDCoefficents(0.1, 0.0001, 3/2);
			this->set_rec_speed(220);
			break;
			
	}
}

void TrackNavigatorLogic::computePowerCorrection(int position) {
	// This function accomplishes of the PID computation and sets the current power difference:
	this->PID.computeErrors(position);
	this->PID.setComputedPowerDifference();
	this->set_rec_power(PID.getpowerDifference());
	
}




