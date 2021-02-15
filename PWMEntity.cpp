#include "PWMEntity.h"
#include <string.h>


PWMEntity::PWMEntity(const uint8_t _pin) {
  pin = _pin;

  setMin( DEFAULT_MIN_T, DEFAULT_MIN_V, false );
  setMax( DEFAULT_MAX_T, DEFAULT_MAX_V, true);

}

void PWMEntity::update(uint8_t const& temp) {
  analogWrite(pin, getPWMFunctionValue(temp) );
}

uint8_t PWMEntity::getPWMFunctionValue(uint8_t const& temp) {
  return f->getValue(temp);
}

void PWMEntity::refreshFunction() {
  // Erase linear function in order to create new.
  delete f;
  coordonates A = {minTemp,minValue};
  coordonates B = {maxTemp,maxValue};
  f = new LinearFunction(A,B);
}

void PWMEntity::setMin(uint8_t const& _t, uint8_t const& _v, bool const& refresh) {
  if (_t == minTemp && _v == minValue ) return;

  setMinTemp(_t, false);
  setMinValue(_v, false);

  if (refresh) refreshFunction();
}

void PWMEntity::setMax(uint8_t const& _t, uint8_t const& _v, bool const& refresh) {
  if (_t == maxTemp && _v == maxValue ) return;

  setMaxTemp(_t, false);
  setMaxValue(_v, false);

  if (refresh) refreshFunction();
}

void PWMEntity::setMinValue(uint8_t const& _v, bool const& refresh) {
  if ( _v == minValue ) return;
  if ( _v < maxValue ) minValue = _v;

  if (refresh) refreshFunction();
}

void PWMEntity::setMaxValue(uint8_t const& _v, bool const& refresh) {
  if ( _v == maxValue ) return;
  if ( _v > minValue ) maxValue = _v;

  if (refresh) refreshFunction();
}

void PWMEntity::setMinTemp(uint8_t const& _t, bool const& refresh) {
  if ( _t < ABSOLUTE_MIN_T ) { minTemp = ABSOLUTE_MIN_T; }
  else if ( _t >= ABSOLUTE_MAX_T ) { minTemp = ABSOLUTE_MAX_T; }
  else if ( _t <= maxTemp ) minTemp = _t;

  if (refresh) refreshFunction();
}

void PWMEntity::setMaxTemp(uint8_t const& _t, bool const& refresh) {
  if ( _t > ABSOLUTE_MAX_T ) { maxTemp = ABSOLUTE_MAX_T; }
  else if ( _t < ABSOLUTE_MIN_T ) { maxTemp = ABSOLUTE_MIN_T; }
  else if ( _t >= minTemp ) maxTemp = _t;

  if (refresh) refreshFunction();
}
