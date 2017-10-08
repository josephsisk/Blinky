//The mail stucture, containing blink data
typedef struct 
{
	uint32_t blink_rate;
}blink_data;

#ifndef MAIL_QUEUES
#define MAIL_QUEUES
osMailQDef (object_pool_q_1, 10, blink_data);  // Declare mail queue
osMailQDef (object_pool_q_2, 10, blink_data);  // Declare mail queue
osMailQDef (object_pool_q_3, 10, blink_data);  // Declare mail queue
osMailQDef (object_pool_q_4, 10, blink_data);  // Declare mail queue
osMailQId  (object_pool_q_id_1);                 // Mail queue ID
osMailQId  (object_pool_q_id_2);                 // Mail queue ID
osMailQId  (object_pool_q_id_3);                 // Mail queue ID
osMailQId  (object_pool_q_id_4);                 // Mail queue ID
#endif
