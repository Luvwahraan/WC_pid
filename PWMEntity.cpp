#include "PWMEntity.h"



PWMEntity::PWMEntity(const uint8_t _pin) {
  pin = _pin;

  setMin( DEFAULT_MIN_T, DEFAULT_MIN_V, false );
  setMax( DEFAULT_MAX_T, DEFAULT_MAX_V, false);
  refreshFunction();

}

uint8_t PWMEntity::update(uint8_t const& temp) {
  analogWrite(pin, getPWMFunctionValue(temp) );
  return value;
}

uint8_t PWMEntity::getPWMFunctionValue(uint8_t const& temp) {
  value = f->getValue(temp);
  return value;
}

void PWMEntity::refreshFunction() {
  // Erase linear function in order to create new.
  delete f;
  coordonates A = {minTemp,minValue};
  coordonates B = {maxTemp,maxValue};
  f = new LinearFunction(A,B);
}

bool PWMEntity::setMin(uint8_t const& _t, uint8_t const& _v, bool const& refresh) {
  /*Serial.print("setMinTemp:");
  Serial.print(_t);
  Serial.print(", setMinValue:");
  Serial.println(_v);/**/

  setMinValue(_v, false);
  return setMinTemp(_t, refresh);;
}

bool PWMEntity::setMax(uint8_t const& _t, uint8_t const& _v, bool const& refresh) {
  /*Serial.print("setMaxTemp:");
  Serial.print(_t);
  Serial.print(", setMaxValue:");
  Serial.println(_v);/**/

  setMaxValue(_v, false);
  return setMaxTemp(_t, refresh);;
}

bool PWMEntity::setMinValue(uint8_t const& _v, bool const& refresh) {
  if ( _v == minValue ) return false;
  if ( _v < maxValue ) minValue = _v;

  if (refresh) refreshFunction();
  return true;
}

bool PWMEntity::setMaxValue(uint8_t const& _v, bool const& refresh) {
  if ( _v == maxValue ) return false;
  if ( _v > minValue ) maxValue = _v;

  if (refresh) refreshFunction();
  return true;
}

bool PWMEntity::setMinTemp(uint8_t const& _t, bool const& refresh) {
  bool ret = false;
  if ( _t < ABSOLUTE_MIN_T ) {
    minTemp = ABSOLUTE_MIN_T;
  }
  else if ( _t >= ABSOLUTE_MAX_T ) {
    minTemp = ABSOLUTE_MAX_T - 1;
  }
  else if ( _t <= maxTemp ) {
    minTemp = _t;
    ret = true;
  } else return ret;

  if (refresh) refreshFunction();
  return ret;
}

bool PWMEntity::setMaxTemp(uint8_t const& _t, bool const& refresh) {
  bool ret = false;
  if ( _t > ABSOLUTE_MAX_T ) {
    maxTemp = ABSOLUTE_MAX_T;
  }
  else if ( _t <= ABSOLUTE_MIN_T ) {
    maxTemp = ABSOLUTE_MIN_T + 1;
  }
  else if ( _t >= minTemp ) {
    maxTemp = _t;
    ret = true;
  } else return ret;

  if (refresh) refreshFunction();
  return ret;
}
