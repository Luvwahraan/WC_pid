#include "LinearFunction.h"
#include "PWMEntity.h""

LinearFunction::LinearFunction(coordonates const& A, coordonates const& B) {
  calculate(A,B);
}

LinearFunction::calculate(coordonates const& A, coordonates const& B) {
  a = (B.y - A.y) / (B.x - A.x);
  b = A.y - (a * A.x);

  //Serial.println( getStringFunction() );
}

const uint8_t LinearFunction::getValue(uint8_t const& temp) {
  return (uint8_t) floor( ( (a * temp) + b) + 0.5 );
}

const String LinearFunction::getStringFunction() {
  String fName = F("F(x)=");
  fName += a;
  fName += F("x + ");
  fName += b;
  return fName;
}

const void LinearFunction::printValues() {
  for (uint8_t i=ABSOLUTE_MIN_T; i<=ABSOLUTE_MAX_T; i++) {
    Serial.print(i);
    Serial.print(",");
    Serial.println(getValue(i));
  }
}
