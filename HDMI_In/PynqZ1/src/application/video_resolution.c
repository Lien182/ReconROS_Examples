#include <stdio.h>
#include "video_resolution.h"


// Located in: microblaze_0/include/
//#include "xbasic_types.h"

vres_timing_t vres_resolutions[NUM_VIDEO_RESOLUTIONS] = {
   // name     vav,  vfp,  vsw,  vbp,  vsp,  hav,  hfp,  hsw,  hbp,  hsp
   { "VGA",    480,   10,    2,   33,    0,  640,   16,   96,   48,    0 }, // VIDEO_RESOLUTION_VGA
   { "480P",   480,    9,    6,   30,    0,  720,   16,   62,   60,    0 }, // VIDEO_RESOLUTION_480P
   { "576P",   576,    5,    5,   39,    0,  720,   12,   64,   68,    0 }, // VIDEO_RESOLUTION_576P
   { "SVGA",   600,    1,    4,   23,    1,  800,   40,  128,   88,    1 }, // VIDEO_RESOLUTION_SVGA
   { "XGA",    768,    3,    6,   29,    0, 1024,   24,  136,  160,    0 }, // VIDEO_RESOLUTION_XGA
   { "720P",   720,    5,    5,   20,    1, 1280,  110,   40,  220,    1 }, // VIDEO_RESOLUTION_720P
   { "SXGA",  1024,    1,    3,   26,    0, 1280,   48,  184,  200,    0 }, // VIDEO_RESOLUTION_SXGA
   { "1080P", 1080,    4,    5,   36,    1, 1920,   88,   44,  148,    1 }, // VIDEO_RESOLUTION_1080P
   { "UXGA",  1200,    1,    3,   46,    0, 1600,   64,  192,  304,    0 }  // VIDEO_RESOLUTION_UXGA
};

char *vres_get_name(uint32_t resolutionId)
{
   if ( resolutionId < NUM_VIDEO_RESOLUTIONS )
   {
      return vres_resolutions[resolutionId].pName;
   }
   else
   {
      return "{UNKNOWN}";
   }
}

uint32_t vres_get_width(uint32_t resolutionId)
{
   return vres_resolutions[resolutionId].HActiveVideo; // horizontal active
}

uint32_t vres_get_height(uint32_t resolutionId)
{
   return vres_resolutions[resolutionId].VActiveVideo; // vertical active
}

uint32_t vres_get_timing(uint32_t ResolutionId, vres_timing_t *pTiming )
{
	pTiming->pName         = vres_resolutions[ResolutionId].pName;
	pTiming->HActiveVideo  = vres_resolutions[ResolutionId].HActiveVideo;
	pTiming->HFrontPorch   = vres_resolutions[ResolutionId].HFrontPorch;
	pTiming->HSyncWidth    = vres_resolutions[ResolutionId].HSyncWidth;
	pTiming->HBackPorch    = vres_resolutions[ResolutionId].HBackPorch;
	pTiming->HSyncPolarity = vres_resolutions[ResolutionId].HSyncPolarity;
	pTiming->VActiveVideo  = vres_resolutions[ResolutionId].VActiveVideo;
	pTiming->VFrontPorch   = vres_resolutions[ResolutionId].VFrontPorch;
	pTiming->VSyncWidth    = vres_resolutions[ResolutionId].VSyncWidth;
	pTiming->VBackPorch    = vres_resolutions[ResolutionId].VBackPorch;
	pTiming->VSyncPolarity = vres_resolutions[ResolutionId].VSyncPolarity;

//	xil_printf("vres_get_timing(%d,...)\n\r", ResolutionId );
//	xil_printf("\tpName = %s\n\r", pTiming->pName );
//	xil_printf("\tHActiveVideo = %d\n\r", pTiming->HActiveVideo );
//	xil_printf("\tHFrontPorch = %d\n\r", pTiming->HFrontPorch );
//	xil_printf("\tHSyncWidth = %d\n\r", pTiming->HSyncWidth );
//	xil_printf("\tHBackPorch = %d\n\r", pTiming->HBackPorch );
//	xil_printf("\tHSyncPolarity = %d\n\r", pTiming->HSyncPolarity );
//	xil_printf("\tVActiveVideo = %d\n\r", pTiming->VActiveVideo );
//	xil_printf("\tVFrontPorch = %d\n\r", pTiming->VFrontPorch );
//	xil_printf("\tVSyncWidth = %d\n\r", pTiming->VSyncWidth );
//	xil_printf("\tVBackPorch = %d\n\r", pTiming->VBackPorch );
//	xil_printf("\tVSyncPolarity = %d\n\r", pTiming->VSyncPolarity );

	return 0;
}
/////////////////////////////////////////////////////////////////////////
uint32_t vres_detect( uint32_t width, uint32_t height )
{
  uint32_t i;
  uint32_t resolution = -1;

  for ( i = 0; i < NUM_VIDEO_RESOLUTIONS; i++ )
  {
     if ( width == vres_get_width(i) && height == vres_get_height(i) )
     {
        //xil_printf( "Detected Video Resolution = %s\r\n", vres_get_name(i) );
        resolution = i;
        break;
     }
  }  
  return resolution;
}

