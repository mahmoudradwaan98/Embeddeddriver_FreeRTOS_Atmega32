/*
 * main.c
 *
 *  Created on: Mar 21, 2023
 *      Author: User
 */
#include"STD_TYPES.h"
#include"BIT_MATHS.h"

#include"PORT_interface.h"
#include"DIO_interface.h"

#include"FreeRTOS.h"
#include"task.h"
#include"semphr.h"

void led1(void *pv);
void led2(void *pv);
void led3(void *pv);

xSemaphoreHandle LedSem;

void main(void){

	PORT_voidInit();

	xTaskCreate(&led1,NULL,100,NULL,0,NULL);
	xTaskCreate(&led2,NULL,100,NULL,1,NULL);
	xTaskCreate(&led3,NULL,100,NULL,2,NULL);

	xSemaphoreCreateCounting(1,1);

	vTaskStartScheduler();
	while(1){

	}
}

void led1(void *pv){

	u8 Local_LedsemState;

	static u8 Local_LedState = 0;

	while(1){

		/* try to take semaphore */
		Local_LedsemState = xSemaphoreTake(LedSem,0);

		if(Local_LedsemState==pdPASS){

			/*semaphore is taken and access LED*/
			TOGGLE_BIT(Local_LedState,0);

			DIO_u8SetPinValue(DIO_U8PORTA,DIO_U8PIN0,Local_LedState);
			vTaskDelay(1000);

			/* Access is finished , give semaphore now */
			xSemaphoreGive(LedSem);
		}


	}
}


void led2(void *pv){

	static u8 Local_LedState = 0;

	while(1){

		TOGGLE_BIT(Local_LedState,0);

		DIO_u8SetPinValue(DIO_U8PORTA,DIO_U8PIN1,Local_LedState);

		vTaskDelay(2000);
	}
}


void led3(void *pv){

	static u8 Local_LedState = 0;

	while(1){

		TOGGLE_BIT(Local_LedState,0);

		DIO_u8SetPinValue(DIO_U8PORTA,DIO_U8PIN2,Local_LedState);

		vTaskDelay(3000);
	}
}
