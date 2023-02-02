#include<stdio.h>
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"freertos/queue.h"

TaskHandle_t T1,T2,T3,T4,T5;
QueueHandle_t Q=NULL;
static int taskcore=1;

void T_1(void *data)
{
    
    while(1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
        printf("periodicity of 1000\n");
        vTaskResume(T2);
        // vTaskSuspend(T1);
       
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
      vTaskSuspend(T3);
    }
    vTaskDelete(T3);
}

void T_4(void *data)
{
    
    unsigned int count=100;
	if(Q==NULL)
	{
		printf("Queue is not ready\n");
	}
		printf("values sending to Queue %d......\n",count);
		xQueueSend(Q,(void *)&count,pdMS_TO_TICKS(10000));
		vTaskDelay(pdMS_TO_TICKS(6000));
	
}
void T_5(void *data)
{
    unsigned int count=0;
	if(Q==NULL)
	{
		printf("Queue is not ready\n");
	}
		xQueueReceive(Q,&count,pdMS_TO_TICKS(10000));
		printf("\n\t\tvalue from queue %d\n",count);
		vTaskDelay(pdMS_TO_TICKS(3000));
	
}
void app_main()
{
     Q=xQueueCreate(20,sizeof(unsigned int));
    xTaskCreatePinnedToCore(T_1,"task1",2048,NULL,5,&T1,taskcore);
	xTaskCreatePinnedToCore(T_2,"task2",2048,NULL,6,&T2,taskcore);
	xTaskCreatePinnedToCore(T_3,"task3",2048,NULL,7,&T3,taskcore);
    xTaskCreatePinnedToCore(T_5,"task5",2048,NULL,9,&T5,taskcore);
    xTaskCreatePinnedToCore(T_4,"task4",2048,NULL,8,&T4,taskcore);
}
