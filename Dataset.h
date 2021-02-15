#ifndef _DATASET_
#define _DATASET_

#include "Sensor.h"
#include "Arduino.h"
#include "Data.h"

#define MAX_SET 10


class Dataset {
  private:
    uint8_t set;
    Sensor* dataSensor;
    Data dataSet;

  protected:
    void processData();

  public:
    Dataset( Sensor*, uint8_t _set = MAX_SET );
    ~Dataset();
    Data getData();

};

#endif
