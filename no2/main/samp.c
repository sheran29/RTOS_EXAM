#include<stdio.h>
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"freertos/timers.h"

TaskHandle_t T1,T2,T3;
TimerHandle_t tim;
static int taskcore=1;
void timer_call(TimerHandle_t tim)
{
    printf("task 3 callback is called\n");
}
void T_1(void *data)
{
    
    while(1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
        printf("periodicity of 1000\n");
        vTaskResume(T2);
        vTaskSuspend(T1);
       
    }
    vTaskDelete(T1);

}
void T_2(void *data)
{
    vTaskSuspend(T2);
    
    while(1)
    {
      vTaskDelay(pdMS_TO_TICKS(2000));
      printf("periodicity of 2000\n");
      vTaskResume(T3);
      vTaskSuspend(T2);
   
    }
    
    vTaskDelete(T2);

}
void T_3(void *data)
{
    vTaskSuspend(T3);
    
    while(1)
    {
      vTaskDelay(pdMS_TO_TICKS(5000));
      printf("periodicity of 5000\n");
      
    tim=xTimerCreate("timer",pdMS_TO_TICKS(1000),pdFALSE,NULL,timer_call);
	if(tim==NULL)
	{
		printf("timer is not created\n");
	}
	else
	{
    	xTimerStart(tim,0);
    }
     vTaskResume(T1);
    }
    vTaskDelete(T3);
}



void app_main()
{
    
    xTaskCreatePinnedToCore(T_1,"task1",2048,NULL,5,&T1,taskcore);
    xTaskCreatePinnedToCore(T_2,"task2",2048,NULL,6,&T2,taskcore);
    xTaskCreatePinnedToCore(T_3,"task3",2048,NULL,7,&T3,taskcore);    
}
