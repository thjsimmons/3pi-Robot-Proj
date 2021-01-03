/*
 * 3pi-linefollower-pid - demo code for the Pololu 3pi Robot
 * 
 * The TrackNavigatorLogic object will manipulate a AutonomousVehicle
 * object to follow a black line on a white background,
 * using a PID-based algorithm.
 *
 * http://www.pololu.com/docs/0J21
 * http://www.pololu.com
 * http://forum.pololu.com
 *
 */

#include "AutonomousVehicle.h"
#include "TrackNavigatorLogic.h"

volatile bool runForever = true;

int main() {
	// We have a car:
    AutonomousVehicle myAutoCar;
	// and a driver:
    TrackNavigatorLogic autonomousDriver;
	// initializeVehicle initializes the robot and the vehicle's timers:
	
	myAutoCar.initializeVehicle();
	
    while (runForever)
    {
	    // This function responds to the track number (starting at 1) which determines the PID coefficients
	    autonomousDriver.optimizeTrackReponse();
	    // The vehicle tries to detect signs:
	    myAutoCar.performSignDetection();
	    // The vehicle updates its display, displaying sign# if a sign is encountered, and power/bar graphs otherwise:
	    myAutoCar.updateDisplay(autonomousDriver.get_rec_power());
		// If a sign is detected:
	    if(myAutoCar.get_sign_crossed() > 0){
		    // The track number is the sign#
		    autonomousDriver.set_trackNumber(myAutoCar.get_sign_crossed());
	    }
		// The cars positions is ascertained by its sensors:
	    myAutoCar.set_position(myAutoCar.detect_position());
		// The navigators PID controller calculates the necessary power difference:
	    autonomousDriver.computePowerCorrection(myAutoCar.get_position());
	    // The vehicle applies this power difference to its motors:
	    myAutoCar.performPowerCorrection(autonomousDriver.get_rec_speed(), autonomousDriver.get_rec_power());
    }
	return 0;
}

// NOTE: it seems like the correct operation of sign detection depends strongly
// on the what the robot "sees" initially during calibration i.e. initializeRobot
// so probably it determines the background
