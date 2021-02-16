#include "Arduino.h"
#include "config.h"
#include "Sensor.h"
#include "Dataset.h"
#include "PWMEntity.h"
#include "LinearFunction.h"


/*
 * See config.h for config
 */


PWMEntity* PWMTab[MAX_PWM];
uint8_t nbPWMEntities = 0;

uint32_t wDelay = 2000;

#if USE_DS18B20 > 0
/*
 * DS18B20 OneWire temperature sensor.
 * See https://github.com/matmunk/DS18B20
 */
DS18B20 ds(AIR_SENSOR_PIN);
#endif



/*
 * Counts how many PWM are activated
 */
void getNbPWM() {
  nbPWMEntities = 0;
#if USE_PWM_FAN0 > 0
  nbPWMEntities++;
#endif
#if USE_PWM_FAN1 > 0
  nbPWMEntities++;
#endif
  #if USE_PWM_PUMP > 0
  nbPWMEntities++;
#endif
}

/*
 * Fills PWMEntity tab
 */
void initPWM() {
  getNbPWM();

  uint8_t i=0;
  do {
#if USE_PWM_FAN0 > 0
    PWMTab[i] = new PWMEntity(PWM0_PIN);
    i++;
#endif
#if USE_PWM_FAN1 > 0
    PWMTab[i] = new PWMEntity(PWM1_PIN);
    i++;
#endif
#if USE_PWM_PUMP > 0
    PWMTab[i] = new PWMEntity(PWM2_PIN);
    i++;
#endif
  } while ( i < nbPWMEntities );
}

void setup() {
  Serial.begin(19200);

  // Printing blanks to clean up a little.
  for (int8_t i = 0; i < 10; i++) { Serial.println(); }

  // Initializing pwm tab
  Serial.println(F("Init PWM entities."));
  initPWM();
}



uint32_t timer = millis();
void loop() {
  static Dataset WCData( new Sensor(WC_SENSOR_PIN, true), 3 );

  timer = millis() - timer;
  if (timer >= wDelay) {
#if USE_DS18B20 > 0
    // DS18B20 temperature
    while (ds.selectNext()) {
      Serial.print("AirTemp:");
      Serial.print(ds.getTempC());
      Serial.print(",");
    }
#endif
    Data dat = WCData.getData();
    uint16_t value = dat.getValue();      // sensor value
    uint8_t temp = dat.getTemperature();  // tab temperature
    Serial.print("Sensor:");
    Serial.print(value);
    Serial.print(",Temp:");
    Serial.println(temp);/**/

    timer = millis();
  }


}
