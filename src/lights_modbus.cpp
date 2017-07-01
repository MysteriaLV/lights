#include "Atm_lights.h"

#define USE_HOLDING_REGISTERS_ONLY

#include <Modbus.h>

extern void modbus_setup();
extern void modbus_loop();
extern void modbus_set(word event, word value);

//////////////// registers of LIGHTS ///////////////////
enum {
	// The first register starts at address 0
			ACTIONS,      // Always present, used for incoming actions

	// Any registered events, denoted by 'triggered_by_register' in rs485_node of Lua script, 1 and up

	TOTAL_ERRORS     // leave this one, error counter
};

#ifdef USE_SOFTWARE_SERIAL
#include <ModbusSerial.h>
ModbusSerial mb;

#define SSerialTxControl 6   //RS485 Direction control
#define SSerialRX        8  //Serial Receive pin
#define SSerialTX        9  //Serial Transmit pin
SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX
#endif

#ifdef USE_ALT_SOFT_SERIAL

#include <ModbusSerial.h>

ModbusSerial mb;

#define SSerialTxControl 6   //RS485 Direction control
#define SSerialRX        8  //Serial Receive pin
#define SSerialTX        9  //Serial Transmit pin
AltSoftSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX
#endif

#ifdef USE_SERIAL1
#include <ModbusSerial.h>
ModbusSerial mb;

#define SSerialRX        19  //Serial3 Receive pin (just a reference, can't be changed)
#define SSerialTX        18  //Serial3 Transmit pin (just a reference, can't be changed)
#define SSerialTxControl 20   //RS485 Direction control

#define RS485Serial Serial1
#endif

#ifdef USE_ESP8266_TCP
#include <ESP8266WiFi.h>
#include <ModbusIP_ESP8266.h>
ModbusIP mb;
#endif

// Action handler. Add all your actions mapped by action_id in rs485_node of Lua script
void process_actions() {
	if (mb.Hreg(ACTIONS) == 0)
		return;

	switch (mb.Hreg(ACTIONS)) {
		case 1 : // Put here code for Go_dim
			Serial.println("[Go_dim] action fired");
			digitalWrite(LED_BUILTIN, HIGH);
			atm_lights.dim();
			break;
		case 2 : // Put here code for Go_normal
			Serial.println("[Go_normal] action fired");
			digitalWrite(LED_BUILTIN, LOW);
			atm_lights.normal();
			break;
		case 3 : // Put here code for Go_alarms
			Serial.println("[Go_alarms] action fired");
			digitalWrite(LED_BUILTIN, LOW);
			atm_lights.dim();
			break;
		case 4 : // Put here code for Go_off
			Serial.println("[Go_off] action fired");
			digitalWrite(LED_BUILTIN, LOW);
			atm_lights.off();
			break;
		case 5 : // Put here code for Go_max
			Serial.println("[Go_max] action fired");
			digitalWrite(LED_BUILTIN, LOW);
			atm_lights.maintenace();
			break;
		default:
			break;
	}

	// Signal that action was processed
	mb.Hreg(ACTIONS, 0);
}

void modbus_set(word event, word value) {
	mb.Hreg(event, value);
}

void modbus_setup() {
	Serial.println("ModBus Slave LIGHTS:1 for lua/Aliens.lua");

#ifndef USE_ESP8266_TCP
	mb.config(&RS485Serial, 57600, SSerialTxControl);
	mb.setSlaveId(1);
#else
	mb.config("Aliens Room", "123123123");
	WiFi.config(IPAddress(1), IPAddress(), IPAddress(), IPAddress(), IPAddress());

	Serial.print("Connecting to Aliens Room ");
	while (WiFi.status() != WL_CONNECTED) {
	  delay(500);
	  Serial.print(".");
	}

	Serial.println(" CONNECTED!");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

	Serial.print("Netmask: ");
	Serial.println(WiFi.subnetMask());

	Serial.print("Gateway: ");
	Serial.println(WiFi.gatewayIP());
#endif

	mb.addHreg(ACTIONS, 0);

	pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output (D4)
}


void modbus_loop() {
	mb.task();              // not implemented yet: mb.Hreg(TOTAL_ERRORS, mb.task());
	process_actions();
}
