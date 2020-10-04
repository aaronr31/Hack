#ifndef UTILS_H_
#define UTILS_H_

#include <stdint.h>
#include "msp.h"

enum PinMode {OUTPUT, INPUT, INPUT_PULLUP};
enum DigitalIO {LOW, HIGH};


/**
 * Contains various helper methods to make certain operations simpler.
 *
 * Each pin manipulation method is overloaded to handle both odd and even pin ports.
 */
class Utils
{
public:
    /**
     * Writes HIGH or LOW to the pin identified by the pinGroup and pin (index).
     */
    static void digitalWrite(DIO_PORT_Odd_Interruptable_Type *pinGroup, uint8_t pin, enum DigitalIO output) {
        pin = 1 << pin;
        pinGroup->OUT = (pinGroup->OUT & (~pin)) | (pin * output);
    }


    /**
     * Writes HIGH or LOW to the pin identified by the pinGroup and pin (index).
     */

    static void digitalWrite(DIO_PORT_Even_Interruptable_Type *pinGroup, uint8_t pin, enum DigitalIO output) {
        pin = 1 << pin;
        pinGroup->OUT = (pinGroup->OUT & (~pin)) | (pin * output);
    }


    /**
     * Reads HIGH or LOW from the pin identified by the pinGroup and pin (index).
     */
    static enum DigitalIO digitalRead(DIO_PORT_Odd_Interruptable_Type *pinGroup, uint8_t pin) {
        pin = 1 << pin;
        if (pinGroup->IN & pin)
        {
            return HIGH;
        }
        return LOW;
    }


    /**
     * Reads HIGH or LOW from the pin identified by the pinGroup and pin (index).
     */
    static enum DigitalIO digitalRead(DIO_PORT_Even_Interruptable_Type *pinGroup, uint8_t pin) {
        pin = 1 << pin;
        if (pinGroup->IN & pin)
        {
            return HIGH;
        }
        return LOW;
    }


    /**
     * Sets the PinMode (OUTPUT, INPUT, INPUT_PULLUP) of the pin identified by the pinGroup and pin (index).
     */
    static void pinMode(DIO_PORT_Even_Interruptable_Type *pinGroup, uint8_t pin, enum PinMode mode) {
        pin = 1 << pin;
        pinGroup->SEL0 &= ~pin;
        pinGroup->SEL1 &= ~pin;
        switch (mode)
        {
        case OUTPUT:
            pinGroup->DIR |= pin;
            break;
        case INPUT:
            pinGroup->REN &= ~pin;
            pinGroup->DIR &= ~pin;
            pinGroup->OUT &= ~pin;
            pinGroup->IN &= ~pin;
            break;
        case INPUT_PULLUP:
            pinGroup->REN |= pin;
            pinGroup->DIR &= ~pin;
            pinGroup->OUT |= pin;
        default:
            break;
        }
    }


    /**
     * Sets the PinMode (OUTPUT, INPUT, INPUT_PULLUP) of the pin identified by the pinGroup and pin (index).
     */
    static void pinMode(DIO_PORT_Odd_Interruptable_Type *pinGroup, uint8_t pin, enum PinMode mode) {
        pin = 1 << pin;
        pinGroup->SEL0 &= ~pin;
        pinGroup->SEL1 &= ~pin;
        switch (mode)
        {
        case OUTPUT:
            pinGroup->DIR |= pin;
            break;
        case INPUT:
            pinGroup->REN &= ~pin;
            pinGroup->DIR &= ~pin;
            pinGroup->OUT &= ~pin;
            pinGroup->IN &= ~pin;
            break;
        case INPUT_PULLUP:
            pinGroup->REN |= pin;
            pinGroup->DIR &= ~pin;
            pinGroup->OUT |= pin;
        default:
            break;
        }
    }

    /**
     *  Initialize SysTick with busy wait running at bus clock.
     */
    static void SysTick_Init(void){
      SysTick->LOAD = 0x00FFFFFF;           // maximum reload value
      SysTick->CTRL = 0x00000005;           // enable SysTick with no interrupts
    }

    /**
     * Wait for a specified delay. The SysTick clock is 48 MHz.
     */
    static void SysTickWait(uint32_t delay) {
        SysTick_Init();
        if(delay <= 1){
            // without this step:
            // if delay == 0, this function will wait 0x00FFFFFF cycles
            // if delay == 1, this function will never return (because COUNTFLAG is set on 1->0 transition)
            return;                   // do nothing; at least 1 cycle has already passed anyway
          }
          SysTick->LOAD = (delay - 1);// count down to zero
          SysTick->VAL = 0;          // any write to CVR clears it and COUNTFLAG in CSR
          while(( SysTick->CTRL&0x00010000) == 0){};
    }

    /**
     * Wait for a specified amount of microseconds.
     */
    static void SysTickWaitMicros(uint32_t delay) {
        SysTickWait(delay * 48);
    }

    /**
     * Wait for a specified amount of milliseconds.
     */
    static void SysTickWaitMillis(uint32_t delay) {
        SysTickWaitMicros(delay * 1000);
    }

    /**
     * Wait for a specified amount of seconds.
     */
    static void SysTickWaitSeconds(uint32_t delay) {
        SysTickWaitMillis(delay * 1000);
    }
};



/**
 * The Pin class makes reading from and writing to pins even simpler than using the helper methods.
 *
 * The two constructors handle the use of the two types of ports, and the setMode, write, and read methods create functionality through the Utils methods.
 */
class Pin
{
public:
    Pin(DIO_PORT_Even_Interruptable_Type* pinGroup, uint8_t pinIndex) :
            pinGroupEven(pinGroup), pinIndex(pinIndex), pinGroupOdd(0) {};
    Pin(DIO_PORT_Odd_Interruptable_Type* pinGroup, uint8_t pinIndex) :
            pinGroupOdd(pinGroup), pinIndex(pinIndex), pinGroupEven(0) {};

    /**
     * Sets the PinMode (OUTPUT, INPUT, INPUT_PULLUP) of this Pin.
     */
    void setMode(enum PinMode pinMode) {
        if (pinGroupEven) {
            Utils::pinMode(pinGroupEven, pinIndex, pinMode);
        } else if (pinGroupOdd) {
            Utils::pinMode(pinGroupOdd, pinIndex, pinMode);
        }
    }

    /**
     * Writes HIGH or LOW to this Pin.
     */
    void write(enum DigitalIO output) {
        if (pinGroupEven) {
            Utils::digitalWrite(pinGroupEven, pinIndex, output);
        } else if (pinGroupOdd) {
            Utils::digitalWrite(pinGroupOdd, pinIndex, output);
        }

    }

    /**
     * Reads HIGH or LOW from this Pin.
     */
    enum DigitalIO read() {
        if (pinGroupEven) {
            return Utils::digitalRead(pinGroupEven, pinIndex);
        } else if (pinGroupOdd) {
            return Utils::digitalRead(pinGroupOdd, pinIndex);
        }
        return LOW;
    }

protected:
    DIO_PORT_Even_Interruptable_Type* pinGroupEven;
    DIO_PORT_Odd_Interruptable_Type* pinGroupOdd;
    uint8_t pinIndex;
};

#endif /* UTILS_H_ */
