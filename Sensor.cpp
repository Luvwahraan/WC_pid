#include "Sensor.h"

Sensor::Sensor(const uint8_t _pin, const bool _external) {
  pin = _pin;
  pinMode(pin, INPUT);

  //Serial.println("New sensor");

  if ( ! _external) {
    external = false;
  } else {
    analogReference(EXTERNAL);
  }

}

const uint8_t Sensor::getPin() { return pin; }


uint16_t Sensor::read() {
  return analogRead(pin);
}
