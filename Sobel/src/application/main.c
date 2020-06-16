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
	int i;

	reconos_init();
	reconos_app_init();


	struct reconos_thread * thread_sobel = reconos_thread_create_hwt_sobel(0);


	while(1) 
	{
		sleep(100);
	}

	reconos_cleanup();
	reconos_app_cleanup();
}
