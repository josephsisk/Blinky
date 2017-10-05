
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "Board_LED.h"                  // ::Board Support:LED
//#include "UpdateRates.h"								// Contains mailbox data structures

/*----------------------------------------------------------------------------
 *      Thread 1 'Update_Rates': LED Blink Rate Controller
 *---------------------------------------------------------------------------*/
 
uint32_t random_seed = 111; //Used for calculating pseudo-random blink times
 
void Update_Rates (void const *argument);                 // thread function
osThreadId tid_Update_Rates;                              // thread id
osThreadDef(Update_Rates, osPriorityNormal, 1, 0);        // thread object

//The mail stucture, containing blink data
typedef struct 
{
	uint32_t blink_rate;
}blink_data;

//Individual data structures for the mailboxes
blink_data * blink_data_1;
blink_data * blink_data_2;
blink_data * blink_data_3;
blink_data * blink_data_4;

osMailQDef (object_pool_q_1, 10, blink_data);  // Declare mail queue
osMailQDef (object_pool_q_2, 10, blink_data);  // Declare mail queue
osMailQDef (object_pool_q_3, 10, blink_data);  // Declare mail queue
osMailQDef (object_pool_q_4, 10, blink_data);  // Declare mail queue
osMailQId  (object_pool_q_id_1);                 // Mail queue ID
osMailQId  (object_pool_q_id_2);                 // Mail queue ID
osMailQId  (object_pool_q_id_3);                 // Mail queue ID
osMailQId  (object_pool_q_id_4);                 // Mail queue ID

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

void Init_Mail_Queues()
{
	#ifndef OBJECT_POOLS
	#define OBJECT_POOLS
	object_pool_q_id_1 = osMailCreate(osMailQ(object_pool_q_1), NULL); //Create the mail pool
	object_pool_q_id_2 = osMailCreate(osMailQ(object_pool_q_2), NULL); //Create the mail pool
	object_pool_q_id_3 = osMailCreate(osMailQ(object_pool_q_3), NULL); //Create the mail pool
	object_pool_q_id_4 = osMailCreate(osMailQ(object_pool_q_4), NULL); //Create the mail pool
	#endif
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


void Thread_Blinky1 (void const *argument) {
  uint32_t led_num = 0;
	uint32_t delay_value = 0; //The amount to delay the blink

  while (1) {
		//Check for mail every cycle
		osEvent event = osMailGet(object_pool_q_id_1, 0);
		if(event.status == osEventMail)
		{
			blink_data *received = (blink_data *)event.value.p;       // ".p" indicates that the message is a pointer
			delay_value = received->blink_rate;
			osMailFree(object_pool_q_id_1, received);
		}
    LED_On(led_num);                    // Turn specified LED on
		osDelay(delay_value);
    LED_Off(led_num);                   // Turn specified LED off
		osDelay(delay_value);
  }
}

void Thread_Blinky2 (void const *argument);                 // thread function
osThreadId tid_Thread_Blinky2;                              // thread id
osThreadDef(Thread_Blinky2, osPriorityNormal, 1, 0);        // thread object

int Init_Thread_Blinky2 (void) {

  tid_Thread_Blinky2 = osThreadCreate(osThread(Thread_Blinky2), NULL);
  if (!tid_Thread_Blinky2) return(-1);
  
  return(0);
}

void Thread_Blinky2 (void const *argument) {
  //uint32_t led_cnt = LED_GetCount();
  uint32_t led_num = 1;
	uint32_t delay_value = 0; //The amount to delay the blink


  while (1) {
		//Check for mail every cycle
		osEvent event = osMailGet(object_pool_q_id_2, 0);
		if(event.status == osEventMail)
		{
			blink_data *received = (blink_data *)event.value.p;       // ".p" indicates that the message is a pointer
			delay_value = received->blink_rate;
			osMailFree(object_pool_q_id_1, received);
		}
    //osSignalWait(1U, osWaitForever);    // Wait for signal
    LED_On(led_num);                    // Turn specified LED on
		osDelay(delay_value);
    //osSignalWait(1U, osWaitForever);    // Wait for signal
    LED_Off(led_num);                   // Turn specified LED off
		osDelay(delay_value);
  }
}

/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Blinky3': LED thread
 *---------------------------------------------------------------------------*/
 
void Thread_Blinky3 (void const *argument);                 // thread function
osThreadId tid_Thread_Blinky3;                              // thread id
osThreadDef(Thread_Blinky3, osPriorityNormal, 1, 0);        // thread object

int Init_Thread_Blinky3 (void) {

  tid_Thread_Blinky3 = osThreadCreate(osThread(Thread_Blinky3), NULL);
  if (!tid_Thread_Blinky3) return(-1);
  
  return(0);
}

void Thread_Blinky3 (void const *argument) {
  //uint32_t led_cnt = LED_GetCount();
  uint32_t led_num = 2;
	uint32_t delay_value = 0; //The amount to delay the blink


  while (1) {
		//Check for mail every cycle
		osEvent event = osMailGet(object_pool_q_id_3, 0);
		if(event.status == osEventMail)
		{
			blink_data *received = (blink_data *)event.value.p;       // ".p" indicates that the message is a pointer
			delay_value = received->blink_rate;
			osMailFree(object_pool_q_id_1, received);
		}
    //osSignalWait(1U, osWaitForever);    // Wait for signal
    LED_On(led_num);                    // Turn specified LED on
		osDelay(delay_value);
    //osSignalWait(1U, osWaitForever);    // Wait for signal
    LED_Off(led_num);                   // Turn specified LED off
		osDelay(delay_value);
  }
}

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
	uint32_t delay_value = 0; //The amount to delay the blink


  while (1) {
		//Check for mail every cycle
		osEvent event = osMailGet(object_pool_q_id_4, 0);
		if(event.status == osEventMail)
		{
			blink_data *received = (blink_data *)event.value.p;       // ".p" indicates that the message is a pointer
			delay_value = received->blink_rate;
			osMailFree(object_pool_q_id_1, received);
		}
    //osSignalWait(1U, osWaitForever);    // Wait for signal
    LED_On(led_num);                    // Turn specified LED on
		osDelay(delay_value);
    //osSignalWait(1U, osWaitForever);    // Wait for signal
    LED_Off(led_num);                   // Turn specified LED off
		osDelay(delay_value);
  }
}
