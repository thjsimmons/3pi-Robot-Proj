// Write program to navigate one track at a time.


#include "AutonomousVehicle.h"


int main() {
	// In step1 we don't include the trackNavigatorLogic yet, as the track is fixed:
	AutonomousVehicle myAutoCar;
	// Instead the car simply has pidController without a "driver":
	pidController PID;
	// The controller's coefficients are fixed as well:
	PID.setPIDCoefficents(1.5, 0, 25);
	// initializeVehicle initializes the robot and the vehicle's timers:
	myAutoCar.initializeVehicle();
	// The vehicle's speed is also fixed:
	myAutoCar.set_speed(250);
	
	while (true)
	{
		// The car's position is ascertained by its sensors:
		myAutoCar.set_position(myAutoCar.detect_position());
		// The PID controller computes the errors as a function of this position:
		PID.computeErrors(myAutoCar.get_position());
		// The PID controller computes the power difference as a sum of scaled PID errors:
		PID.setComputedPowerDifference();
		// The car applies this power difference to the motors:
		myAutoCar.performPowerCorrection(myAutoCar.get_speed(), PID.getpowerDifference());
		// The car only displays the power difference and motor speed bar graphs:
		myAutoCar.telemetricDisplay(PID.getpowerDifference());
	}
	return 0;
}


