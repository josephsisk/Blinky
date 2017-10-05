
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "Board_LED.h"                  // ::Board Support:LED

/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Blinky4': LED thread
 *---------------------------------------------------------------------------*/
 
void Thread_Blinky4 (void const *argument);                 // thread function
osThreadId tid_Thread_Blinky4;                              // thread id
osThreadDef(Thread_Blinky4, osPriorityNormal, 1, 0);        // thread object

int Init_Thread_Blinky4 (void) {

  tid_Thread_Blinky4 = osThreadCreate(osThread(Thread_Blinky4), NULL);
  if (!tid_Thread_Blinky4) return(-1);
  
  return(0);
}

void Thread_Blinky4 (void const *argument) {
  //uint32_t led_cnt = LED_GetCount();
  uint32_t led_num = 3;

  while (1) {
    //osSignalWait(1U, osWaitForever);    // Wait for signal
    LED_On(led_num);                    // Turn specified LED on
		osDelay(400);
    //osSignalWait(1U, osWaitForever);    // Wait for signal
    LED_Off(led_num);                   // Turn specified LED off
		osDelay(400);

//    led_num++;                          // Change LED number
//    if (led_num >= led_cnt) {
//      led_num = 0;                      // Restart with first LED
//    }
  }
}
