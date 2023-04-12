#include "reconos_calls.h"
#include "reconos_thread.h"
#include "ap_cint.h"

#include <std_msgs/msg/u_int32_multi_array.h>

#define BLOCK_SIZE 2048


THREAD_ENTRY() {
	RAM(uint32, BLOCK_SIZE, ram);
	uint32 addr, initdata;	
	uint32 pMessage;
	uint32 payload_addr[1];

	THREAD_INIT();
	initdata = GET_INIT_DATA();

	while(1) {

		pMessage = ROS_SUBSCRIBE_TAKE(resources_subdata, resources_sort_msg );
		addr = OFFSETOF(std_msgs__msg__UInt32MultiArray, data.data) + pMessage;

		MEM_READ(addr, payload_addr, 4);					//Get the address of the data
		for(int i = 0; i < 768; i++)
		{
			MEM_READ(payload_addr[0], ram, BLOCK_SIZE * 4);
			MEM_WRITE(ram, payload_addr[0], BLOCK_SIZE * 4);
			payload_addr[0] +=(BLOCK_SIZE * 4);
		}
		
		ROS_PUBLISH(resources_pubdata,resources_sort_msg);
	}
}
