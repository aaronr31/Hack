#include "msp.h"
#include "Utils.h"
#include "Stepper.h"
#include <stdio.h>


#define HANDLE_HOLD_TIME 10
#define HANDLE_TURN_STEPS 1304
#define STEPPER_SPEED 80
#define ZEROING_MULTIPLIER 1

void setup(void);
void loop(void);
void zero(void);
void turnHandle(void);


Stepper* stepper;

Pin RED_LED = Pin(P1, 0);
Pin S1 = Pin(P1, 1);
Pin S2 = Pin(P1, 4);
Pin PHOTON_IN = Pin(P6, 6);
Pin PHOTON_OUT = Pin(P6, 7);
Pin S_EXT = Pin(P3, 6);


void setup(void) {
    RED_LED.setMode(OUTPUT);
    S1.setMode(INPUT_PULLUP);
    S2.setMode(INPUT_PULLUP);
    PHOTON_IN.setMode(INPUT);
    PHOTON_OUT.setMode(OUTPUT);
    S_EXT.setMode(INPUT_PULLUP);

    stepper = new Stepper(Pin(P2, 3), Pin(P3, 5), Pin(P5, 1), Pin(P3, 7));
    stepper->setSpeed(STEPPER_SPEED);

    zero();

}

void loop(void) {
    if (PHOTON_IN.read() == HIGH) {
        turnHandle();
    } else if (S1.read() == LOW) {
        RED_LED.write(HIGH);
        stepper->step(1);
    } else if (S2.read() == LOW) {
        RED_LED.write(HIGH);
        stepper->step(-1);
    } else {
        RED_LED.write(LOW);
        stepper->unpower();
    }
}

void zero(void) {
    // TODO turn motor back until external switch is pressed
    while (S_EXT.read() == HIGH) {
        if (abs(ZEROING_MULTIPLIER) < 1) {
            stepper->step(-ZEROING_MULTIPLIER / abs(ZEROING_MULTIPLIER));
        } else {
            stepper->step(-ZEROING_MULTIPLIER);
        }
    }
    stepper->unpower();
}

void turnHandle(void) {
    stepper->step(HANDLE_TURN_STEPS);

    PHOTON_OUT.write(HIGH);
    Utils::SysTickWaitMillis(250);
    PHOTON_OUT.write(LOW);

    Utils::SysTickWaitSeconds(HANDLE_HOLD_TIME);

    stepper->step(-HANDLE_TURN_STEPS);

    zero();
}


/**
 * main.c
 */
void main(void)
{
    setup();

    while (1) {
        loop();
    }
}
