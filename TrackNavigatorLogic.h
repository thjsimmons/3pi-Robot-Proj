

#ifndef HW2_GEAR_H
#define HW2_GEAR_H

#include "math.h"

#include <pololu/3pi.h>

#include "PIDControllerLogic.h"

class TrackNavigatorLogic {
public:
	// This public attribute is the navigator's pidController which is
	// managed in bulk in its member functions:
    pidController PID;
	// Sets the track number that the vehicle is on:
	void set_trackNumber(int track){
		m_trackNumber = track;
	}
	// Returns the track number the vehicle is on:
	int get_trackNumber(){
		return m_trackNumber;
	}
	// Sets the reccommended speed for the current track:
	void set_rec_speed(int speed){
		m_recommended_speed = speed;
	}
	// Returns the reccommended speed for the current track:
	int get_rec_speed(){
		return m_recommended_speed;
	}
	// Sets the reccommended power difference for the current instant in time:
	void set_rec_power(int power){
		m_reccomended_power_difference = power;
	}
	// Returns the reccommended power difference for the current instant in time:
	int get_rec_power(){
		return m_reccomended_power_difference;
	}
	// This functions choses differnent coefficients for the navigator's pidController as function of trackNumber:
	void optimizeTrackReponse();
	// This function applies the pidController's functions to compute the power difference:
	void computePowerCorrection(int position);
	// This function resets the pidController's integral error when no longer needed:
	
private:
	// The track number the vehicle is on:
	int m_trackNumber{1};
	// The reccomended linear speed of the vehicle for a given track:
	int m_recommended_speed{0};
	// The reccomended power difference to each of the vehicle's wheels for a given instant in time:
	int m_reccomended_power_difference{0};
	
	unsigned long m_univeral_time_seed{0};
	
	unsigned long m_acceleration_time_seed{0};
};

#endif //HW2_GEAR_H

