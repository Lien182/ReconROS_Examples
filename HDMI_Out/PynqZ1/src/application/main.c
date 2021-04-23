#include "memory.h"
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "zed_hdmi_display.h"
#include "hdmi_display_bsp/ps7_cortexa9_0/include/xparameters.h"

#include "reconos.h"
#include "reconos_app.h"


#define FB_SIZE 1920*1080*4

zed_hdmi_display_t demo;






int main(int argc, char **argv) {

	memory_init();

    reconos_app_init();
	
/*	demo.uBaseAddr_IIC_HdmiOut = XPAR_ZED_HDMI_IIC_0_BASEADDR;
    demo.uDeviceId_VTC_HdmioGenerator = XPAR_ZED_HDMI_DISPLAY_V_TC_0_DEVICE_ID;
    demo.uDeviceId_VDMA_HdmiDisplay = XPAR_ZED_HDMI_DISPLAY_AXI_VDMA_0_DEVICE_ID;
    demo.uBaseAddr_MEM_HdmiDisplay = XPAR_DDR_MEM_BASEADDR + 0x10000000;
    demo.uNumFrames_HdmiDisplay = XPAR_AXIVDMA_0_NUM_FSTORES;

	*/




	uint32_t* fb = mmap(0, FB_SIZE*2, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE, memfd, 0x1D000000);
    if(fb == NULL)
    {
        printf("Error while mapping fb \n");
        return -1;
    }

	demo.uBaseAddr_IIC_HdmiOut = mmap(0, 0x10000, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE, memfd, XPAR_ZED_HDMI_IIC_0_BASEADDR);
    demo.uDeviceId_VTC_HdmioGenerator = XPAR_ZED_HDMI_DISPLAY_V_TC_0_DEVICE_ID;
    demo.uBaseAddr_VTC_HdmioGenerator = mmap(0, 0x10000, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE, memfd, XPAR_ZED_HDMI_DISPLAY_V_TC_0_BASEADDR);
	demo.uDeviceId_VDMA_HdmiDisplay = XPAR_ZED_HDMI_DISPLAY_AXI_VDMA_0_DEVICE_ID;
	demo.uBaseAddr_VDMA_HdmiDisplay = mmap(0, 0x10000, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE, memfd, XPAR_ZED_HDMI_DISPLAY_AXI_VDMA_0_BASEADDR);
    demo.uBaseAddr_MEM_HdmiDisplay = (fb);
    demo.uNumFrames_HdmiDisplay = XPAR_AXIVDMA_0_NUM_FSTORES;




    //video_image_msg_in->data.size = FB_SIZE;
    //video_image_msg_in->data.capacity = FB_SIZE+2;
    //video_image_msg_in->data.data = fb;

    while(1)
    {
        ros_subscriber_message_take(video_subdata, video_image_msg_in);
		{
			printf("MSG= 0x%x \n", video_image_msg_in);
			memcpy(fb, video_image_msg_in->data.data,  800*600*4);
		}

        sleep(1);

    }

	return 0;
}