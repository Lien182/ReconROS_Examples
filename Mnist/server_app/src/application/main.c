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
		printf("Usage: ./mnist <sw/hw> \n");
		return -1;
	}
	

	if(bUseHW == 1)
	{
		struct reconos_thread * thread_mnist = reconos_thread_create_hwt_mnist(&(resources_mnist_srv_res->digit) );
	}
	else
	{
		struct reconos_thread * thread_mnist = reconos_thread_create_swt_mnist(&(resources_mnist_srv_res->digit),0 );
	}
	

	while(1) 
	{
		sleep(100);
	}

	reconos_cleanup();
	reconos_app_cleanup();
}
