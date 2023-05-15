
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

//WiringPI Pin 1 or GPIO 18
#define PWM_PIN01 1
#define MAX_LOAD_POWER 3000
#define PWM_CLK 4
#define MAIN_FREQ 192000000
#define PWM_RANGE 512


void pwm_setup(void);
int check_heatpower (int heat);
int heat2pwm (int heat);

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

char *json_str14 = "{\"version\":\"0.3\",\"data\":{\"tuples\":[[1682965855511,468,1]],\"uuid\":\"cba86870-dd59-11ed-81fe-8b6b00f83eed\",\"from\":1682965854509,\"to\":1682965855511,\"min\":[1682965855511,468],\"max\":[1682965855511,468],\"average\":468,\"consumption\":0.13,\"rows\":2}}";

static bool flag1, flag2;
static int count;
static int intstore[4], intcount;
static int tuples[3];
int status =0;
static int tuples_count;

static char json_inner_name_string_dst[256];
static int inner_value;

//static const char *json_str14 = "{\"name\":\"wobble\",\"value\":{\"inner\":23}}";
const struct json_attr_t json_inner_int_value[] = {
    {"tuples", t_integer,
         .addr.integer = &inner_value},
    {NULL},
};

///
static const struct json_attr_t json_inner_att[] = {
    {"tuples",      t_array,	.addr.array.element_type = t_integer,
				.addr.array.arr.integers = tuples,
				.addr.array.maxlen = 3,
				.addr.array.count = &tuples_count
    }
};


static const struct json_array_t json_array_11 = {
    .element_type = t_integer,
    .arr.integers.store = intstore,
    .count = &intcount,
    .maxlen = sizeof(intstore)/sizeof(intstore[0]),
};


static const struct json_attr_t json_object_14[] = {
    {"data", t_string,
        .addr.string = json_inner_name_string_dst,
        .len = sizeof(json_inner_name_string_dst)},
    {"tuples", t_array,
         //.addr.attrs = json_inner_int_value},
    	.addr.attrs = json_inner_att},
	{NULL},
    {"uuid", t_ignore},
    {"from", t_ignore},
    {"to", t_ignore},
    {"min", t_ignore},
    {"max", t_ignore},
    {"average", t_ignore},
    {"consumption", t_ignore},
    {"rows", t_ignore}
};



int main()
{
  status = json_read_object(json_str14, json_object_14, NULL);
 
//  json_read_array(json_str14, &json_array_11, NULL);
  printf("%i\n%s\n", tuples[1], status);

  return 0;
}
