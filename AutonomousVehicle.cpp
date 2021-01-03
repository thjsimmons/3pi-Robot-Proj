
#include "AutonomousVehicle.h"
#include "robotHelperFunctions.h"
#include "math.h"


void AutonomousVehicle::performPowerCorrection(int speed, int power_difference) {
	// These two conditionals clamp the magnitude of the power difference so it doesn't exceed the speed value,
	// which would result in unwanted elliptical movement of the vehicle.
	if (power_difference > speed){
		power_difference = speed;
	}
	if (power_difference < -speed){
		power_difference = -speed;
	}
	// Here is where the motor speeds are actually set.
	// This one-liner implements the speed difference between wheels necessary to turn.
	// My "step" function from robotHelperFunctions.cpp is simply a step function variant
	// with a magnitude of the power difference.
	// Note that when the power difference is nonzero the difference is only applied to one wheel
	// at a time, as opposed to applying it oppositely to both wheels.
	// This means the tangential speed of the vehicle on the track during a turn is reduced by default.
	set_motors(speed - step(-power_difference, 0), speed - step(power_difference, 0));
}

void AutonomousVehicle::initializeVehicle() {
	// This function lumps some pre-mainloop initializations together.
	// Do the standard robot initialization routine:
	initializeRobot();
	// Set all of the robots timers (for timing displays, sign detection intervals) to the current time:
	this->set_telemetry_seed(ticks_to_microseconds(get_ticks()));
	this->set_crossing_time_seed(ticks_to_microseconds(get_ticks()));
	this->set_sign_reaction_seed(ticks_to_microseconds(get_ticks()));
}


int AutonomousVehicle::detect_position(){
	// This function just makes a member function out of the 3pi's readline function to reduce #includes.
	return read_line(this->m_sensors, IR_EMITTERS_ON);
}

void AutonomousVehicle::telemetricDisplay(int power_difference) {
		// This function implements the power difference and bar graph display
		// Time elapsed since updating display:
		unsigned long time_elapsed = ticks_to_microseconds(get_ticks()) - this->get_telemetry_seed();
		// Display period is 100ms:
		unsigned long display_period = 100000;
		// when the time elapsed exceeds the display period - > update:
		if (time_elapsed > display_period){ //if time_elapsed = 100ms = 0.1s = 10^5 us
			// Array holds wheel speeds to make bar graphs of:
			unsigned int reading[2];
			// Wheels speeds are normed and scaled by 4 to make good bar graphs:
			reading[0] = 4 * abs((this->get_speed()- step(-power_difference, 0)));
			reading[1] = 4 * abs((this->get_speed() - step(power_difference, 0)));
			// Here the display is written:
			clear();
			print("PWR:");
			lcd_goto_xy(4, 0);
			print_long(power_difference);
			lcd_goto_xy(0, 1);
			display_readings(2, reading);
			// Set the display timer to the current time so that the time elapsed since last update is zeroed:
			this->set_telemetry_seed(ticks_to_microseconds(get_ticks()));
		}
}

void AutonomousVehicle::detectionDisplay(){
	// This function displays the sign detected:
	clear();
	lcd_goto_xy(0,0);
	print("SIGN#");
	lcd_goto_xy(6,0);
	print_long(this->get_sign_crossed());
}

void AutonomousVehicle::updateDisplay(int power_difference) {
	// This function manages the two displays--the power display and the sign detection display:
	// Time elapsed since leaving a sign:
	unsigned long time_since_last_sign = ticks_to_microseconds(get_ticks()) - this->get_sign_reaction_seed();
	// Sign# display period is 1 second:
	unsigned long reaction_display_period = 500000;
	
	// If the time elapsed exceeds 1 second after crossing a sign, always display the power display
	if (time_since_last_sign > reaction_display_period){
		this->telemetricDisplay(power_difference);
		// Always set the dash count to zero when the robot has not yet encountered a sign
		this->set_dash_count(0);
	}
		// If the time elapsed since a sign has been detected is less than 1 second AND the sign# is nonzero,
		// there is a sign crossed and display its number:
	else if(this->get_sign_crossed() != 0){
		this->detectionDisplay();
	}
}


void AutonomousVehicle::makeNewDetection() {
	// Read the IR sensor brightness data into the vehicle's sensor array:
	unsigned int sensors[5];
	read_line(sensors, IR_EMITTERS_ON);
	// Assume a detection is made until proven false:
	bool detection = true;
	// Iterate through the sensor values and nullify the detection bool if any is not 1000 (black):
	for (int i = 0; i < 5; i++)
	{
		if (sensors[i] != 1000)
		{
			detection = false;
			this->set_ON_DASH(false);
			break;
		}
	}
	// If a new detection is made:
	if (detection){
		// and if  the vehicle is not already on a dash:
		if(!this->is_ON_DASH()){
			// Set the ON_DASH bool to true:
			this->set_ON_DASH(true);
			// Increment the dash count (1 dash in a sign is detected):
			this->set_dash_count(this->get_dash_count() + 1);
			// Play a note signalling detection:
			play_note(A(4), 15, 30);
		}
			// and instead if the vehicle is already on a dash:
		else{
			// Do nothing except reset the timer measuring allowed transit time between dashes:
			this->set_crossing_time_seed(ticks_to_microseconds(get_ticks()));
		}
	}
}

void AutonomousVehicle::performSignDetection() { 
	// This function extends makeNewDetection to detect entire signs:
	// Time elapsed since leaving a dash within a sign:
	unsigned long time_since_last_dash = ticks_to_microseconds(get_ticks()) - this->get_crossing_time_seed();
	// Maximum transit time allowed between dashes before sign detection considered complete is 1 second:
	unsigned long crossing_period =  1000000;
	// Make a new detection in order to count dashes:
	makeNewDetection();
	// A maximum of 4 dashes is meaningful:
	if (this->get_dash_count() > 4){
		this->set_dash_count(0);
	}
	// The sign crossed is equal to the number of dashes detected:
	this->set_sign_crossed(this->get_dash_count());
	// If the transit time is greater than maximum time allowed, sign detection is complete and
	// vehicle will display sign number in updateDisplay:
	if(time_since_last_dash > crossing_period){
		// Start the timer that determines the sign# display:
		this->set_sign_reaction_seed(ticks_to_microseconds(get_ticks()));
		
	}
}




