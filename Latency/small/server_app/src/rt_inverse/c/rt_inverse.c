/********************************************************************          
* main.c           -software implementation inverse thread function	*
*                        				                            *
*                                                                   *  
* Author(s): Christoph Rueting, Christian Lienen                    *   
*                                                                   *   
********************************************************************/
#include "reconos_thread.h"
#include "reconos_calls.h"
#include "utils.h"

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <float.h>


#define DIRECTAXIACCESS 1
#define DEBUG 0
#define DEBUG_LIGHT 1

// definitions of stewart platform

// coordinates of platform joints in base coordinates
int p_p_j_x[6] = {51,-51,-64,-13,13,64};
int p_p_j_y[6] = {44,44,22,-66,-66,22};

// transformation to base coordinates
float t_p2b_t_z = 80 + 25;

// transformation to servo coordinates
float t_b2s_rz_sin[6] = {0.00000000,0.00000000,-0.86602540,-0.86602540,0.86602540,0.86602540};
float t_b2s_rz_cos[6] = {1.00000000,1.00000000,-0.50000000,-0.50000000,-0.50000000,-0.50000000};
int t_b2s_s_x[6] = {-1,1,-1,1,-1,1};
int t_b2s_s_y[6] = {1,1,1,1,1,1};
int t_b2s_s_z[6] = {1,-1,1,-1,1,-1};
int t_b2s_t_x = 33;
int t_b2s_t_y = -69;
int t_b2s_t_z = 0;

// leg and arm lengths
int c_leg = 115;
int c_legs = 115 * 115;
int c_arm = 20;

// sine and cosine lookup tables
#define TRIG_COUNT 2048
#define TRIG_ADDR 11
#define TRIG_MIN_ANGLE_DEG 0
#define TRIG_MAX_ANGLE_DEG 204.7
#define TRIG_STEP 0.1



static inline float radians(float deg) {
	return deg * (M_PI / 180.0);
}
static inline float sin_lut(float a) {
	return sin(radians(a * TRIG_STEP));
}
static inline float cos_lut(float a) {
	return cos(radians(a * TRIG_STEP));
}

	static inline uint32_t fltofi(float f, int n, int dn) {
		int i;
		int wn = n - dn;

		int d;
		float w;

		uint32_t df, wf;
		uint32_t m = 0xffffffff;

		if (f > 0) {
			d = floor(f);
			w = f - d;
		} else {
			d = floor(f);
			w = f - d;
		}

		df = 0 | (d << wn);

		wf = 0;
		for (i = -1; i >= -wn; i--) {
			if (w >= pow(2, i)) {
				wf |= 1 << (wn + i);
				w -= pow(2, i);
			}
		}

		return (df | wf) & (m >> (32 - n));
	}

	static inline float fitofl(uint32_t f, int n, int dn) {
		int i;
		int wn = n - dn;

		int d;
		float w;

		uint32_t m = 0xffffffff;

		if (((f >> (n - 1)) & 0x1) == 1) {
			d = (m << dn) | (f >> wn);
		} else {
			d = 0 | (f >> wn);
		}

		w = 0;
		for (i = -1; i >= -wn; i--) {
			if (((f >> (wn + i)) & 0x1) == 1) {
				w += pow(2, i);
			}
		}

		return d + w;
	}


THREAD_ENTRY() {
	int i;
	clock_t start, end;
	
	THREAD_INIT();

	while (1) {
		

		ROS_SUBSCRIBE_TAKE(inverse_subdata, inverse_input_msg);
		start = clock();
		uint32_t data = inverse_input_msg->data;

		
		inverse_output_msg->data = data;
		end = clock();
		ROS_PUBLISH(inverse_pubdata, inverse_output_msg);
		printf("%3.6f; \n", (double)(end-start)/CLOCKS_PER_SEC);
	}
}