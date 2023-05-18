
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
#include "microjson/mjson.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <regex.h>

//WiringPI Pin 1 or GPIO 18
#define PWM_PIN01 1
#define MAX_LOAD_POWER 3000
#define PWM_CLK 4
#define MAIN_FREQ 192000000
#define PWM_RANGE 512


void pwm_setup(void);
int check_heatpower (int heat);
int heat2pwm (int heat);
char *source = "{\"version\":\"0.3\",\"data\":{\"tuples\":[[1682965855511,468,1]],\"uuid\":\"cba86870-dd59-11ed-81fe-8b6b00f83eed\",\"from\":1682965854509,\"to\":1682965855511,\"min\":[1682965855511,468],\"max\":[1682965855511,468],\"average\":468,\"consumption\":0.13,\"rows\":2}}";
const char * regexString =  "tuples\":\[\[[0-9]*,([0-9]*)";
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

int extract_json(const char *regex, const char *String);

int main()
{
  pwm_setup();
  int measured_power = 0;
  for (;;)
    {
//      printf("%i\n", index);
    
      measured_power = extract_json(regexString, actual_json_string);
      pwmWrite(PWM_PIN01, 200);
    }
  return 0;
}


















/*
* Quelle: https://gist.github.com/ianmackinnon/3294587
*/
int extract_json(const char *regex, const char *String){
  size_t maxMatches = 1;
  size_t maxGroups = 2;

  regex_t regexCompiled;
  regmatch_t groupArray[maxGroups];
  unsigned int m;
  char * cursor;
  if (regcomp(&regexCompiled, regexString, REG_EXTENDED))
    {
      printf("Could not compile regular expression.\n");
      return 1;
    };

  m = 0;
  cursor = source;
  if (regexec(&regexCompiled, cursor, maxGroups, groupArray, 0))
  {
      return 1;
  }
    char *result ="";
    int = num_result = 0;
    char cursorCopy[strlen(cursor) + 1];
    strcpy(cursorCopy, cursor);
    cursorCopy[groupArray[1].rm_eo] = 0;
    result = cursorCopy + groupArray[1].rm_so;
    num_result = atoi(result);   



    regfree(&regexCompiled);

    return num_result;
 
}
