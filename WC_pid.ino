#include "Arduino.h"
#include "config.h"
#include "Sensor.h"
#include "Dataset.h"
#include "PWMEntity.h"
#include <Commander.h>
#include "LinearFunction.h"



PWMEntity* PWMTab[MAX_PWM];
uint8_t nbPWMEntities = 0;

uint32_t wDelay = 1500;

#if USE_DS18B20 > 0
/*
 * DS18B20 OneWire temperature sensor.
 * See https://github.com/matmunk/DS18B20
 */
DS18B20 ds(AIR_SENSOR_PIN);
#endif




/*
 * Error messages
 */
bool printMissingParam(Commander &Cmdr) {
  Cmdr.println(F("Missing params. See help."));
  return false;
}

bool printBadPWMOut(Commander &Cmdr, uint8_t const& i) {
  Cmdr.print(F("There is no PWM out "));
  Cmdr.println(i);
  return false;
}

/*
 * End error msgs
 */




bool testPwmHandlers(Commander &Cmdr, uint8_t &value, uint8_t temp, uint8_t i) {
  // There is nb, temp and value?
  if ( !Cmdr.getInt(i) || !Cmdr.getInt(temp) || !Cmdr.getInt(value) ) {
    return printMissingParam(Cmdr);
  }

  if (i >= (nbPWMEntities) ) {
    return printBadPWMOut(Cmdr, i);
  }

  return true;
}

bool setPwmMinHandler(Commander &Cmdr){
  uint8_t value, temp, i;
  if ( testPwmHandlers( Cmdr, value, temp, i ) ) {
    PWMTab[i]->setMin(temp,value);
  }

  coordonates mins = PWMTab[i]->getMinimums();
  Cmdr.print("\nminTemp:");
  Cmdr.println(mins.x);
  Cmdr.print("minValue:");
  Cmdr.println(mins.y);
  return false;
}

bool setPwmMaxHandler(Commander &Cmdr){
  uint8_t value, temp, i;
  if ( testPwmHandlers( Cmdr, value, temp, i ) ) {
    PWMTab[i]->setMax(temp,value);
  }

  coordonates maxs = PWMTab[i]->getMaximums();
  Cmdr.print("\nmaxTemp:");
  Cmdr.println(maxs.x);
  Cmdr.print("maxValue:");
  Cmdr.println(maxs.y);
  return false;
}



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

/*
 * Serial commands handler.
 * See https://github.com/CreativeRobotics/Commander
 */
Commander cmd;
const commandList_t commands[] = {
  {"setPwmMin",       setPwmMinHandler,     "setPwmMin n minTemp minPwm, with n =~ [012]"},
  {"setPwmMax",       setPwmMaxHandler,     "setPwmMax n maxTemp maxPwm, with n =~ [012]"},
};

void setup() {
  Serial.begin(19200);
  while(!Serial){;} // Wait for the serial port to open (if using USB)

  // Printing blanks to clean up a little.
  for (int8_t i = 0; i < 10; i++) { Serial.println(); }

  // Initializing pwm tab
  initPWM();


  cmd.begin(&Serial, commands, sizeof(commands)); //start Commander on Serial
  cmd.commandPrompt(ON);                          //enable the command prompt
  cmd.echo(true);                                 //Echo incoming characters to theoutput port
  Serial.println("Hello: Type 'help' to get help");
  cmd.printCommandPrompt();

}




void loop() {
  uint32_t timer = millis();
  static Dataset WCData( new Sensor(WC_SENSOR_PIN, true), 3 );

  cmd.update();

  timer = millis() - timer;
  if (timer >= wDelay) {
#if USE_DS18B20 > 0
    // DS18B20 temperature
    while (ds.selectNext()) {
      Serial.print(ds.getTempC());
      Serial.print(",");
    }
#endif
    Data dat = WCData.getData();
    uint16_t value = dat.getValue();      // sensor value
    uint8_t temp = dat.getTemperature();  // tab temperature
    /*Serial.print(value);
    Serial.print(",");
    *
    Serial.println(temp);*/
  }


}
