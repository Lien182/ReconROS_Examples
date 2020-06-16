/********************************************************************          
* rt_sobel.cpp         -- hardware sobel implementation             *
*                         calculated the sobel operation for        *
*                         all three color channels                  * 
*																	* 
* Author(s):  Christian Lienen                                      *   
*                                                                   *   
********************************************************************/

#include "reconos_thread.h"
#include "reconos_calls.h"

#include <sensor_msgs/msg/image.h>

#include "ap_int.h"
#include "ap_fixed.h"
#include "hls_math.h"

#define INPUT_WIDTH 640
#define INPUT_HEIGHT 480
#define INPUT_LINEBUFFER_SIZE (INPUT_WIDTH * 4 * 4)
#define INPUT_PREFETCH_SIZE	  (INPUT_WIDTH * 4 * 2)
#define INPUT_LINESIZE (INPUT_WIDTH * 4)
#define OUTPUT_LINEBUFFER_SIZE (INPUT_WIDTH * 4)
#define OUTPUT_WIDTH 1680
#define OUTPUT_LINE_SIZE (OUTPUT_WIDTH * 4 )

const int filter_x[] = { 1,  2,  1,  0,  0,  0, -1, -2, -1};
const int filter_y[] = { 1,  0, -1,  2,  0, -2,  1,  0, -1};

//const int filter_x[] = { 0,  0,  0,  0,  4,  0,  0,  0,  0};
//const int filter_y[] = { 0,  0,  0,  0,  4,  0,  0,  0,  0};

THREAD_ENTRY()
{

	int32 input_linebuffer[INPUT_LINEBUFFER_SIZE];
	int32 output_linebuffer[OUTPUT_LINEBUFFER_SIZE];;
	int32 i,k,j, ii, jj;
	int16 tmp_x[3], tmp_y[3];
	uint8 filter_pointer;

	THREAD_INIT();


	while (1)
	{
		uint32 status = 0;
		uint32 payload_addr[1];
		

		uint32 pMessage= ROS_SUBSCRIBE_TAKE(video_subdata, video_image_msg );
		uint32 address = OFFSETOF(sensor_msgs__msg__Image, data.data) + pMessage;
		MEM_READ(address, payload_addr, 4);	

		//address <<=2;
		MEM_READ( payload_addr[0], input_linebuffer, INPUT_PREFETCH_SIZE);

		payload_addr[0] += (INPUT_WIDTH<<3); // <<3 = *2*4

		for(i = 1; i < (INPUT_HEIGHT-1); i++)
		{
			MEM_READ( payload_addr[0] , &(input_linebuffer[INPUT_WIDTH* ((i+1)&3)]) , INPUT_LINESIZE );
			payload_addr[0] += (INPUT_WIDTH<<2);

			for(j = 1; j < (INPUT_WIDTH-1); j++)
			{

				tmp_x[0]= 0; tmp_y[0] = 0;
				tmp_x[1]= 0; tmp_y[1] = 0;
				tmp_x[2]= 0; tmp_y[2] = 0;

				filter_pointer = 0;
				for(ii=-1; ii < 2; ii++)
				{
					for(jj=-1; jj < 2; jj++)  
					{		
						uint32 buffer_pointer = ((INPUT_WIDTH*((i+ii)&3)+(j+jj)));
						uint32 actindata  = 	input_linebuffer[buffer_pointer];	
						for(k = 0; k < 3; k++)
						{
							#pragma HLS unroll factor=3
							int16 data = ((actindata >> 8*k) & 0x000000ff);
							tmp_x[k] += data * filter_x[filter_pointer];
							tmp_y[k] += data * filter_y[filter_pointer];
							
						}
						filter_pointer++;
					}	
				}
				output_linebuffer[(j)] = 0xff000000 | (((abs(tmp_x[0]) + abs(tmp_y[0])) >> 3)) | (((abs(tmp_x[1]) + abs(tmp_y[1])) >> 3) << 8) | (((abs(tmp_x[2]) + abs(tmp_y[2])) >> 3) << 16);
			}
			
			MEM_WRITE( output_linebuffer , (payload_addr[0] + i*OUTPUT_LINE_SIZE), INPUT_LINESIZE );

		}		
	}

}
