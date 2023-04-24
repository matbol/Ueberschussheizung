
/*
In Abhängigkeit der gemessenen Leistung soll die Hardware PWM die entsprechende Pulsweite einstellen. 
Die PWM muss mit einer festen Frequenz zwischen 1kHz - 10kHz laufen - Vorgabe des Leistungsmoduls.
Der Heizstab hat eine maximale Leistung von 3 kW.


*/

#include <wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define PWM_PIN01 = 1
#define MAX_LOAD_POWER = 3000
#define PWM_CLK = 4
#define MAIN_FREQ = 192000000
#define PWM_RANGE = 512


void pwm_setup(void);
int check_heatpower (int heat2pwm);
int heat2pwm (int heat2pwm);

void pwm_setup(void)
{
  if (wiringPiSetupGpio() == -1)
    exit (1) ;
    
  pinMode (PWM_PIN01, PWM_OUTPUT);
  pwmSetClock (MAIN_FREQ / PWM_RANGE / PWM_CLK);
  pwmSetRange (PWM_RANGE);
 
  return 0;
}


int check_heatpower (int heat2pwm)
{
  if (heat2pwm > MAX_LOAD_POWER)
  {
    return MAX_LOAD_POWER;
  }
  return heat2pwm;
}

int heat2pwm (int heat2pwm)
{
  heat2pwm = check_heatpower(heat2pwm);
  return heat2pwm / MAX_LOAD_POWER * PWM_RANGE;  
}



