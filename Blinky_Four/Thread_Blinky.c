
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "Board_LED.h"                  // ::Board Support:LED
//#include "UpdateRates.h"								// Contains mailbox data structures

/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Blinky1': LED thread
 *---------------------------------------------------------------------------*/
 
void Thread_Blinky1 (void const *argument);                 // thread function
osThreadId tid_Thread_Blinky1;                              // thread id
osThreadDef(Thread_Blinky1, osPriorityNormal, 1, 0);        // thread object

int Init_Thread_Blinky1 (void) {

  tid_Thread_Blinky1 = osThreadCreate(osThread(Thread_Blinky1), NULL);
  if (!tid_Thread_Blinky1) return(-1);
  
  return(0);
}

void Check_For_Mail()
{

}

void Thread_Blinky1 (void const *argument) {
  uint32_t led_num = 0;
	uint32_t delay_value = 0; //The amount to delay the blink

  while (1) {
//		osEvent event = osMailGet(object_pool_q_id_1, osWaitForever);
//		blink_data *received = (blink_data *)event.value.p;       // ".p" indicates that the message is a pointer
//		delay_value = received->blink_rate;
//		osMailFree(object_pool_q_id_1, received);
    LED_On(led_num);                    // Turn specified LED on
		osDelay(delay_value);
    LED_Off(led_num);                   // Turn specified LED off
		osDelay(delay_value);
  }
}
