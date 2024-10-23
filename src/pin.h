
#include <Arduino.h>

#ifndef PIN_H
#define PIN_H

class Pin
{
public:
    int pinNumber;
    String pinName;
    String pinState;

    Pin(int pinNumber, String pinName, String pinState)
    {
        this->pinNumber = pinNumber;
        this->pinName = pinName;
        this->pinState = pinState;
    }

    void setPinState(String pinState)
    {
        this->pinState = pinState;
    }

    bool isPinOn()
    {
        return this->pinState == "ON";
    }

    void setPinOFF()
    {
        this->pinState = "OFF";
    }
};

#endif
