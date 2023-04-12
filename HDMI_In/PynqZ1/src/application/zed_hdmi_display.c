#include <stdio.h>

#include "zed_hdmi_display.h"

#include "axivdma.h"

#define ADV7511_ADDR   0x72
#define CARRIER_HDMI_OUT_CONFIG_LEN  (40)
uint8_t carrier_hdmi_out_config[CARRIER_HDMI_OUT_CONFIG_LEN][3] =
{
	{ADV7511_ADDR>>1, 0x15, 0x01}, // Input YCbCr 4:2:2 with seperate syncs
	{ADV7511_ADDR>>1, 0x16, 0x38}, // Output format 444, Input Color Depth = 8
                                   //    R0x16[  7] = Output Video Format = 0 (444)
                                   //    R0x16[5:4] = Input Video Color Depth = 11 (8 bits/color)
                                   //    R0x16[3:2] = Input Video Style = 10 (style 1)
                                   //    R0x16[  1] = DDR Input Edge = 0 (falling edge)
                                   //    R0x16[  0] = Output Color Space = 0 (RGB)
#if 0
    // HDTV YCbCr (16to235) to RGB (0to255)
	{ADV7511_ADDR>>1, 0x18, 0xE7}, // Color Space Conversion
                                   //    R0x18[  7] = CSC enable = 1 (CSC enabled)
                                   //    R0x18[6:5] = CSC Scaling Factor = 11 (+/- 4.0, -16384 - 16380)
                                   //    R0x18[4:0] = CSC coefficient A1[12:8] = 00111
	{ADV7511_ADDR>>1, 0x19, 0x34}, //    R0x19[7:0] = CSC coefficient A1[ 7:0] =      00110100
	{ADV7511_ADDR>>1, 0x1A, 0x04}, //    R0x1A[  5] = CSC coefficient update
                                   //    R0x1A[4:0] = CSC coefficient A2[12:8] = 00100
	{ADV7511_ADDR>>1, 0x1B, 0xAD}, //    R0x1B[7:0] = CSC coefficient A2[ 7:0] =      10101101
	{ADV7511_ADDR>>1, 0x1C, 0x00}, //    R0x1C[4:0] = CSC coefficient A3[12:8] = 00000
	{ADV7511_ADDR>>1, 0x1D, 0x00}, //    R0x1D[7:0] = CSC coefficient A3[ 7:0] =      00000000
	{ADV7511_ADDR>>1, 0x1E, 0x1C}, //    R0x1E[4:0] = CSC coefficient A4[12:8] = 11100
	{ADV7511_ADDR>>1, 0x1F, 0x1B}, //    R0x1F[7:0] = CSC coefficient A4[ 7:0] =      00011011
	{ADV7511_ADDR>>1, 0x20, 0x1D}, //    R0x20[4:0] = CSC coefficient B1[12:8] = 11101
	{ADV7511_ADDR>>1, 0x21, 0xDC}, //    R0x21[7:0] = CSC coefficient B1[ 7:0] =      11011100
	{ADV7511_ADDR>>1, 0x22, 0x04}, //    R0x22[4:0] = CSC coefficient B2[12:8] = 00100
	{ADV7511_ADDR>>1, 0x23, 0xAD}, //    R0x23[7:0] = CSC coefficient B2[ 7:0] =      10101101
	{ADV7511_ADDR>>1, 0x24, 0x1F}, //    R0x24[4:0] = CSC coefficient B3[12:8] = 11111
	{ADV7511_ADDR>>1, 0x25, 0x24}, //    R0x25[7:0] = CSC coefficient B3[ 7:0] =      00100100
	{ADV7511_ADDR>>1, 0x26, 0x01}, //    R0x26[4:0] = CSC coefficient B4[12:8] = 00001
	{ADV7511_ADDR//>>1, 0x27, 0x35}, //    R0x27[7:0] = CSC coefficient B4[ 7:0] =      00110101
	{ADV7511_ADDR>>1, 0x28, 0x00}, //    R0x28[4:0] = CSC coefficient C1[12:8] = 00000
	{ADV7511_ADDR>>1, 0x29, 0x00}, //    R0x29[7:0] = CSC coefficient C1[ 7:0] =      00000000
	{ADV7511_ADDR>>1, 0x2A, 0x04}, //    R0x2A[4:0] = CSC coefficient C2[12:8] = 00100
	{ADV7511_ADDR>>1, 0x2B, 0xAD}, //    R0x2B[7:0] = CSC coefficient C2[ 7:0] =      10101101
	{ADV7511_ADDR>>1, 0x2C, 0x08}, //    R0x2C[4:0] = CSC coefficient C3[12:8] = 01000
	{ADV7511_ADDR>>1, 0x2D, 0x7C}, //    R0x2D[7:0] = CSC coefficient C3[ 7:0] =      01111100
	{ADV7511_ADDR>>1, 0x2E, 0x1B}, //    R0x2E[4:0] = CSC coefficient C4[12:8] = 11011
	{ADV7511_ADDR>>1, 0x2F, 0x77}, //    R0x2F[7:0] = CSC coefficient C4[ 7:0] =      01110111
#else
	// HDTV YCbCr (16to235) to RGB (16to235)
	{ADV7511_ADDR>>1, 0x18, 0xAC},
	{ADV7511_ADDR>>1, 0x19, 0x53},
	{ADV7511_ADDR>>1, 0x1A, 0x08},
	{ADV7511_ADDR>>1, 0x1B, 0x00},
	{ADV7511_ADDR>>1, 0x1C, 0x00},
	{ADV7511_ADDR>>1, 0x1D, 0x00},
	{ADV7511_ADDR>>1, 0x1E, 0x19},
	{ADV7511_ADDR>>1, 0x1F, 0xD6},
	{ADV7511_ADDR>>1, 0x20, 0x1C},
	{ADV7511_ADDR>>1, 0x21, 0x56},
	{ADV7511_ADDR>>1, 0x22, 0x08},
	{ADV7511_ADDR>>1, 0x23, 0x00},
	{ADV7511_ADDR>>1, 0x24, 0x1E},
	{ADV7511_ADDR>>1, 0x25, 0x88},
	{ADV7511_ADDR>>1, 0x26, 0x02},
	{ADV7511_ADDR>>1, 0x27, 0x91},
	{ADV7511_ADDR>>1, 0x28, 0x1F},
	{ADV7511_ADDR>>1, 0x29, 0xFF},
	{ADV7511_ADDR>>1, 0x2A, 0x08},
	{ADV7511_ADDR>>1, 0x2B, 0x00},
	{ADV7511_ADDR>>1, 0x2C, 0x0E},
	{ADV7511_ADDR>>1, 0x2D, 0x85},
	{ADV7511_ADDR>>1, 0x2E, 0x18},
	{ADV7511_ADDR>>1, 0x2F, 0xBE},
#endif
	{ADV7511_ADDR>>1, 0x41, 0x10}, // Power down control
                                   //    R0x41[  6] = PowerDown = 0 (power-up)
	{ADV7511_ADDR>>1, 0x48, 0x08}, // Video Input Justification
                                   //    R0x48[8:7] = Video Input Justification = 01 (right justified)
	{ADV7511_ADDR>>1, 0x55, 0x00}, // Set RGB in AVinfo Frame
                                   //    R0x55[6:5] = Output Format = 00 (RGB)
	{ADV7511_ADDR>>1, 0x56, 0x28}, // Aspect Ratio
                                   //    R0x56[5:4] = Picture Aspect Ratio = 10 (16:9)
                                   //    R0x56[3:0] = Active Format Aspect Ratio = 1000 (Same as Aspect Ratio)
	{ADV7511_ADDR>>1, 0x98, 0x03}, // ADI Recommended Write
	{ADV7511_ADDR>>1, 0x9A, 0xE0}, // ADI Recommended Write
	{ADV7511_ADDR>>1, 0x9C, 0x30}, // PLL Filter R1 Value
	{ADV7511_ADDR>>1, 0x9D, 0x61}, // Set clock divide
	{ADV7511_ADDR>>1, 0xA2, 0xA4}, // ADI Recommended Write
	{ADV7511_ADDR>>1, 0xA3, 0xA4}, // ADI Recommended Write
	{ADV7511_ADDR>>1, 0xAF, 0x04}, // HDMI/DVI Modes
                                   //    R0xAF[  7] = HDCP Enable = 0 (HDCP disabled)
                                   //    R0xAF[  4] = Frame Encryption = 0 (Current frame NOT HDCP encrypted)
                                   //    R0xAF[3:2] = 01 (fixed)
                                   //    R0xAF[  1] = HDMI/DVI Mode Select = 0 (DVI Mode)
    //{ADV7511_ADDR>>1, 0xBA, 0x00}, // Programmable delay for input video clock = 000 = -1.2ns
	{ADV7511_ADDR>>1, 0xBA, 0x60}, // Programmable delay for input video clock = 011 = no delay
	{ADV7511_ADDR>>1, 0xE0, 0xD0}, // Must be set to 0xD0 for proper operation
	{ADV7511_ADDR>>1, 0xF9, 0x00}  // Fixed I2C Address (This should be set to a non-conflicting I2C address)
};


#define ___SC_PAGESIZE 0x1000

uintptr_t vvtop(uintptr_t vaddr) {
  FILE *pagemap;
    intptr_t paddr = 0;
    int offset = (vaddr / ___SC_PAGESIZE) * sizeof(uint64_t);
    uint64_t e;

    // https://www.kernel.org/doc/Documentation/vm/pagemap.txt
    if ((pagemap = fopen("/proc/self/pagemap", "r"))) {
        if (lseek(fileno(pagemap), offset, SEEK_SET) == offset) {
            if (fread(&e, sizeof(uint64_t), 1, pagemap)) {
                if (e & (1ULL << 63)) { // page present ?
                    paddr = e & ((1ULL << 54) - 1); // pfn mask
                    paddr = paddr * ___SC_PAGESIZE;
                    // add offset within page
                    paddr = paddr | (vaddr & (___SC_PAGESIZE - 1));
                }   
            }   
        }   
        fclose(pagemap);
    }   

    return paddr;
}   

int zed_hdmi_display_init( zed_hdmi_display_t *pDemo )
{
   int ret;
   uint32_t timeout = 100;
   uint32_t iterations = 0;


   // Set HDMI output to 1080P60 resolution
   // pDemo->hdmio_resolution = VIDEO_RESOLUTION_1080P;
   // pDemo->hdmio_width  = 1920;
   // pDemo->hdmio_height = 1080;

   pDemo->hdmio_resolution = VIDEO_RESOLUTION_SVGA;
   pDemo->hdmio_width  = 800;
   pDemo->hdmio_height = 600;

   // Clear frame stores
   printf( "Clear Frame Buffer\n\r" );
   zed_hdmi_display_clear( pDemo );

   // Initialize Output Side of AXI VDMA
   printf( "Video DMA (Output Side) Initialization ...\n\r" );




   // Configure VTC on output data path
   printf( "Video Timing Controller (generator) Initialization ...\n\r" );
   vgen_init( &(pDemo->vtc_hdmio_generator), pDemo->uBaseAddr_VTC_HdmioGenerator, pDemo->uDeviceId_VTC_HdmioGenerator );
   vgen_config( &(pDemo->vtc_hdmio_generator), pDemo->hdmio_resolution, 2 );
/*
  
   XAxiVdma_WriteReg((uint32_t*)pDemo->uBaseAddr_VDMA_HdmiDisplay,  0x05c, 0x1D000000); // start address
   XAxiVdma_WriteReg((uint32_t*)pDemo->uBaseAddr_VDMA_HdmiDisplay,  0x060, 0x1D000000); // start address
   XAxiVdma_WriteReg((uint32_t*)pDemo->uBaseAddr_VDMA_HdmiDisplay,  0x064, 0x1D000000); // start address
   XAxiVdma_WriteReg((uint32_t*)pDemo->uBaseAddr_VDMA_HdmiDisplay,  0x058, (800*4)); // h offset (640 * 4) bytes
   XAxiVdma_WriteReg((uint32_t*)pDemo->uBaseAddr_VDMA_HdmiDisplay,  0x054, (800*4)); // h size (640 * 4) bytes
   XAxiVdma_WriteReg((uint32_t*)pDemo->uBaseAddr_VDMA_HdmiDisplay,  0x050, 600); // v size (480)
 XAxiVdma_WriteReg((uint32_t*)pDemo->uBaseAddr_VDMA_HdmiDisplay,  0x000, 0x00000003); // enable circular mode
  */ 
#if 1 // Activate for debug
   sleep(1);
   // Status of AXI VDMA
   vfb_dump_registers( pDemo->uBaseAddr_VDMA_HdmiDisplay );
   if ( vfb_check_errors( pDemo->uBaseAddr_VDMA_HdmiDisplay, 0/*clear errors, if any*/ ) )
   {
      vfb_dump_registers( pDemo->uBaseAddr_VDMA_HdmiDisplay );
   }
#endif

   for(int i = 0; i < 20; i++)
   {
      printf("%03x ", i*8*4);
      for(int j = 0; j < 8; j++)
      {
         printf("0x%08x ", ((uint32_t*)pDemo->uBaseAddr_VDMA_HdmiDisplay)[j+i*8]);
      }
      printf("\n");
   }




   return 0;
}

int zed_hdmi_display_clear( zed_hdmi_display_t *pDemo )
{
   // Clear frame stores
   printf( "Video Frame Buffer Initialization ...\n\r" );
   uint32_t frame, row, col;
   uint32_t pixel;
   volatile uint32_t *pStorageMem = (uint32_t *)pDemo->uBaseAddr_MEM_HdmiDisplay;
   for ( frame = 0; frame < pDemo->uNumFrames_HdmiDisplay; frame++ )
   {
      for ( row = 0; row < pDemo->hdmio_height; row++ )
      {
         for ( col = 0; col < pDemo->hdmio_width; col++ )
         {
            //pixel = 0x00000000; // Black
            pixel = 0x000000FF; // White
            *pStorageMem++ = pixel;
         }
      }
   }
}

int zed_hdmi_display_cbars( zed_hdmi_display_t *pDemo, uint32_t offset )
{
   uint32_t frame, row, col;
   uint32_t cbar, pixel;
   volatile uint32_t *pStorageMem = (uint32_t *)pDemo->uBaseAddr_MEM_HdmiDisplay;
   for ( frame = 0; frame < pDemo->uNumFrames_HdmiDisplay; frame++ )
   {
      for ( row = 0; row < pDemo->hdmio_height; row++ )
      {
         for ( col = 0; col < pDemo->hdmio_width; col++ )
         {
            cbar = (col * 8) / pDemo->hdmio_width; // color bar = 0..7
            cbar = (cbar + offset) % 8;
            switch ( cbar )
            {
               case 0: pixel = 0x00000000; break; // Black
               case 1: pixel = 0x00FF0000; break; // Red
               case 2: pixel = 0x0000FF00; break; // Green
               case 3: pixel = 0x000000FF; break; // Blue
               case 4: pixel = 0x0000FFFF; break; // Cyan
               case 5: pixel = 0x00FF00FF; break; // Purple
               case 6: pixel = 0x00FFFF00; break; // Yellow
               case 7: pixel = 0x00FFFFFF; break; // White
            }
            *pStorageMem++ = pixel;
         }
      }
   }

   // Wait for DMA to synchronize.
  
#warning todo
  //Xil_DCacheFlush();

   return 0;
}
