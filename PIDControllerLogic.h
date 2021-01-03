#ifndef HW3_PID_H
#define HW3_PID_H


#include "AutonomousVehicle.h"

class pidController {
public:

  /* Actionas a pidController may need to do
  The PID controller should probably NOT manipulate the autonomous vehicle

   void resetPID()
  void computeOptimalWheelSpeeds() based on Sensor indicated position and current speed

  */
	
	// NOTE: We did not use and removed the getters and setters for the motor speeds because
	// they were redundant in our coding scheme in which the motor speed is an attribute of the vehicle:
	
	// Computes P, I, and D errors with respect to position from the line:
    void computeErrors(int position);
	// Calculates the required power difference between wheels as sum of scaled P, I, and D errors:
	void setComputedPowerDifference();
	// Returns the proprtional error:
    int getProportional() const {
        return m_Proportional;
    }
	// Sets the proportional error:
    void setProportional(int Proportional) {
        m_Proportional = Proportional;
    }
	// Returns the previous proportional error:
    int getLastProportional() const {
        return m_LastProportional;
    }
	// Sets the previous proportional error:
    void setLastProportional(int LastProportional) {
        m_LastProportional = LastProportional;
    }
	// Returns the integral error:
    int getIntegral() const {
        return m_Integral;
    }
    // Sets the integral error:
    void setIntegral(int Integral) {
        m_Integral = Integral;
    }
	// Returns the differential error:
    int getDifferential() const {
        return m_Differential;
    }
	// Sets the differential error:
    void setDifferential(int Differential) {
        m_Differential = Differential;
    }
	// Returns the power difference to be applied to the vehicle's motors:
    int getpowerDifference() const {
        return m_powerDifference;
    }
	// Sets the power difference to be applied to the vehicle's motors:
    void setpowerDifference(int powerDifference) {
        m_powerDifference = powerDifference;
    }
	// Returns the coefficent K_p which scales the proportional error in the power calculation:
	float getK_p() const{
		return mK_p;
	}
	// Returns the coefficent K_i which scales the integral error in the power calculation:
	float getK_i() const{
		return mK_i;
	}
	// Returns the coefficent K_d which scales the differential error in the power calculation:
	float getK_d() const{
		return mK_d;
	}
	// Sets all three of the above mentioned coefficents:
	void setPIDCoefficents(float K_p, float K_i, float K_d){
		mK_p = K_p;
		mK_i = K_i;
		mK_d = K_d;
	}
	
private:
	// The proportional error:
    int m_Proportional{0};
	// The previous proportional error:
    int m_LastProportional{0};
	// The integral error:
    int m_Integral{0};
	// The differential error:
    int m_Differential{0};
	// The power difference determining wheel speeds during terms:
    int m_powerDifference{0};
	//Coefficient used to scale proportional term:
	float mK_p{0};
	//Coefficient used to scale integral term:
	float mK_i{0};
	//Coefficient used to scale differential term:
	float mK_d{0};
};


#endif



