
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "Board_LED.h"                  // ::Board Support:LED
#include "Board_Buttons.h"

/*----------------------------------------------------------------------------
 *      Thread 1 'Button_Watch': LED thread
 *---------------------------------------------------------------------------*/
 
void Button_Watch (void const *argument);                 // thread function
osThreadId tid_Button_Watch;                              // thread id
osThreadDef(Button_Watch, osPriorityNormal, 1, 0);        // thread object

int Init_Button_Watch (void) {

  tid_Button_Watch = osThreadCreate(osThread(Button_Watch), NULL);
  if (!tid_Button_Watch) return(-1);
  
  return(0);
}

void Button_Watch (void const *argument) {
  uint32_t led_cnt = LED_GetCount();
  uint32_t led_num = 0;

  while (1) {
		if(Buttons_GetState > 0)
		{
		}
  }
}
