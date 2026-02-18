/***************************************************************************//**
* \file cy_ppca_epu.h
* \version 1.00
*
* Provides the API declarations of the PPCA EPU driver.
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
* \addtogroup group_ppca_epu
* \{
* \section group_ppca_epu_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
* \defgroup group_ppca_epu_functions Functions
* \defgroup group_ppca_epu_structures Configuration Structures
* \defgroup group_ppca_epu_enums Enumerations
* \defgroup group_ppca_epu_macros Macros
*
*/
#if !defined(CY_PPCA_EPU_H)
#define CY_PPCA_EPU_H

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
* \addtogroup group_ppca_epu_macros
* \{
*/
/** The driver major version */
#define CY_PPCA_EPU_DRV_VERSION_MAJOR       1U

/** The driver minor version */
#define CY_PPCA_EPU_DRV_VERSION_MINOR       0U

/** The CORDIC driver ID */
#define CY_PPCA_EPU_ID               CY_PDL_DRV_ID(0x97U)

/** \cond INTERNAL */

#define CY_IS_PARAM_VALID(base)              (NULL != base)
#define CY_IS_PUT1_INDEX_VALID(index)        (index <= 31u)
#define CY_IS_PUT2_INDEX_VALID(index)        (index <= 15u)
#define CY_IS_COMBO_INDEX_VALID(index)       (index <= 122u)
#define CY_IS_COMBO_FB_INDEX_VALID(index)    (index <= 7u)

/** \endcond */

/** \} group_ppca_epu_macros */


/***************************************
*       Enumerations
***************************************/
/**
* \addtogroup group_ppca_epu_enums
* \{
*/

/** PPCA epu status enumeration */
typedef enum
{
    CY_PPCA_EPU_SUCCESS = 0U,                                             /**< Returned successful */
    CY_PPCA_EPU_BAD_PARAM = (CY_PPCA_EPU_ID | CY_PDL_STATUS_ERROR | 1U), /**< Bad parameter was passed */
} cy_en_ppca_epu_status_t;


/** Enable/Disable and Bypass Configure of Processing Unit */
typedef enum
{
    CY_PU_DISABLE          = 0U, /**< Disable PU */
    CY_ENABLE_SYNC_BYPASS  = 1U, /**< Enable Synchronous Bypass */
    CY_ENABLE_ASYNC_BYPASS = 2U, /**< Enable Asynchronous Bypass */
    CY_ENABLE_PU           = 3U, /**< Enable Processing Unit */
} cy_en_ppca_epu_en_pu_t;


/** Input of PU */
typedef enum
{
    CY_LEVEL_SIGNAL        = 0U,   /**< Output of Polarity Inversion Stage */
    CY_EDGE_SIGNAL         = 1U,   /**< Output of Edge Extractor whose input is the output of Polarity Inversion Stage */
} cy_en_ppca_epu_input_pu_t;

/** Constant Input Level from PU */
typedef enum
{
    CY_CONSTANT_0        = 0U,   /**< Constant 0 is sent to combiner */
    CY_CONSTANT_1        = 1U,   /**< Constant 1 is sent to combiner */
} cy_en_ppca_epu_constant_level_t;


/** PU Processing Function */
typedef enum
{
    CY_EXTRACT_RISING_EDGE        = 0U,   /**< Extracted rising edge and delay extracted pulse by configured DATA numbers of clock cycles */
    CY_MASK_INPUT_SIGNAL          = 1U,   /**< Mask input signal after detection of first valid transition by configured DATA numbers of clock cycles */
    CY_BLANK_INPUT_SIGNAL         = 2U,   /**< Blank input signal after detection of first valid transition (rising and falling) by configured DATA numbers of clock cycles */
    CY_DEBOUNCE_INPUT_SIGNAL      = 3U,   /**< Debounce input signal by configured DATA threshold express in number of clock cycles */
} cy_en_ppca_epu_pu_processing_func_t;


/**
 * COMBO Block:
 * Combination of 2 Processing Unit T1 module outputs. {SIGNAL_A, SIGNAL_B}
 * Select input signals : put1_selected[i] = {put1[2*i],put1[2*i+1]}, i=[0,7]
 */
typedef enum
{
    CY_COMBO_UNASSIGNED_BANK_OUT   = 0U,  /**< PUT Out unassigned */
    CY_COMBO_PUT1_OUT0_PUT1_OUT1   = 0U,  /**< Select input signals PUT1_OUT0 and PUT1_OUT1   */
    CY_COMBO_PUT1_OUT2_PUT1_OUT3   = 1U,  /**< Select input signals PUT1_OUT2 and PUT1_OUT3   */
    CY_COMBO_PUT1_OUT4_PUT1_OUT5   = 2U,  /**< Select input signals PUT1_OUT4 and PUT1_OUT5   */
    CY_COMBO_PUT1_OUT6_PUT1_OUT7   = 3U,  /**< Select input signals PUT1_OUT6 and PUT1_OUT7   */
    CY_COMBO_PUT1_OUT8_PUT1_OUT9   = 4U,  /**< Select input signals PUT1_OUT8 and PUT1_OUT9   */
    CY_COMBO_PUT1_OUT10_PUT1_OUT11 = 5U,  /**< Select input signals PUT1_OUT10 and PUT1_OUT11 */
    CY_COMBO_PUT1_OUT12_PUT1_OUT13 = 6U,  /**< Select input signals PUT1_OUT12 and PUT1_OUT13 */
    CY_COMBO_PUT1_OUT14_PUT1_OUT15 = 7U,  /**< Select input signals PUT1_OUT14 and PUT1_OUT15 */
}cy_en_ppca_epu_bank_sel_t;


/**
 * COMBO Block: Enable input signals. {SIGNAL_A, SIGNAL_B}
 */
typedef enum
{
    CY_COMBO_DISABLE_INPUT_SIGNAL_A_AND_B = 0U, /**< Disable both SIGNAL_A and SIGNAL_B*/
    CY_COMBO_ENABLE_INPUT_SIGNAL_A        = 1U, /**< tbd - check with IP team; Enable SIGNAL_A */
    CY_COMBO_ENABLE_INPUT_SIGNAL_B        = 2U, /**< tbd - check with IP team; Enable SIGNAL_B */
    CY_COMBO_ENABLE_INPUT_SIGNAL_A_AND_B  = 3U, /**< Enable both SIGNAL_A and SIGNAL_B*/
}cy_en_ppca_epu_en_input_signal_t;


/**
 * COMBO Block:
 * Select 1 of 16 Processing Units T1 and 1 of 16 Processing Units T2. {SIGNAL_A, SIGNAL_B}
 * Select {pu_src_sel0, pu_src_sel1} = {put1[16+i],put2[i]}, i=[0,15]
 */
typedef enum
{
    CY_COMBO_UNASSIGNED_PUT_OUT     = 0U,  /**< PUT Out unassigned */
    CY_COMBO_PUT1_OUT16_PUT2_OUT0   = 0U,  /**< Select input signals PUT1_OUT16 and PUT2_OUT0   */
    CY_COMBO_PUT1_OUT17_PUT2_OUT1   = 1U,  /**< Select input signals PUT1_OUT17 and PUT2_OUT1   */
    CY_COMBO_PUT1_OUT18_PUT2_OUT2   = 2U,  /**< Select input signals PUT1_OUT18 and PUT2_OUT2   */
    CY_COMBO_PUT1_OUT19_PUT2_OUT3   = 3U,  /**< Select input signals PUT1_OUT19 and PUT2_OUT3   */
    CY_COMBO_PUT1_OUT20_PUT2_OUT4   = 4U,  /**< Select input signals PUT1_OUT20 and PUT2_OUT4   */
    CY_COMBO_PUT1_OUT21_PUT2_OUT5   = 5U,  /**< Select input signals PUT1_OUT21 and PUT2_OUT5   */
    CY_COMBO_PUT1_OUT22_PUT2_OUT6   = 6U,  /**< Select input signals PUT1_OUT22 and PUT2_OUT6   */
    CY_COMBO_PUT1_OUT23_PUT2_OUT7   = 7U,  /**< Select input signals PUT1_OUT23 and PUT2_OUT7   */
    CY_COMBO_PUT1_OUT24_PUT2_OUT8   = 8U,  /**< Select input signals PUT1_OUT24 and PUT2_OUT8   */
    CY_COMBO_PUT1_OUT25_PUT2_OUT9   = 9U,  /**< Select input signals PUT1_OUT25 and PUT2_OUT9   */
    CY_COMBO_PUT1_OUT26_PUT2_OUT10  = 10U, /**< Select input signals PUT1_OUT26 and PUT2_OUT10  */
    CY_COMBO_PUT1_OUT27_PUT2_OUT11  = 11U, /**< Select input signals PUT1_OUT27 and PUT2_OUT11  */
    CY_COMBO_PUT1_OUT28_PUT2_OUT12  = 12U, /**< Select input signals PUT1_OUT28 and PUT2_OUT12  */
    CY_COMBO_PUT1_OUT29_PUT2_OUT13  = 13U, /**< Select input signals PUT1_OUT29 and PUT2_OUT13  */
    CY_COMBO_PUT1_OUT30_PUT2_OUT14  = 14U, /**< Select input signals PUT1_OUT30 and PUT2_OUT14  */
    CY_COMBO_PUT1_OUT31_PUT2_OUT15  = 15U, /**< Select input signals PUT1_OUT31 and PUT2_OUT15  */
}cy_en_ppca_epu_pu_src_in_t;

/**
 * COMBO Block: Select PU (= PUT1_OUT31:PUT1_OUT28, PUT2_OUT15:PUT2_OUT12) as qualifier.
 */
typedef enum
{
    CY_COMBO_UNASSIGNED_QUAL = 0U,  /**< Qualifier unassigned */
    CY_COMBO_PUT1_OUT28_QUAL = 0U,  /**< PUT1_OUT28 as qualifier */
    CY_COMBO_PUT1_OUT29_QUAL = 1U,  /**< PUT1_OUT29 as qualifier */
    CY_COMBO_PUT1_OUT30_QUAL = 2U,  /**< PUT1_OUT30 as qualifier */
    CY_COMBO_PUT1_OUT31_QUAL = 3U,  /**< PUT1_OUT31 as qualifier */
    CY_COMBO_PUT2_OUT12_QUAL = 4U,  /**< PUT2_OUT12 as qualifier */
    CY_COMBO_PUT2_OUT13_QUAL = 5U,  /**< PUT2_OUT13 as qualifier */
    CY_COMBO_PUT2_OUT14_QUAL = 6U,  /**< PUT2_OUT14 as qualifier */
    CY_COMBO_PUT2_OUT15_QUAL = 7U,  /**< PUT2_OUT15 as qualifier */
}cy_en_ppca_epu_in_qual_t;


/** \} group_ppca_epu_enums */


/***************************************
*       Configuration Structures
***************************************/

/**
* \addtogroup group_ppca_epu_structures
* \{
*/

/** PPCA EPU PU Type 1 Configuration */
typedef struct cy_stc_ppca_epu_PU_T1_config
{
    cy_en_ppca_epu_en_pu_t PUT1_enable;             /**< Enable/Disable and Bypass Configuration of Processing Unit */
    bool inpPolarityInv;                            /**< Enable/Disable Input Polarity Inversion */
    cy_en_ppca_epu_input_pu_t PUT1_IN_Sel;          /**< Input of PU */
    cy_en_ppca_epu_pu_processing_func_t opcode;     /**< PU processing function code */
    uint8_t clk_cycles;                             /**< DATA: Number of clock cycles */
    bool PUT1_ENQ;                                  /**< Enable/Disable Qualifier Input */
    uint8_t PUT1_SRC_SEL;                           /**< PUT1 Input Source */
    uint8_t PUT1_SRCQ_SEL;                          /**< PUT1 Qualifier Input Source */
    bool swEventEnable;                             /**< Enable/Disable Software event generation or Constant input*/
    cy_en_ppca_epu_constant_level_t inputLevel;     /**< Constant input level from PUT1 */
}cy_stc_ppca_epu_PU_T1_config_t;


/** PPCA EPU PU Type 2 Configuration */
typedef struct cy_stc_ppca_epu_PU_T2_config
{
    cy_en_ppca_epu_en_pu_t PUT2_enable;             /**< Enable/Disable and Bypass Configuration of Processing Unit */
    bool inpPolarityInv;                            /**< Enable/Disable Input Polarity Inversion */
    cy_en_ppca_epu_input_pu_t PUT2_IN_Sel;          /**< Input of PU */
    uint8_t PUT2_SRC_SEL;                           /**< PUT2 Input Source */
    bool swEventEnable;                             /**< Enable/Disable Software event generation or Constant input*/
    cy_en_ppca_epu_constant_level_t inputLevel;     /**< Constant input level from PUT2 */
}cy_stc_ppca_epu_PU_T2_config_t;


/** PPCA EPU Combo block Configuration */
typedef struct cy_stc_ppca_epu_combo_config
{
    cy_en_ppca_epu_bank_sel_t bankSel;             /**< Input Signals from PUT1_OUT[0-15] */
    cy_en_ppca_epu_en_input_signal_t put1InEnable; /**< Enable Input Signals from PUT1_OUT[0-15] */
    cy_en_ppca_epu_pu_src_in_t puSrcIn;            /**< Input signals from PUT1_OUT[16-31] and PUT2_OUT[0-15] */
    cy_en_ppca_epu_en_input_signal_t srcInEnable;  /**< Enable Input Signals PUT1_OUT[16-31] and PUT2_OUT[0-15] */
    cy_en_ppca_epu_in_qual_t inQual;               /**< Select PU (= PUT1_OUT31:PUT1_OUT27, PUT2_OUT15:PUT2_OUT12) as qualifier */
    bool enableQual;                               /**< Enable/Disable Qualifier */
    bool enablePolInv;                             /**< Enable/Disable Polarity Inversion */
}cy_stc_ppca_epu_combo_config_t;

/** \} group_ppca_epu_structures */


/***************************************
*        Function Prototypes
***************************************/

/**
* \addtogroup group_ppca_epu_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_PPCA_EPU_Enable
****************************************************************************//**
*
* Enables PPCA EPU block.
*
* \param *base
* The PPCA EPU registers structure pointer.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_EPU_Enable(PPCA_EPU_Type *base)
{
    PPCA_EPU_CTRL(base) |= PPCA_EPU_CTRL_EPU_EN_Msk;
}


/*******************************************************************************
* Function Name: Cy_PPCA_EPU_Disable
****************************************************************************//**
*
* Disables PPCA EPU block.
*
* \param *base
* The PPCA EPU registers structure pointer.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_EPU_Disable(PPCA_EPU_Type *base)
{
    PPCA_EPU_CTRL(base) &= (uint32_t) ~PPCA_EPU_CTRL_EPU_EN_Msk;
}


/*******************************************************************************
* Function Name: Cy_PPCA_EPU_EnableExclusiveAccess
****************************************************************************//**
*
* Enable exclusive access to the EPU resources based on the provided
* resources allocation configuration.
*
* \param *base
* The PPCA EPU registers structure pointer.
*
* \param enable
* true: CPU0 or CPU1 can access only its own resources,
*       as specified by the configuration registers (PPCA CNFG))
* false: all EPU resources can be accessed by both CPU0 & CPU1,
*        i.e. the configuration registers are ignored.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_EPU_EnableExclusiveAccess(PPCA_EPU_Type *base, bool enable)
{
    if(enable)
    {
        PPCA_EPU_CTRL(base) |= PPCA_EPU_CTRL_EN_EXCLUSIVE_ACCESS_Msk;
    }
    else
    {
        PPCA_EPU_CTRL(base) &= (uint32_t) ~(PPCA_EPU_CTRL_EN_EXCLUSIVE_ACCESS_Msk);
    }
}


/*******************************************************************************
* Function Name: Cy_PPCA_EPU_PU_T1_Configure
****************************************************************************//**
*
* Configure Processing Unit Type 1.
*
* \param *base
* The PPCA EPU registers structure pointer.
*
* \param index
* The Processing Unit Type 1 index (PUT1) . Range: 0-31
*
* \param config
* The pointer to the Processing Unit Type1 configuration structure.
*
*******************************************************************************/
void Cy_PPCA_EPU_PU_T1_Configure( PPCA_EPU_EPU_Type *base, uint32_t index, cy_stc_ppca_epu_PU_T1_config_t const *config);


/*******************************************************************************
* Function Name: Cy_PPCA_EPU_PU_T2_Configure
****************************************************************************//**
*
* Configure Processing Unit Type 2.
*
* \param *base
* The PPCA EPU registers structure pointer.
*
* \param index
* The Processing Unit Type 2 index (PUT2) . Range: 0-15.
*
* \param config
* The pointer to the Processing Unit Type2 configuration structure.
*
*******************************************************************************/
void Cy_PPCA_EPU_PU_T2_Configure( PPCA_EPU_EPU_Type *base, uint32_t index, cy_stc_ppca_epu_PU_T2_config_t const *config);


/*******************************************************************************
* Function Name: Cy_PPCA_EPU_Combo_Configure
****************************************************************************//**
*
* Configure Combo block.
*
* \param *base
* The PPCA EPU registers structure pointer.
*
* \param index
* The COMBO block index. Range: 0-122.
*
* \param config
* The pointer to the combo configuration structure.
*
*******************************************************************************/
void Cy_PPCA_EPU_Combo_Configure( PPCA_EPU_EPU_Type *base, uint32_t index, cy_stc_ppca_epu_combo_config_t const  *config);


/*******************************************************************************
* Function Name: Cy_PPCA_EPU_Combo_Feedback_Configure
****************************************************************************//**
*
* Configure Combo Feedback block.
*
* \param *base
* The PPCA EPU registers structure pointer.
*
* \param index
* The COMBO Feedback block index. Range: 0-7.
*
* \param comboFBSrcIn
* The COMBO output before PUT1_IN_QUALIFIER section. Range: 0 - 122.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_EPU_Combo_Feedback_Configure( PPCA_EPU_EPU_Type *base, uint32_t index, uint32_t comboFBSrcIn)
{
    CY_ASSERT_L1(CY_IS_PARAM_VALID(base));
    CY_ASSERT_L2(CY_IS_COMBO_FB_INDEX_VALID(index));

    PPCA_EPU_EPU_COMBO_FB_CNFG(base, index) = comboFBSrcIn;
}

//PUT1

/*******************************************************************************
* Function Name: Cy_PPCA_EPU_PU_T1_Enable
****************************************************************************//**
*
* Enable/Disable and Bypass Configure the Processing Unit.
*
* \param *base
* The PPCA EPU registers structure pointer.
*
* \param index
* The Processing Unit Type 1 index (PUT1) . Range: 0-31.
*
* \param enable
* Enable/Disable or Bypass the PU. See \ref cy_en_ppca_epu_en_pu_t .
*
*******************************************************************************/
void Cy_PPCA_EPU_PU_T1_Enable(PPCA_EPU_EPU_Type *base, uint32_t index, cy_en_ppca_epu_en_pu_t enable);


/*******************************************************************************
* Function Name: Cy_PPCA_EPU_PU_T1_Enable_PolInv
****************************************************************************//**
*
* Enable/Disable Input Polarity Inversion.
*
* \param *base
* The PPCA EPU registers structure pointer.
*
* \param index
* The Processing Unit Type 1 index (PUT1) . Range: 0-31
*
* \param enable
* true: enable
* false: disable.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_EPU_PU_T1_Enable_PolInv(PPCA_EPU_EPU_Type *base, uint32_t index, bool enable)
{
    if(enable)
    {
        PPCA_EPU_EPU_PU_T1_CNFG(base, index) |= PPCA_EPU_EPU_PU_T1_CNFG_PUT1_POL_Msk;
    }
    else
    {
        PPCA_EPU_EPU_PU_T1_CNFG(base, index) &= (uint32_t) ~(PPCA_EPU_EPU_PU_T1_CNFG_PUT1_POL_Msk);
    }
}

/*******************************************************************************
* Function Name: Cy_PPCA_EPU_PU_T1_Enable_SWEventGeneration
****************************************************************************//**
*
* Enable/Disable Software Event Generation.
*
* \param *base
* The PPCA EPU registers structure pointer.
*
* \param index
* The Processing Unit Type 1 index (PUT1) . Range: 0-31
*
* \param enable
* true: enable
* false: disable.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_EPU_PU_T1_Enable_SWEventGeneration(PPCA_EPU_EPU_Type *base, uint32_t index, bool enable)
{
    if(enable)
    {
        PPCA_EPU_EPU_PU_T1_CNFG(base, index) |= PPCA_EPU_EPU_PU_T1_CNFG_PUT1_SEL_CONSTANT_IN_Msk;
    }
    else
    {
        PPCA_EPU_EPU_PU_T1_CNFG(base, index) &= (uint32_t) ~(PPCA_EPU_EPU_PU_T1_CNFG_PUT1_SEL_CONSTANT_IN_Msk);
    }
}

/*******************************************************************************
* Function Name: Cy_PPCA_EPU_PU_T1_Generate_SW_Event
****************************************************************************//**
*
* Generates a SW event.
*
* \param *base
* The PPCA EPU registers structure pointer.
*
* \note For this to generate a SW event Cy_PPCA_EPU_PU_T1_Enable_SWEventGeneration this needs to be set
*
* \param index
* The Processing Unit Type 1 index (PUT1) . Range: 0-31
*
* \param enable
* true: generates a SW event.
* false: should be set to false after event generation is complete.
*
* \note User should call this API to Generate a Software Event.
* \note User should also call this API to set this to 0 after event is generated.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_EPU_PU_T1_Generate_SW_Event(PPCA_EPU_EPU_Type *base, uint32_t index, bool enable)
{
    if(enable)
    {
        PPCA_EPU_EPU_PU_T1_CNFG(base, index) |= PPCA_EPU_EPU_PU_T1_CNFG_PUT1_CONSTANT_IN_Msk;
    }
    else
    {
        PPCA_EPU_EPU_PU_T1_CNFG(base, index) &= (uint32_t) ~(PPCA_EPU_EPU_PU_T1_CNFG_PUT1_CONSTANT_IN_Msk);
    }
}

/*******************************************************************************
* Function Name: Cy_PPCA_EPU_PU_T1_Select_Input
****************************************************************************//**
*
* Select Input of Processing Uint Type 1.
*
* \param *base
* The PPCA EPU registers structure pointer.
*
* \param index
* The Processing Unit Type 1 index (PUT1) . Range: 0-31
*
* \param input
* Input of PUT1. See \ref cy_en_ppca_epu_input_pu_t.
*
*******************************************************************************/
void Cy_PPCA_EPU_PU_T1_Select_Input(PPCA_EPU_EPU_Type *base, uint32_t index, cy_en_ppca_epu_input_pu_t input);


/*******************************************************************************
* Function Name: Cy_PPCA_EPU_PU_T1_Select_ProcessingFunc
****************************************************************************//**
*
* Select the processing function for Processing Uint Type 1
* and configure the number of clocks.
*
* \param *base
* The PPCA EPU registers structure pointer.
*
* \param index
* The Processing Unit Type 1 index (PUT1) . Range: 0-31.
*
* \param func
* PU Processing function. See \ref cy_en_ppca_epu_pu_processing_func_t.
*
* \param clk_cycles
* Number of clock cycles. Range 0-127.
*
*******************************************************************************/
void Cy_PPCA_EPU_PU_T1_Select_ProcessingFunc(PPCA_EPU_EPU_Type *base, uint32_t index, cy_en_ppca_epu_pu_processing_func_t func, uint32_t clk_cycles);


/*******************************************************************************
* Function Name: Cy_PPCA_EPU_PU_T1_Config_QualifierInput
****************************************************************************//**
*
* Select the qualifier input for Processing Uint Type 1 if qualifier is enabled.
*
* \param *base
* The PPCA EPU registers structure pointer.
*
* \param index
* The Processing Unit Type 1 index (PUT1) . Range: 0-31.
*
* \param enable
* Enable/Disable Qualifier.
*
* \param qualInSrc
* The qualifier input source.
*
*******************************************************************************/
void Cy_PPCA_EPU_PU_T1_Config_QualifierInput(PPCA_EPU_EPU_Type *base, uint32_t index, bool enable, uint8_t qualInSrc);


/*******************************************************************************
* Function Name: Cy_PPCA_EPU_PU_T1_Config_InputSource
****************************************************************************//**
*
* Select Input Source of Processing Uint Type 1.
*
* \param *base
* The PPCA EPU registers structure pointer.
*
* \param index
* The Processing Unit Type 1 index (PUT1) . Range: 0-31.
*
* \param inSrc
* Input source of PUT1.
*
*******************************************************************************/
void Cy_PPCA_EPU_PU_T1_Config_InputSource(PPCA_EPU_EPU_Type *base, uint32_t index, uint8_t inSrc);


/*******************************************************************************
* Function Name: Cy_PPCA_EPU_PU_T1_Config_NumOfClkCycles
****************************************************************************//**
*
* Configures the Number of Clock Cycles parameter for Processing Uint Type 1.
*
* \param *base
* The PPCA EPU registers structure pointer.
*
* \param index
* The Processing Unit Type 1 index (PUT1) . Range: 0-31.
*
* \param data
* Number of clock cycles.
*
*******************************************************************************/
void Cy_PPCA_EPU_PU_T1_Config_NumOfClkCycles(PPCA_EPU_EPU_Type *base, uint32_t index, uint8_t data);


/*******************************************************************************
* Function Name: Cy_PPCA_EPU_PU_T1_TestInConfig
****************************************************************************//**
*
* Select Test Input Signal to Processing Uint Type 1.
*
* \param *base
* The PPCA EPU registers structure pointer.
*
* \param index
* The Processing Unit Type 1 index PUT1) . Range: 0-31.
*
* \param enableTestIn
* Enable TEST_IN input to the PU unit.
*
* \param testInVal
* Set the value of the TEST_IN input signal.
* * 0 = TEST_IN set to 0
* * 1 = TEST_IN set to 1
*
*******************************************************************************/
void Cy_PPCA_EPU_PU_T1_TestInConfig(PPCA_EPU_EPU_Type *base, uint32_t index, bool enableTestIn, bool testInVal);


//PUT2

/*******************************************************************************
* Function Name: Cy_PPCA_EPU_PU_T2_Enable
****************************************************************************//**
*
* Enable/Disable and Bypass Configure the Processing Unit.
*
* \param *base
* The PPCA EPU registers structure pointer.
*
* \param index
* The Processing Unit Type 2 index (PUT1) . Range: 0-15.
*
* \param enable
* Enable/Disable or Bypass the PU. See \ref cy_en_ppca_epu_en_pu_t .
*
*******************************************************************************/
void Cy_PPCA_EPU_PU_T2_Enable(PPCA_EPU_EPU_Type *base, uint32_t index, cy_en_ppca_epu_en_pu_t enable);


/*******************************************************************************
* Function Name: Cy_PPCA_EPU_PU_T2_Enable_PolInv
****************************************************************************//**
*
* Enable/Disable Input Polarity Inversion.
*
* \param *base
* The PPCA EPU registers structure pointer.
*
* \param index
* The Processing Unit Type 2 index (PUT2) . Range: 0-15.
*
* \param enable
* true: enable
* false: disable.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_EPU_PU_T2_Enable_PolInv(PPCA_EPU_EPU_Type *base, uint32_t index, bool enable)
{
    if(enable)
    {
        PPCA_EPU_EPU_PU_T2_CNFG(base, index) |= PPCA_EPU_EPU_PU_T2_CNFG_PUT2_POL_Msk;
    }
    else
    {
        PPCA_EPU_EPU_PU_T2_CNFG(base, index) &= (uint32_t) ~(PPCA_EPU_EPU_PU_T2_CNFG_PUT2_POL_Msk);
    }
}


/*******************************************************************************
* Function Name: Cy_PPCA_EPU_PU_T2_Enable_SWEventGeneration
****************************************************************************//**
*
* Enable/Disable Software Event Generation.
*
* \param *base
* The PPCA EPU registers structure pointer.
*
* \param index
* The Processing Unit Type 2 index (PUT2) . Range: 0-15
*
* \param enable
* true: enable
* false: disable.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_EPU_PU_T2_Enable_SWEventGeneration(PPCA_EPU_EPU_Type *base, uint32_t index, bool enable)
{
    if(enable)
    {
        PPCA_EPU_EPU_PU_T2_CNFG(base, index) |= PPCA_EPU_EPU_PU_T2_CNFG_PUT2_SEL_CONSTANT_IN_Msk;
    }
    else
    {
        PPCA_EPU_EPU_PU_T2_CNFG(base, index) &= (uint32_t) ~(PPCA_EPU_EPU_PU_T2_CNFG_PUT2_SEL_CONSTANT_IN_Msk);
    }
}

/*******************************************************************************
* Function Name: Cy_PPCA_EPU_PU_T2_Generate_SW_Event
****************************************************************************//**
*
* Generates a SW event.
*
* \param *base
* The PPCA EPU registers structure pointer.
*
* \note For this to generate a SW event Cy_PPCA_EPU_PU_T2_Enable_SWEventGeneration this needs to be set
*
* \param index
* The Processing Unit Type 2 index (PUT2) . Range: 0-15
*
* \param enable
* true: generates a SW event.
* false: should be set to false after event generation is complete.
*
* \note User should call this API to Generate a Software Event.
* \note User should also call this API to set this to 0 after event is generated.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_EPU_PU_T2_Generate_SW_Event(PPCA_EPU_EPU_Type *base, uint32_t index, bool enable)
{
    if(enable)
    {
        PPCA_EPU_EPU_PU_T2_CNFG(base, index) |= PPCA_EPU_EPU_PU_T2_CNFG_PUT2_CONSTANT_IN_Msk;
    }
    else
    {
        PPCA_EPU_EPU_PU_T2_CNFG(base, index) &= (uint32_t) ~(PPCA_EPU_EPU_PU_T2_CNFG_PUT2_CONSTANT_IN_Msk);
    }
}


/*******************************************************************************
* Function Name: Cy_PPCA_EPU_PU_T2_Select_Input
****************************************************************************//**
*
* Select Input of Processing Uint Type 2.
*
* \param *base
* The PPCA EPU registers structure pointer.
*
* \param index
* The Processing Unit Type 2 index (PUT2) . Range: 0-15.
*
* \param input
* Input of PUT2. See \ref cy_en_ppca_epu_input_pu_t.
*
*******************************************************************************/
void Cy_PPCA_EPU_PU_T2_Select_Input(PPCA_EPU_EPU_Type *base, uint32_t index, cy_en_ppca_epu_input_pu_t input);


/*******************************************************************************
* Function Name: Cy_PPCA_EPU_PU_T2_Config_InputSource
****************************************************************************//**
*
* Select Input Source of Processing Uint Type 2.
*
* \param *base
* The PPCA EPU registers structure pointer.
*
* \param index
* The Processing Unit Type 2 index (PUT2) . Range: 0-15.
*
* \param inSrc
* Input source of PUT2. See \ref cy_en_ppca_epu_input_pu_t.
*
*******************************************************************************/
void Cy_PPCA_EPU_PU_T2_Config_InputSource(PPCA_EPU_EPU_Type *base, uint32_t index, uint8_t inSrc);

/*******************************************************************************
* Function Name: Cy_PPCA_EPU_PU_T2_TestInConfig
****************************************************************************//**
*
* Select Test Input Signal to Processing Uint Type 2.
*
* \param *base
* The PPCA EPU registers structure pointer.
*
* \param index
* The Processing Unit Type 2 index PUT2) . Range: 0-15.
*
* \param enableTestIn
* Enable TEST_IN input to the PU unit.
*
* \param testInVal
* Set the value of the TEST_IN input signal.
* * 0 = TEST_IN set to 0
* * 1 = TEST_IN set to 1
*
*******************************************************************************/
void Cy_PPCA_EPU_PU_T2_TestInConfig(PPCA_EPU_EPU_Type *base, uint32_t index, bool enableTestIn, bool testInVal);


//COMBINER APIs

/*******************************************************************************
* Function Name: Cy_PPCA_EPU_COMBO_InputSignals_PUT1_0_15
****************************************************************************//**
*
* Select Input Signals from PUT1_OUT[0-15] and
* enable Input Signals of the pair selected from PUT1_OUT[0-15]
*
* \param *base
* The PPCA EPU registers structure pointer.
*
* \param index
* The COMBO block index. Range: 0-122.
*
* \param bankSel
* A pair of input Signals from PUT1_OUT[0-15]. See \ref cy_en_ppca_epu_bank_sel_t.
*
* \param put1InEnable
* Enable Input Signals of the pair selected from PUT1_OUT[0-15].
*
*******************************************************************************/
void Cy_PPCA_EPU_COMBO_InputSignals_PUT1_0_15(PPCA_EPU_EPU_Type *base, uint32_t index, cy_en_ppca_epu_bank_sel_t bankSel, cy_en_ppca_epu_en_input_signal_t put1InEnable);


/*******************************************************************************
* Function Name: Cy_PPCA_EPU_COMBO_InputSignals_PUT1_PUT2
****************************************************************************//**
*
* Select Input Signals from PUT1_OUT[16-31] and PUT2_OUT[0-15].
* Enable Input Signals of the pair selected from PUT1_OUT[0-15].
*
* \param *base
* The PPCA EPU registers structure pointer.
*
* \param index
* The COMBO block index. Range: 0-122.
*
* \param puSrcIn
* A pair of input Signals from PUT1_OUT[16-31] and PUT2_OUT[0-15].
* See \ref cy_en_ppca_epu_pu_src_in_t.
*
* \param srcInEnable
* Enable Input Signals of the pair selected from PUT1_OUT[16-31] and PUT2_OUT[0-15].
*
*******************************************************************************/
void Cy_PPCA_EPU_COMBO_InputSignals_PUT1_PUT2(PPCA_EPU_EPU_Type *base, uint32_t index, cy_en_ppca_epu_pu_src_in_t puSrcIn, cy_en_ppca_epu_en_input_signal_t srcInEnable);


/*******************************************************************************
* Function Name: Cy_PPCA_EPU_COMBO_QualifierInput
****************************************************************************//**
*
* Enable/Disable Qualifier and select the input qualifier signal.
*
* \param *base
* The PPCA EPU registers structure pointer.
*
* \param index
* The COMBO block index. Range: 0-122.
*
* \param enableQual
* Enable/Disable Qualifier.
*
* \param inQual
* Select PU (= PUT1_OUT31:PUT1_OUT27, PUT2_OUT15:PUT2_OUT12) as qualifier.
*
*******************************************************************************/
void Cy_PPCA_EPU_COMBO_QualifierInput(PPCA_EPU_EPU_Type *base, uint32_t index, bool enableQual, cy_en_ppca_epu_in_qual_t inQual);


/*******************************************************************************
* Function Name: Cy_PPCA_EPU_COMBO_Enable_PolInv
****************************************************************************//**
*
* Enable/Disable COMBO Polarity Inversion.
*
* \param *base
* The PPCA EPU registers structure pointer.
*
* \param index
* The COMBO block index. Range: 0-122.
*
* \param enable
* true: enable
* false: disable.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_EPU_COMBO_Enable_PolInv(PPCA_EPU_EPU_Type *base, uint32_t index, bool enable)
{
    if(enable)
    {
        PPCA_EPU_EPU_COMBO_CNFG(base, index) |= PPCA_EPU_EPU_COMBO_CNFG_COMBO_POL_Msk;
    }
    else
    {
        PPCA_EPU_EPU_COMBO_CNFG(base, index) &= (uint32_t) ~(PPCA_EPU_EPU_COMBO_CNFG_COMBO_POL_Msk);
    }
}



//Interrupt Functions

/*******************************************************************************
* Function Name: Cy_PPCA_EPU_InterruptSourceSelect
****************************************************************************//**
*
* Select one of the COMBO Output as interrupt source.
*
* \param base
* The pointer to the PPCA_EPU_EPU_IRQ instance.
*
* \param bypassFormatter
* Enable/Disable EPU IRQ formatter.
*
* \param srcSel
* Select one of the COMBO Output as interrupt source.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_EPU_InterruptSourceSelect(PPCA_EPU_EPU_IRQ_Type *base, bool bypassFormatter, uint8_t srcSel)
{
    if(bypassFormatter)
    {
        PPCA_EPU_EPU_IRQ_INTR_SRCSEL(base) = _BOOL2FLD(PPCA_EPU_EPU_IRQ_INTR_SRCSEL_BYPASS_EPU_IRQ, bypassFormatter);
    }
    else
    {
        PPCA_EPU_EPU_IRQ_INTR_SRCSEL(base) = _BOOL2FLD(PPCA_EPU_EPU_IRQ_INTR_SRCSEL_BYPASS_EPU_IRQ, bypassFormatter) |
                                                  _VAL2FLD(PPCA_EPU_EPU_IRQ_INTR_SRCSEL_EPU_IRQ_SRCSEL, (uint32_t)srcSel);
    }
}

/*******************************************************************************
* Function Name: Cy_PPCA_EPU_GetInterruptStatus
****************************************************************************//**
*
* Returns the interrupt status.
*
* \param base
* The pointer to the PPCA_EPU_EPU_IRQ instance.
*
* \return
* The current status of the interrupt source.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_PPCA_EPU_GetInterruptStatus(PPCA_EPU_EPU_IRQ_Type *base)
{
    return (PPCA_EPU_EPU_IRQ_INTR(base));
}


/*******************************************************************************
* Function Name: Cy_PPCA_EPU_ClearInterrupt
****************************************************************************//**
*
* Clears the interrupt sources in the interrupt cause register.
*
* \param base
* The pointer to the PPCA_EPU_EPU_IRQ instance.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_EPU_ClearInterrupt(PPCA_EPU_EPU_IRQ_Type *base)
{
        PPCA_EPU_EPU_IRQ_INTR(base) = 1u;
}


/*******************************************************************************
* Function Name: Cy_PPCA_EPU_SetInterrupt
****************************************************************************//**
*
* Sets the interrupt sources in the interrupt set register.
*
* \param base
* The pointer to the PPCA_EPU_EPU_IRQ instance.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_EPU_SetInterrupt(PPCA_EPU_EPU_IRQ_Type *base)
{
    PPCA_EPU_EPU_IRQ_INTR_SET(base) = 1u;
}

/*******************************************************************************
* Function Name: Cy_PPCA_EPU_GetInterruptMask
****************************************************************************//**
*
* Returns the interrupt mask register.
*
* \param base
* The pointer to the PPCA_EPU_EPU_IRQ instance.
*
* \return
* Enabled interrupt sources.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_PPCA_EPU_GetInterruptMask(PPCA_EPU_EPU_IRQ_Type *base)
{
    return (PPCA_EPU_EPU_IRQ_INTR_MASK(base));
}


/*******************************************************************************
* Function Name: Cy_PPCA_EPU_SetInterruptMask
****************************************************************************//**
*
* Writes interrupt mask register.
*
* \param base
* The pointer to the PPCA_EPU_EPU_IRQ instance.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_EPU_SetInterruptMask(PPCA_EPU_EPU_IRQ_Type *base)
{
    PPCA_EPU_EPU_IRQ_INTR_MASK(base) = 1u;
}


/*******************************************************************************
* Function Name: Cy_PPCA_EPU_GetInterruptStatusMasked
****************************************************************************//**
*
* Returns the interrupt masked register. This register contains a
* logical AND of corresponding bits from the interrupt cause and mask
* registers.
* This function is intended to be used in the interrupt service routine to
* identify which of enabled interrupt sources caused the interrupt
* event.
*
* \param base
* The pointer to the PPCA_EPU_EPU_IRQ instance.
*
* \return
* The current status of enabled interrupt sources.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_PPCA_EPU_GetInterruptStatusMasked(PPCA_EPU_EPU_IRQ_Type *base)
{
    return (PPCA_EPU_EPU_IRQ_INTR_MASKED(base));
}


/** \} group_ppca_epu_functions */

#if defined(__cplusplus)
}
#endif

#endif /* #if defined(CY_IP_MXS40PPSS) */

#endif /* (CY_PPCA_EPU_H) */

/** \} group_ppca_epu */

/* [] END OF FILE */
