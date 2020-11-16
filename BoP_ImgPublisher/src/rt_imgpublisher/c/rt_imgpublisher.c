/********************************************************************          
* rt_imgpublisher.c    -- rt_imgpublisher: writes the subscribed	*
*                         images in the framebuffer fb0		        *
*                        							                * 
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
#include "hdmi_input.h"


extern struct mbox video_cmd;


int set_message_size(sensor_msgs__msg__Image * ros_msg, uint32_t length) {

	if(length != ros_msg->data.capacity)
	{

		if(ros_msg->data.capacity > 0)
		{
			if(ros_msg->data.data != NULL)
				free(ros_msg->data.data); 
			ros_msg->data.capacity = 0;
			ros_msg->data.size = 0;
		}

		if(length != 0)
		{
			ros_msg->data.data = malloc(length); 
			ros_msg->data.capacity = length;
			ros_msg->data.size = length;
		}

	}
	return 0;
}


THREAD_ENTRY()
{
	THREAD_INIT();

	t_hdmi_input * hdmi_input = (t_hdmi_input*)(((struct reconos_thread*)data)->init_data);

	set_message_size(video_image_msg, hdmi_input->height * hdmi_input->width * 3);

	video_image_msg->encoding.data = "bgr8";
	video_image_msg->encoding.size = 5;
	video_image_msg->encoding.capacity = 6;
	video_image_msg->width  = hdmi_input->width;
	video_image_msg->height = hdmi_input->height;
	video_image_msg->step = hdmi_input->width * 3;
	
	while (1)
	{
		uint32_t* addr = (uint32_t*)mbox_get(&video_cmd);
		
		for(int i = 0; i < video_image_msg->height; i++)
			{
				for(int j = 0; j < video_image_msg->width; j++)
				{
					
					video_image_msg->data.data[3*j + video_image_msg->step * i + 0] =   addr[ j+ video_image_msg->width * i] & 0x000000ff;
					video_image_msg->data.data[3*j + video_image_msg->step * i + 1] =  (addr[ j+ video_image_msg->width * i] & 0x0000ff00) >> 8;
					video_image_msg->data.data[3*j + video_image_msg->step * i + 2] =  (addr[ j+ video_image_msg->width * i] & 0x00ff0000) >> 16;
				}

			}

		ROS_PUBLISH(video_pubdata, video_image_msg);
	}
}

