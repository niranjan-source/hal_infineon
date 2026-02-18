/***************************************************************************//**
* \file cy_ppca_aref.h
* \version 1.0
*
* The header file of the PPCA AREF driver.
*
********************************************************************************
* \copyright
* Copyright 2024 Cypress Semiconductor Corporation
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


#if !defined(CY_PPCA_AREF_H)
#define CY_PPCA_AREF_H

#include "cy_device.h"

#if defined (CY_IP_MXS40PPSS) || defined (CY_DOXYGEN)

#if defined(__cplusplus)
extern "C" {
#endif

/**
* \addtogroup group_ppca_aref
* Driver API for PPCA AREF.
*
* \{
*/

/**
* \defgroup group_ppca_aref_macros                Macros
* \defgroup group_ppca_aref_functions             Functions
* \defgroup group_ppca_aref_data_structures Data Structures
* \} */

/**
* \addtogroup group_ppca_aref_macros
* \{
*/
/** ATPSS IDAC Type */
#define ATOPSS_IDAC_TYPE PPCA_ATOPSS_ADC_GRP_IDAC_Type
/** ATOPSS AREF Type */
#define ATOPSS_AREF_TYPE PPCA_ATOPSS_ADC_GRP_AREF_Type
/** ATOPSS GPI Type */
#define ATOPSS_GPI_TYPE PPCA_ATOPSS_ADC_GRP_GPI_Type

/** \} group_ppca_aref_macros */

/**
* \addtogroup group_ppca_aref_data_structures
* \{
*/


/** IDAC Mode Configuration */
typedef enum
{
    CY_IDAC_CNFG_MODE_TRISTATE      = 0UL,        /**<No connection of the IDAC_MUX  */
    CY_IDAC_CNFG_MODE_AI0           = 1UL,        /**<Connect to AI0  */
    CY_IDAC_CNFG_MODE_AI1           = 2UL,        /**<Connect to A11  */
    CY_IDAC_CNFG_MODE_DCSG_VINP     = 4UL,        /**<Connect to DCSG vinp - Allow to do open circuit test. */
    CY_IDAC_CNFG_MODE_DCSG_VINN     = 8UL,        /**<Connect to DCSG vinn - Allow to do open circuit test. */

} cy_en_idac_cnfg_mode_t;

/** AREF Analog Control */
typedef enum
{
    CY_AREF_POR_CONTROLLED_BY_HW      = 0UL,        /**<No connection of the IDAC_MUX  */
    CY_AREF_FORCE_POR_0               = 1UL,        /**<Force POR asserted (POR is an active low signal)  */
    CY_AREF_FORCE_POR_1               = 2UL,        /**<Force POR negated. (POR is an active low signal)  */

} cy_en_aref_analog_control_t;

/** VREF Source */
typedef enum
{
    CY_LOCALLY_GENERATED_VREF         = 1UL,        /**< Use locally generated Vref. */
    CY_EXTERNALLY_SUPPLIED_VREF       = 2UL,        /**< Use externally supplied Vref (aref_ext_vref)  */
} cy_en_vref_source_select_t;


/** PPCA IDAC configuration structure */
typedef struct cy_stc_ppca_idac_config
{
    cy_en_idac_cnfg_mode_t         idac_mode_cnfg;                       /**< IDAC Mode Configuration */

}cy_stc_ppca_idac_config_t;

/** PPCA AREF configuration structure */
typedef struct cy_stc_ppca_aref_config
{
    bool         aref_mode;                       /**< false : Nominal noise normal startup mode. true : High noise fast startup mode */
    bool         enable_current_to_ts;            /**< Enable Bias current to Temp Sensor */
    cy_en_aref_analog_control_t analog_ctrl;      /**< POR Analog control configuration   */
    cy_en_vref_source_select_t vref_source_sel;   /**< voltage source select. Locally generated vref or externally supplied vref. */

}cy_stc_ppca_aref_config_t;

/** PPCA GPI configuration structure */
typedef struct cy_stc_ppca_gpi_config
{
    bool         ai0_enable;                    /**< GPI  Enable for AI0 */
    bool         ai1_enable;                    /**< GPI  Enable for AI1 */

}cy_stc_ppca_gpi_config_t;

/** \} group_ppca_aref_data_structures */


/**
* \addtogroup group_ppca_aref_functions
* \{
*/

/******* IDAC *******/

/******************************************************************************
* Function Name: Cy_PPCA_IDAC_Init
***************************************************************************//**
*
* Initializes and enables the IDAC
*
* \param config IDAC Mode configuration.
*
* \param base The pointer to the IDAC instance address.
*
******************************************************************************/
__STATIC_INLINE void Cy_PPCA_IDAC_Init(ATOPSS_IDAC_TYPE *base, cy_stc_ppca_idac_config_t const *config)
{
    PPCA_ATOP_IDAC_CNFG(base) = _VAL2FLD(PPCA_ATOPSS_ADC_GRP_IDAC_IDAC_CNFG_MUX_SEL, config->idac_mode_cnfg);
}

/******************************************************************************
* Function Name: Cy_PPCA_IDAC_Enable
***************************************************************************//**
*
* Enables the IDAC
*
* \param base The pointer to the IDAC instance address.
*
******************************************************************************/
__STATIC_INLINE void Cy_PPCA_IDAC_Enable(ATOPSS_IDAC_TYPE *base)
{
    PPCA_ATOP_IDAC_CTL(base) |= PPCA_ATOPSS_ADC_GRP_IDAC_IDAC_CTL_IDAC_EN_Msk;
}

/******************************************************************************
* Function Name: Cy_PPCA_IDAC_Disable
***************************************************************************//**
*
* Disables the IDAC
*
* \param base The pointer to the IDAC instance address.
*
******************************************************************************/
__STATIC_INLINE void Cy_PPCA_IDAC_Disable(ATOPSS_IDAC_TYPE *base)
{
    PPCA_ATOP_IDAC_CTL(base) &= (uint32_t) ~PPCA_ATOPSS_ADC_GRP_IDAC_IDAC_CTL_IDAC_EN_Msk;
}


/******* AREF *******/

/******************************************************************************
* Function Name: Cy_PPCA_AREF_Init
***************************************************************************//**
*
* Initializes and enables the AREF
*
* \param config AREF configuration.
*
* \param base The pointer to the AREF instance address.
*
*
* \note Should be called from Main core so that all the trim registers are configured. If called from PPCA core trim registers are not configured.
******************************************************************************/
#if defined (COMPONENT_PPCA_DEVICE) && !defined (__ICCARM__)
void Cy_PPCA_AREF_Init(ATOPSS_AREF_TYPE *base, cy_stc_ppca_aref_config_t const *config)__attribute__((warning("Initialization of PPCA peripherals like AREF, ADC, DAC and DCSG to be done on Main core. Trim values are not configured if called on PPCA cores.")));
#else
void Cy_PPCA_AREF_Init(ATOPSS_AREF_TYPE *base, cy_stc_ppca_aref_config_t const *config);
#endif

/******************************************************************************
* Function Name: Cy_PPCA_AREF_Enable
***************************************************************************//**
*
* Enables the AREF
*
* \param base The pointer to the AREF instance address.
*
******************************************************************************/
__STATIC_INLINE void Cy_PPCA_AREF_Enable(ATOPSS_AREF_TYPE *base)
{
    PPCA_ATOP_AREF_CTL(base) |= PPCA_ATOPSS_ADC_GRP_AREF_AREF_CTL_ENABLED_Msk;
}

/******************************************************************************
* Function Name: Cy_PPCA_AREF_Disable
***************************************************************************//**
*
* Disables the AREF
*
* \param base The pointer to the AREF instance address.
*
******************************************************************************/
__STATIC_INLINE void Cy_PPCA_AREF_Disable(ATOPSS_AREF_TYPE *base)
{
    PPCA_ATOP_AREF_CTL(base) &= (uint32_t) ~PPCA_ATOPSS_ADC_GRP_AREF_AREF_CTL_ENABLED_Msk;
}

/******************************************************************************
* Function Name: Cy_PPCA_AREF_Current_To_TSNS_Enable
***************************************************************************//**
*
* Enables Bias Current to Temperature Sensor
*
* \param base The pointer to the AREF instance address.
*
******************************************************************************/
__STATIC_INLINE void Cy_PPCA_AREF_Current_To_TSNS_Enable(ATOPSS_AREF_TYPE *base)
{
    PPCA_ATOP_AREF_CTL(base) |= PPCA_ATOPSS_ADC_GRP_AREF_AREF_CTL_TSNS_CUR_ENABLED_Msk;
}

/******************************************************************************
* Function Name: Cy_PPCA_AREF_Current_To_TSNS_Disable
***************************************************************************//**
*
* Disables Bias Current to Temperature Sensor
*
* \param base The pointer to the AREF instance address.
*
******************************************************************************/
__STATIC_INLINE void Cy_PPCA_AREF_Current_To_TSNS_Disable(ATOPSS_AREF_TYPE *base)
{
    PPCA_ATOP_AREF_CTL(base) &= (uint32_t) ~PPCA_ATOPSS_ADC_GRP_AREF_AREF_CTL_TSNS_CUR_ENABLED_Msk;
}


/******************************************************************************
* Function Name: Cy_PPCA_AREF_Get_VDDA_Status
***************************************************************************//**
*
* Returns if VDDA is below or above minimum threshold.
*
* \param base The pointer to the AREF instance address.
*
* \return returns if VDDA is below or above minimum threshold.
*
******************************************************************************/
__STATIC_INLINE bool Cy_PPCA_AREF_Get_VDDA_Status(ATOPSS_AREF_TYPE *base)
{
    return (bool)_FLD2VAL(PPCA_ATOPSS_ADC_GRP_AREF_VDDA_STATUS_VDDA_OK, PPCA_ATOP_AREF_VDDA_STATUS(base));
}

/******************************************************************************
* Function Name: Cy_PPCA_AREF_Get_VREF_Source
***************************************************************************//**
*
* Returns if VREF generated internally or supplied from external source.
*
* \param base The pointer to the AREF instance address.
*
* \return returns the source type for VREF.
*
******************************************************************************/
__STATIC_INLINE cy_en_vref_source_select_t Cy_PPCA_AREF_Get_VREF_Source(ATOPSS_AREF_TYPE *base)
{
    uint32_t aref_ctl = _FLD2VAL(PPCA_ATOPSS_ADC_GRP_AREF_AREF_CTL_VREF_SEL, PPCA_ATOP_AREF_CTL(base));
    return (cy_en_vref_source_select_t)(aref_ctl);
}
/******* GPI *******/

/******************************************************************************
* Function Name: Cy_PPCA_GPI_Init
***************************************************************************//**
*
* Initializes the GPI module
*
* \param config GPI configuration.
*
* \param base The pointer to the GPI instance address.
*
******************************************************************************/
__STATIC_INLINE void Cy_PPCA_GPI_Init(ATOPSS_GPI_TYPE *base, cy_stc_ppca_gpi_config_t const *config)
{
    PPCA_ATOP_GPI_CTL(base) = _VAL2FLD(PPCA_ATOPSS_ADC_GRP_GPI_GPI_CTL_GPI_EN_AI0, config->ai0_enable) |
                              _VAL2FLD(PPCA_ATOPSS_ADC_GRP_GPI_GPI_CTL_GPI_EN_AI1, config->ai1_enable);
}


/******************************************************************************
* Function Name: Cy_PPCA_GPI_Get_AI0_Input_Status
***************************************************************************//**
*
* Returns input status of the AI0.
*
* \param base The pointer to the GPI instance address.
*
* \return returns input status of the AI0 .
*
******************************************************************************/
__STATIC_INLINE bool Cy_PPCA_GPI_Get_AI0_Input_Status(ATOPSS_GPI_TYPE *base)
{
    return (bool)_FLD2VAL(PPCA_ATOPSS_ADC_GRP_GPI_GPI_CTL_GPI_INPUT_AI0, PPCA_ATOP_GPI_CTL(base));
}


/******************************************************************************
* Function Name: Cy_PPCA_GPI_Get_AI1_Input_Status
***************************************************************************//**
*
* Returns input status of the AI1.
*
* \param base The pointer to the GPI instance address.
*
* \return returns input status of the AI1 .
*
******************************************************************************/
__STATIC_INLINE bool Cy_PPCA_GPI_Get_AI1_Input_Status(ATOPSS_GPI_TYPE *base)
{
    return (bool)_FLD2VAL(PPCA_ATOPSS_ADC_GRP_GPI_GPI_CTL_GPI_INPUT_AI1, PPCA_ATOP_GPI_CTL(base));
}


/** \} group_ppca_aref_functions */



#if defined(__cplusplus)
}
#endif
#endif /*defined (CY_IP_MXS40PPSS) || defined (CY_DOXYGEN) */

#endif /* CY_PPCA_AREF_H */

