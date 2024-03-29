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

#include "hdmi_output.h"


THREAD_ENTRY()
{
	THREAD_INIT();

	t_hdmi_output * hdmi_output = (t_hdmi_output*)(((struct reconos_thread*)data)->init_data);
	while (1)
	{
		ROS_SUBSCRIBE_TAKE(video_subdata, video_image_msg);
		if(strcmp("bgr8",video_image_msg->encoding.data) == 0)
		{
			for(int i = 0; i < video_image_msg->height; i++)
			{
				for(int j = 0; j < video_image_msg->width; j++)
					hdmi_output->image[hdmi_output->width * i + j] =  	(video_image_msg->data.data[3*j + video_image_msg->step * i]) | 
															  			(video_image_msg->data.data[3*j + video_image_msg->step * i + 1] << 8) | 
															  			(video_image_msg->data.data[3*j + video_image_msg->step * i + 2] << 16) | 
															  			0xff000000;
			}

		}
	
	}
}

