#include <Arduino_FreeRTOS.h>
#include "queue.h"

QueueHandle_t xStringQueue;
int timer1_counter ;


void setup(){
  Serial.begin(9600);
  xTaskCreate(vStringPrinter," String Printer", 100, NULL, 1,NULL);     
  xStringQueue  = xQueueCreate(5,sizeof(char *));       //create queue with 5 slots
  InterruptInit();                                      //interrupt cant be triggered without this
}

void loop(){
  
}

void vStringPrinter(void *pvParameters){
  char *pcString;
  while(1)
  {
    xQueueReceive(xStringQueue,&pcString,portMAX_DELAY);
    Serial.println(pcString);
  }
}

ISR(TIMER1_OVF_vect)              //on every timer1 overflow it writes on the queue
{
  static const char *pcStrings[]=
  {
    "Hello 1\r\n",
    "Hi 2\r\n",
    "vrednost 3\r\n",
    "sledna vrednost 4\r\n",
    "posledna vrednost 5\r\n", 
  }; 
  //sending the values to the que
  xQueueSendToBackFromISR(xStringQueue,&pcStrings[0],pdFALSE);
  xQueueSendToBackFromISR(xStringQueue,&pcStrings[1],pdFALSE);
  xQueueSendToBackFromISR(xStringQueue,&pcStrings[2],pdFALSE);
  xQueueSendToBackFromISR(xStringQueue,&pcStrings[3],pdFALSE);
  xQueueSendToBackFromISR(xStringQueue,&pcStrings[4],pdFALSE);
  
}

void InterruptInit()          //this helps with the interrupt      
{
  noInterrupts();
  TCCR1A =0;
  TCCR1B =0;
  timer1_counter = 34286;
  TCNT1 = timer1_counter;
  TCCR1B |=(1<<CS12);
  TIMSK1 |= (1 << TOIE1);
  interrupts(); 
}
