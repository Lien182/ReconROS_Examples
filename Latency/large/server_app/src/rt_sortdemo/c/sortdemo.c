#include "reconos_thread.h"
#include "reconos_calls.h"

#define BLOCK_SIZE 2048



uint32_t msg[2048];

void *rt_sortdemo(void *data) {
	clock_t start, end;

	

	while (1) {
		ROS_SUBSCRIBE_TAKE(resources_subdata, resources_sort_msg);
		start = clock();
		memcpy(msg, resources_sort_msg->data.data, 2048 * 4);		
		memcpy(resources_sort_msg->data.data, msg, 2048 * 4);
		end = clock();
		ROS_PUBLISH(resources_pubdata, resources_sort_msg  );

		printf("%3.6f \n", (double)(end-start)/CLOCKS_PER_SEC);
	}
}
