#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#define debug(...)

#define SHOW_DATA 1

#include "../lib/comp/ros.h"
#include "../lib/comp/ros_sub.h"
#include "../lib/comp/ros_pub.h"


#define BLOCK_SIZE 	2048
#define ITERATIONS	1000

#define MODE_PUBLISHER	1
#define MODE_SUBSCRIBER	2
#define MODE_NONE		99

#define ROS_TYPE_MESSAGE_TYPE rosidl_typesupport_c__get_message_type_support_handle__std_msgs__msg__UInt32()

#define OFFSETOF(type, member) ((uint32_t)(intptr_t)&(((type *)(void*)0)->member) )

pthread_mutex_t mutex;

struct ros_node_t 		resources_rosnode[2];
struct ros_subscriber_t resources_subdata[2];
struct ros_publisher_t 	resources_pubdata[2];

typedef struct {
	uint32_t	cnt;
	uint32_t 	mode;
	uint32_t 	wait_time;
	char* 		topic;
	char* 		nodename;
	uint8_t*	msg;
	uint32_t 	msg_length;
}t_thread_settings;



void timespec_diff(struct timespec *start, struct timespec *stop,
                   struct timespec *result)
{
    if ((stop->tv_nsec - start->tv_nsec) < 0) {
        result->tv_sec = stop->tv_sec - start->tv_sec - 1;
        result->tv_nsec = stop->tv_nsec - start->tv_nsec + 1000000000;
    } else {
        result->tv_sec = stop->tv_sec - start->tv_sec;
        result->tv_nsec = stop->tv_nsec - start->tv_nsec;
    }

    return;
}


void my_handler (int sig)
{
	printf("Interrupt\n");
	ros_subscriber_destroy(resources_subdata);
  	ros_node_destroy(resources_rosnode);
	exit(0);
}

struct timespec t_start, t_end, t_res;


void* node_thread(void * arg)
{
	int i = 0;
	t_thread_settings* sett = (t_thread_settings*)arg;

	std_msgs__msg__UInt32 input_msg;


	pthread_mutex_lock (&mutex);

	if(ros_node_init(&resources_rosnode[sett->cnt],sett->nodename) < 0)
	{
		printf("Thread %d: ROS Node init failed \n", sett->cnt);
		return (void*)-1;
	}
	pthread_mutex_unlock (&mutex);

	if(sett->mode == MODE_PUBLISHER)
	{
		if( ros_publisher_init(&resources_pubdata[sett->cnt], &resources_rosnode[sett->cnt], ROS_TYPE_MESSAGE_TYPE, sett->topic) < 0 )
		{
			ros_node_destroy(&resources_rosnode[sett->cnt]);
			return (void*)-1;
		}
		usleep(200000);	

		for(i = 0; i < ITERATIONS; i++ )
		{
			input_msg.data = ((i*101) << 3) | ((i*152) << 17)  | (i%7); 
			ros_publisher_publish(&resources_pubdata[sett->cnt], &input_msg);
			clock_gettime(CLOCK_MONOTONIC, &t_start);
			usleep(sett->wait_time);
			//printf("[ReconROS_Publisher_Node_%d_%d] \n", sett->cnt,i);
		}

		ros_publisher_destroy(&resources_pubdata[sett->cnt]);

	}
	else if(sett->mode == MODE_SUBSCRIBER)
	{
		if(ros_subscriber_init(&resources_subdata[sett->cnt], &resources_rosnode[sett->cnt],ROS_TYPE_MESSAGE_TYPE, sett->topic, 10) < 0)
		{
			ros_node_destroy(&resources_rosnode[sett->cnt]);
			return (void*)-1;
		}
		
		printf("wait for msg; topic: %s \n", sett->topic);
		for(i = 0; i < ITERATIONS; i++ )
		{
			
			
			ros_subscriber_message_take(&resources_subdata[sett->cnt], &input_msg);
			clock_gettime(CLOCK_MONOTONIC, &t_end);
			//usleep(sett->wait_time);
			timespec_diff(&t_start, &t_end, &t_res);
			printf("%3.6f;\n", (double)(t_res.tv_nsec)/1000000000);

			//printf("[ReconROS_Node_%d_%d]", sett->cnt,i);

		}

		ros_subscriber_destroy(&resources_subdata[sett->cnt]);



	}
	else if(sett->mode == MODE_NONE)
	{
		for(i = 0; i < 10; i++)
		{
			printf("Sleep: %d \n", i);
			sleep(1);
		}
	}


	ros_node_destroy(&resources_rosnode[sett->cnt]);

	return (void*)0;
}


int main(int argc, char **argv) 
{

	uint32_t u32usorted[BLOCK_SIZE];
	uint32_t u32sorted[BLOCK_SIZE];

	pthread_t p1, p2;

	t_thread_settings settings[2];

	signal (SIGQUIT, my_handler);
	signal (SIGINT, my_handler);
	pthread_mutex_init (&mutex, NULL);
	
	srand(time(0));

	for(int i = 0; i < BLOCK_SIZE; i++)
	{
		u32usorted[i] = rand();
		u32sorted[i] = 0;
	}

	settings[0].cnt = 0;
	settings[0].mode = MODE_PUBLISHER;
	settings[0].wait_time = 200000;
	settings[0].msg = (uint8_t*)u32usorted;
	settings[0].msg_length = BLOCK_SIZE * sizeof(uint32_t);
	settings[0].topic = "angle";
	settings[0].nodename = "node_1";
	

	settings[1].cnt = 1;
	settings[1].mode = MODE_SUBSCRIBER;
	settings[1].wait_time = 200000;
	settings[1].msg = (uint8_t*)u32sorted;
	settings[1].msg_length = BLOCK_SIZE * sizeof(uint32_t);
	settings[1].topic = "legangle";
	settings[1].nodename = "node_2";

	

	pthread_create(&p1, NULL, &node_thread, &settings[0]);
	pthread_create(&p2, NULL, &node_thread, &settings[1]);

  	pthread_join (p1, NULL);
  	pthread_join (p2, NULL);

	return 0;
}