/***************************************************************************//**
* \file cy_ppca_hwfilt3p3z.h
* \version 1.00
*
* Provides the API declarations of the PPCA HW Filter 3P3Z driver.
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
* \addtogroup group_ppca_hwfilt3p3z
* \{
*
* \section group_ppca_hwfilt3p3z_glossary Glossary
*  The HW3P3Z module is a Soft IP. It implements a configurable HW filter function, three poles / three zeroes.
*  The HW3P3Z features:
* * 3 poles, 3 zeroes
* * 16-bit input, 24-bit output
* * 40-bit multiplier
* * 44-bit internal accumulator
* * Max 8 CPU clock cycles execution latency
* * Saturation Operators supported
* * Arithmetic 2's complement
* * Programmed and programmable data path
* * Filter processing triggered by writing into one of the two data registers
* * Generates a pulse event at the completion of Filter computation
* * AHB Slave interface (AHB interface is chosen to reduce the access latency)
* * Register Slave interface (connected to ADC_FILT outputs)
*
*
* Equations:
* * x(n)= x_ref- xin(n)
* * y(n) = Sigma(i=0 to 3) [bi.x(n-i)] - Sigma(j=1 to 3) [aj.y(n-j)]
* * y(out)=y(n)+Offset
* * y(out)=y(n),  LimMin  <= y(n) <= LimMax
* * y(out)=LimMin,LimMin > y(n)
* * y(out)=LimMax,   LimMax <= y(n)
*
* The 3-Pole/ 3-Zero (3P3Z) Compensator is the digital implementation of the analog type III controller.
* It is a filter that introduces a specific gain and phase boost into the system by considering three poles and three zeroes.
*
* The 3P3Z is implementing a fixed-point structure with 24bits coefficient registers, in which 1 bit is for the sign,
* remaining for the fractional value.
* Input to 3p3z filter is a 16 bit value.
* Output from 3p3z filter is a fixed-point 24 bit value.
* Coefficients are also fixed-point 24 bit values, ranged between 1 and -1.
* If any x coefficient is greater than 1 then divide all the x coefficients by 2 and add 1 to scaleCX to match the reduced value. \ref cy_stc_ppca_hwfilt3p3z_config_t
* If any y coefficient is greater than 1 then divide all the y coefficients by 2 and add 1 to scaleCY to match the reduced value. \ref cy_stc_ppca_hwfilt3p3z_config_t
* All the Y coefficients must swap the sign: if it is a negative value, it should be converted to positive, and if it is positive, it should be converted to negative. This is to numerically solve Transfer Function equation.
* dataOutOffset is direct addition to the output value. dataOutOffset will also contain the same number of fractional bits as actual output. \ref cy_stc_ppca_hwfilt3p3z_config_t
* gIn is mainly for amplifying the output. maximum supported value is 3 ie the output will be left shifted by 3. \ref cy_stc_ppca_hwfilt3p3z_config_t
* gOut is mainly to scale down. output is right shifted by the gOut value. \ref cy_stc_ppca_hwfilt3p3z_config_t
*
* Floating point to Hex conversion
* * All the floating points are 23 bit fractional values.
* * Multiply the floating pointer number with 2^23.
* * Convert the resulting integer to hex. The binary representation will have 23 bits.
* * If the floating point number is a negative number then calculate the 2's complement of the resulting hex.
*
* \section group_ppca_hwfilt3p3z_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
*
* \defgroup group_ppca_hwfilt3p3z_functions Functions
* \defgroup group_ppca_hwfilt3p3z_structures Configuration Structures
* \defgroup group_ppca_hwfilt3p3z_enums Enumerations
* \defgroup group_ppca_hwfilt3p3z_macros Macros
*
*/
#if !defined(CY_PPCA_HWFILT3P3Z_H)
#define CY_PPCA_HWFILT3P3Z_H

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
* \addtogroup group_ppca_hwfilt3p3z_macros
* \{
*/
/** The driver major version */
#define CY_PPCA_HWFILT3P3Z_DRV_VERSION_MAJOR       1U

/** The driver minor version */
#define CY_PPCA_HWFILT3P3Z_DRV_VERSION_MINOR       0U

/** The CORDIC driver ID */
#define CY_PPCA_HWFILT3P3Z_ID                      CY_PDL_DRV_ID(0x98U)

/** \cond INTERNAL */

#define CY_IS_HWFILTER_PARAM_VALID(param)              (NULL != param)
#define PPCA_HWFILT3P3Z_CNFG_EN_DATA_IN_Pos (PPCA_HWFILT3P3Z_SS_0_HWFILT3P3Z_CNFG_EN_TRIG0_Pos)
#define PPCA_HWFILT3P3Z_CNFG_EN_DATA_IN_Msk (PPCA_HWFILT3P3Z_SS_0_HWFILT3P3Z_CNFG_EN_TRIG0_Msk | PPCA_HWFILT3P3Z_SS_0_HWFILT3P3Z_CNFG_EN_TRIG1_Msk)

/** \endcond */

/** \} group_ppca_hwfilt3p3z_macros */


/***************************************
*       Enumerations
***************************************/
/**
* \addtogroup group_ppca_hwfilt3p3z_enums
* \{
*/

/** Source for DATA_IN1 data register */
typedef enum
{
    CY_AHB_IF    = 0U,   /**< The register is sourced from AHB interface */
    CY_DATA_PATH = 1U,  /**< The register is sourced from the ADC Filter */
}cy_en_ppca_filter_src_sel_t;

/** Data from DATA IN0 or DATA IN1 */
typedef enum
{
    CY_DISABLE_DATA_IN     = 0U,  /**< Both DATA IN0 and DATA IN1 are disabled. */
    CY_ENABLE_DATA_IN0     = 1U,  /**< DATA IN0 is enabled. */
    CY_ENABLE_DATA_IN1     = 2U,  /**< DATA IN1 is enabled. */
}cy_en_ppca_filter_data_sel_t;


/** Scale Factors for Coefficients */
typedef enum
{
    CY_SCALE_FACTOR_0 = 0U,  /**< Scale Factor is 0 */
    CY_SCALE_FACTOR_1 = 1U,  /**< Scale Factor is 1 */
    CY_SCALE_FACTOR_2 = 2U,  /**< Scale Factor is 2 */
    CY_SCALE_FACTOR_3 = 3U,  /**< Scale Factor is 3 */
    CY_SCALE_FACTOR_4 = 4U,  /**< Scale Factor is 4 */
    CY_SCALE_FACTOR_5 = 5U,  /**< Scale Factor is 5 */
    CY_SCALE_FACTOR_6 = 6U,  /**< Scale Factor is 6 */
    CY_SCALE_FACTOR_7 = 7U,  /**< Scale Factor is 7 */
}cy_en_ppca_filter_scale_factor_t;


/** Filter Status */
typedef enum
{
    CY_FILTER_IS_FREE    = 0U,  /**< The filter is free */
    CY_FILTER_IS_BUSY    = 1U,  /**< The filer is busy */
}cy_en_ppca_filter_status_t;

/** \} group_ppca_hwfilt3p3z_enums */


/***************************************
*       Configuration Structures
***************************************/

/**
* \addtogroup group_ppca_hwfilt3p3z_structures
* \{
*/

/** Filter Coefficients */
typedef struct cy_stc_ppca_filter_coefficients
{
    uint32_t cx0;       /**< X0 coefficient data */
    uint32_t cx1;       /**< X1 coefficient data */
    uint32_t cx2;       /**< X2 coefficient data */
    uint32_t cx3;       /**< X3 coefficient data */
    uint32_t cy1;       /**< Y1 coefficient data */
    uint32_t cy2;       /**< Y2 coefficient data */
    uint32_t cy3;       /**< Y3 coefficient data */
}cy_stc_ppca_filter_coefficients_t;


/** HWFILT3P3Z configuration structure */
typedef struct cy_stc_ppca_hwfilt3p3z_config
{
    cy_en_ppca_filter_src_sel_t srcSel;          /**< Source for the DATA_IN1 data register */
    bool enTrig0;                                /**< Enable/Disable filter processing on writing into DATA_IN0. enTrig0 and enTrig1 should not be set at the same time */
    bool enTrig1;                                /**< Enable/Disable filter processing on writing into DATA_IN1. enTrig0 and enTrig1 should not be set at the same time */
    uint32_t cx0;                                /**< X0 coefficient data */
    uint32_t cx1;                                /**< X1 coefficient data */
    uint32_t cx2;                                /**< X2 coefficient data */
    uint32_t cx3;                                /**< X3 coefficient data */
    uint32_t cy1;                                /**< Y1 coefficient data */
    uint32_t cy2;                                /**< Y2 coefficient data */
    uint32_t cy3;                                /**< Y3 coefficient data */
    uint32_t dataOutOffset;                      /**< Filter data out offset */
    uint32_t limMax;                             /**< Max limit of filter out */
    uint32_t limMin;                             /**< Min limit of filter out */
    uint8_t scaleCX;                             /**< Scale X coefficients factor */
    uint8_t scaleCY;                             /**< Scale Y coefficients factor */
    uint8_t gIn;                                 /**< Amplify input difference factor */
    uint8_t gOut;                                /**< Scale down output factor */
}cy_stc_ppca_hwfilt3p3z_config_t;

/** \} group_ppca_hwfilt3p3z_structures */


/***************************************
*        Function Prototypes
***************************************/

/**
* \addtogroup group_ppca_hwfilt3p3z_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_PPCA_HWFILT3P3Z_SS_PeripheralEnable
****************************************************************************//**
*
* Enables PPCA HWFILT3P3Z_SS block.
*
* \param *base
* The PPCA HWFILT3P3Z_SS registers structure pointer.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_HWFILT3P3Z_SS_PeripheralEnable(PPCA_HWFILT3P3Z_SS_Type *base)
{
    PPCA_HWFILT3P3Z_CTRL(base) |= PPCA_HWFILT3P3Z_SS_0_CTRL_HWFILT3P3Z_EN_Msk;
}


/*******************************************************************************
* Function Name: Cy_PPCA_HWFILT3P3Z_PeripheralDisable
****************************************************************************//**
*
* Disables PPCA HWFILT3P3Z_SS block.
*
* \param *base
* The PPCA HWFILT3P3Z_SS registers structure pointer.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_HWFILT3P3Z_SS_PeripheralDisable(PPCA_HWFILT3P3Z_SS_Type *base)
{
    PPCA_HWFILT3P3Z_CTRL(base) &= (uint32_t)~PPCA_HWFILT3P3Z_SS_0_CTRL_HWFILT3P3Z_EN_Msk;
}


/*******************************************************************************
* Function Name: Cy_PPCA_HWFILT3P3Z_FilterEnable
****************************************************************************//**
*
* Enables/Disables filter.
*
* \param *base
* The PPCA HWFILT3P3Z_SS registers structure pointer.
*
* \param enable
* true: enables the filter
* false: disables the filter.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_HWFILT3P3Z_FilterEnable(PPCA_HWFILT3P3Z_SS_HWFILT3P3Z_Type *base, bool enable)
{
    if(enable)
    {
        PPCA_HWFILT3P3Z_SS_CTRL(base) |= PPCA_HWFILT3P3Z_SS_0_HWFILT3P3Z_CTRL_FILTER_EN_Msk;
    }
    else
    {
        PPCA_HWFILT3P3Z_SS_CTRL(base) &= (uint32_t)~PPCA_HWFILT3P3Z_SS_0_HWFILT3P3Z_CTRL_FILTER_EN_Msk;
    }
}


 /*******************************************************************************
* Function Name: Cy_PPCA_HWFILT3P3Z_InitFilterConfig
****************************************************************************//**
*
* Configures the initial parameters of the HWFILT3P3Z filter including the
* filter processing config, coefficients, data out offset, limits,
* coefficients scaling factors, and gains.
*
* \param *base
* The PPCA HWFILT3P3Z_SS registers structure pointer.
*
* \param *config
* The pointer to the HWFILT3P3Z configuration structure.
*
*******************************************************************************/
void Cy_PPCA_HWFILT3P3Z_InitFilterConfig(PPCA_HWFILT3P3Z_SS_HWFILT3P3Z_Type *base, cy_stc_ppca_hwfilt3p3z_config_t const *config);


/*******************************************************************************
* Function Name: Cy_PPCA_HWFILT3P3Z_ReadFilterStatus
****************************************************************************//**
*
* Provides the filter busy status.
*
* \param *base
* The PPCA HWFILT3P3Z_SS registers structure pointer.
*
* \return
* The filter busy status. \ref cy_en_ppca_filter_status_t .
*
*******************************************************************************/

__STATIC_INLINE cy_en_ppca_filter_status_t Cy_PPCA_HWFILT3P3Z_ReadFilterStatus(PPCA_HWFILT3P3Z_SS_HWFILT3P3Z_Type *base)
{
    uint32_t ss_ctrl = _FLD2VAL(PPCA_HWFILT3P3Z_SS_0_HWFILT3P3Z_CTRL_FILTER_BUSY, PPCA_HWFILT3P3Z_SS_CTRL(base));
    return (cy_en_ppca_filter_status_t)(ss_ctrl);
}


/*******************************************************************************
* Function Name: Cy_PPCA_HWFILT3P3Z_ReadFilterDataOutput
****************************************************************************//**
*
* Provides the filter data output.
*
* \param *base
* The PPCA HWFILT3P3Z_SS registers structure pointer.
*
* \return
* Filter data output.
*
*******************************************************************************/
__STATIC_INLINE int32_t Cy_PPCA_HWFILT3P3Z_ReadFilterDataOutput(PPCA_HWFILT3P3Z_SS_HWFILT3P3Z_Type *base)
{
    return (int32_t)PPCA_HWFILT3P3Z_SS_DATA_OUT(base);  /* TBD */
}


/*******************************************************************************
* Function Name: Cy_PPCA_HWFILT3P3Z_ConfigFilterProcessing
****************************************************************************//**
*
* Configures the filter processing parameters.
*
* \param *base
* The PPCA HWFILT3P3Z_SS registers structure pointer.
*
* \param srcSel
* The data source for register DATA_IN1. \ref cy_en_ppca_filter_src_sel_t.
*
* \param data_in
* Configures data from DATA IN0 or DATA IN1. \ref cy_en_ppca_filter_data_sel_t
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_HWFILT3P3Z_ConfigFilterProcessing(PPCA_HWFILT3P3Z_SS_HWFILT3P3Z_Type *base, cy_en_ppca_filter_src_sel_t srcSel, cy_en_ppca_filter_data_sel_t data_in)
{
    PPCA_HWFILT3P3Z_SS_CNFG(base) = _VAL2FLD(PPCA_HWFILT3P3Z_SS_0_HWFILT3P3Z_CNFG_SRC_SEL, srcSel) |
                                    _VAL2FLD(PPCA_HWFILT3P3Z_CNFG_EN_DATA_IN, data_in);
}

/*******************************************************************************
* Function Name: Cy_PPCA_HWFILT3P3Z_Write_DATA_IN0
****************************************************************************//**
*
* Writes Filter Data 0 Input.
*
* \param *base
* The PPCA HWFILT3P3Z_SS registers structure pointer.
*
* \param inputData
* 16 bit Filter Data 0 input value.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_HWFILT3P3Z_Write_DATA_IN0(PPCA_HWFILT3P3Z_SS_HWFILT3P3Z_Type *base, int32_t inputData)
{
    PPCA_HWFILT3P3Z_SS_DATA_IN0(base) = (uint32_t)inputData;
}



/*******************************************************************************
* Function Name: Cy_PPCA_HWFILT3P3Z_Write_DATA_IN1
****************************************************************************//**
*
* Writes Filter Data 1 Input.
*
* \param *base
* The PPCA HWFILT3P3Z_SS registers structure pointer.
*
* \param inputData
* 16 bit Filter Data 1 input value.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_HWFILT3P3Z_Write_DATA_IN1(PPCA_HWFILT3P3Z_SS_HWFILT3P3Z_Type *base, int32_t inputData)
{
    PPCA_HWFILT3P3Z_SS_DATA_IN1(base) = (uint32_t)inputData;
}


/*******************************************************************************
* Function Name: Cy_PPCA_HWFILT3P3Z_ConfigCoefficients
****************************************************************************//**
*
* Configures the filter coefficients: CX0, CX1, CX2, CX3, CY1, CY2, CY3.
*
* \param *base
* The PPCA HWFILT3P3Z_SS registers structure pointer.
*
* \param *config
* The pointer to the HWFILT3P3Z filter coefficients structure.
* \ref cy_stc_ppca_filter_coefficients_t .
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_HWFILT3P3Z_ConfigCoefficients(PPCA_HWFILT3P3Z_SS_HWFILT3P3Z_Type *base, cy_stc_ppca_filter_coefficients_t const *config)
{
    PPCA_HWFILT3P3Z_SS_CX0(base) = config->cx0;
    PPCA_HWFILT3P3Z_SS_CX1(base) = config->cx1;
    PPCA_HWFILT3P3Z_SS_CX2(base) = config->cx2;
    PPCA_HWFILT3P3Z_SS_CX3(base) = config->cx3;
    PPCA_HWFILT3P3Z_SS_CY1(base) = config->cy1;
    PPCA_HWFILT3P3Z_SS_CY2(base) = config->cy2;
    PPCA_HWFILT3P3Z_SS_CY3(base) = config->cy3;
}

/*******************************************************************************
* Function Name: Cy_PPCA_HWFILT3P3Z_ConfigOffset
****************************************************************************//**
*
* Configures the filter data out offset value.
*
* \param *base
* The PPCA HWFILT3P3Z_SS registers structure pointer.
*
* \param offset
* The filter data out offset value.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_HWFILT3P3Z_ConfigOffset(PPCA_HWFILT3P3Z_SS_HWFILT3P3Z_Type *base, int32_t offset)
{
    PPCA_HWFILT3P3Z_SS_OFFSET(base) = (uint32_t)offset;
}


/*******************************************************************************
* Function Name: Cy_PPCA_HWFILT3P3Z_ConfigFilterOutLimits
****************************************************************************//**
*
* Configures the filter out max and min limit values.
*
* \param *base
* The PPCA HWFILT3P3Z_SS registers structure pointer.
*
* \param lmax
* The filter out max limit value.
*
* \param lmin
* The filter out min limit value.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_HWFILT3P3Z_ConfigFilterOutLimits(PPCA_HWFILT3P3Z_SS_HWFILT3P3Z_Type *base, int32_t lmax, int32_t lmin)
{
    PPCA_HWFILT3P3Z_SS_LIMMAX(base) = (uint32_t)lmax;
    PPCA_HWFILT3P3Z_SS_LIMMIN(base) = (uint32_t)lmin;
}


/*******************************************************************************
* Function Name: Cy_PPCA_HWFILT3P3Z_ConfigCoefficientScaleFactors
****************************************************************************//**
*
* Configures the scaling factors for the filter coefficients.
*
* \param *base
* The PPCA HWFILT3P3Z_SS registers structure pointer.
*
* \param scaleCX
* Scale X coefficients factor. \ref cy_en_ppca_filter_scale_factor_t.
*
* \param scaleCY
* Scale Y coefficients factor. \ref cy_en_ppca_filter_scale_factor_t.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_HWFILT3P3Z_ConfigCoefficientScaleFactors(PPCA_HWFILT3P3Z_SS_HWFILT3P3Z_Type *base, cy_en_ppca_filter_scale_factor_t scaleCX, cy_en_ppca_filter_scale_factor_t scaleCY)
{
    PPCA_HWFILT3P3Z_SS_SCALECX(base) = (uint32_t)scaleCX;
    PPCA_HWFILT3P3Z_SS_SCALECY(base) = (uint32_t)scaleCY;
}


/*******************************************************************************
* Function Name: Cy_PPCA_HWFILT3P3Z_ConfigCoefficientScaleFactors
****************************************************************************//**
*
* Configures the filter gain factors.
*
* \param *base
* The PPCA HWFILT3P3Z_SS registers structure pointer.
*
* \param gIn
* Amplify input difference factor.
*
* \param gOut
* Scale down output factor.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_HWFILT3P3Z_ConfigGains(PPCA_HWFILT3P3Z_SS_HWFILT3P3Z_Type *base, uint8_t gIn, uint8_t gOut)
{
    PPCA_HWFILT3P3Z_SS_GIN(base)  = gIn;
    PPCA_HWFILT3P3Z_SS_GOUT(base) = gOut;
}


/** \} group_ppca_hwfilt3p3z_functions */

#if defined(__cplusplus)
}
#endif

#endif /* #if defined(CY_IP_MXS40PPSS) */

#endif /* (CY_PPCA_HWFILT3P3Z_H) */

/** \} group_ppca_hwfilt3p3z */

/* [] END OF FILE */
