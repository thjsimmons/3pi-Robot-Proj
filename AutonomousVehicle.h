
#ifndef HW3_AUTONOMOUSVEHICLE_H
#define HW3_AUTONOMOUSVEHICLE_H

#define MAXMOTORSPEED 254
#define MINMOTORSPEED 1


//#include "PIDControllerLogic.h"

typedef unsigned int SensorPositionIndicatorType;

class AutonomousVehicle {
public:
	
	// Equivalent to your "set_wheel_speed(wheel1, wheel2):
	void performPowerCorrection(int speed, int power_difference);
	// Display the power difference and wheel speed bar graphs:
	void telemetricDisplay(int power_difference);
	// Displays the sign# after encounter with sign:
	void detectionDisplay();
	// Manages the telemetricDisplay and the detectionDisplay:
	void updateDisplay(int power_difference);
	// Detects signs under restriction of a "transit" timer:
	void performSignDetection();
	// Detects individual dashes:
	void makeNewDetection();
	// Includes initializeRobot and other value intializations:
	void initializeVehicle();
	// Equivalent to your "UpdateSensors":
	int detect_position();
	// Sets linear speed of vehicle:
	void set_speed(unsigned int speed){
		m_VehicleSpeed = speed;
	}
	// Returns linear speed of vehicle:
	unsigned int get_speed(){
		return m_VehicleSpeed;
	}
	// Sets display timer start point to update power, bar graphs:
	void set_telemetry_seed(unsigned long time_0){
		m_telemetry_time_seed = time_0;
	}
	// Returns the time described above (microseconds):
	unsigned long get_telemetry_seed(){
		return m_telemetry_time_seed;
	}
	// Sets the timer start point to count transit time between dashes in a sign:
	void set_crossing_time_seed(unsigned long time_0){
		m_crossing_time_seed = time_0;
	}
	// Returns the time described above (microseconds):
	unsigned long get_crossing_time_seed(){
		return m_crossing_time_seed;
	}
	
	// Sets the display timer to display the sign# after a sign encounter:
	void set_sign_reaction_seed(unsigned long time_0){
		m_sign_reaction_time_seed = time_0;
	}
	// Returns the time described above (microseconds):
	unsigned long get_sign_reaction_seed(){
		return m_sign_reaction_time_seed;
	}
	
	// Counts the number of dashes in a sign to be set as the sign# detection is complete:
	void set_dash_count(int COUNT){
		m_dash_count = COUNT;
	}
	// Returns the dash count described above:
	int get_dash_count(){
		return m_dash_count;
	}
	// Is set equal to the dash count when sign detection is complete to govern trackNavigationLogic:
	void set_sign_crossed(int SIGN_NUMBER){
		m_sign_crossed = SIGN_NUMBER;
	}
	
	// Returns the sign# described above:
	int get_sign_crossed(){
		return m_sign_crossed;
	}
	// A bool used to prevent multiple detection of the same dash in a sign:
	void set_ON_DASH(bool is_ON){
		m_ON_DASH = is_ON;
	}
	// Returns the above mentioned bool:
	bool is_ON_DASH(){
		return m_ON_DASH;
	}
	// Sets the position of the vehicle to the current position given by the sensors:
	void set_position(int position){
		m_position = position;
	}
	// Returns the above mentioned position:
	int get_position(){
		return m_position;
	}
	
private:
	// Speed of the vehicle attribute:
	unsigned int m_VehicleSpeed{0};
	// Power display timer of the vehicle:
	unsigned long m_telemetry_time_seed{0};
	// Transit-between-dashes timer of the vehicle:
	unsigned long m_crossing_time_seed{0};
	// Sign# timer of the vehicle:
	unsigned long m_sign_reaction_time_seed{0};
	// The vehicle's current position:
	int m_position{0};
	// The number of dashes detected in a sign:
	int m_dash_count{0};
	// The sign the vehicle recently crossed:
	int m_sign_crossed{0};
	// Communicates whether or not the vehicle is currently on dash:
	bool m_ON_DASH{false};
	// The vehicle's sensors for determining position and presence of signs:
	unsigned int m_sensors[5] = {0};
};


#endif //HW3_AUTONOMOUSVEHICLE_H

