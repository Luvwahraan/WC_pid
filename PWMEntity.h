#ifndef _PWMENTITY_
#define _PWMENTITY_

#include "Arduino.h"
#include "LinearFunction.h"

#define DEFAULT_MIN_V   80
#define DEFAULT_MAX_V   200

#define DEFAULT_MIN_T   25
#define DEFAULT_MAX_T   45

#define ABSOLUTE_MIN_T  12
#define ABSOLUTE_MAX_T  50

class PWMEntity {
 private:
  uint8_t pin;
  uint8_t value;
  uint8_t minValue;
  uint8_t maxValue;
  uint8_t minTemp;
  uint8_t maxTemp;
  LinearFunction* f;

 protected:
  void searchLinearFunction();
  void refreshFunction();

 public:
  PWMEntity(const uint8_t);

  // set temp and value at same time, then refresh function.
  void setMin(uint8_t const&,uint8_t const&);
  void setMax(uint8_t const&,uint8_t const&);

  // just set one, then eventually refresh function
  void setMinValue(uint8_t const& _v, bool const& refresh = true);
  void setMaxValue(uint8_t const& _v, bool const& refresh = true);
  void setMinTemp(uint8_t const& _t, bool const& refresh = true);
  void setMaxTemp(uint8_t const& _t, bool const& refresh = true);

  const uint8_t getMinValue() { return minValue; }
  const uint8_t getMaxValue() { return maxValue; }
  const uint8_t getMinTemp() { return minTemp; }
  const uint8_t getMaxTemp() { return maxTemp; }
  const coordonates getMinimums() { return {minTemp,minValue}; }
  const coordonates getMaximums() { return {maxTemp,maxValue}; }

  uint8_t getPWMFunctionValue(uint8_t const&);
};

#endif
