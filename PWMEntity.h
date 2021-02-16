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

/*
 * Class to manage PWM duty cycle for fans or pump.
 *
 * Contains min and max temperature and duty cycle, and a function Object
 * related to temperature.
 * Defaults and absolutes values are related with sensors data table (see Data.h).
 */
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
  // Set linear function Object with min and max temp/values.
  void refreshFunction();

 public:
  PWMEntity(const uint8_t);

  // Apply duty cycle value on pin.
  void update(uint8_t const&);

  // set temp and value at same time, then refresh function.
  bool setMin(uint8_t const& _t, uint8_t const& _v, bool const& refresh = true);
  bool setMax(uint8_t const& _t, uint8_t const& _v, bool const& refresh = true);

  // just set one, then eventually refresh function
  bool setMinValue(uint8_t const& _v, bool const& refresh = true);
  bool setMaxValue(uint8_t const& _v, bool const& refresh = true);
  bool setMinTemp(uint8_t const& _t, bool const& refresh = true);
  bool setMaxTemp(uint8_t const& _t, bool const& refresh = true);

  inline const uint8_t getMinValue() { return minValue; }
  inline const uint8_t getMaxValue() { return maxValue; }
  inline const uint8_t getMinTemp() { return minTemp; }
  inline const uint8_t getMaxTemp() { return maxTemp; }
  inline const coordonates getMinimums() { return {minTemp,minValue}; }
  inline const coordonates getMaximums() { return {maxTemp,maxValue}; }

  uint8_t getPWMFunctionValue(uint8_t const&);
};

#endif
