#ifndef _CONF_
#define _CONF_

#include "Arduino.h"


#define USE_DS18B20 1
#define USE_PWM_PUMP 0
#define USE_PWM_FAN0 1
#define USE_PWM_FAN1 1

#define MAX_PWM 3



/*
 * PWM pins definitions
 */

#if USE_PWM_FAN0 > 0
#define PWM0_PIN 13 // D10
#endif

#if USE_PWM_FAN1 > 0
#define PWM1_PIN 14 // D11
#endif

#if USE_PWM_PUMP > 0
#define PWM2_PIN 12 // D9
#endif

/*
 * End PWN pins defs
 */





/*
 * SENSORS pins definitions
 */

// Random thermistor
#define WC_SENSOR_PIN A7

// DS18B20
#if USE_DS18B20 > 0
#include <DS18B20.h>
#define ONEWIRE_SEARCH 0
#define CASE_SENSOR_PIN 5 // D5
#define AIR_SENSOR_PIN 6 // D6
#endif

/*
 * End SENSORS pins defs
 */


#endif
