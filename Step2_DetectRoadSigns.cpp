// Write program to navigate one track at a time.

#include "AutonomousVehicle.h"


int main() {
	// In step1 we don't include the trackNavigatorLogic yet, as the track is fixed:
	AutonomousVehicle myAutoCar;
	// Instead the car simply has pidController without a "driver":
	pidController PID;
	// The controller's coefficients are fixed as well:
	PID.setPIDCoefficents(0.1, 0.0001, 3/2);
	// initializeVehicle initializes the robot and the vehicle's timers:
	myAutoCar.initializeVehicle();
	// The vehicle's speed is also fixed:
	myAutoCar.set_speed(150);
	
	while (true)
	{
		// First the vehicle tries to detect signs:
		myAutoCar.performSignDetection();
		// Now it decides which display to display and displays it:
		myAutoCar.updateDisplay(PID.getpowerDifference());
		// The car's position is ascertained by its sensors:
		myAutoCar.set_position(myAutoCar.detect_position());
		// The PID controller computes the power difference as a sum of scaled PID errors:
		PID.computeErrors(myAutoCar.get_position());
		PID.setComputedPowerDifference();
		// The car applies this power difference to the motors:  (commented out to test stationary behavior)
		//myAutoCar.performPowerCorrection(myAutoCar.get_speed(), PID.getpowerDifference());
	}
	return 0;
}


