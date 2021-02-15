#ifndef _LINEAR_FUNCTION_
#define _LINEAR_FUNCTION_

#include "Arduino.h"

typedef struct {
  uint8_t x;
  uint8_t y;
} coordonates;

/*
 * Define a linear function with two coordonates ({minTemp,minPWM} and {maxTemp,maxPWM}),
 * and offer to get values on there function.
 * This class doesnt care if function is increasing or decreasing, so pay attention to min and max.
 */
class LinearFunction {
 private:
  double a;
  double b;

 protected:
  calculate(coordonates const&, coordonates const&);

 public:
  LinearFunction(coordonates const&,coordonates const&);
  const uint8_t getValue(uint8_t const&);
};

#endif
