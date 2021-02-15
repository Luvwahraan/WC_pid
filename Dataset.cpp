
#include "Sensor.h"
#include "Dataset.h"
#include "Data.h"
#include "Arduino.h"


Dataset::Dataset( Sensor* _sensor, uint8_t _set ) {
  set = _set;
  dataSensor = _sensor;
}


Dataset::~Dataset() {
  delete dataSensor;
}

Data Dataset::getData() {
  processData();
  return dataSet;
}


void Dataset::processData() {
  uint16_t value = 0;
  uint32_t vTime = millis();

  // Read some data
  for (uint8_t i=0; i < set; i++) {
    value += dataSensor->read();
    delay(50);
  }

  // calc average value
  dataSet = Data(value,set);
  dataSet /= set;

  // associate time
  dataSet.setTime( millis() );

}
