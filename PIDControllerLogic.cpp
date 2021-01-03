
#include "PIDControllerLogic.h"


void pidController::computeErrors(int position) {
	// this function computes each of the P, I, and D errors relative to the line"
	// Proportional error is the distance from the setpoint (the line):
	this->setProportional(position - 2000);
	// Integral error is the sum of past proportional errors, the steady state error:
	this->setIntegral(this->getIntegral() + this->getProportional());
	// Differential error is the change in proportional error in each time step, high frequency error:
	this->setDifferential(this->getProportional() - this->getLastProportional());
	// Last error gets set to current error for next calculation
	this->setLastProportional(this->getProportional());
}

void pidController::setComputedPowerDifference(){
	// This function scales the PID errors by their corresponding track-specific coefficients
	// and computes (and sets) the controller's power difference as the sum of the PID terms.
	int P_term = (this->getK_p()) * (this->getProportional());
	int I_term = (this->getK_i()) * (this->getIntegral());
	int D_term = (this->getK_d()) * (this->getDifferential());
	this->setpowerDifference((int)(P_term + I_term + D_term));
}



