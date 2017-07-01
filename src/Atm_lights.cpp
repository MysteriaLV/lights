#include "Atm_lights.h"
Atm_lights atm_lights;

#define LED_CIN 2 //pins definitions for the driver
#define LED_DIN 3
#define LED_VCC 4
#define LED_GND 5

#include "RGBdriver.h"
RGBdriver Driver(LED_CIN, LED_DIN);

Atm_lights &Atm_lights::begin() {
	// clang-format off
	const static state_t state_table[] PROGMEM = {
    /*                     ON_ENTER  ON_LOOP  ON_EXIT  EVT_OFF  EVT_DIM  EVT_ALARM  EVT_FLICKER  EVT_NORMAL  EVT_MAINTENACE  ELSE */
    /*        OFF */        ENT_OFF,      -1,      -1,      -1,     DIM,     ALARM,  FLICKERING,     NORMAL,     MAINTENACE,   -1,
    /*        DIM */        ENT_DIM,      -1,      -1,     OFF,      -1,     ALARM,  FLICKERING,     NORMAL,     MAINTENACE,   -1,
    /*      ALARM */      ENT_ALARM,      -1,      -1,     OFF,     DIM,        -1,  FLICKERING,     NORMAL,     MAINTENACE,   -1,
    /* FLICKERING */ ENT_FLICKERING,      -1,      -1,     OFF,     DIM,     ALARM,          -1,     NORMAL,     MAINTENACE,   -1,
    /*     NORMAL */     ENT_NORMAL,      -1,      -1,     OFF,     DIM,     ALARM,  FLICKERING,         -1,     MAINTENACE,   -1,
    /* MAINTENACE */ ENT_MAINTENACE,      -1,      -1,     OFF,     DIM,     ALARM,  FLICKERING,     NORMAL,             -1,   -1,
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
	return 0;
}

/* Add C++ code for each action
 * This generates the 'output' for the state machine
 */

void Atm_lights::action(int id) {
	switch (id) {
		case ENT_OFF:
			Driver.begin(); // begin
			Driver.SetColor(0, 0, 0);
			Driver.SetColor(0, 0, 0);
			Driver.SetColor(0, 0, 0);
			Driver.SetColor(0, 0, 0);
			Driver.SetColor(0, 0, 0);
			Driver.SetColor(0, 0, 0);
			Driver.SetColor(0, 0, 0);
			Driver.end();
			return;
		case ENT_DIM:
			Driver.begin(); // begin
			Driver.SetColor(20, 20, 20);
			Driver.SetColor(20, 20, 20);
			Driver.SetColor(20, 20, 20);
			Driver.SetColor(20, 20, 20);
			Driver.SetColor(20, 20, 20);
			Driver.SetColor(20, 20, 20);
			Driver.SetColor(20, 20, 20);
			Driver.end();
			return;
		case ENT_ALARM:
			Driver.begin(); // begin
			Driver.SetColor(100, 00, 10);
			Driver.SetColor(100, 00, 10);
			Driver.end();
			return;
		case ENT_FLICKERING:
			return;
	    case ENT_NORMAL:
		    Driver.begin(); // begin
			Driver.SetColor(9, 255, 255);
			Driver.SetColor(9, 255, 255);
			Driver.SetColor(9, 255, 255);
			Driver.SetColor(9, 255, 255);
			Driver.SetColor(9, 255, 255);
			Driver.SetColor(9, 255, 255);
			Driver.SetColor(9, 255, 255);
			Driver.end();
	        return;
	    case ENT_MAINTENACE:
		    Driver.begin(); // begin
			Driver.SetColor(255, 255, 255);
			Driver.SetColor(255, 255, 255);
			Driver.SetColor(255, 255, 255);
			Driver.SetColor(255, 255, 255);
			Driver.SetColor(255, 255, 255);
			Driver.SetColor(255, 255, 255);
			Driver.SetColor(255, 255, 255);
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

Atm_lights &Atm_lights::alarm() {
	trigger(EVT_ALARM);
	return *this;
}

Atm_lights &Atm_lights::flicker() {
	trigger(EVT_FLICKER);
	return *this;
}

Atm_lights& Atm_lights::normal() {
  trigger( EVT_NORMAL );
  return *this;
}

Atm_lights& Atm_lights::maintenace() {
  trigger( EVT_MAINTENACE );
	return *this;
}

/* State trace method
 * Sets the symbol table and the default logging method for serial monitoring
 */

Atm_lights &Atm_lights::trace(Stream &stream) {
	Machine::setTrace(&stream, atm_serial_debug::trace,
    "LIGHTS\0EVT_OFF\0EVT_DIM\0EVT_ALARM\0EVT_FLICKER\0EVT_NORMAL\0EVT_MAINTENACE\0ELSE\0OFF\0DIM\0ALARM\0FLICKERING\0NORMAL\0MAINTENACE" );
	return *this;
}



