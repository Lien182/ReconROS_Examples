/********************************************************************          
* main.c           -       main function							*
*                        				                            *
*                                                                   *  
* Author(s): Christian Lienen                    					*   
*                                                                   *   
********************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>

#include "memory.h"
#include "hdmi_output.h"

#include "reconos_app.h"

static void exit_signal(int sig) 
{
	reconos_cleanup();
	printf("[recobop] aborted\n");
	exit(0);
}


t_hdmi_output hdmi_out;

int main(int argc, char **argv) {
	
	if(argc < 2)
	{
		printf("[BoP_ImgSubscriber] Error: Not enough arguments \n",]);
		return -1;
	}


	if(memory_init() < 0)
	{
		printf("Error while allocating memory \n");
		return -1;
	}

	printf("[BoP_ImgSubscriber] Subscribe Topic %s \n", argv[1]);

	ros_node_init(video_node_1, "BoP_ImgSubscriber");
	ros_subscriber_init(video_subdata, video_node_1,rosidl_typesupport_c__get_message_type_support_handle__sensor_msgs__msg__Image(), argv[1], 1000);
	
	video_image_msg = sensor_msgs__msg__Image__create( );
	memcpy(&video_image_msg_s, video_image_msg, sizeof(video_image_msg_s));
	video_image_msg = &video_image_msg_s;
	
	signal(SIGINT, exit_signal);
	signal(SIGTERM, exit_signal);
	signal(SIGABRT, exit_signal);	
	

	
	while(1) 
	{

		sleep(100);
	}
}
