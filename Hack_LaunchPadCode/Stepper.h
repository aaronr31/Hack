/*
 * Stepper.h
 *
 *  Created on: Sep 28, 2020
 *      Author: Russell
 */

#ifndef STEPPER_H_
#define STEPPER_H_

#include <stdint.h>
#include "msp.h"
#include "Utils.h"


/**
 * This code is mostly used from the Arduino Stepper library (https://github.com/arduino-libraries/Stepper)
 */
class Stepper
{
public:
    /**
     * Initializes a 28BYJ-48 stepper motor to run in half-step mode with pins from only odd pin groups.
     */
    Stepper(Pin pin1, Pin pin2, Pin pin3, Pin pin4);

    /**
     * Sets the speed in rpm.
     */
    void setSpeed(long speed);

    /**
     * Moves the motor by steps steps. Negative numbers reverse the direction.
     */
    void step(int steps);

    /**
     * Unpowers the coils.
     */
    void unpower();

protected:
    Pin pin1;
    Pin pin2;
    Pin pin3;
    Pin pin4;

    int direction;                  // Direction of rotation
    unsigned long stepDelay;        // delay between steps, in ms, based on speed
    int stepsPerRev;                   // total number of steps this motor can take
    int stepNumber;                 // which step the motor is on
    unsigned long lastStepTime;   // time stamp in us of when the last step was taken

    void stepMotor(int this_step);
};

#endif /* STEPPER_H_ */
