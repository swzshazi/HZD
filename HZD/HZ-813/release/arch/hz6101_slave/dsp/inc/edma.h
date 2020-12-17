/**
 *  \file       edma.h
 *
 *  \brief      This file contains the function prototypes for the device
 *              abstraction layer for EDMA. It also contains some
 *              related macro definitions and some files to be included.
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#ifndef __EDMA_H__
#define __EDMA_H__

#include <stdio.h>
#include <stdlib.h>
#include "hw_edma3cc.h"
#include "hw_edma3tc.h"

#ifdef __cplusplus
extern "C" {
#endif
//***********************************************************************
//  Values that can be used by the application for configuration via APIs
//***********************************************************************/

/** Maximum number of EDMA Shadow regions available */
#define EDMA3_MAX_REGIONS                     (2u)

/** Number of PaRAM Sets available */
#define EDMA3_NUM_PARAMSET                    (128u)

/** Number of Event Queues available */
#define EDMA3_0_NUM_EVTQUE                    (2u)

/** Number of Transfer Controllers available */
#define EDMA3_0_NUM_TC                        (2u)

/** Interrupt no. for Transfer Completion */
#define EDMA3_0_CC_XFER_COMPLETION_INT        (11u)

/** Interrupt no. for CC Error */
#define EDMA3_0_CC0_ERRINT                    (12u)

/** Interrupt no. for TCs Error */
#define EDMA3_0_TC0_ERRINT                    (13u)
#define EDMA3_0_TC1_ERRINT                    (32u)

#define EDMA3CC_DMA_CHANNELS                  (32u)
#define EDMA3CC_QDMA_CHANNELS                 (8u)

/** DMAQNUM bits Clear */
#define EDMA3CC_DMAQNUM_CLR(chNum)            ( ~ (0x7u << (((chNum) % 8u) \
                                                                      * 4u)))
/** DMAQNUM bits Set */
#define EDMA3CC_DMAQNUM_SET(chNum,queNum)     ((0x7u & (queNum)) << \
                                                       (((chNum) % 8u) * 4u))
/** QDMAQNUM bits Clear */
#define EDMA3CC_QDMAQNUM_CLR(chNum)           ( ~ (0x7u << ((chNum) * 4u)))
/** QDMAQNUM bits Set */
#define EDMA3CC_QDMAQNUM_SET(chNum,queNum)    ((0x7u & (queNum)) << \
                                                           ((chNum) * 4u))

#define EDMA3CC_QCHMAP_PAENTRY_CLR            (~EDMA3CC_QCHMAP_PAENTRY)
/** QCHMAP-PaRAMEntry bitfield Set */
#define EDMA3CC_QCHMAP_PAENTRY_SET(paRAMId)   (((EDMA3CC_QCHMAP_PAENTRY >> \
                                              EDMA3CC_QCHMAP_PAENTRY_SHIFT) & \
                                              (paRAMId)) << \
                                              EDMA3CC_QCHMAP_PAENTRY_SHIFT)
/** QCHMAP-TrigWord bitfield Clear */
#define EDMA3CC_QCHMAP_TRWORD_CLR             (~EDMA3CC_QCHMAP_TRWORD)
/** QCHMAP-TrigWord bitfield Set */
#define EDMA3CC_QCHMAP_TRWORD_SET(paRAMId)    (((EDMA3CC_QCHMAP_TRWORD >> \
                                              EDMA3CC_QCHMAP_TRWORD_SHIFT) & \
                                              (paRAMId)) << \
                                              EDMA3CC_QCHMAP_TRWORD_SHIFT)

/** OPT-TCC bitfield Clear */
#define EDMA3CC_OPT_TCC_CLR                   (~EDMA3CC_OPT_TCC)

/** OPT-TCC bitfield Set */
#define EDMA3CC_OPT_TCC_SET(tcc)              (((EDMA3CC_OPT_TCC >> \
                                              EDMA3CC_OPT_TCC_SHIFT) & \
                                              (tcc)) << EDMA3CC_OPT_TCC_SHIFT)

#define EDMA3_SET_ALL_BITS                    (0xFFFFFFFFu)
#define EDMA3_CLR_ALL_BITS                    (0x00000000u)

#define EDMA3CC_COMPL_HANDLER_RETRY_COUNT     (10u)
#define EDMA3CC_ERR_HANDLER_RETRY_COUNT       (10u)

#define EDMA3_TRIG_MODE_MANUAL                (0u)
#define EDMA3_TRIG_MODE_QDMA                  (1u)
#define EDMA3_TRIG_MODE_EVENT                 (2u)

#define EDMA3_CHANNEL_TYPE_DMA                (0u)
#define EDMA3_CHANNEL_TYPE_QDMA               (1u)


#define EDMA3_XFER_COMPLETE                   (0u)
#define EDMA3_CC_DMA_EVT_MISS                 (1u)
#define EDMA3_CC_QDMA_EVT_MISS                (2u)

#define EDMA3_SYNC_A                          (0u)
#define EDMA3_SYNC_AB                         (1u)

#define EDMA3CC_CLR_TCCERR                     EDMA3CC_CCERRCLR_TCCERR
#define EDMA3CC_CLR_QTHRQ0                     EDMA3CC_CCERRCLR_QTHRXCD0
#define EDMA3CC_CLR_QTHRQ1                     EDMA3CC_CCERRCLR_QTHRXCD1


/* paRAMEntry Fields*/
    /**
     * The OPT field (Offset Address 0x0 Bytes)
     */
#define    EDMA3CC_PARAM_ENTRY_OPT            (0x0u)

    /**
     * The SRC field (Offset Address 0x4 Bytes)
     */
#define    EDMA3CC_PARAM_ENTRY_SRC            (0x1u)

    /**
     * The (ACNT+BCNT) field (Offset Address 0x8 Bytes)
     */
#define    EDMA3CC_PARAM_ENTRY_ACNT_BCNT      (0x2u)

    /**
     * The DST field (Offset Address 0xC Bytes)
     */
#define    EDMA3CC_PARAM_ENTRY_DST            (0x3u)

    /**
     * The (SRCBIDX+DSTBIDX) field (Offset Address 0x10 Bytes)
     */
#define    EDMA3CC_PARAM_ENTRY_SRC_DST_BIDX   (0x4u)

    /**
     * The (LINK+BCNTRLD) field (Offset Address 0x14 Bytes)
     */
#define    EDMA3CC_PARAM_ENTRY_LINK_BCNTRLD   (0x5u)

    /**
     * The (SRCCIDX+DSTCIDX) field (Offset Address 0x18 Bytes)
     */
#define    EDMA3CC_PARAM_ENTRY_SRC_DST_CIDX   (0x6u)

    /**
     * The (CCNT+RSVD) field (Offset Address 0x1C Bytes)
     */
#define    EDMA3CC_PARAM_ENTRY_CCNT           (0x7u)


/** The offset for each PaRAM Entry field  */
#define    EDMA3CC_PARAM_FIELD_OFFSET         (0x4u)

/** Number of PaRAM Entry fields
  * OPT, SRC, A_B_CNT, DST, SRC_DST_BIDX, LINK_BCNTRLD, SRC_DST_CIDX
  * and CCNT
  */
#define    EDMA3CC_PARAM_ENTRY_FIELDS         (0x8u)


#define    EDMA_REVID_AM335X                  (0x02u)


#define SOC_EDMA3_NUM_DMACH                 64
#define SOC_EDMA3_NUM_QDMACH                8
#define SOC_EDMA3_NUM_PARAMSETS             256
#define SOC_EDMA3_NUM_EVQUE                 4
#define SOC_EDMA3_CHMAPEXIST                0
#define SOC_EDMA3_NUM_REGIONS               8
#define SOC_EDMA3_MEMPROTECT                0



/** Number of TCCS available */
#define EDMA3_NUM_TCC                        SOC_EDMA3_NUM_DMACH

/**
 * \brief EDMA3 Parameter RAM Set in User Configurable format
 *
 * This is a mapping of the EDMA3 PaRAM set provided to the user
 * for ease of modification of the individual fields
 */
typedef struct EDMA3CCPaRAMEntry {
        /** OPT field of PaRAM Set */
        Uint32 opt;

        /**
         * \brief Starting byte address of Source
         * For FIFO mode, srcAddr must be a 256-bit aligned address.
         */
        Uint32 srcAddr;

        /**
         * \brief Number of bytes in each Array (ACNT)
         */
        Uint16 aCnt;

        /**
         * \brief Number of Arrays in each Frame (BCNT)
         */
        Uint16 bCnt;

        /**
         * \brief Starting byte address of destination
         * For FIFO mode, destAddr must be a 256-bit aligned address.
         * i.e. 5 LSBs should be 0.
         */
        Uint32 destAddr;

        /**
         * \brief Index between consec. arrays of a Source Frame (SRCBIDX)
         */
        short  srcBIdx;

        /**
         * \brief Index between consec. arrays of a Destination Frame (DSTBIDX)
         */
        short  destBIdx;

        /**
         * \brief Address for linking (AutoReloading of a PaRAM Set)
         * This must point to a valid aligned 32-byte PaRAM set
         * A value of 0xFFFF means no linking
         */
        Uint16 linkAddr;

        /**
         * \brief Reload value of the numArrInFrame (BCNT)
         * Relevant only for A-sync transfers
         */
        Uint16 bCntReload;

        /**
         * \brief Index between consecutive frames of a Source Block (SRCCIDX)
         */
        short  srcCIdx;

        /**
         * \brief Index between consecutive frames of a Dest Block (DSTCIDX)
         */
        short  destCIdx;

        /**
         * \brief Number of Frames in a block (CCNT)
         */
        Uint16 cCnt;
        
        Uint16 Rsvd;
        
}EDMA3CCPaRAMEntry;

/*
** Structure to store the EDMA context
*/
typedef struct edmaContext {
    /* Channel mapping reg Val */
    Uint32 dchMap[64];
    /* DMA Queue Number Register Val */    
    Uint32 dmaQNum[8];    
    
    /* DMA Region Access Enable Register val */    
    Uint32 regAccEnableLow;    
    Uint32 regAccEnableHigh;        

    /* Event Set Register value */    
    Uint32 eventSetRegLow;
    Uint32 eventSetRegHigh;    
    
    /* Enable Event Set Register value */    
    Uint32 enableEvtSetRegLow;
    Uint32 enableEvtSetRegHigh;
    
    /* Interrupt Enable Set Register value */            
    Uint32 intEnableSetRegLow;        
    Uint32 intEnableSetRegHigh;    
    
    struct EDMA3CCPaRAMEntry dmaParEntry[512];    
    
} EDMACONTEXT;

/****************************************************************************
**                 API FUNCTION PROTOTYPES
****************************************************************************/


void EDMA3Init(Uint32 baseAdd,
               Uint32 queNum);

void EDMA3EnableChInShadowReg(Uint32 baseAdd,
                              Uint32 chType,
                              Uint32 chNum);

void EDMA3DisableChInShadowReg(Uint32 baseAdd,
                               Uint32 chType,
                               Uint32 chNum);

void EDMA3MapChToEvtQ(Uint32 baseAdd,
                      Uint32 chType,
                      Uint32 chNum,
                      Uint32 evtQNum);

void EDMA3UnmapChToEvtQ(Uint32 baseAdd,
                        Uint32 chType,
                        Uint32 chNum);

void EDMA3MapQdmaChToPaRAM(Uint32 baseAdd,
                           Uint32 chNum,
                           Uint32 *paRAMId);

void EDMA3SetQdmaTrigWord(Uint32 baseAdd,
                          Uint32 chNum,
                          Uint32 trigWord);

void EDMA3ClrMissEvt(Uint32 baseAdd,
                     Uint32 chNum);

void EDMA3QdmaClrMissEvt(Uint32 baseAdd,
                         Uint32 chNum);

void EDMA3ClrCCErr(Uint32 baseAdd,
                   Uint32 Flags);

void EDMA3SetEvt(Uint32 baseAdd,
                 Uint32 chNum);

void EDMA3ClrEvt(Uint32 baseAdd,
                 Uint32 chNum);

void EDMA3EnableDmaEvt(Uint32 baseAdd,
                       Uint32 chNum);

void EDMA3DisableDmaEvt(Uint32 baseAdd,
                        Uint32 chNum);

void EDMA3EnableQdmaEvt(Uint32 baseAdd,
                        Uint32 chNum);

void EDMA3DisableQdmaEvt(Uint32 baseAdd,
                         Uint32 chNum);

Uint32 EDMA3GetIntrStatus(Uint32 baseAdd);

void EDMA3EnableEvtIntr(Uint32 baseAdd,
                        Uint32 chNum);

void EDMA3DisableEvtIntr(Uint32 baseAdd,
                         Uint32 chNum);

void EDMA3ClrIntr(Uint32 baseAdd, Uint32 value);

void EDMA3GetPaRAM(Uint32 baseAdd,
                   Uint32 chNum,
                   EDMA3CCPaRAMEntry* currPaRAM);

void EDMA3QdmaGetPaRAM(Uint32 baseAdd,
                       Uint32 chNum,
                       Uint32 paRAMId,
                       EDMA3CCPaRAMEntry* currPaRAM);

void EDMA3SetPaRAM(Uint32 baseAdd,
                   Uint32 chNum,
                   EDMA3CCPaRAMEntry* newPaRAM);

void EDMA3QdmaSetPaRAM(Uint32 baseAdd,
                       Uint32 chNum,
                       Uint32 paRAMId,
                       EDMA3CCPaRAMEntry* newPaRAM);

void EDMA3QdmaSetPaRAMEntry(Uint32 baseAdd,
                            Uint32 paRAMId,
                            Uint32 paRAMEntry,
                            Uint32 newPaRAMEntryVal);

Uint32 EDMA3QdmaGetPaRAMEntry(Uint32 baseAdd,
                                    Uint32 paRAMId,
                                    Uint32 paRAMEntry);

Uint32 EDMA3RequestChannel(Uint32 baseAdd, Uint32 chType,
                                 Uint32 chNum, Uint32 tccNum,
                                 Uint32 evtQNum);

Uint32 EDMA3FreeChannel(Uint32 baseAdd, Uint32 chType,
                              Uint32 chNum, Uint32 trigMode,
                              Uint32 tccNum, Uint32 evtQNum);

Uint32 EDMA3EnableTransfer(Uint32 baseAdd,
                                 Uint32 chNum,
                                 Uint32 trigMode);

Uint32 EDMA3DisableTransfer(Uint32 baseAdd,
                                  Uint32 chNum,
                                  Uint32 trigMode);

void EDMA3ClearErrorBits(Uint32 baseAdd,
                         Uint32 chNum,
                         Uint32 evtQNum);

Uint32 EDMA3GetCCErrStatus(Uint32 baseAdd);

Uint32 EDMA3GetErrIntrStatus(Uint32 baseAdd);

Uint32 EDMA3QdmaGetErrIntrStatus(Uint32 baseAdd);

void EDMA3Deinit(Uint32 baseAdd,
                 Uint32 queNum);

Uint32 EDMAVersionGet(void);

Uint32 EDMA3PeripheralIdGet(Uint32 baseAdd);
Uint32 EDMA3IntrStatusHighGet(Uint32 baseAdd);
Uint32 EDMA3ErrIntrHighStatusGet(Uint32 baseAdd);

void EDMA3ChannelToParamMap(Uint32 baseAdd,
                            Uint32 channel,
                            Uint32 paramSet);

extern void EDMA3ContextSave(Uint32 baseAddr,
                                EDMACONTEXT *edmaCntxPtr);
extern void EDMA3ContextRestore(Uint32 baseAddr,
                                EDMACONTEXT *edmaCntxPtr);

#ifdef __cplusplus
}
#endif
#endif

/* !! EOF !!                                                                  */
