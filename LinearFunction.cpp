#include "LinearFunction.h"

LinearFunction::LinearFunction(coordonates const& A, coordonates const& B) {
  calculate(A,B);
}

LinearFunction::calculate(coordonates const& A, coordonates const& B) {
  double a = (B.y - A.y) / (B.x - A.x);
  double b = A.y - (a * A.x);
}

const uint8_t LinearFunction::getValue(uint8_t const& temp) {
  return (a * temp) + b;
}
