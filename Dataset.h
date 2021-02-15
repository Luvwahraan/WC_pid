#ifndef _DATASET_
#define _DATASET_

#include "Sensor.h"
#include "Arduino.h"
#include "Data.h"

#define MAX_SET 10

/*
 * Set of data with a sensor, to easily get data with smooth reading.
 */
class Dataset {
private:
  uint8_t set;
  Sensor* dataSensor;
  Data dataSet;

protected:
  // read some data and store average
  void processData();

 public:
  Dataset( Sensor*, uint8_t _set = MAX_SET );
  ~Dataset();
  Data getData();

};

#endif
