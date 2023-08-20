#include <Arduino_FreeRTOS.h>
#include <timers.h>
#define Timer_p1 pdMS_TO_TICKS( 500 ) 
#define Timer_p2 pdMS_TO_TICKS( 1000 )
#define Timer_p3 pdMS_TO_TICKS( 2000 )
TimerHandle_t xAutoReloadTimer;
BaseType_t xTimerStartedFlag;


void setup(){
  Serial.begin(9600); 
  xAutoReloadTimer = xTimerCreate("AutoReload" , Timer_p1 , pdTRUE , 0 , prvTimerCallback);
  
  /* Check the software timers were created. */
  if(( xAutoReloadTimer != NULL ) ){
    /* Start the software timer, using a block time of 0 (no block time)*/
    xTimerStartedFlag = xTimerStart( xAutoReloadTimer, 0 );
    /* if xTimerStart passes begin scheduler */
    if(xTimerStartedFlag == pdPASS ){
      vTaskStartScheduler();
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}

static void prvTimerCallback( TimerHandle_t xTimer ){
  TickType_t xTimeNow;
  uint32_t ulExecutionCount;
  /* we use the id of the timer to see how many itterations have passed */
  /* id e void pa mora da kastirame  */
  /* kastirame pak vo void pre setiranje na nov id  */
  ulExecutionCount = ( uint32_t ) pvTimerGetTimerID( xTimer );
  ulExecutionCount++;
  vTimerSetTimerID( xTimer, ( void * ) ulExecutionCount );
  /* Obtain the current tick count. */
  xTimeNow = xTaskGetTickCount();
  
  Serial.print("Auto-reload timer callback executing ");
  Serial.println( xTimeNow/31 );
  /* double the period first time and print 10 times */
  if( ulExecutionCount >= 10 &&  ulExecutionCount < 20){      
    xTimerChangePeriod( xAutoReloadTimer,Timer_p2, 0 ); 
  }
  /* double it again and print infinitely */
  if(ulExecutionCount >= 20){
    xTimerChangePeriod( xAutoReloadTimer,Timer_p3, 0 ); 
  }
}
