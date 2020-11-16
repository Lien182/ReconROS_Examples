#include "reconos.h"
#include "reconos_app.h"
#include "mbox.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BLOCK_SIZE 2048




#define log(...) printf(__VA_ARGS__); fflush(stdout)


int cmp_uint32t(const void *a, const void *b) {
	return *(uint32_t *)a - *(uint32_t *)b;
}

void _merge(uint32_t *data, uint32_t *tmp,
           int l_count, int r_count) {
	int i;
	uint32_t *l = data, *r = data + l_count;
	int li = 0, ri = 0;

	for (i = 0; i < l_count; i++) {
		tmp[i] = l[i];
	}

	for (i = 0; i < l_count + r_count; i++) {
		if (ri >= r_count || (li < l_count && tmp[li] < r[ri])) {
			data[i] = tmp[li];
			li++;
		} else {
			data[i] = r[ri];
			ri++;
		}
	}
}

void merge(uint32_t *data, int data_count) {
	int bs, bi;
	uint32_t *tmp;

	tmp = (uint32_t *)malloc(data_count * sizeof(uint32_t));

	for (bs = BLOCK_SIZE; bs < data_count; bs += bs) {
		for (bi = 0; bi < data_count; bi += bs + bs) {
			if (bi + bs + bs > data_count) {
				_merge(data + bi, tmp, bs, data_count - bi - bs);
			} else {
				_merge(data + bi, tmp, bs, bs);
			}
		}
	}

	free(tmp);
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
		printf("Usage: ./sortdemo <sw/hw> \n");
		return -1;
	}
	

	if(bUseHW == 1)
	{
		struct reconos_thread * thread_sobel = reconos_thread_create_hwt_sortdemo(10 );
	}
	else
	{
		struct reconos_thread * thread_sobel = reconos_thread_create_swt_sortdemo(0,0);
	}

	while(1)
	{
		sleep(1);
		
	} 

	reconos_app_cleanup();
	reconos_cleanup();

	return 0;
}