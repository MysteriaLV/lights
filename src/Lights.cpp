#include <Arduino.h>
#include "Atm_lights.h"

//
// Created by VermutMac on 4/23/2017.
//
extern void modbus_setup();
extern void modbus_loop();
extern unsigned int holdingRegs[];

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