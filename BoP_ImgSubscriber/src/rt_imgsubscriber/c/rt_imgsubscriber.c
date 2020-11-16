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

#include "hdmi_output.h"




THREAD_ENTRY()
{
	THREAD_INIT();

	t_hdmi_output * hdmi_output = (t_hdmi_output*)data;

	while (1)
	{
		ROS_SUBSCRIBE_TAKE(video_subdata, video_image_msg);
		memcpy(hdmi_output->image, video_image_msg->data.data, 100);
	}
}

