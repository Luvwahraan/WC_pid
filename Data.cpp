#include "Data.h"
#include "Arduino.h"

Data::Data() {
  init(0, millis());
}
Data::Data(uint16_t const& _v) {
  Data();
  init(_v, millis());
}
Data::Data(uint16_t const& _v, uint32_t const& _t) {
  Data();
  init(_v, _t);
}


void Data::setValue(uint16_t const& _v) { value = _v; }
void Data::setTime(uint32_t const& _t) { time = _t; }

void Data::init(uint16_t const& _v, uint32_t const& _t) {
  setValue(_v);
  setTime(_t);
}


const uint16_t Data::getValue() { return value; }
const uint32_t Data::getTime() { return time; }

const bool Data::isValid() {
  if ( getValue() > 0 && getTime() > 0 ) return true;
  return false;
}


void Data::print() {
  Serial.print( getValue() );
  Serial.print( ',' );
  Serial.print( getTemperature() );
  Serial.print( ',' );
  Serial.println( getTime() );
}


Data Data::operator-(const Data& A) {
  Data nData(0,0);
  uint16_t v = this->getValue() - A.getValue();
  uint32_t t = this->getTime() - A.getTime();
  nData.setValue( v );
  nData.setTime( t );
  return nData;
}


void Data::operator+=(Data const& A) {
  value += A.getValue();
  time += A.getTime();
}

void Data::operator/=(uint8_t const& A) {
  value /= A;
  time /= A;
}


uint8_t Data::getTemperature() { return getTemperature( getValue() ); };
uint8_t Data::getTemperature(uint16_t const& value) {
  // Tab's index is sensor value. See *TempTab*.csv
  uint16_t index = 0;

  if (value < MINSENSOR_VALUE) {
    index = 0;
  }
  else if (value > MAXSENSOR_VALUE) {
    index = MAXSENSOR_VALUE - MINSENSOR_VALUE;
  } else {
    index = value - MINSENSOR_VALUE;
  }

  return pgm_read_word_near( &temperature[index] );
}
