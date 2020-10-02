/*
 * Stepper.cpp
 *
 *  Created on: Sep 28, 2020
 *      Author: Russell
 */

#include <Stepper.h>

Stepper::Stepper(Pin pin1, Pin pin2, Pin pin3, Pin pin4) :
    pin1(pin1), pin2(pin2), pin3(pin3), pin4(pin4), direction(0), stepNumber(0), lastStepTime(0), stepsPerRev(2048)
{
    pin1.setMode(OUTPUT);
    pin2.setMode(OUTPUT);
    pin3.setMode(OUTPUT);
    pin4.setMode(OUTPUT);

    unpower();
}

void Stepper::setSpeed(long speed) {
    stepDelay = 60L * 1000L * 1000L / (stepsPerRev * speed);
}

void Stepper::step(int steps) {
    int stepsLeft = abs(steps);  // how many steps to take

    // determine direction based on whether steps_to_mode is + or -:
    if (steps > 0) { direction = 1; }
    if (steps < 0) { direction = 0; }


    // decrement the number of steps, moving one step each time:
    while (stepsLeft > 0)
    {
        // get the timeStamp of when you stepped:
//        lastStepTime = now;
        // increment or decrement the step number,
        // depending on direction:
        if (direction == 1) {
            stepNumber++;
            if (stepNumber == stepsPerRev) {
                stepNumber = 0;
            }
        } else {
            if (stepNumber == 0) {
                stepNumber = stepsPerRev;
            }
            stepNumber--;
        }
        // decrement the steps left:
        stepsLeft--;

        // step the motor to step number 0, 1, ..., {3 or 10}
        stepMotor(this->stepNumber % 4);
        Utils::SysTickWaitMicros(stepDelay);
    }
}

void Stepper::stepMotor(int thisStep) {
    switch (thisStep) {
        case 0:  // 1010
            pin1.write(HIGH);
            pin2.write(LOW);
            pin3.write(HIGH);
            pin4.write(LOW);
            break;
        case 1:  // 0110
            pin1.write(LOW);
            pin2.write(HIGH);
            pin3.write(HIGH);
            pin4.write(LOW);
            break;
        case 2:  // 0101
            pin1.write(LOW);
            pin2.write(HIGH);
            pin3.write(LOW);
            pin4.write(HIGH);
            break;
        case 3:  // 1001
            pin1.write(HIGH);
            pin2.write(LOW);
            pin3.write(LOW);
            pin4.write(HIGH);
            break;
    }
}

void Stepper::unpower() {
    pin1.write(LOW);
    pin2.write(LOW);
    pin3.write(LOW);
    pin4.write(LOW);

}
