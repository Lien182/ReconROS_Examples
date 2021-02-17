#include "reconos_thread.h"
#include "reconos_calls.h"


THREAD_ENTRY()
{
	THREAD_INIT();
	uint32 output_buffer_addr = GET_INIT_DATA();

	while (1)
	{
		uint32 status = 0;
		uint32 payload_addr[1];
		
		uint32 ram[100];

		uint32 pMessage= ROS_SERVICESERVER_TAKE(video_subdata, video_image_msg_in );
		MEM_READ( pMessage, payload_addr, 4);
		MEM_READ( payload_addr[0], ram, 4);


		MEM_WRITE( ram, output_buffer_addr, 4);
		ROS_SERVICESERVER_SEND_RESPONSE(video_subdata, video_image_msg_in);		
	}
}
