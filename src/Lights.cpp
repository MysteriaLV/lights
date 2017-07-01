#include <Arduino.h>
#include "Atm_lights.h"

extern void modbus_setup();
extern void modbus_loop();
extern void modbus_set(word event, word value);

void setup()
{
	Serial.begin(115200);
	modbus_setup();
	atm_lights.begin();
}

void loop() {
	automaton.run();
	modbus_loop();
}