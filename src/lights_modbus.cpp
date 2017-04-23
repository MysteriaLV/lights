#include <SimpleModbusSlave.h>
#include "Atm_lights.h"

//////////////// registers of LIGHTS ///////////////////
enum {
	// The first register starts at address 0
			ACTIONS,      // Always present, used for incoming actions

	// Any registered events, denoted by 'triggered_by_register' in rs485_node of Lua script, 1 and up

	TOTAL_ERRORS,     // leave this one, error counter
	TOTAL_REGS_SIZE   // INTERNAL: total number of registers for function 3 and 16 share the same register array
};

unsigned int holdingRegs[TOTAL_REGS_SIZE]; // function 3 and 16 register array
////////////////////////////////////////////////////////////

// Action handler. Add all your actions mapped by action_id in rs485_node of Lua script
void process_actions() {
	if (holdingRegs[ACTIONS] == 0)
		return;

	switch (holdingRegs[ACTIONS]) {
		case 1 : // Put here code for Go_dim
			Serial.println("[Go_dim] action fired");
			digitalWrite(LED_BUILTIN, LOW);
			atm_lights.off();
			break;
		case 2 : // Put here code for Go_normal
			Serial.println("[Go_normal] action fired");
			digitalWrite(LED_BUILTIN, HIGH);
			atm_lights.full();
			break;
		case 3 : // Put here code for Go_alarms
			Serial.println("[Go_alarms] action fired");
			digitalWrite(LED_BUILTIN, HIGH);
			atm_lights.alarm();
			break;
		default:break;
	}

	// Signal that action was processed
	holdingRegs[ACTIONS] = 0;
}

// Just debug functions for easy testing. Won't be used probably
/* Holds current button state in register */
void buttonStatus(int reg, uint8_t pin) { // LOOP
	holdingRegs[reg] = digitalRead(pin) ? 1 : 0;
}

void buttonStatus_setup(int reg, uint8_t pin) { // SETUP
	pinMode(pin, INPUT_PULLUP);
}
/////////////////////////////////////////////////////////////////

void modbus_setup() {
	Serial.println("Serial ModBus Slave LIGHTS:1 for lua/Aliens.lua");

	/* parameters(long baudrate,
				  unsigned char ID,
				  unsigned char transmit enable pin,
				  unsigned int holding registers size)
	*/

	modbus_configure(57600, 1, SSerialTxControl, TOTAL_REGS_SIZE);
	holdingRegs[ACTIONS] = 0;
	// Sample calls
	pinMode(LED_BUILTIN, OUTPUT);
	// buttonStatus_setup(, <buttonPin>);
}


void modbus_loop() {
	holdingRegs[TOTAL_ERRORS] = modbus_update(holdingRegs);
	process_actions();

	// Notify main console of local events


	// Sample calls
	// buttonStatus(, <buttonPin>);
}