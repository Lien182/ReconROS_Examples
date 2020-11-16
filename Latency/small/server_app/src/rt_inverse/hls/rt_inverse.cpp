/********************************************************************          
* inverse.cpp    -hardware implementation inverse thread function	*
*                        				                            *
*                                                                   *  
* Author(s): Christoph Rueting, Christian Lienen                    *   
*                                                                   *   
********************************************************************/

#include "reconos_thread.h"
#include "reconos_calls.h"

#include "ap_int.h"
#include "ap_fixed.h"



THREAD_ENTRY() {

	THREAD_INIT();

	uint32 output_buffer_addr = GET_INIT_DATA();

	while (1) {

		ap_uint<32> data;
		uint32 tmp;

		uint32 message_data[1];		
		uint32 pMessage = ROS_SUBSCRIBE_TAKE(inverse_subdata, inverse_input_msg );

		MEM_READ(pMessage, message_data, 4 );
		uint32 outputdata[1];		
	{	
		#pragma HLS PROTOCOL fixed
		
		outputdata[0] = message_data[0];	
		MEM_WRITE(outputdata, output_buffer_addr,4);
		ap_wait();
		ROS_PUBLISH(inverse_pubdata,inverse_output_msg);	
	}
	
		
	}


}
