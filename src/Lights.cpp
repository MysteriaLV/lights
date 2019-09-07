#include <Arduino.h>
#include "Atm_lights.h"

extern void modbus_setup();
extern void modbus_loop();
extern void modbus_set(word event, word value);

Atm_led exit_door, xray_screen;

/*
 * http://www.analog.com/media/en/technical-documentation/data-sheets/ADuM1200_1201.pdf
 * http://www.aimtec.com/site/Aimtec/files/Datasheet/HighResolution/AM1S-Z.pdf
 */

#ifdef MY_TEST_MODE

#include <RGBdriver.h>

Atm_timer test_mode_timer1;
Atm_timer test_mode_timer2;
extern RGBdriver Driver;
#endif

void setup() {
    Serial.begin(115200);
    modbus_setup();
    atm_lights.begin();

    exit_door.begin(10, true);
    xray_screen.begin(11, true);

#ifdef MY_TEST_MODE
    exit_door.blink(5000, 5000).start();
    xray_screen.blink(15000, 5000).start();

    test_mode_timer1.begin(1000, 999)
            .onTimer([](int idx, int v, int up) {
                switch (v % 3) {
                    case 0:
                        Serial.println("RED");
                        Driver.begin();
                        Driver.SetColor(255, 0, 0);
                        Driver.SetColor(255, 0, 0);
                        Driver.SetColor(255, 0, 0);
                        Driver.SetColor(255, 0, 0);
                        Driver.SetColor(255, 0, 0);

                        Driver.SetColor(255, 0, 0);
                        Driver.SetColor(255, 0, 0);
                        Driver.SetColor(255, 0, 0);
                        Driver.SetColor(255, 0, 0);
                        Driver.SetColor(255, 0, 0);
                        Driver.end();
                        break;
                    case 1:
                        Serial.println("GREEN");
                        Driver.begin();
                        Driver.SetColor(0, 255, 0);
                        Driver.SetColor(0, 255, 0);
                        Driver.SetColor(0, 255, 0);
                        Driver.SetColor(0, 255, 0);
                        Driver.SetColor(0, 255, 0);

                        Driver.SetColor(0, 255, 0);
                        Driver.SetColor(0, 255, 0);
                        Driver.SetColor(0, 255, 0);
                        Driver.SetColor(0, 255, 0);
                        Driver.SetColor(0, 255, 0);
                        Driver.end();
                        break;
                    case 2:
                        Serial.println("BLUE");
                        Driver.begin();
                        Driver.SetColor(0, 0, 255);
                        Driver.SetColor(0, 0, 255);
                        Driver.SetColor(0, 0, 255);
                        Driver.SetColor(0, 0, 255);
                        Driver.SetColor(0, 0, 255);

                        Driver.SetColor(0, 0, 255);
                        Driver.SetColor(0, 0, 255);
                        Driver.SetColor(0, 0, 255);
                        Driver.SetColor(0, 0, 255);
                        Driver.SetColor(0, 0, 255);
                        Driver.end();
                        break;
                    default:
                        break;
                }
            })
            .onFinish(test_mode_timer2, test_mode_timer1.EVT_START)
            .start();

    test_mode_timer2.begin(1)
            .onFinish(test_mode_timer1, test_mode_timer1.EVT_START);
#endif
}

void loop() {
    automaton.run();
    modbus_loop();
}