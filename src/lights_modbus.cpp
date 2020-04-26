#include "Atm_lights.h"
extern Atm_led exit_door, xray_screen, lapa_door;

#include <Modbus.h>

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

#define SSerialGND       10
#define SSerialRX        9  //Serial Receive pin
#define SSerialTX        8  //Serial Transmit pin
#define SSerialVCC       7
#define SSerialTxControl 6   //RS485 Direction control
SoftwareSerial RS485Serial(SSerialRX, SSerialTX); // RX, TX
#endif

#ifdef USE_ALT_SOFT_SERIAL

#include <ModbusSerial.h>

ModbusSerial mb;
#define SSerialTxControl 6   //RS485 Direction control
#define SSerialRX        8  //Serial Receive pin
#define SSerialTX        9  //Serial Transmit pin
AltSoftSerial RS485Serial(111, 222); // RX, TX hardcoded
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
        case 1 : // Put here code for Full_lights
            Serial.println("[Full_lights] action fired");
            atm_lights.maintenace();
            break;
        case 2 : // Put here code for No_power
            Serial.println("[No_power] action fired");
            atm_lights.dim();
            break;
        case 3 : // Put here code for Power_active
            Serial.println("[Power_active] action fired");
            atm_lights.normal();
            break;
        case 4 : // Put here code for Alarms
            Serial.println("[Alarms] action fired");
            atm_lights.alarm();
            break;
        case 5 : // Put here code for Lock_door
            Serial.println("[Lock_door] action fired");
            exit_door.on();
            break;
        case 6 : // Put here code for Unlock_door
            Serial.println("[Unlock_door] action fired");
            exit_door.off();
            break;
        case 7 : // Put here code for Enable_xray
            Serial.println("[Enable_xray] action fired");
            xray_screen.on();
            break;
        case 8 : // Put here code for Disable_xray
            Serial.println("[Disable_xray] action fired");
            xray_screen.off();
            break;
        case 9 : // Put here code for Force_lapa
            Serial.println("[Force_lapa] action fired");
            lapa_door.on();
            break;
        case 10 : // Put here code for Power_console_connected
            Serial.println("[Power_console_connected] action fired");
            atm_lights.power_console_connected();
            break;
        case 11 : // Put here code for Lab_light_on
            Serial.println("[Lab_light_on] action fired");
            atm_lights.laboratory();
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

#ifdef EMULATE_RS3485_POWER_PINS
	pinMode(SSerialVCC, OUTPUT);
	digitalWrite(SSerialVCC, HIGH);
	pinMode(SSerialGND, OUTPUT);
	digitalWrite(SSerialGND, LOW);
	delay(10);
#endif

#ifndef USE_ESP8266_TCP
	mb.config(&RS485Serial, 31250, SSerialTxControl);
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
