
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
//#include "microjson/mjson.h"

#include <unistd.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <regex.h>

//WiringPI Pin 1 or GPIO 18
#define PWM_PIN01 1
#define MAX_LOAD_POWER 3000
#define PWM_CLK 3
#define MAIN_FREQ 192000000
#define PWM_RANGE 1024
#define POWER_OFFSET 300

#define CTRL_KP 1
#define CTRL_KI 0
#define CTRL_KD 0
#define CTRL_TA 1


void pwm_setup(void);
int check_heatpower (int heat);
int heat2pwm (int heat);
//char *source = "{\"version\":\"0.3\",\"data\":{\"tuples\":[[1682965855511,468,1]],\"uuid\":\"cba86870-dd59-11ed-81fe-8b6b00f83eed\",\"from\":1682965854509,\"to\":1682965855511,\"min\":[1682965855511,468],\"max\":[1682965855511,468],\"average\":468,\"consumption\":0.13,\"rows\":2}}";
const char * regexString =  "tuples\": \[ \[ [0-9]*, (.[0-9]*)";

void pwm_setup(void)
{
  if (wiringPiSetup() == -1)
    exit (1) ;

  pinMode (PWM_PIN01, PWM_OUTPUT);
  pwmSetMode (PWM_MODE_MS);  //https://raspberrypi.stackexchange.com/questions/4906/control-hardware-pwm-frequency
  pwmSetClock (PWM_CLK);
  pwmSetRange (PWM_RANGE);

  return;
}


int pid_ctrl (int error)
{
  static int esum = 0;
  static int ealt = 0;
  int y = 0;
  if (error < 3000 && error > 0)
  {
    esum = esum + error;   
  }
  
  y = CTRL_KP * error 
    + CTRL_KI * CTRL_TA * esum 
    + CTRL_KD/CTRL_TA * (error - ealt);
  ealt = e;

}


int check_heatpower (int heat)
{
  if (heat >= 0)
	{
	return 0;
	}
  else
  {
  heat = -heat;
  heat = heat + POWER_OFFSET;
  }
  if (heat > MAX_LOAD_POWER)
  {
    return (MAX_LOAD_POWER);
  }
  return (heat);
}

int heat2pwm (int heat)
{
  heat = check_heatpower(heat);
  return heat * PWM_RANGE / MAX_LOAD_POWER;
}

int extract_json(const char *regex, char *String);


struct MemoryStruct {
  char *memory;
  size_t size;
};


static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    printf("not enough memory (realloc returned NULL)\n");    return 0;
	}

  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
  return realsize;
}




int main()
{
  pwm_setup();
  int measured_power = 0;
  int pwm_value = 0;
  for (;;)
    {

	 CURL *curl_handle;
	 CURLcode res;

	struct MemoryStruct chunk;
	chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */
	chunk.size = 0;    /* no data at this point */
	curl_global_init(CURL_GLOBAL_ALL);
	curl_handle = curl_easy_init(); 
	curl_easy_setopt(curl_handle, CURLOPT_URL, "http://192.168.178.60:8081/cba86870-dd59-11ed-81fe-8b6b00f83eed");
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
	curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");


	res = curl_easy_perform(curl_handle);
	if(res != CURLE_OK) {
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
		curl_easy_strerror(res));
	}
    else {
		measured_power = extract_json(regexString, chunk.memory);
		measured_power =  pid_ctrl(measured_power);
    pwm_value = heat2pwm(measured_power);
//		printf("Measured Power, PWM:\t%i\t%i\n\n", measured_power, pwm_value);

		pwmWrite(PWM_PIN01, pwm_value);
	}
	curl_easy_cleanup(curl_handle);
	free(chunk.memory);
	curl_global_cleanup();


        usleep(500000);	
}
	return 0;
}

















/*
* Quelle: https://gist.github.com/ianmackinnon/3294587
*/
int extract_json(const char *regex, char *String){
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
  cursor = String;
  if (regexec(&regexCompiled, cursor, maxGroups, groupArray, 0))
  {
      return 1;
  }
    char *result ="";
    int num_result = 0;
    char cursorCopy[strlen(cursor) + 1];
    strcpy(cursorCopy, cursor);
    cursorCopy[groupArray[1].rm_eo] = 0;
    result = cursorCopy + groupArray[1].rm_so;
//    printf("Extract Json:\t%s\n", result);
    num_result = atoi(result);   



    regfree(&regexCompiled);

    return num_result;
 
}
