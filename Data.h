#ifndef _DATA_
#define _DATA_

#include "Arduino.h"

#define MINSENSOR_VALUE 426
#define MAXSENSOR_VALUE 912
const uint8_t temperature[] PROGMEM = {
  50,  50,  50,  50,  50,  49,  49,  49,  49,  49,  49,  49,  49,  48,  48,
  48,  48,  48,  48,  48,  48,  48,  48,  48,  48,  47,  47,  47,  47,  47,
  47,  47,  47,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  45,
  45,  45,  45,  45,  45,  45,  45,  45,  45,  44,  44,  44,  44,  44,  44,
  44,  44,  44,  44,  44,  44,  44,  43,  43,  43,  43,  43,  43,  43,  42,
  42,  42,  42,  42,  42,  42,  41,  41,  41,  41,  41,  41,  41,  41,  41,
  41,  41,  41,  41,  41,  41,  41,  41,  41,  41,  41,  41,  40,  40,  40,
  40,  40,  40,  40,  40,  40,  40,  39,  39,  39,  39,  39,  39,  39,  39,
  39,  39,  39,  39,  39,  39,  39,  39,  38,  38,  38,  38,  38,  38,  38,
  38,  38,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,  37,
  37,  36,  36,  36,  36,  36,  36,  36,  36,  36,  36,  36,  36,  36,  35,
  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,
  34,  34,  34,  34,  34,  34,  34,  34,  34,  34,  34,  34,  34,  33,  33,
  33,  33,  33,  33,  33,  33,  33,  33,  33,  33,  33,  32,  32,  32,  32,
  32,  32,  32,  32,  32,  32,  32,  32,  31,  31,  31,  31,  31,  31,  31,
  31,  31,  31,  31,  31,  31,  30,  30,  30,  30,  30,  30,  30,  30,  30,
  30,  30,  30,  30,  30,  29,  29,  29,  29,  29,  29,  29,  29,  29,  29,
  29,  29,  29,  28,  28,  28,  28,  28,  28,  28,  28,  28,  28,  28,  28,
  28,  28,  27,  27,  27,  27,  27,  27,  27,  27,  27,  27,  27,  27,  27,
  27,  26,  26,  26,  26,  26,  26,  26,  26,  26,  26,  26,  26,  26,  25,
  25,  25,  25,  25,  25,  25,  25,  25,  25,  25,  25,  25,  24,  24,  24,
  24,  24,  24,  24,  24,  24,  24,  24,  24,  24,  22,  22,  22,  21,  22,
  22,  23,  23,  21,  20,  20,  20,  20,  20,  20,  20,  20,  20,  20,  20,
  20,  20,  20,  20,  20,  20,  21,  21,  21,  21,  21,  21,  21,  21,  21,
  21,  21,  21,  21,  21,  21,  21,  21,  20,  20,  20,  20,  20,  20,  20,
  20,  20,  20,  20,  20,  20,  19,  19,  19,  19,  19,  19,  19,  19,  19,
  19,  19,  19,  19,  19,  18,  18,  18,  18,  18,  18,  18,  18,  18,  18,
  18,  18,  18,  18,  18,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,
  17,  17,  17,  17,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,  16,
  16,  16,  16,  16,  16,  16,  16,  16,  15,  15,  15,  15,  15,  15,  15,
  15,  15,  15,  15,  15,  15,  15,  15,  15,  14,  14,  14,  14,  14,  14,
  14,  14,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,  13,
  13,  13,  12,  12,  12,  12,  12
};

/*
 * This class links sensors values and temperatures thanks to a data table.
 *
 * The data table is limited and for a particular sensor and assembly (here with
 * thermistor from 12 to 50°C, readed from a digital pin with ~4V max).
 * Please create a table related to your assembly.
 */
class Data {
  private:
    uint16_t value;
    uint32_t time;
  public:
    Data();
    Data(uint16_t const&);
    Data(uint16_t const&, uint32_t const&);

    void setValue(uint16_t const&);
    void setTime(uint32_t const&);

    void init(const uint16_t&, const uint32_t&);

    uint8_t getTemperature(uint16_t const&);
    uint8_t getTemperature();
    const uint16_t getValue();
    const uint32_t getTime();

    const bool isValid();

    Data operator-(const Data&);
    void operator+=(Data const&);
    void operator/=(uint8_t const&);

    void print();


};

#endif
