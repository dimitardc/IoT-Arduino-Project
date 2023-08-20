#include <Arduino_FreeRTOS.h>
#include "semphr.h"

SemaphoreHandle_t  xMutex;

void setup()
{
  Serial.begin(9600);

  // create mutex 
  xMutex = xSemaphoreCreateMutex(); 

  //creating the task instances                                                   
  xTaskCreate(OutputTask,"Printer Task 1", 100,"Task 1 +++++++++++++++++++++ Task1 \r\n",1,NULL);  //smaller prio
  xTaskCreate(OutputTask,"Printer Task 2", 100,"Task 2 --------------------- Task2 \r\n",2,NULL);  //bigger  prio prints first 
}

void loop(){
  
}

//the task itself
void OutputTask(void *pvParameters){
  char *pcStringToPrint;
  pcStringToPrint = (char *)pvParameters;
  while(1)
  {
    printer(pcStringToPrint);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}


// this printer task send data to arduino serial monitor
// aslo it is shared resource between both instances of the tasks
void printer(const char* pcString){   
  xSemaphoreTake(xMutex, portMAX_DELAY);    // we take the mutex
  Serial.println(pcString);                 // send string to serial monitor
  xSemaphoreGive(xMutex);                   // release mutex to allow other task to use mutex
}
