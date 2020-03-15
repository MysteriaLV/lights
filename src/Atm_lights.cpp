#include "Atm_lights.h"

Atm_lights atm_lights;

#define LED_CIN PIN2 //pins definitions for the driver
#define LED_DIN PIN3
#define LED_VCC PIN4
#define LED_GND PIN5

/* LEDS Connected
 *
 * 1 LED Foor Room2
 * 2 LED Foor Room1
 * 3 LED TopLight Room1
 * 4 Stol-Shema
 * 5 Bolshie Kolbi (Nad zhuzhimi)
 * 6 Perimeter Led1
 * 7 Perimeter Led2
 * 8 LED TopLight Room2
 * 9 Maneken
 * */


#define RGB(r, g, b) Driver.SetColor(b, g, r)

#include "RGBdriver.h"

RGBdriver Driver(LED_CIN, LED_DIN);

Atm_lights &Atm_lights::begin() {
	// clang-format off
	const static state_t state_table[] PROGMEM = {
    /*                              ON_ENTER  ON_LOOP  ON_EXIT  EVT_OFF  EVT_DIM  EVT_POWER_CONSOLE_CONNECTED  EVT_ALARM  EVT_FLICKER  EVT_NORMAL  EVT_MAINTENACE  ELSE */
    /*            OFF */             ENT_OFF,      -1,      -1,      -1,     DIM,              DIM_WITH_TABLE,     ALARM,  FLICKERING,     NORMAL,     MAINTENACE,   -1,
    /*            DIM */             ENT_DIM,      -1,      -1,     OFF,      -1,              DIM_WITH_TABLE,     ALARM,  FLICKERING,     NORMAL,     MAINTENACE,   -1,
    /* DIM_WITH_TABLE */  ENT_DIM_WITH_TABLE,      -1,      -1,     OFF,     DIM,                          -1,     ALARM,  FLICKERING,     NORMAL,     MAINTENACE,   -1,
    /*          ALARM */           ENT_ALARM,      -1,      -1,     OFF,     DIM,                          -1,        -1,  FLICKERING,     NORMAL,     MAINTENACE,   -1,
    /*     FLICKERING */      ENT_FLICKERING,      -1,      -1,     OFF,     DIM,                          -1,     ALARM,          -1,     NORMAL,     MAINTENACE,   -1,
    /*         NORMAL */          ENT_NORMAL,      -1,      -1,     OFF,     DIM,                          -1,     ALARM,  FLICKERING,         -1,     MAINTENACE,   -1,
    /*     MAINTENACE */      ENT_MAINTENACE,      -1,      -1,     OFF,     DIM,                          -1,     ALARM,  FLICKERING,     NORMAL,             -1,   -1,
    };
    // clang-format on
	Machine::begin(state_table, ELSE);

    pinMode(LED_VCC, OUTPUT);
    digitalWrite(LED_VCC, HIGH);
    pinMode(LED_GND, OUTPUT);
    digitalWrite(LED_GND, LOW);

    trace(Serial);
    return *this;
}

/* Add C++ code for each internally handled event (input) 
 * The code must return 1 to trigger the event
 */

int Atm_lights::event(int id) {
    switch (id) {
    }
    return 0;
}

/* Add C++ code for each action
 * This generates the 'output' for the state machine
 */

void Atm_lights::action(int id) {
    switch (id) {
        case ENT_OFF:
            Driver.begin(); // begin

            RGB(0, 0, 0);
            RGB(0, 0, 0);
            RGB(0, 0, 0);
            RGB(0, 0, 0);
            RGB(0, 0, 0);
            RGB(0, 0, 0);
            RGB(0, 0, 0);
            RGB(0, 0, 0);
            RGB(0, 0, 0);

            Driver.end();
            return;
        case ENT_DIM:   // No_power
            // top edge 0 0 255
            // floor/other 255 0 0
            Driver.begin(); // begin
            RGB(255, 000, 000);  // LED Foor Room2
            RGB(255, 000, 000);  // LED Foor Room1
            RGB(000, 000, 255);  // LED TopLight Room1
            RGB(255, 000, 000);  // Stol-Shema
            RGB(255, 000, 000);  // Bolshie Kolbi (Nad chuzhimi)
            RGB(000, 000, 255);  // Perimeter Led1
            RGB(000, 000, 255);  // Perimeter Led2
            RGB(000, 000, 255);  // LED TopLight Room2
            RGB(255, 000, 000);  // Maneken
            Driver.end();
            return;
        case ENT_DIM_WITH_TABLE: // Power_console_connected
            // top edge 0 0 255
            // floor/other 255 0 0
            Driver.begin(); // begin
            RGB(255, 000, 000);  // LED Foor Room2
            RGB(255, 000, 000);  // LED Foor Room1
            RGB(000, 000, 255);  // LED TopLight Room1
            RGB(200, 100, 050);  // Stol-Shema
            RGB(255, 000, 000);  // Bolshie Kolbi (Nad chuzhimi)
            RGB(000, 000, 255);  // Perimeter Led1
            RGB(000, 000, 255);  // Perimeter Led2
            RGB(000, 000, 255);  // LED TopLight Room2
            RGB(255, 000, 000);  // Maneken
            Driver.end();
            return;
        case ENT_ALARM:
            Driver.begin(); // begin
            RGB(255, 0, 0);  // LED Foor Room2
            RGB(255, 0, 0);  // LED Foor Room1
            RGB(255, 0, 0);  // LED TopLight Room1
            RGB(255, 0, 0);  // Stol-Shema
            RGB(255, 0, 0);  // Bolshie Kolbi (Nad chuzhimi)
            RGB(255, 0, 0);  // Perimeter Led1
            RGB(255, 0, 0);  // Perimeter Led2
            RGB(255, 0, 0);  // LED TopLight Room2
            RGB(255, 0, 0);  // Maneken
            Driver.end();
            return;
        case ENT_FLICKERING:
            return;
        case ENT_NORMAL:    // Power_active
            /*  other 255 255 255
                top 70 0 184
                edge 105 255 177
                floor 0 0 255
             */
            Driver.begin(); // begin
            RGB(000, 000, 255);  // LED Foor Room2
            RGB(000, 000, 255);  // LED Foor Room1
            RGB(070, 000, 184);  // LED TopLight Room1
            RGB(200, 100, 050);  // Stol-Shema
            RGB(255, 255, 255);  // Bolshie Kolbi (Nad chuzhimi)
            RGB(105, 255, 177);  // Perimeter Led1
            RGB(105, 255, 177);  // Perimeter Led2
            RGB(070, 000, 184);  // LED TopLight Room2
            RGB(255, 255, 255);  // Maneken
            Driver.end();
            return;
        case ENT_MAINTENACE:    // Full_lights
            Driver.begin(); // begin
            RGB(255, 255, 255);  // LED Foor Room2
            RGB(255, 255, 255);  // LED Foor Room1
            RGB(255, 255, 255);  // LED TopLight Room1
            RGB(255, 255, 255);  // Stol-Shema
            RGB(255, 255, 255);  // Bolshie Kolbi (Nad chuzhimi)
            RGB(255, 255, 255);  // Perimeter Led1
            RGB(255, 255, 255);  // Perimeter Led2
            RGB(255, 255, 255);  // LED TopLight Room2
            RGB(255, 255, 255);  // Maneken
            Driver.end();
            return;
    }
}

/* Optionally override the default trigger() method
 * Control how your machine processes triggers
 */

Atm_lights &Atm_lights::trigger(int event) {
    Machine::trigger(event);
    return *this;
}

/* Optionally override the default state() method
 * Control what the machine returns when another process requests its state
 */

int Atm_lights::state(void) {
    return Machine::state();
}

/* Nothing customizable below this line                          
 ************************************************************************************************
*/

/* Public event methods
 *
 */

Atm_lights &Atm_lights::off() {
    trigger(EVT_OFF);
    return *this;
}

Atm_lights &Atm_lights::dim() {
    trigger(EVT_DIM);
    return *this;
}

Atm_lights &Atm_lights::power_console_connected() {
    trigger(EVT_POWER_CONSOLE_CONNECTED);
    return *this;
}

Atm_lights &Atm_lights::alarm() {
    trigger(EVT_ALARM);
    return *this;
}

Atm_lights &Atm_lights::flicker() {
    trigger(EVT_FLICKER);
    return *this;
}

Atm_lights &Atm_lights::normal() {
    trigger(EVT_NORMAL);
    return *this;
}

Atm_lights &Atm_lights::maintenace() {
    trigger(EVT_MAINTENACE);
    return *this;
}

/* State trace method
 * Sets the symbol table and the default logging method for serial monitoring
 */

Atm_lights &Atm_lights::trace(Stream &stream) {
    Machine::setTrace(&stream, atm_serial_debug::trace,
                      "LIGHTS\0EVT_OFF\0EVT_DIM\0EVT_POWER_CONSOLE_CONNECTED\0EVT_ALARM\0EVT_FLICKER\0EVT_NORMAL\0EVT_MAINTENACE\0ELSE\0OFF\0DIM\0DIM_WITH_TABLE\0ALARM\0FLICKERING\0NORMAL\0MAINTENACE");
    return *this;
}



