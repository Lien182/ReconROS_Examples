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
#include "hdmi_input.h"

#include "reconos_app.h"

static void exit_signal(int sig) 
{
	reconos_cleanup();
	printf("[BoP_ImgPublisher] aborted\n");
	exit(0);
}


t_hdmi_input hdmi_in;

struct mbox video_cmd;

int main(int argc, char **argv) {
	
	if(argc < 2)
	{
		printf("[BoP_ImgPublisher] Error: Not enough arguments \n");
		return -1;
	}

	ros_node_init(video_node_1, "BoP_ImgPublisher");
	ros_publisher_init(video_pubdata, video_node_1,rosidl_typesupport_c__get_message_type_support_handle__sensor_msgs__msg__Image(), argv[1]);
	
	video_image_msg = sensor_msgs__msg__Image__create( );
	memcpy(&video_image_msg_s, video_image_msg, sizeof(video_image_msg_s));
	video_image_msg = &video_image_msg_s;


	mbox_init(&video_cmd, 1);

	if(memory_init() < 0)
	{
		printf("[BoP_ImgPublisher] Error while allocating memory \n");
		return -1;
	}

	if(hdmi_input_init(&hdmi_in, "/dev/video0", &video_cmd) != 0)
	{
		printf("[BoP_ImgPublisher] HDMI Output: Init error \n");
	}

	printf("[BoP_ImgPublisher] Publish to topic %s \n", argv[1]);

	
	signal(SIGINT, exit_signal);
	signal(SIGTERM, exit_signal);
	signal(SIGABRT, exit_signal);	
	

	reconos_thread_create_swt_imgpublisher(&hdmi_in, 0);

	
	while(1) 
	{
		sleep(100);
	}
}
