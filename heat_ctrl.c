
/*
In Abhängigkeit der gemessenen Leistung soll die Hardware PWM die entsprechende Pulsweite einstellen.
Die PWM muss mit einer festen Frequenz zwischen 1kHz - 10kHz laufen - Vorgabe des Leistungsmoduls.
Der Heizstab hat eine maximale Leistung von 3 kW.


*/

/**
*
* Testjson: {"version":"0.3","data":{"tuples":[[1682965855511,468,1]],"uuid":"cba86870-dd59-11ed-81fe-8b6b00f83eed","from":1682965854509,"to":1682965855511,"min":[1682965855511,468],"max":[1682965855511,468],"average":468,"consumption":0.13,"rows":2}}
*/

#include <wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//WiringPI Pin 1 or GPIO 18
#define PWM_PIN01 1
#define MAX_LOAD_POWER 3000
#define PWM_CLK 4
#define MAIN_FREQ 192000000
#define PWM_RANGE 512


void pwm_setup(void);
int check_heatpower (int heat);
int heat2pwm (int heat);
char actual_power_json[] = "{\"version\":\"0.3\",\"data\":{\"tuples\":[[1682965855511,468,1]],\"uuid\":\"cba86870-dd59-11ed-81fe-8b6b00f83eed\",\"from\":1682965854509,\"to\":1682965855511,\"min\":[1682965855511,468],\"max\":[1682965855511,468],\"average\":468,\"consumption\":0.13,\"rows\":2}}"

void pwm_setup(void)
{
  if (wiringPiSetupGpio() == -1)
    exit (1) ;

  pinMode (PWM_PIN01, PWM_OUTPUT);
  pwmSetClock (MAIN_FREQ / PWM_RANGE / PWM_CLK);
  pwmSetRange (PWM_RANGE);

  return;
}


int check_heatpower (int heat)
{
  if (heat > MAX_LOAD_POWER)
  {
    return MAX_LOAD_POWER;
  }
  return heat;
}

int heat2pwm (int heat)
{
  heat = check_heatpower(heat);
  return heat * PWM_RANGE / MAX_LOAD_POWER;
}



int main()
{
  pwm_setup();
  for (int index=0; index<10; index++)
    {
      printf("%i\n", index);
      pwmWrite(PWM_PIN01, 256);
    }
  return 0;
}
