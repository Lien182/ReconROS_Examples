/*
 *                                                        ____  _____
 *                            ________  _________  ____  / __ \/ ___/
 *                           / ___/ _ \/ ___/ __ \/ __ \/ / / /\__ \
 *                          / /  /  __/ /__/ /_/ / / / / /_/ /___/ /
 *                         /_/   \___/\___/\____/_/ /_/\____//____/
 *
 * ======================================================================
 *
 *   title:        Thread library header file
 *
 *   project:      ReconOS
 *   author:       Andreas Agne, University of Paderborn
 *                 Christoph Rüthing, University of Paderborn
 *   description:  Auto-generated thread specific header file including
 *                 resource definitions and helper macros.
 *
 * ======================================================================
 */



#ifndef RECONOS_THREAD_H
#define RECONOS_THREAD_H

#include "hls_stream.h"
#include "ap_cint.h"
#include "ap_int.h"
#include "ap_fixed.h"

/* == Thread resources ================================================= */

/*
 * Definition of resource ids local to this thread. These ids should be
 * used together with the ReconOS call functions to issue system calls on
 * resource objects.
 */
#define resources_mnist_srv_res 0x00000000
#define resources_mnist_srv_req 0x00000001
#define resources_node_1 0x00000002
#define resources_srv 0x00000003



/* == Thread helper macros ============================================= */

/*
 * Definition of the entry function to the ReconOS thread. Every ReconOS
 * thread should be defined using this macro:
 *
 *   THREAD_ENTRY() {
 *     // thread code here
 *   }
 }
 */
#define THREAD_ENTRY() void rt_imp(hls::stream<uint32> osif_sw2hw,\
                                   hls::stream<uint32> osif_hw2sw,\
                                   hls::stream<uint32> memif_hwt2mem,\
                                   hls::stream<uint32> memif_mem2hwt)

#endif /* RECONOS_THREAD_H */