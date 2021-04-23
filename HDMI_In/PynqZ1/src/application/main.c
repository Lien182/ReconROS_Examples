#include "memory.h"
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <fcntl.h>


#include "zed_hdmi_display.h"
#include "hdmi_display_bsp/ps7_cortexa9_0/include/xparameters.h"

#include "reconos.h"
#include "reconos_app.h"


#define FB_SIZE 1920*1080*4

zed_hdmi_display_t demo;



int check_errors(uint32_t* uBaseAddr, uint8_t bClearErrors )
{

   uint32_t inErrors;
   uint32_t outErrors;
   uint32_t Errors;

   // Get Status of Error Flags
   //inErrors = XAxiVdma_GetStatus(pAxiVdma, XAXIVDMA_WRITE) & XAXIVDMA_SR_ERR_ALL_MASK;
   //outErrors = XAxiVdma_GetStatus(pAxiVdma, XAXIVDMA_READ) & XAXIVDMA_SR_ERR_ALL_MASK;


   inErrors  = uBaseAddr[(XAXIVDMA_RX_OFFSET+XAXIVDMA_SR_OFFSET)/4 ] & 0x0000CFF0;
   outErrors = uBaseAddr[(XAXIVDMA_TX_OFFSET+XAXIVDMA_SR_OFFSET)/4 ] & 0x000046F0;
   printf( "AXI_VDMA - Checking Error Flags\n\r" );

   Errors = (inErrors << 16) | (outErrors);

   if ( Errors )
   {
	   if ( inErrors & 0x00004000 )
	   {
          printf( "\tS2MM_DMASR - ErrIrq\n\r" );
	   }
	   if ( inErrors & 0x00008000 )
	   {
          printf( "\tS2MM_DMASR - EOLLateErr\n\r" );
	   }
	   if ( inErrors & 0x00000800 )
	   {
          printf( "\tS2MM_DMASR - SOFLateErr\n\r" );
	   }
	   if ( inErrors & 0x00000400 )
	   {
          printf( "\tS2MM_DMASR - SGDecErr\n\r" );
	   }
	   if ( inErrors & 0x00000200 )
	   {
          printf( "\tS2MM_DMASR - SGSlvErr\n\r" );
	   }
	   if ( inErrors & 0x00000100 )
	   {
          printf( "\tS2MM_DMASR - EOLEarlyErr\n\r" );
	   }
	   if ( inErrors & 0x00000080 )
	   {
          printf( "\tS2MM_DMASR - SOFEarlyErr\n\r" );
	   }
	   if ( inErrors & 0x00000040 )
	   {
          printf( "\tS2MM_DMASR - DMADecErr\n\r" );
	   }
	   if ( inErrors & 0x00000020 )
	   {
          printf( "\tS2MM_DMASR - DMASlvErr\n\r" );
	   }
	   if ( inErrors & 0x00000010 )
	   {
          printf( "\tS2MM_DMASR - DMAIntErr\n\r" );
	   }

	   if ( outErrors & 0x00004000 )
	   {
          printf( "\tMM2S_DMASR - ErrIrq\n\r" );
	   }
	   if ( outErrors & 0x00000400 )
	   {
          printf( "\tMM2S_DMASR - SGDecErr\n\r" );
	   }
	   if ( outErrors & 0x00000200 )
	   {
          printf( "\tMM2S_DMASR - SGSlvErr\n\r" );
	   }
	   if ( outErrors & 0x00000080 )
	   {
          printf( "\tMM2S_DMASR - SOFEarlyErr\n\r" );
	   }
	   if ( outErrors & 0x00000040 )
	   {
          printf( "\tMM2S_DMASR - DMADecErr\n\r" );
	   }
	   if ( outErrors & 0x00000020 )
	   {
          printf( "\tMM2S_DMASR - DMASlvErr\n\r" );
	   }
	   if ( outErrors & 0x00000010 )
	   {
          printf( "\tMM2S_DMASR - DMAIntErr\n\r" );
	   }

	   // Clear error flags
	   printf( "AXI_VDMA - Clearing Error Flags\n\r" );
       if(bClearErrors)
       {
        XAxiVdma_WriteReg(uBaseAddr,XAXIVDMA_RX_OFFSET+XAXIVDMA_SR_OFFSET, 0x0000CFF0); //XAXIVDMA_SR_ERR_ALL_MASK;
        XAxiVdma_WriteReg(uBaseAddr,XAXIVDMA_TX_OFFSET+XAXIVDMA_SR_OFFSET, 0x000046F0); //XAXIVDMA_SR_ERR_ALL_MASK;
       }

   }

   return Errors;
}

/*
 * Triple buffering example for Xilinx VDMA v6.2 IP-core,
 * loosely based on Ales Ruda's work.
 *
 *  Created on: 17.3.2013
 *      Author: Ales Ruda
 *         web: www.arbot.cz
 *
 *  Modified on: 18.12.2014
 *       Author: Lauri Vosandi
 *          web: lauri.vosandi.com
 */



/* Register offsets */
#define OFFSET_PARK_PTR_REG                     0x28
#define OFFSET_VERSION                          0x2c

#define OFFSET_VDMA_MM2S_CONTROL_REGISTER       0x00
#define OFFSET_VDMA_MM2S_STATUS_REGISTER        0x04
#define OFFSET_VDMA_MM2S_VSIZE                  0x50
#define OFFSET_VDMA_MM2S_HSIZE                  0x54
#define OFFSET_VDMA_MM2S_FRMDLY_STRIDE          0x58
#define OFFSET_VDMA_MM2S_FRAMEBUFFER1           0x5c
#define OFFSET_VDMA_MM2S_FRAMEBUFFER2           0x60
#define OFFSET_VDMA_MM2S_FRAMEBUFFER3           0x64
#define OFFSET_VDMA_MM2S_FRAMEBUFFER4           0x68

#define OFFSET_VDMA_S2MM_CONTROL_REGISTER       0x30
#define OFFSET_VDMA_S2MM_STATUS_REGISTER        0x34
#define OFFSET_VDMA_S2MM_IRQ_MASK               0x3c
#define OFFSET_VDMA_S2MM_REG_INDEX              0x44
#define OFFSET_VDMA_S2MM_VSIZE                  0xa0
#define OFFSET_VDMA_S2MM_HSIZE                  0xa4
#define OFFSET_VDMA_S2MM_FRMDLY_STRIDE          0xa8
#define OFFSET_VDMA_S2MM_FRAMEBUFFER1           0xac
#define OFFSET_VDMA_S2MM_FRAMEBUFFER2           0xb0
#define OFFSET_VDMA_S2MM_FRAMEBUFFER3           0xb4
#define OFFSET_VDMA_S2MM_FRAMEBUFFER4           0xb8

/* S2MM and MM2S control register flags */
#define VDMA_CONTROL_REGISTER_START                     0x00000001
#define VDMA_CONTROL_REGISTER_CIRCULAR_PARK             0x00000002
#define VDMA_CONTROL_REGISTER_RESET                     0x00000004
#define VDMA_CONTROL_REGISTER_GENLOCK_ENABLE            0x00000008
#define VDMA_CONTROL_REGISTER_FrameCntEn                0x00000010
#define VDMA_CONTROL_REGISTER_INTERNAL_GENLOCK          0x00000080
#define VDMA_CONTROL_REGISTER_WrPntr                    0x00000f00
#define VDMA_CONTROL_REGISTER_FrmCtn_IrqEn              0x00001000
#define VDMA_CONTROL_REGISTER_DlyCnt_IrqEn              0x00002000
#define VDMA_CONTROL_REGISTER_ERR_IrqEn                 0x00004000
#define VDMA_CONTROL_REGISTER_Repeat_En                 0x00008000
#define VDMA_CONTROL_REGISTER_InterruptFrameCount       0x00ff0000
#define VDMA_CONTROL_REGISTER_IRQDelayCount             0xff000000

/* S2MM status register */
#define VDMA_STATUS_REGISTER_HALTED                     0x00000001  // Read-only
#define VDMA_STATUS_REGISTER_VDMAInternalError          0x00000010  // Read or write-clear
#define VDMA_STATUS_REGISTER_VDMASlaveError             0x00000020  // Read-only
#define VDMA_STATUS_REGISTER_VDMADecodeError            0x00000040  // Read-only
#define VDMA_STATUS_REGISTER_StartOfFrameEarlyError     0x00000080  // Read-only
#define VDMA_STATUS_REGISTER_EndOfLineEarlyError        0x00000100  // Read-only
#define VDMA_STATUS_REGISTER_StartOfFrameLateError      0x00000800  // Read-only
#define VDMA_STATUS_REGISTER_FrameCountInterrupt        0x00001000  // Read-only
#define VDMA_STATUS_REGISTER_DelayCountInterrupt        0x00002000  // Read-only
#define VDMA_STATUS_REGISTER_ErrorInterrupt             0x00004000  // Read-only
#define VDMA_STATUS_REGISTER_EndOfLineLateError         0x00008000  // Read-only
#define VDMA_STATUS_REGISTER_FrameCount                 0x00ff0000  // Read-only
#define VDMA_STATUS_REGISTER_DelayCount                 0xff000000  // Read-only

typedef struct {
    unsigned int baseAddr;
    int vdmaHandler;
    int width;
    int height;
    int pixelLength;
    int fbLength;
    unsigned int* vdmaVirtualAddress;
    unsigned char* fb1VirtualAddress;
    unsigned char* fb1PhysicalAddress;
    unsigned char* fb2VirtualAddress;
    unsigned char* fb2PhysicalAddress;
    unsigned char* fb3VirtualAddress;
    unsigned char* fb3PhysicalAddress;

    pthread_mutex_t lock;
} vdma_handle;



int vdma_setup(vdma_handle *handle, unsigned int baseAddr, int width, int height, int pixelLength, unsigned int fb1Addr, unsigned int fb2Addr, unsigned int fb3Addr) {
    handle->baseAddr=baseAddr;
    handle->width=width;
    handle->height=height;
    handle->pixelLength=pixelLength;
    handle->fbLength=pixelLength*width*height;
    handle->vdmaHandler = open("/dev/mem", O_RDWR | O_SYNC);
    handle->vdmaVirtualAddress = (unsigned int*)mmap(NULL, 65535, PROT_READ | PROT_WRITE, MAP_SHARED, handle->vdmaHandler, (off_t)handle->baseAddr);
    if(handle->vdmaVirtualAddress == MAP_FAILED) {
        perror("vdmaVirtualAddress mapping for absolute memory access failed.\n");
        return -1;
    }

    handle->fb1PhysicalAddress = fb1Addr;
    handle->fb1VirtualAddress = (unsigned char*)mmap(NULL, handle->fbLength, PROT_READ | PROT_WRITE, MAP_SHARED, handle->vdmaHandler, (off_t)fb1Addr);
    if(handle->fb1VirtualAddress == MAP_FAILED) {
        perror("fb1VirtualAddress mapping for absolute memory access failed.\n");
        return -2;
    }

    handle->fb2PhysicalAddress = fb2Addr;
    handle->fb2VirtualAddress = (unsigned char*)mmap(NULL, handle->fbLength, PROT_READ | PROT_WRITE, MAP_SHARED, handle->vdmaHandler, (off_t)fb2Addr);
    if(handle->fb2VirtualAddress == MAP_FAILED) {
        perror("fb2VirtualAddress mapping for absolute memory access failed.\n");
        return -3;
    }

    handle->fb3PhysicalAddress = fb3Addr;
    handle->fb3VirtualAddress = (unsigned char*)mmap(NULL, handle->fbLength, PROT_READ | PROT_WRITE, MAP_SHARED, handle->vdmaHandler, (off_t)fb3Addr);
    if(handle->fb3VirtualAddress == MAP_FAILED)
    {
     perror("fb3VirtualAddress mapping for absolute memory access failed.\n");
     return -3;
    }

    memset(handle->fb1VirtualAddress, 255, handle->width*handle->height*handle->pixelLength);
    memset(handle->fb2VirtualAddress, 255, handle->width*handle->height*handle->pixelLength);
    memset(handle->fb3VirtualAddress, 255, handle->width*handle->height*handle->pixelLength);
    return 0;
}


void vdma_halt(vdma_handle *handle) {
    vdma_set(handle, OFFSET_VDMA_S2MM_CONTROL_REGISTER, VDMA_CONTROL_REGISTER_RESET);
    vdma_set(handle, OFFSET_VDMA_MM2S_CONTROL_REGISTER, VDMA_CONTROL_REGISTER_RESET);
    munmap((void *)handle->vdmaVirtualAddress, 65535);
    munmap((void *)handle->fb1VirtualAddress, handle->fbLength);
    munmap((void *)handle->fb2VirtualAddress, handle->fbLength);
    munmap((void *)handle->fb3VirtualAddress, handle->fbLength);
    close(handle->vdmaHandler);
}

unsigned int vdma_get(vdma_handle *handle, int num) {
    return handle->vdmaVirtualAddress[num>>2];
}

void vdma_set(vdma_handle *handle, int num, unsigned int val) {
    handle->vdmaVirtualAddress[num>>2]=val;
}

void vdma_status_dump(int status) {
    if (status & VDMA_STATUS_REGISTER_HALTED) printf(" halted"); else printf("running");
    if (status & VDMA_STATUS_REGISTER_VDMAInternalError) printf(" vdma-internal-error");
    if (status & VDMA_STATUS_REGISTER_VDMASlaveError) printf(" vdma-slave-error");
    if (status & VDMA_STATUS_REGISTER_VDMADecodeError) printf(" vdma-decode-error");
    if (status & VDMA_STATUS_REGISTER_StartOfFrameEarlyError) printf(" start-of-frame-early-error");
    if (status & VDMA_STATUS_REGISTER_EndOfLineEarlyError) printf(" end-of-line-early-error");
    if (status & VDMA_STATUS_REGISTER_StartOfFrameLateError) printf(" start-of-frame-late-error");
    if (status & VDMA_STATUS_REGISTER_FrameCountInterrupt) printf(" frame-count-interrupt");
    if (status & VDMA_STATUS_REGISTER_DelayCountInterrupt) printf(" delay-count-interrupt");
    if (status & VDMA_STATUS_REGISTER_ErrorInterrupt) printf(" error-interrupt");
    if (status & VDMA_STATUS_REGISTER_EndOfLineLateError) printf(" end-of-line-late-error");
    printf(" frame-count:%d", (status & VDMA_STATUS_REGISTER_FrameCount) >> 16);
    printf(" delay-count:%d", (status & VDMA_STATUS_REGISTER_DelayCount) >> 24);
    printf("\n");
}

void vdma_s2mm_status_dump(vdma_handle *handle) {
    int status = vdma_get(handle, OFFSET_VDMA_S2MM_STATUS_REGISTER);
    printf("S2MM status register (%08x):", status);
    vdma_status_dump(status);
}

void vdma_mm2s_status_dump(vdma_handle *handle) {
    int status = vdma_get(handle, OFFSET_VDMA_MM2S_STATUS_REGISTER);
    printf("MM2S status register (%08x):", status);
    vdma_status_dump(status);
}

void vdma_start_triple_buffering(vdma_handle *handle) {
    // Reset VDMA
    vdma_set(handle, OFFSET_VDMA_S2MM_CONTROL_REGISTER, VDMA_CONTROL_REGISTER_RESET);
    vdma_set(handle, OFFSET_VDMA_MM2S_CONTROL_REGISTER, VDMA_CONTROL_REGISTER_RESET);

    // Wait for reset to finish
    while((vdma_get(handle, OFFSET_VDMA_S2MM_CONTROL_REGISTER) & VDMA_CONTROL_REGISTER_RESET)==4) usleep(100);
    while((vdma_get(handle, OFFSET_VDMA_MM2S_CONTROL_REGISTER) & VDMA_CONTROL_REGISTER_RESET)==4) usleep(100);

    // Clear all error bits in status register
    vdma_set(handle, OFFSET_VDMA_S2MM_STATUS_REGISTER, 0);
    vdma_set(handle, OFFSET_VDMA_MM2S_STATUS_REGISTER, 0);

    // Do not mask interrupts
    vdma_set(handle, OFFSET_VDMA_S2MM_IRQ_MASK, 0xf);

    int interrupt_frame_count = 3;

    // Start both S2MM and MM2S in triple buffering mode
    vdma_set(handle, OFFSET_VDMA_S2MM_CONTROL_REGISTER,
        (interrupt_frame_count << 16) |
        VDMA_CONTROL_REGISTER_START |
        VDMA_CONTROL_REGISTER_GENLOCK_ENABLE |
        VDMA_CONTROL_REGISTER_INTERNAL_GENLOCK |
        VDMA_CONTROL_REGISTER_CIRCULAR_PARK);
    vdma_set(handle, OFFSET_VDMA_MM2S_CONTROL_REGISTER,
        (interrupt_frame_count << 16) |
        VDMA_CONTROL_REGISTER_START |
        VDMA_CONTROL_REGISTER_GENLOCK_ENABLE |
        VDMA_CONTROL_REGISTER_INTERNAL_GENLOCK |
        VDMA_CONTROL_REGISTER_CIRCULAR_PARK);


    //while((vdma_get(handle, 0x30)&1)==0 || (vdma_get(handle, 0x34)&1)==1) 
    {
        printf("Waiting for VDMA to start running...\n");
        sleep(1);
    }

    // Extra register index, use first 16 frame pointer registers
    vdma_set(handle, OFFSET_VDMA_S2MM_REG_INDEX, 0);

    // Write physical addresses to control register
    vdma_set(handle, OFFSET_VDMA_S2MM_FRAMEBUFFER1, handle->fb1PhysicalAddress);
    vdma_set(handle, OFFSET_VDMA_MM2S_FRAMEBUFFER1, handle->fb1PhysicalAddress);
    vdma_set(handle, OFFSET_VDMA_S2MM_FRAMEBUFFER2, handle->fb2PhysicalAddress);
    vdma_set(handle, OFFSET_VDMA_MM2S_FRAMEBUFFER2, handle->fb2PhysicalAddress);
    vdma_set(handle, OFFSET_VDMA_S2MM_FRAMEBUFFER3, handle->fb3PhysicalAddress);
    vdma_set(handle, OFFSET_VDMA_MM2S_FRAMEBUFFER3, handle->fb3PhysicalAddress);

    // Write Park pointer register
    vdma_set(handle, OFFSET_PARK_PTR_REG, 0);

    // Frame delay and stride (bytes)
    vdma_set(handle, OFFSET_VDMA_S2MM_FRMDLY_STRIDE, handle->width*handle->pixelLength);
    vdma_set(handle, OFFSET_VDMA_MM2S_FRMDLY_STRIDE, handle->width*handle->pixelLength);

    // Write horizontal size (bytes)
    vdma_set(handle, OFFSET_VDMA_S2MM_HSIZE, handle->width*handle->pixelLength);
    vdma_set(handle, OFFSET_VDMA_MM2S_HSIZE, handle->width*handle->pixelLength);

    // Write vertical size (lines), this actually starts the transfer
    vdma_set(handle, OFFSET_VDMA_S2MM_VSIZE, handle->height);
    vdma_set(handle, OFFSET_VDMA_MM2S_VSIZE, handle->height);
}

int vdma_running(vdma_handle *handle) {
    // Check whether VDMA is running, that is ready to start transfers
    return (vdma_get(handle, 0x34)&1)==1;
}

int vdma_idle(vdma_handle *handle) {
    // Check whtether VDMA is transferring
    return (vdma_get(handle, OFFSET_VDMA_S2MM_STATUS_REGISTER) & VDMA_STATUS_REGISTER_FrameCountInterrupt)!=0;
}




int main(int argc, char **argv) {

	memory_init();

    reconos_app_init();
	

	uint32_t* fb = mmap(0, FB_SIZE*2, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE, memfd, 0x1D000000);
    if(fb == NULL)
    {
        printf("Error while mapping fb \n");
        return -1;
    }

    uint32_t * clk_generator =  mmap(0, 0x10000 , PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE, memfd, 0x43C10000);
    uint32_t * clk_out       =  mmap(0, 0x10000 , PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE, memfd, 0x43C00000);  

    while(clk_out[0x04/4] & 1 != 1) usleep(100);

    /*0x208 reg values*/
    /* see readme on how values are derived.
     * 0x000E for 720p
     * 0x0010 for XGA   1024 × 768 (XGA)
     * 0x001A for SVGA 	800 × 600 (SVGA)
     * */

    clk_out[0x208/4] =  0x000A;
    clk_out[0x25C/4] =  0x3;

    while(clk_out[0x04/4] & 1 != 1) usleep(100);


	//demo.uBaseAddr_IIC_HdmiOut = mmap(0, 0x10000, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE, memfd, XPAR_ZED_HDMI_IIC_0_BASEADDR);
    demo.uDeviceId_VTC_HdmioGenerator =     XPAR_ZED_HDMI_DISPLAY_V_TC_0_DEVICE_ID;
    demo.uBaseAddr_VTC_HdmioGenerator =     clk_generator;
	demo.uDeviceId_VDMA_HdmiDisplay =       XPAR_ZED_HDMI_DISPLAY_AXI_VDMA_0_DEVICE_ID;
	demo.uBaseAddr_VDMA_HdmiDisplay =       clk_generator;
    demo.uBaseAddr_MEM_HdmiDisplay =        (fb);
    demo.uNumFrames_HdmiDisplay =           XPAR_AXIVDMA_0_NUM_FSTORES;


    zed_hdmi_display_init( &demo );



    int j, i;
    vdma_handle handle;

    // Setup VDMA handle and memory-mapped ranges
    vdma_setup(&handle, 0x43000000, 1280, 720, 3, 0x1D000000, 0x1D000000, 0x1D000000);

    // Start triple buffering
    vdma_start_triple_buffering(&handle);

    // Run for 10 seconds, just monitor status registers
    for(i=0; i<100; i++) {
        vdma_s2mm_status_dump(&handle);
        vdma_mm2s_status_dump(&handle);
        printf("FB1:\n");
        for (j = 0; j < 256; j++) printf(" %02x", handle.fb1VirtualAddress[j]); printf("\n");
        sleep(1);
    }

    // Halt VDMA and unmap memory ranges
    vdma_halt(&handle);

    uint32_t * video_dma =      mmap(0, 0x10000 , PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE, memfd, 0x43000000);


    while(1)
    {
        /*
        ros_subscriber_message_take(video_subdata, video_image_msg_in);
		{
			printf("MSG= 0x%x \n", video_image_msg_in);
			memcpy(fb, video_image_msg_in->data.data,  800*600*4);
		}

        */


       
        //vfb_check_errors( video_dma, 0/*clear errors, if any*/ );
        
        printf("VDMA In: \n");
        for(int i = 0; i < 20; i++)
            {
            printf("%03x ", i*8*4);
            for(int j = 0; j < 8; j++)
            {
                printf("0x%08x ", ((uint32_t*)video_dma)[j+i*8]);
            }
            printf("\n");
        }
        
        
        
        printf("Clock Generator Out: \n");
        for(int i = 0; i < 10; i++)
            {
            printf("%03x ", i*8*4);
            for(int j = 0; j < 8; j++)
            {
                printf("0x%08x ", ((uint32_t*)clk_generator)[j+i*8]);
            }
            printf("\n");
        }



       uint32_t hash = 0;

        for(int i = 100; i < 300; i++)
            for(int j = 100; j < 300; j++)
                hash ^= fb[j+i*800];
        
        printf("Hash: %d \n", hash);

         sleep(1);
       
    }

	return 0;
}