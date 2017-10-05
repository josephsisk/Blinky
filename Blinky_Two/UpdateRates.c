
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
//#include "Board_LED.h"                  // ::Board Support:LED
#include "UpdateRates.h"

/*----------------------------------------------------------------------------
 *      Thread 1 'Update_Rates': LED Blink Rate Controller
 *---------------------------------------------------------------------------*/
 
int random_seed = 111; //Used for calculating pseudo-random blink times
 
void Update_Rates (void const *argument);                 // thread function
osThreadId tid_Update_Rates;                              // thread id
osThreadDef(Update_Rates, osPriorityNormal, 1, 0);        // thread object

//Individual data structures for the mailboxes
blink_data * blink_data_1;
blink_data * blink_data_2;
blink_data * blink_data_3;
blink_data * blink_data_4;


int Init_Update_Rates (void) {

  tid_Update_Rates = osThreadCreate(osThread(Update_Rates), NULL);
  if (!tid_Update_Rates) return(-1);
  
  return(0);
}

///Returns a pseudo-random blink rate
///max_ms: the maximum time (ms) to be returned
int Get_Blink_Rate(int max_ms)
{
	int returnVal = (random_seed * random_seed) % max_ms;
	
	//Update random seed for next calculation
	random_seed += returnVal + 11;
	
	return returnVal;
}

void Update_Rates (void const *argument) {
//  uint32_t led_num = 0;
	
	Init_Mail_Queues();
	
	//Allocate the mail queues
	blink_data_1 = (blink_data *) osMailAlloc(object_pool_q_id_1, osWaitForever);
	blink_data_2 = (blink_data *) osMailAlloc(object_pool_q_id_2, osWaitForever);
	blink_data_3 = (blink_data *) osMailAlloc(object_pool_q_id_3, osWaitForever);
	blink_data_4 = (blink_data *) osMailAlloc(object_pool_q_id_4, osWaitForever);

  while (1) {
//		int blink_rate = Get_Blink_Rate(2000);
		blink_data_1->blink_rate = Get_Blink_Rate(2000);
		blink_data_2->blink_rate = Get_Blink_Rate(2000);
		blink_data_3->blink_rate = Get_Blink_Rate(2000);
		blink_data_4->blink_rate = Get_Blink_Rate(2000);
		osMailPut(object_pool_q_id_1, blink_data_1);
		osMailPut(object_pool_q_id_2, blink_data_2);
		osMailPut(object_pool_q_id_3, blink_data_3);
		osMailPut(object_pool_q_id_4, blink_data_4);
		osDelay(5000); //Wait 5 seconds
  }
}
