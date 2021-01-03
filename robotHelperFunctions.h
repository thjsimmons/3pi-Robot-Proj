#ifndef HW3_ROBOTHELPERFUNCTIONS_H
#define HW3_ROBOTHELPERFUNCTIONS_H
/*
#ifndef ALLOW_ROBOT_HELPERS_TO_BE_INCLUDED
#error "You are not allowed to include the robotHelperFunctions.h file anywhere except the AutonomousVehicle.cpp file"
#endif
*/

// The 3pi include file must be at the beginning of any program that
// uses the Pololu AVR library and 3pi.
#include <pololu/3pi.h>

// This include file allows data to be stored in program space.  The
// ATmega168 has 16k of program space compared to 1k of RAM, so large
// pieces of static data should be stored in program space.
#include <avr/pgmspace.h>
#include <stdlib.h>
#include "PIDControllerLogic.h"
#include "TrackNavigatorLogic.h"

void load_custom_characters();
// We added a "quantity" parameter to this function in order to use it for the bar graph display
// which only requires 2 readings.
void display_readings(int quantity, const unsigned int *calibrated_values);
void initializeRobot();
void playBeepTrackChange(); //unused
void playBeepOverDrive(); //unused
int step(int x, int tau);

#endif //HW3_ROBOTHELPERFUNCTIONS_H
