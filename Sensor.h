#ifndef _SENSOR_
#define _SENSOR_

#include "Arduino.h"

class Sensor {
  private:
    uint8_t pin;
    bool external;

  public:
    Sensor(const uint8_t _pin, const bool _external = false);

    const uint8_t getPin();
    uint16_t read();
};

#endif
