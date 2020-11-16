/********************************************************************          
* rt_sobel.c           -- software sobel implementation             *
*                         calculated the sobel operation for        *
*                         all three color channels                  * 
*																	* 
* Author(s):  Christian Lienen                                      *   
*                                                                   *   
********************************************************************/

#include "reconos.h"
#include "reconos_thread.h"
#include "reconos_calls.h"
#include "utils.h"

#include <math.h>
#include <stdio.h>


#define INPUT_WIDTH 480 // because of the rgb8 format -> 24 bit per pixel
#define INPUT_HEIGHT 480
#define INPUT_LINEBUFFER_SIZE (INPUT_WIDTH * 4 * 4)
#define INPUT_PREFETCH_SIZE	  (INPUT_WIDTH * 4 * 2)
#define INPUT_LINESIZE (INPUT_WIDTH * 4)
#define OUTPUT_LINEBUFFER_SIZE (INPUT_WIDTH * 4)
#define OUTPUT_WIDTH INPUT_WIDTH
#define OUTPUT_LINE_SIZE (OUTPUT_WIDTH * 4 )

#define MEM_READ_L( adr, dest, length ) { memcpy( dest, (void*)adr,  length); }
#define MEM_WRITE_L( src, adr, length ) { memcpy((void*)adr, src, length); }


const int filter_x[] = { 1,  2,  1,  0,  0,  0, -1, -2, -1};
const int filter_y[] = { 1,  0, -1,  2,  0, -2,  1,  0, -1};




THREAD_ENTRY()
{
	THREAD_INIT();

	uint32_t bStart = 1;

	uint32_t input_linebuffer[INPUT_LINEBUFFER_SIZE/4];
	uint32_t output_linebuffer[OUTPUT_LINEBUFFER_SIZE/4];
	int32_t i,k,j, ii, jj;
	int16_t tmp_x[4], tmp_y[4];
	uint8_t filter_pointer;

	//uint8_t * outputdata = malloc(640*480*4);

	while (1)
	{
		ROS_SUBSCRIBE_TAKE(video_subdata, video_image_msg);

		printf("%d %d %d \n",   	video_image_msg->data.data,	video_image_msg->data.size,	video_image_msg->data.capacity);

		printf("Got image, compute .. \n");
		uint32_t address = (uint32_t)video_image_msg->data.data;
		
		MEM_READ_L( address, input_linebuffer, INPUT_PREFETCH_SIZE);
		address += (INPUT_WIDTH<<3);

		for(i = 1; i < (INPUT_HEIGHT-1); i++)
		{
			MEM_READ_L( address , &(input_linebuffer[INPUT_WIDTH* ((i+1)&3)]) , INPUT_LINESIZE );
			address += (INPUT_WIDTH<<2);

			for(j = 1; j < (INPUT_WIDTH-1); j++)
			{

				
				tmp= 0; 
				
				uint32_t buffer_pointer = ((INPUT_WIDTH*((i)&3)+(j)));
				uint32_t actindata  = 	input_linebuffer[buffer_pointer];	
				for(k = 0; k < 3; k++)
				{
					int32_t data = ((actindata >> 8*k) & 0x000000ff);
					tmp += data;
				}
				tmp /= 3;


				output_linebuffer[j] = (input_linebuffer[((INPUT_WIDTH*((i)&3)+(j)))] & 0xff000000) | (tmp & 0xff)   | ((tmp & 0xff) << 8) | ((tmp & 0xff) << 16);
			}


			MEM_WRITE_L( output_linebuffer , ((uint8_t*)video_image_msg_out->data.data + i* OUTPUT_LINE_SIZE), INPUT_LINESIZE);
			
		}
		
		ROS_PUBLISH(video_pubdata, video_image_msg_out);







	}
}
