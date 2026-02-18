/***************************************************************************//**
* \file cy_ppca_clb_maco.h
* \version 1.00
*
* Provides the API declarations of the PPCA CLB MACO driver.
*
********************************************************************************
* \copyright
* Copyright 2024 Cypress Semiconductor Corporation (an Infineon company)
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/
/**
* \addtogroup group_ppca_clb_maco
* \{
*
* \defgroup group_ppca_clb_maco_macros Macros
* \defgroup group_ppca_clb_maco_enums Enumerations
* \defgroup group_ppca_clb_maco_structures Configuration Structures
* \defgroup group_ppca_clb_maco_functions Functions
*
*/
#if !defined(CY_PPCA_CLB_MACO_H)
#define CY_PPCA_CLB_MACO_H

#include "cy_device.h"

#if defined (CY_IP_MXS40PPSS) || defined (CY_DOXYGEN)

#include "cy_syslib.h"

#if defined(__cplusplus)
extern "C" {
#endif

/***************************************
*       Macros
***************************************/

/**
* \addtogroup group_ppca_clb_maco_macros
* \{
*/

/**
* \defgroup group_ppca_clb_maco_status MACO Status
* Macros to check current MACO status returned by
* \ref Cy_PPCA_CLB_MACO_ReadStatus function. Each status is encoded
* in a separate bit, therefore multiple bits may be set to indicate the
* current status.
* \{
*/

/** Last Scanned Section - Sector 0 */
#define CY_LAST_SECT_SCANNED_SECT0                0x00U

/** Last Scanned Section - Sector 1 */
#define CY_LAST_SECT_SCANNED_SECT1                0x01U

/** Last Scanned Section - Sector 2 */
#define CY_LAST_SECT_SCANNED_SECT2                0x02U

/** Last Scanned Section - Init Table */
#define CY_LAST_SECT_SCANNED_STARTUP_TABLE        0x03U

/** Scanning in progress */
#define CY_SCAN_IN_PROGRESS                       0x04U

/** Status of exported MUXSEL_OUT */
#define CY_MUXSEL_OUT_EXPO                        0x08U

/** Current Scanning - Sector 0 */
#define CY_CURRENT_SCANNING_SECT0                 0x00U

/** Current Scanning - Sector 1 */
#define CY_CURRENT_SCANNING_SECT1                 0x10U

/** Current Scanning - Sector 2 */
#define CY_CURRENT_SCANNING_SECT2                 0x20U

/** Next Scanning - Sector 0 */
#define CY_NEXT_SCANNING_SECT0                    0x00U

/** Next Scanning - Sector 1 */
#define CY_NEXT_SCANNING_SECT1                    0x40U

/** Next Scanning - Sector 2 */
#define CY_NEXT_SCANNING_SECT2                    0x80U

/** Mask State of MACO */
#define CY__MACO_MASK_STATE                       0x100U

/** Kill State of MACO */
#define CY_MACO_KILL_STATE                        0x100U

/** Safe State of MACO */
#define CY_MACO_SAFE_STATE                        0x100U

/** \} group_ppca_clb_maco_status */

/** \cond INTERNAL */

#define CY_IS_PARAM_VALID(base)       (NULL != base)

/** \endcond */

/** \} group_ppca_clb_maco_macros */


/**
* \addtogroup group_ppca_clb_maco_enums
* \{
*/


/***************************************
*       Enumerations
***************************************/

/** MUXSEL_IN Input Source */
typedef enum
{
    CY_INTERNAL = 0U,    /**< Internal */
    CY_EXTERNAL = 1U,   /**< External (CLB_TRIG_IN[2]) */
}cy_en_ppca_clb_maco_muxsel_in_t;


/** Synchronous or Asynchronous release of generated MUXSEL_OUT */
typedef enum
{
    CY_ASYNC_REL = 0U,    /**< Asynchronous */
    CY_SYNC_REL  = 1U,   /**< synchronous to CLB_TRIG_IN[3] */
}cy_en_ppca_clb_maco_muxsel_out_t;


/** Next pattern to be scanned */
typedef enum
{
    CY_CURRENT_SECTOR  = 0U,   /**< Scan the Current Sector */
    CY_NEXT_SECTOR     = 1U,   /**< Scan the Next Sector */
    CY_PREVIOUS_SECTOR = 2U,   /**< Scan the Previous Sector */
}cy_en_ppca_clb_maco_nxt_sect_t;


/** Start Mode */
typedef enum
{
    CY_START_WITH_ENABLE_BIT = 0U,   /**< Start with enable bit */
    CY_WAIT_FOR_TRIGGER      = 1U,   /**< Wait for trigger SCLB_TRIG_IN[4] before start (after enable has been set) */
}cy_en_ppca_clb_maco_start_mode_t;


/** Table Selection Transition Mode */
typedef enum
{
    CY_MANUAL_TRANSITION = 0U,   /**< Table selection transition - manual mode */
    CY_AUTO_TRANSITION   = 1U,   /**< Auto Transition Table selection */
}cy_en_ppca_clb_maco_transition_mode_t;


/** Function of MACO */
typedef enum
{
    CY_MATRIX_CONVERTER   = 0U,   /**< MACO is used for Matrix Converter */
    CY_TRAJECTORY_CONTROL = 1U,   /**< MACO is used for Trajectory Control */
}cy_en_ppca_clb_maco_func_t;


/** Signals to monitor */
typedef enum
{
    CY_PATTERN_ROW_COUTER_LSB   = 0U,   /**< Monitor pattern (2-bit), row (5-bit), counter_LSB (1-bit) */
    CY_COUNTER = 1U,                    /**< Monitor counter (8-bit) */
}cy_en_ppca_clb_maco_monitor_sel_t;


/** \} group_ppca_clb_maco_enums */


/**
* \addtogroup group_ppca_clb_maco_structures
* \{
*/

/***************************************
*       Configuration Structures
***************************************/

/** Pattern Configuration Structure */
typedef struct cy_stc_ppca_clb_maco_pattern_config_t
{
    uint8_t tranRow;             /**< Number of Rows in Transition Table */
    uint8_t allRow;              /**< Number of Rows in the entire Table */
    uint16_t driverSignal[20];   /**< Set Status of Driver Signals controlling switches  */
    uint8_t  holdTime[20];       /**< Configure Scan Pattern Hold Time in clock cycles   */
    uint16_t safeState;          /**< Safe Status of Driver Signals controlling switches */
}cy_stc_ppca_clb_maco_pattern_config_t;


/** CLB MACO configuration structure */
typedef struct cy_stc_ppca_clb_maco_config_t
{
    cy_en_ppca_clb_maco_muxsel_in_t muxselInSrcSel;         /**< Set FW_MUXSEL_IN internal source */
    cy_en_ppca_clb_maco_muxsel_out_t muxselOutSyncBypass;   /**< Select between synchronous or asynchronous release of generated MUXSEL_OUT */
    cy_en_ppca_clb_maco_start_mode_t startMode;             /**< start mode: 0 = start with enable bit. 1 = wait for trigger  CLB_TRIG_IN[4] before start (after enable has been set) */
    cy_en_ppca_clb_maco_transition_mode_t transitionMode;   /**< Enable/disable Auto Transition Table selection: 0 = manual (by fw or by external input event) 1 = automatic */
    cy_en_ppca_clb_maco_func_t macoFunc;                    /**< Function of MACO 0 = MACO is used for Matrix Converter 1 = MACO is used for Trajectory Control */
    cy_en_ppca_clb_maco_monitor_sel_t monitorSel;           /**< Select signals to monitor: 0 = pattern (2-bit), row (5-bit), counter_LSB (1-bit) 1 = counter (8-bit) */
    cy_en_ppca_clb_maco_nxt_sect_t selNxtSec;               /**< Select NEXT pattern to be scanned. 0 = Select Current Sector 1 = Select Next Sector 2 = Select Previous Sector */
    cy_stc_ppca_clb_maco_pattern_config_t patternConfig[3]; /**< patternConfig  \ref cy_stc_ppca_clb_maco_pattern_config_t */
}cy_stc_ppca_clb_maco_config_t;


/** \} group_ppca_clb_maco_structures */


/**
* \addtogroup group_ppca_clb_maco_functions
* \{
*/

/***************************************
*        Function Prototypes
***************************************/

/*******************************************************************************
* Function Name: Cy_PPCA_CLB_MACO_Enable
****************************************************************************//**
*
* Enables MACO block.
*
* \param *base
* The PPCA CLB MACO registers structure pointer.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_CLB_MACO_Enable(PPCA_CLB_MACO_Type *base)
{
    PPCA_CLB_MACO_CTRL(base) |= PPCA_CLB_MACO_CTRL_EN_Msk;
}


/*******************************************************************************
* Function Name: Cy_PPCA_CLB_MACO_Disable
****************************************************************************//**
*
* Disables MACO block.
*
* \param *base
* The PPCA CLB MACO registers structure pointer.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_CLB_MACO_Disable(PPCA_CLB_MACO_Type *base)
{
    PPCA_CLB_MACO_CTRL(base) &= (uint32_t)~PPCA_CLB_MACO_CTRL_EN_Msk;
}


/*******************************************************************************
* Function Name: Cy_PPCA_CLB_InitConfig_MACO
****************************************************************************//**
*
* Configures the initial parameters for MACO block.
*
* \param *base
* The PPCA CLB MACO registers structure pointer.
*
* \param *config
* The pointer to the CLB MACO configuration structure.
* See \ref cy_stc_ppca_clb_maco_config_t.
*
*******************************************************************************/
void Cy_PPCA_CLB_MACO_InitConfig(PPCA_CLB_MACO_Type *base, cy_stc_ppca_clb_maco_config_t const *config);


/*******************************************************************************
* Function Name: Cy_PPCA_CLB_MACO_ReadStatus
****************************************************************************//**
*
* Provides the status of MACO.
*
* \param *base
* The PPCA CLB MACO registers structure pointer.
*
* \return
* \ref group_ppca_clb_maco_status.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_PPCA_CLB_MACO_ReadStatus(PPCA_CLB_MACO_Type *base)
{
    return PPCA_CLB_MACO_STAT(base);
}


/*******************************************************************************
* Function Name: Cy_PPCA_CLB_MACO_SelectNextPattern
****************************************************************************//**
*
* Selects NEXT pattern to be scanned. 
* This input will be evaluated at the end of the scan pattern. 
* If it will be different from before, then the scan will start from row 0.
*
* \param *base
* The PPCA CLB MACO registers structure pointer.
*
* \param nextSector 
* The next pattern to be scanned. \ref cy_en_ppca_clb_maco_nxt_sect_t .
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_CLB_MACO_SelectNextPattern(PPCA_CLB_MACO_Type *base, cy_en_ppca_clb_maco_nxt_sect_t nextSector)
{
    PPCA_CLB_MACO_EVENT(base) = (PPCA_CLB_MACO_EVENT(base) & ~(PPCA_CLB_MACO_EVENT_SEL_NXT_SECT_Msk)) |
                                (_VAL2FLD(PPCA_CLB_MACO_EVENT_SEL_NXT_SECT, nextSector));
}


/*******************************************************************************
* Function Name: Cy_PPCA_CLB_MACO_TransitPattern
****************************************************************************//**
*
* Transitions to Next/Previous Pattern.
*
* \param *base
* The PPCA CLB MACO registers structure pointer.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_CLB_MACO_TransitPattern(PPCA_CLB_MACO_Type *base)
{
    PPCA_CLB_MACO_EVENT(base) = (PPCA_CLB_MACO_EVENT(base) & ~(PPCA_CLB_MACO_EVENT_TRANS_EVENT_Msk)) |
                                (PPCA_CLB_MACO_EVENT_TRANS_EVENT_Msk);

}


/*******************************************************************************
* Function Name: Cy_PPCA_CLB_MACO_KillEvent
****************************************************************************//**
*
* Transitions to safe state to kill MACO.
*
* \param *base
* The PPCA CLB MACO registers structure pointer.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_CLB_MACO_KillEvent(PPCA_CLB_MACO_Type *base)
{
    PPCA_CLB_MACO_EVENT(base) = (PPCA_CLB_MACO_EVENT(base) & ~(PPCA_CLB_MACO_EVENT_KILL_EVENT_Msk)) |
                                (PPCA_CLB_MACO_EVENT_KILL_EVENT_Msk);

}


/*******************************************************************************
* Function Name: Cy_PPCA_CLB_MACO_KillExit
****************************************************************************//**
*
* Exits the kill event. 
* KILL_EVENT from CPU or EPU has to be de-asserted before or meanwhile.
*
* \param *base
* The PPCA CLB MACO registers structure pointer.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_CLB_MACO_KillExit(PPCA_CLB_MACO_Type *base)
{
    PPCA_CLB_MACO_EVENT(base) = (PPCA_CLB_MACO_EVENT(base) & ~(PPCA_CLB_MACO_EVENT_KILL_EXIT_Msk)) |
                                (PPCA_CLB_MACO_EVENT_KILL_EXIT_Msk);
}


/******************************************************************************
* Function Name: Cy_PPCA_CLB_MACO_GetInterruptStatus
****************************************************************************//**
*
* Returns the interrupt cause register. 
*
* \param *base
* The PPCA CLB_MACO registers structure pointer.
*
* \return
* The current status of the interrupt source.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_PPCA_CLB_MACO_GetInterruptStatus(PPCA_CLB_MACO_Type *base)
{
    return PPCA_CLB_MACO_INTR(base);
}


/******************************************************************************
* Function Name: Cy_PPCA_CLB_MACO_ClearInterrupt
****************************************************************************//**
*
* Clears the interrupt source in the interrupt cause register.
*
* \param *base
* The PPCA CLB_MACO S2IRQ registers structure pointer.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_CLB_MACO_ClearInterrupt(PPCA_CLB_MACO_Type *base)
{
    PPCA_CLB_MACO_INTR(base) = 1U;
}


/******************************************************************************
* Function Name: Cy_PPCA_CLB_MACO_SetInterrupt
****************************************************************************//**
*
* Sets the interrupt source in the interrupt set register.
*
* \param *base
* The PPCA CLB_MACO registers structure pointer.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_CLB_MACO_SetInterrupt(PPCA_CLB_MACO_Type *base)
{
    PPCA_CLB_MACO_INTR_SET(base) = 1U;
}


/******************************************************************************
* Function Name: Cy_PPCA_CLB_MACO_GetInterruptMask
****************************************************************************//**
*
* Returns the interrupt mask register. This register specifies which
* bits from the interrupt cause register can trigger an interrupt event.
*
* \param *base
* The PPCA CLB_MACO registers structure pointer.
*
* \return
* Enabled interrupt sources.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_PPCA_CLB_MACO_GetInterruptMask(PPCA_CLB_MACO_Type *base)
{
    return PPCA_CLB_MACO_INTR_MASK(base);
}


/******************************************************************************
* Function Name: Cy_PPCA_CLB_MACO_SetInterruptMask
****************************************************************************//**
*
* Writes interrupt mask register.
* This register specifies which bits from the interrupt cause register
* can trigger an interrupt event.
*
* \param *base
* The PPCA CLB_MACO registers structure pointer.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_CLB_MACO_SetInterruptMask(PPCA_CLB_MACO_Type *base)
{
    PPCA_CLB_MACO_INTR_MASK(base) = 1U;
}


/******************************************************************************
* Function Name: Cy_PPCA_CLB_MACO_GetInterruptStatusMasked
****************************************************************************//**
*
* Returns the interrupt masked register. This register contains a
* logical AND of corresponding bits from the interrupt cause and mask
* registers.
* This function is intended to be used in the interrupt service routine to
* identify which of enabled interrupt sources caused the interrupt
* event.
*
* \param *base
* The PPCA CLB_MACO registers structure pointer.
*
* \return
* The current status of enabled interrupt sources.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_PPCA_CLB_MACO_GetInterruptStatusMasked(PPCA_CLB_MACO_Type *base)
{
    return PPCA_CLB_MACO_INTR_MASKED(base);
}

/** \} group_ppca_clb_maco_functions */

#if defined(__cplusplus)
}
#endif

#endif /* #if defined(CY_IP_MXS40PPSS) */

#endif /* (CY_PPCA_CLB_H) */

/** \} group_ppca_clb_maco */

/* [] END OF FILE */
