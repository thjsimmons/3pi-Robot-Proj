

#define ALLOW_ROBOT_HELPERS_TO_BE_INCLUDED
#include "robotHelperFunctions.h"
#undef ALLOW_ROBOT_HELPERS_TO_BE_INCLUDED

#include <math.h>

// NOTE: There are only two things we changed in this file:
// 1. We added a quantity parameter to generalize the display_readings function.
// 2. We wrote a utility math function called "step" at the end of the file.

// Introductory messages.  The "PROGMEM" identifier causes the data to
// go into program space.
const char welcome_line1[] PROGMEM = " Pololu";
const char welcome_line2[] PROGMEM = "3\xf7 Robot";
const char demo_name_line1[] PROGMEM = "PID Line";
const char demo_name_line2[] PROGMEM = "follower";

// A couple of simple tunes, stored in program space.
const char welcome[] PROGMEM = ">g32>>c32";
const char go[] PROGMEM = "L16 cdegreg4";

// Data for generating the characters used in load_custom_characters
// and display_readings.  By reading levels[] starting at various
// offsets, we can generate all of the 7 extra characters needed for a
// bargraph.  This is also stored in program space.
const char levels[] PROGMEM = {
        0b00000,
        0b00000,
        0b00000,
        0b00000,
        0b00000,
        0b00000,
        0b00000,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111
};

// This function loads custom characters into the LCD.  Up to 8
// characters can be loaded; we use them for 7 levels of a bar graph.
void load_custom_characters()
{
    lcd_load_custom_character(levels+0,0); // no offset, e.g. one bar
    lcd_load_custom_character(levels+1,1); // two bars
    lcd_load_custom_character(levels+2,2); // etc...
    lcd_load_custom_character(levels+3,3);
    lcd_load_custom_character(levels+4,4);
    lcd_load_custom_character(levels+5,5);
    lcd_load_custom_character(levels+6,6);
    clear(); // the LCD must be cleared for the characters to take effect
}

// This function displays the sensor readings using a bar graph.
void display_readings(int quantity, const unsigned int *calibrated_values) //change back to const?
{
    unsigned char i;

    for(i=0;i<quantity;i++) {
        // Initialize the array of characters that we will use for the
        // graph.  Using the space, an extra copy of the one-bar
        // character, and character 255 (a full black box), we get 10
        // characters in the array.
        const char display_characters[10] = {' ',0,0,1,2,3,4,5,6,127};

        // The variable c will have values from 0 to 9, since
        // calibrated values are in the range of 0 to 1000, and
        // 1000/101 is 9 with integer math.
        char c = display_characters[calibrated_values[i]/101];

        // Display the bar graph character.
        print_character(c);
    }
}

// Initializes the 3pi, displays a welcome message, calibrates, and
// plays the initial music.
void initializeRobot()
{
    unsigned int counter; // used as a simple timer
    unsigned int sensors[5]; // an array to hold sensor values

    // This must be called at the beginning of 3pi code, to set up the
    // sensors.  We use a value of 2000 for the timeout, which
    // corresponds to 2000*0.4 us = 0.8 ms on our 20 MHz processor.
    pololu_3pi_init(2000);
    load_custom_characters(); // load the custom characters

    // Play welcome music and display a message
    print_from_program_space(welcome_line1);
    lcd_goto_xy(0,1);
    print_from_program_space(welcome_line2);
    play_from_program_space(welcome);
    delay_ms(1000);

    clear();
    print_from_program_space(demo_name_line1);
    lcd_goto_xy(0,1);
    print_from_program_space(demo_name_line2);
    delay_ms(1000);

    // Display battery voltage and wait for button press
    while(!button_is_pressed(BUTTON_B))
    {
        int bat = read_battery_millivolts();

        clear();
        print_long(bat);
        print("mV");
        lcd_goto_xy(0,1);
        print("Press B");

        delay_ms(100);
    }

    // Always wait for the button to be released so that 3pi doesn't
    // start moving until your hand is away from it.
    wait_for_button_release(BUTTON_B);
    delay_ms(1000);

    // Auto-calibration: turn right and left while calibrating the
    // sensors.
    for(counter=0;counter<80;counter++)
    {
        if(counter < 20 || counter >= 60)
            set_motors(40,-40);
        else
            set_motors(-40,40);

        // This function records a set of sensor readings and keeps
        // track of the minimum and maximum values encountered.  The
        // IR_EMITTERS_ON argument means that the IR LEDs will be
        // turned on during the reading, which is usually what you
        // want.
        calibrate_line_sensors(IR_EMITTERS_ON);

        // Since our counter runs to 80, the total delay will be
        // 80*20 = 1600 ms.
        delay_ms(20);
    }
    set_motors(0,0);

    // Display calibrated values as a bar graph.
    while(!button_is_pressed(BUTTON_B))
    {
        // Read the sensor values and get the position measurement.
        unsigned int position = read_line(sensors,IR_EMITTERS_ON);

        // Display the position measurement, which will go from 0
        // (when the leftmost sensor is over the line) to 4000 (when
        // the rightmost sensor is over the line) on the 3pi, along
        // with a bar graph of the sensor readings.  This allows you
        // to make sure the robot is ready to go.
        clear();
        print_long(position);
        lcd_goto_xy(0,1);
        display_readings(5, sensors);

        delay_ms(100);

    }
    wait_for_button_release(BUTTON_B);

    clear();

    print("Go!");

    // Play music and wait for it to finish before we start driving.
    //play_from_program_space(go); //comment back in the music when needed
    //while(is_playing());
}


void playBeepTrackChange()
{
    play_note(F_SHARP(4), 30, 15);
}

void playBeepOverDrive()
{
    play_note(A_FLAT(4), 30, 15);
}

int step(int x, int tau){ // Author: tjsimmons
	// A heaviside function scaled by magnitude of input,
	// i.e. this is y = x * u(x - tau):
	if (x >= tau){
		return x;
	}
	else{
		return 0;
	}
}
