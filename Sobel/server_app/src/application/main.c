#include "reconos.h"
#include "reconos_app.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>


static void exit_signal(int sig) 
{
	reconos_cleanup();
	printf("[recobop] aborted\n");
	exit(0);
}


int main(int argc, char **argv) {
	uint32_t bUseHW = 0;

	reconos_init();
	reconos_app_init();

	if(argc == 2)
	{
		if(strcmp(argv[1], "sw") == 0)
		{
			bUseHW = 0;
			printf("Starting Software Thread \n");
		}
		else
		{
			bUseHW = 1;
			printf("Starting Hardware Thread \n");
		}
		
		
	}
	else
	{
		printf("Usage: ./sobel <sw/hw> \n");
		return -1;
	}
	
	

	//std_msgs__msg__Header header;
  	video_image_msg_out->height = 480;
  	video_image_msg_out->width = 640;
  	video_image_msg_out->encoding.data = "bgr8";
	video_image_msg_out->encoding.size = 4;  
	video_image_msg_out->encoding.capacity = 5;  
  	video_image_msg_out->is_bigendian = 0;
  	video_image_msg_out->step = 1920;
  	video_image_msg_out->data.data = malloc(480*640*3);
	video_image_msg_out->data.size = 480*640*3;
	video_image_msg_out->data.capacity = 480*640*3;

	if(bUseHW == 1)
	{
		struct reconos_thread * thread_sobel = reconos_thread_create_hwt_sobel(video_image_msg_out->data.data );
	}
	else
	{
		struct reconos_thread * thread_sobel = reconos_thread_create_swt_sobel(0,0);
	}
	

	while(1) 
	{
		sleep(100);
	}

	reconos_cleanup();
	reconos_app_cleanup();
}
