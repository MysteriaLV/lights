#include <Arduino.h>
#include "Atm_lights.h"

Atm_led exit_door, xray_screen;

char cmd_buffer[80];
Atm_command cmd;

enum {
    CMD_ALL, CMD_FLOOR, CMD_TOP, CMD_EDGE, CMD_OTHER
};
const char cmdlist[] = "all floor top edge other";

#include "RGBdriver.h"

#define RGB(r, g, b) Driver.SetColor(b, g, r)
extern RGBdriver Driver;

uint8_t values[9][3] = {
        {255, 0, 0},
        {255, 0, 0},
        {255, 0, 0},
        {255, 0, 0},
        {255, 0, 0},
        {255, 0, 0},
        {255, 0, 0},
        {255, 0, 0},
        {255, 0, 0},
};

void set_value(int i, uint8_t r, uint8_t g, uint8_t b) {
    values[i][0] = r;
    values[i][1] = g;
    values[i][2] = b;
}

void cmd_callback(int idx, int v, int up) {
    int newRGB[3] = {atoi(cmd.arg(1)), atoi(cmd.arg(2)), atoi(cmd.arg(3))};

    switch (v) {
        case CMD_ALL:
            for (int i = 0; i < 9; i++)
                set_value(i, atoi(cmd.arg(1)), atoi(cmd.arg(2)), atoi(cmd.arg(3)));
            break;
        case CMD_EDGE:
            set_value(6-1, atoi(cmd.arg(1)), atoi(cmd.arg(2)), atoi(cmd.arg(3)));
            set_value(7-1, atoi(cmd.arg(1)), atoi(cmd.arg(2)), atoi(cmd.arg(3)));
            break;
        case CMD_FLOOR:
            set_value(1-1, atoi(cmd.arg(1)), atoi(cmd.arg(2)), atoi(cmd.arg(3)));
            set_value(2-1, atoi(cmd.arg(1)), atoi(cmd.arg(2)), atoi(cmd.arg(3)));
            break;
        case CMD_TOP:
            set_value(3-1, atoi(cmd.arg(1)), atoi(cmd.arg(2)), atoi(cmd.arg(3)));
            set_value(8-1, atoi(cmd.arg(1)), atoi(cmd.arg(2)), atoi(cmd.arg(3)));
            break;
        case CMD_OTHER:
            set_value(4-1, atoi(cmd.arg(1)), atoi(cmd.arg(2)), atoi(cmd.arg(3)));
            set_value(5-1, atoi(cmd.arg(1)), atoi(cmd.arg(2)), atoi(cmd.arg(3)));
            set_value(9-1, atoi(cmd.arg(1)), atoi(cmd.arg(2)), atoi(cmd.arg(3)));
            break;
    }

    Driver.begin(); // begin
    for (int i = 0; i < 9; ++i) {
        RGB(values[i][0], values[i][1], values[i][2]);
    }
    Driver.end();
}

void setup() {
    Serial.begin(9600);
    cmd.begin(Serial, cmd_buffer, sizeof(cmd_buffer))
            .list(cmdlist)
            .onCommand(cmd_callback);

    atm_lights.begin();

    exit_door.begin(10, true);
    xray_screen.begin(11, true);
}

void loop() {
    automaton.run();
}