/***************************************************************************//**
* \file cy_ppca_adc.h
* \version 1.0
*
* The header file of the PPCA ADC driver.
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


#if !defined(CY_PPCA_ADC_H)
#define CY_PPCA_ADC_H

#include "cy_device.h"

#if defined (CY_IP_MXS40PPSS) || defined (CY_DOXYGEN)

#include "cy_syslib.h"

#if defined(__cplusplus)
extern "C" {
#endif



/**
* \addtogroup group_ppca_atop          ATOP
* \{
* The ATOP PDL driver provides API to use the ATOP HW block.
*
* \section group_ppca_atop_glossary Glossary
* Some of the key sub-blocks of the ATOP includes:
*
* * ADC
* * ADC Filter
* * Digital Comparator
* * GPI
* * IDAC
* * AREF
* * Analog Comparator
* * Slope generator
* * DAC R2R
*

*******************************************************************************
* \section group_ppca_atop_changelog Changelog
*******************************************************************************
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td rowspan="1">1.0</td>
*     <td>Initial version.</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_ppca_adc           ADC
* \{
*   \section group_ppca_adc_changelog Changelog
*    <table class="doxtable">
*     <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*     <tr>
*       <td>1.0</td>
*       <td>Initial version</td>
*       <td></td>
*     </tr>
*    </table>
*   \defgroup group_ppca_adc_macros                Macros
*   \defgroup group_ppca_adc_functions             Functions
*   \defgroup group_ppca_adc_data_structures Data Structures
*
* \}
* \defgroup group_ppca_adc_filter    ADC Filter
* \defgroup group_ppca_dcmp          DCMP         (Digital Comparator)
* \defgroup group_ppca_dcsg          DCSG         (Differential Comparator And Slope Generator)
* \defgroup group_ppca_dcsg_slgen    DCSG SLGEN   (Slope Generator)
* \defgroup group_ppca_dacr2r        DAC          (DAC R2R)
* \defgroup group_ppca_aref          AREF
* \} */

/**
* \addtogroup group_ppca_adc_macros
* \{
*/
/** ATOPSS AFE Type */
#define ATOPSS_AFE_TYPE PPCA_ATOPSS_ADC_GRP_SLICE_AFE_Type
/** ATOPSS ADC Type */
#define ATOPSS_ADC_TYPE PPCA_ATOPSS_ADC_GRP_SLICE_ADC_Type
/** ADC Error interrupt mask */
#define ATOPSS_ADC_ERROR_INTERRUPT_MASK PPCA_ATOPSS_ADC_GRP_ADC_SLICE_ADC_ADC_INTR_MASK_TR_ERROR_Msk

/** \} group_ppca_adc_macros */

/** \cond INTERNAL */
#define CY_ADC_CHANNEL(ch_num)            (ch_num <= 16u)
#define CY_ADC_AUX_CHANNEL(ch_num)        ((uint16_t)ch_num <= 16u)
#define CY_ADC_ALT_AUX_CHANNEL(ch_num)    ((uint16_t)ch_num <= 8u)

#define CY_ADC_SINGLE_ENDED_CHANNEL    0
#define CY_ADC_DIFFERENTIAL_CHANNEL    1

#define CY_ADC_SIGNED_CHANNEL          1
#define CY_ADC_UNSIGNED_CHANNEL        0
#define CY_PPCA_ADC_TEMP_VALID(val)       ((0 < (val)))
#define CY_PPCA_TWO_TOPOWEROF_TEN ((int32_t)1024)
#define CY_PPCA_TWO_TOPOWEROF_SIXTEEN ((int32_t)65536)
#define CY_PPCA_XC (float)15.0
#define CY_PPCA_YC (float)0.5
#define CY_PPCA_SAR_100C (float)100.0
#define CY_PPCA_SAR_40C (float)40.0
#define Cy_PPCA_ADC_Manual_Trigger Cy_PPCA_ADC_Trigger
/** \endcond */
/**
* \addtogroup group_ppca_adc_data_structures
* \{
*/

/** ADC Auxiliary Channels selection multiplexed with channel 7 P Pin  */
typedef enum
{
    CY_DAC_R2R0_OUTPUT      = 0UL,        /**< DAC_R2R_0 Output      */
    CY_DAC_R2R1_OUTPUT      = 1UL,        /**< DAC_R2R_1 Output      */
    CY_AUX_CHANNEL_AI0      = 2UL,        /**< Auxiliary channel AI0  */
    CY_AUX_CHANNEL_AI1      = 3UL,        /**< Auxiliary channel AI1  */
    CY_AUX_CHANNEL_TSNS     = 4UL,        /**< Auxiliary channel TSNS */
    CY_AUX_CHANNEL_VREF     = 5UL,        /**< Auxiliary channel VREF */
    CY_VDDA_DIV2_DCSG_GRP0  = 6UL,        /**< VDDA Div 2 Voltage from DCSG_GRP_0   */
    CY_VDDA_DIV2_DCSG_GRP1  = 7UL,        /**< VDDA Div 2 Voltage from DCSG_GRP_1   */
} cy_en_aux_channel_t;

/** ADC ALT Auxiliary Channels selection multiplexed with AI_AUX  */
typedef enum
{
    CY_ALT_AUX_AIN3N_AIN11N   = 0UL,        /**< For ADC_GRP_0, it will be AIN3N. For ADC_GRP_3, it will be AIN11N */
    CY_ALT_AUX_AI2_AI9        = 1UL,        /**< For ADC_GRP_0, it will be AI2. For ADC_GRP_3, it will be AI9      */
    CY_ALT_AUX_AI3_AI10       = 2UL,        /**< For ADC_GRP_0, it will be AI3. For ADC_GRP_3, it will be AI10     */
    CY_ALT_AUX_AI4_AI11       = 3UL,        /**< For ADC_GRP_0, it will be AI4. For ADC_GRP_3, it will be AI11     */
    CY_ALT_AUX_AI5_AI12       = 4UL,        /**< For ADC_GRP_0, it will be AI5. For ADC_GRP_3, it will be AI12     */
    CY_ALT_AUX_AI6_AI13       = 5UL,        /**< For ADC_GRP_0, it will be AI6. For ADC_GRP_3, it will be AI13     */
    CY_ALT_AUX_AI7_AI14       = 6UL,        /**< For ADC_GRP_0, it will be AI7. For ADC_GRP_3, it will be AI14     */
    CY_ALT_AUX_AI8_AI15       = 7UL,        /**< For ADC_GRP_0, it will be AI8. For ADC_GRP_3, it will be AI15     */
} cy_en_alt_aux_channel_t;

/** VSSA  */
typedef enum
{
    CY_ADC_VSSA_ADC3            = 0UL,        /**< For VSSA_ADC3          */
    CY_ADC_VSSA_DCSG_GRP0       = 1UL,        /**< For VSSA_DCSG_GRP0     */
    CY_ADC_VSSA_DCSG_GRP1       = 2UL,        /**< For VSSA_DCSG_GRP1     */
    CY_ADC_VSSA_DCSG_GRP1_SP    = 3UL,        /**< For VSSA_DCSG_GRP1_SP  */
} cy_en_adc_vssa_t;

/** Specifies the ADC7,AUX_DATA,ALT_AUX_DATA path  */
typedef enum
{
    CY_DATA_PATH_ADC7      = 0UL,        /**< ADC data path set to ADC7    */
    CY_DATA_PATH_AUX       = 2UL,        /**< ADC data path set to AUX     */
    CY_DATA_PATH_ALT_AUX   = 3UL,        /**< ADC data path set to ALT_AUX */
} cy_en_adc_data_path_t;

/** Specifies the Trigger Mode  */
typedef enum
{
    CY_ADC_MANUAL_TRIGGER      = 0UL,        /**< Manual Trigger Mode    */
    CY_ADC_AUTO_TRIGGER        = 1UL,        /**< Auto trigger Mode (Continuous Conversion)     */
    CY_ADC_ARBITRARY_TRIGGER   = 2UL,        /**< Arbitrary trigger Mode (Arbitrary Conversion - Based on the individual adc_soc_i[x]) */
} cy_en_adc_trigger_mode_t;

/** AFE GAIN Settings. */
typedef enum
{
    CY_AFE_GAIN_0       = 0UL,        /**<AFE gain Set to 0. Gain is off. */
    CY_AFE_GAIN_3       = 1UL,        /**<AFE gain of 3 is set.  */
    CY_AFE_GAIN_6       = 2UL,        /**<AFE gain of 6 is set.  */
    CY_AFE_GAIN_12      = 3UL,        /**<AFE gain of 12 is set. */
    CY_AFE_GAIN_24      = 4UL,        /**<AFE gain of 24 is set. */
} cy_en_afe_gain_t;

/** AFE Power Setting. */
typedef enum
{
    CY_AFE_PWR_HFLG       = 0UL,        /**<AFE power setting for High frequency low gain. */
    CY_AFE_PWR_HFLG_LP    = 1UL,        /**<AFE power setting for High frequency low gain, Low Power */
    CY_AFE_PWR_HFLG_ULP   = 2UL,        /**<AFE power setting for High frequency low gain, Ultra Low Power */
    CY_AFE_PWR_LFHG       = 3UL,        /**<AFE power setting for Low frequency high gain */

} cy_en_afe_power_t;

/** AFE Clock Ratio Setting. Define the ADC MSPS setup based on ATOP_CLK relationship */
typedef enum
{
    CY_AFE_CLK_RATIO_ATOPCLK_BY_4    = 0UL,        /**<AFE Clock Ratio set to ATOP_CLOCK/4  */
    CY_AFE_CLK_RATIO_ATOPCLK_BY_8    = 1UL,        /**<AFE Clock Ratio set to ATOP_CLOCK/8  */
    CY_AFE_CLK_RATIO_ATOPCLK_BY_16   = 2UL,        /**<AFE Clock Ratio set to ATOP_CLOCK/16 */
    CY_AFE_CLK_RATIO_ATOPCLK_BY_32   = 3UL,        /**<AFE Clock Ratio set to ATOP_CLOCK/32 */

} cy_en_afe_clock_ratio_t;

/** PPCA ADC Auxiliary Slot configuration structure */
typedef struct cy_stc_aux_slot_config
{
    uint8_t                 aux_ch;               /**< ADC Auxiliary Channels selection multiplexed with channel 7 P Pin  */
    uint8_t                 aux_ch_gnd;           /**< ADC Auxiliary Channels selection multiplexed with channel 7 N Pin  */
    uint8_t                 alt_aux_ch;           /**< ADC ALT Auxiliary Channels selection multiplexed with AI_AUX  */
    uint8_t                 alt_aux_ch_gnd;       /**< ADC ALT Auxiliary Channels GND selection multiplexed with AI_AUX  */
    cy_en_adc_vssa_t        aux_gnd_group2;       /**< AUX_GND_GRP_2  */
    cy_en_adc_vssa_t        alt_aux_gnd_group2;   /**< ALT_AUX_GND_GRP_2  */
    cy_en_adc_data_path_t   ch7_data_path;        /**< Specifies the ADC7,AUX_DATA,ALT_AUX_DATA  */
    bool                    gnd_group;            /**< When set to 0 : Bit 11:8/Bit 26:24 are used for ground. When set to 1 : Bit 13:12/Bit 28:27 are used for ground. */
}cy_stc_aux_slot_config_t;


/** PPCA ADC Conversion configuration structure */
typedef struct cy_stc_adc_conversion_config
{
    bool              group_channel;                  /**< Select between Single channel or Group of sequence of Channels to be converted at provided trigger. */
    cy_en_adc_trigger_mode_t  trigger_mode;           /**< Trigger Mode Selection \ref cy_en_adc_trigger_mode_t  */
    uint8_t           auto_trigger_sample_clck;       /**< Number of system clock cycles for sampling on top of a minimum of 4 clock cycles (0+4). This is not applicable for Arbitrary trigger mode. When AFE is used, AFE_CLOCK_RATIO will define the sample period . Range : 0 to 63 */
    uint8_t           num_of_slot;                    /**< Number of Slot to be converted for each provided trigger when Group of Channel flag is set. Do not set more than the maximum number of the NUM_CH of in the GRP ADC.   */
    bool              eos_src;                        /**< Select Source of EOS (when in Manual Trigger mode). false : Internal EOS. true : External EOS  */
    uint8_t           num_of_aux_slot;                /**< Number of AUX Slot to be converted for each provided trigger when Group of Channel flag is set */
    uint8_t           num_of_alt_aux_slot;            /**< Number of ALT AUX Slot to be converted for each provided trigger when Group of Channel flag is set */
    uint8_t           aux_slot_scan_rate;             /**< To define how many time the channel will be converted before slot switches to the next AUX Channel 0x00 = 1 time. 0x1F is 32 times */
    bool              ext_src;                        /**< EXT_SOURCE_SEL 0: not part of the AUX and ALT_AUX channel slot control. 1: part of slot control, This means EXT_SOURCE_SEL channel is configured in the ADC_CH_CNFGx  */
    uint32_t          sequence_of_channel;            /**< sequence of Channel to be converted. Sequence to be provided in hex. example: if ch2 and ch6 are enabled and 6 to be converted first then the value should be 0x26. CH1_TBC will be the default channel for AFE if AFE is enabled. */
    uint32_t          sequence_of_aux_channel;        /**< sequence of Auxiliary Channel to be converted. Sequence to be provided in hex. example: if ch3 and ch2 are enabled and 2 to be converted first then the value should be 0x32. */
    uint32_t          sequence_of_alt_aux_channel;    /**< sequence of ALT Auxiliary Channel to be converted. Sequence to be provided in hex. example: if ch0 and ch7 are enabled and 0 to be converted first then the value should be 0x70. */
}cy_stc_adc_conversion_config_t;

/** PPCA ADC configuration structure */
typedef struct cy_stc_ppca_adc_config
{
    bool              calib_gain_mode;                   /**< if enabled, IP handles calibration and gain computation. */
    bool              aux_slot;                          /**< Specifies the slot control scheme for the AUX Channel */
    bool              alt_aux_slot;                      /**< Specifies the slot control scheme for the ALT AUX Channel */
    uint16_t          channels;                          /**< Channels to be enabled. each bit represent one channel */
    uint16_t          channel_type;                      /**< Single ended or differential channel. Each bit represent one channel  */
    uint16_t          channel_data_type;                 /**< configuration for signed or unsigned ADC channel. 0: unsigned, 1: signed. Each bit represent one channel  */
    uint16_t          aux_channel_data_type;             /**< configuration for signed or unsigned AUX ADC channel. 0: unsigned, 1: signed. Each bit represent one channel  */
    uint8_t           alt_aux_channel_data_type;         /**< configuration for signed or unsigned ALT AUX ADC channel. 0: unsigned, 1: signed. Each bit represent one channel  */
    cy_stc_aux_slot_config_t   *aux_slot_config;         /**< Aux Slot Configuration */
    cy_stc_adc_conversion_config_t adc_conv_config;      /**< ADC Conversion Configuration */
}cy_stc_ppca_adc_config_t;

/** PPCA AFE configuration structure */
typedef struct cy_stc_ppca_afe_config
{
    cy_en_afe_gain_t afe_gain;                        /**< AFE gain Setting. */
    cy_en_afe_power_t afe_pwr;                        /**< AFE Power Setting. */
    cy_en_afe_clock_ratio_t afe_clk_ratio;            /**< AFE Clock Ratio Setting. Define the ADC MSPS setup based on ATOP_CLK relationship */
}cy_stc_ppca_afe_config_t;


/** \} group_ppca_adc_data_structures */


/**
* \addtogroup group_ppca_adc_functions
* \{
*/

/******************************************************************************
* Function Name: Cy_PPCA_AFE_Init
***************************************************************************//**
*
* Initializes AFE
*
* \param base The pointer to the AFE instance address.
*
* \param config The pointer to the config structure.
*
* \note Should be called from Main core so that all the trim registers are configured. If called from PPCA core trim registers are not configured. 
******************************************************************************/
#if defined (COMPONENT_PPCA_DEVICE) && !defined (__ICCARM__)
void Cy_PPCA_AFE_Init(ATOPSS_AFE_TYPE *base, cy_stc_ppca_afe_config_t const *config )__attribute__((warning("Initialization of PPCA peripherals like AREF, ADC, DAC and DCSG to be done on Main core. Trim values are not configured if called on PPCA cores.")));
#else
void Cy_PPCA_AFE_Init(ATOPSS_AFE_TYPE *base, cy_stc_ppca_afe_config_t const *config );
#endif

/******************************************************************************
* Function Name: Cy_PPCA_AFE_DeInit
***************************************************************************//**
*
* De-Initializes and disables the AFE
*
* \param base The pointer to the AFE instance address.
*
******************************************************************************/
void Cy_PPCA_AFE_DeInit(ATOPSS_AFE_TYPE *base);


/******************************************************************************
* Function Name: Cy_PPCA_ADC_Init
***************************************************************************//**
*
* Initializes ADC
*
* \param base The pointer to the ADC instance address.
*
* \param config The pointer to the config structure.
*
*
* \note Should be called from Main core so that all the trim registers are configured. If called from PPCA core trim registers are not configured.
******************************************************************************/
#if defined (COMPONENT_PPCA_DEVICE) && !defined (__ICCARM__)
void Cy_PPCA_ADC_Init(ATOPSS_ADC_TYPE *base, cy_stc_ppca_adc_config_t const *config )__attribute__((warning("Initialization of PPCA peripherals like AREF, ADC, DAC and DCSG to be done on Main core. Trim values are not configured if called on PPCA cores.")));
#else
void Cy_PPCA_ADC_Init(ATOPSS_ADC_TYPE *base, cy_stc_ppca_adc_config_t const *config );
#endif



/******************************************************************************
* Function Name: Cy_PPCA_ADC_DeInit
***************************************************************************//**
*
* De-Initializes and disables the ADC
*
* \param base The pointer to the ADC instance address.
*
******************************************************************************/
void Cy_PPCA_ADC_DeInit(ATOPSS_ADC_TYPE *base);

/******************************************************************************
* Function Name: Cy_PPCA_ADC_Enable
***************************************************************************//**
*
* Enables the ADC
*
* \param base The pointer to the ADC instance address.
*
******************************************************************************/
__STATIC_INLINE void Cy_PPCA_ADC_Enable(ATOPSS_ADC_TYPE *base)
{
    PPCA_ATOP_ADC_CTRL(base) |= PPCA_ATOPSS_ADC_GRP_SLICE_ADC_ADC_CTL_ADC_EN_Msk;
}

/******************************************************************************
* Function Name: Cy_PPCA_ADC_Disable
***************************************************************************//**
*
* Disables the ADC
*
* \param base The pointer to the ADC instance address.
*
******************************************************************************/
__STATIC_INLINE void Cy_PPCA_ADC_Disable(ATOPSS_ADC_TYPE *base)
{
    PPCA_ATOP_ADC_CTRL(base) &= (uint32_t) ~PPCA_ATOPSS_ADC_GRP_SLICE_ADC_ADC_CTL_ADC_EN_Msk;
}

/******************************************************************************
* Function Name: Cy_PPCA_AFE_Enable
***************************************************************************//**
*
* Enables the AFE
*
* \param base The pointer to the AFE instance address.
*
******************************************************************************/
__STATIC_INLINE void Cy_PPCA_AFE_Enable(ATOPSS_AFE_TYPE *base)
{
    PPCA_ATOP_AFE_CTL(base) |= PPCA_ATOPSS_ADC_GRP_SLICE_AFE_AFE_CTL_AFE_EN_0_Msk;
}

/******************************************************************************
* Function Name: Cy_PPCA_AFE_Disable
***************************************************************************//**
*
* Disables the AFE
*
* \param base The pointer to the AFE instance address.
*
******************************************************************************/
__STATIC_INLINE void Cy_PPCA_AFE_Disable(ATOPSS_AFE_TYPE *base)
{
    PPCA_ATOP_AFE_CTL(base) &= (uint32_t) ~PPCA_ATOPSS_ADC_GRP_SLICE_AFE_AFE_CTL_AFE_EN_0_Msk;
}


/******************************************************************************
* Function Name: Cy_PPCA_ADC_Is_ADC_Busy
***************************************************************************//**
*
* Returns the status of the ADC
*
* \param base The pointer to the ADC instance address.
*
* \return returns if ADC is busy or not.
*
******************************************************************************/
__STATIC_INLINE bool Cy_PPCA_ADC_Is_ADC_Busy(ATOPSS_ADC_TYPE *base)
{
    return (bool)_FLD2VAL(PPCA_ATOPSS_ADC_GRP_SLICE_ADC_ADC_CTL_ADC_BUSY, PPCA_ATOP_ADC_CTRL(base));
}

/******************************************************************************
* Function Name: Cy_PPCA_ADC_Set_Calib_Gain_mode
***************************************************************************//**
*
* if enabled, IP handles calibration and gain computation.
* if disabled, based on the AFE enabled status, gain and offset will be picked from the AFE or ADC 
*
* \param base The pointer to the ADC instance address.
*
* \param gain_mode Gain calibrated by IP or by the subsystem.
*
******************************************************************************/
__STATIC_INLINE void Cy_PPCA_ADC_Set_Calib_Gain_mode(ATOPSS_ADC_TYPE *base, bool gain_mode)
{
    if(gain_mode)
    {
        PPCA_ATOP_ADC_CTRL(base) |= PPCA_ATOPSS_ADC_GRP_SLICE_ADC_ADC_CTL_CALIB_GAIN_MODE_Msk;
    }
    else
    {
        PPCA_ATOP_ADC_CTRL(base) &= (uint32_t) ~(PPCA_ATOPSS_ADC_GRP_SLICE_ADC_ADC_CTL_CALIB_GAIN_MODE_Msk);
    }
}

/******************************************************************************
* Function Name: Cy_PPCA_ADC_Set_Test_mode
***************************************************************************//**
*
* If enabled, IP runs in test mode. Test data will be copied to the Channel output.
* Use API Cy_PPCA_ADC_Write_Test_data to write the test data.
*
* \param base The pointer to the ADC instance address.
*
* \param test_mode enable/disable test mode.
*
******************************************************************************/
__STATIC_INLINE void Cy_PPCA_ADC_Set_Test_mode(ATOPSS_ADC_TYPE *base, bool test_mode)
{
    if(test_mode)
    {
        PPCA_ATOP_ADC_CTRL(base) |= PPCA_ATOPSS_ADC_GRP_SLICE_ADC_ADC_CTL_ADC_TEST_DATA_SEL_Msk;
    }
    else
    {
        PPCA_ATOP_ADC_CTRL(base) &= (uint32_t) ~(PPCA_ATOPSS_ADC_GRP_SLICE_ADC_ADC_CTL_ADC_TEST_DATA_SEL_Msk);
    }
}

/******************************************************************************
* Function Name: Cy_PPCA_ADC_Write_Test_data
***************************************************************************//**
*
* Sets Test data. This data will be copied to the Channel output on trigger.
* For this to work, Cy_PPCA_ADC_Set_Test_mode should be enabled.
*
* \param base The pointer to the ADC instance address.
*
* \param test_data 12 bit test data.
*
******************************************************************************/
__STATIC_INLINE void Cy_PPCA_ADC_Write_Test_data(ATOPSS_ADC_TYPE *base, uint32_t test_data)
{
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 11.3','Intentional pointer type conversion to access DATA_TEST_OFFSET');
    CY_SET_REG32((base + PPCA_ATOP_ADC_DATA_TEST_OFFSET), test_data);
}

/******************************************************************************
* Function Name: Cy_PPCA_ADC_Set_Trigger_mode
***************************************************************************//**
*
* Sets ADC trigger mode.
* For arbitrary mode, the TRIGGER signal comes from SOC signal (external signal) or by Cy_PPCA_ADC_Trigger call.
* For auto mode, the trigger signal comes from Cy_PPCA_ADC_Trigger call. In the auto trigger mode, the first trigger occurrence will start the auto trigger sequence.
* In the manual trigger mode, Cy_PPCA_ADC_Trigger call will start the programmed conversion sequence and then it waits for the next trigger.
*
* \param base The pointer to the ADC instance address.
*
* \param trigger_mode Trigger mode selection.
*
******************************************************************************/
__STATIC_INLINE void Cy_PPCA_ADC_Set_Trigger_mode(ATOPSS_ADC_TYPE *base, cy_en_adc_trigger_mode_t trigger_mode)
{
    PPCA_ATOP_ADC_CNV_CNFG(base) &= (uint32_t) ~(PPCA_ATOPSS_ADC_GRP_SLICE_ADC_ADC_CNV_CNFG_TRIGGER_MODE_Msk);
    PPCA_ATOP_ADC_CNV_CNFG(base) |= _VAL2FLD(PPCA_ATOPSS_ADC_GRP_SLICE_ADC_ADC_CNV_CNFG_TRIGGER_MODE, trigger_mode);
}

/******************************************************************************
* Function Name: Cy_PPCA_ADC_Trigger
***************************************************************************//**
*
* Software trigger or Manual trigger for ADC 
* In arbitrary mode, This will start conversion.
* In auto mode, this trigger occurrence will start the auto trigger sequence. and conversion will continue until trigger mode is set to Manual trigger mode.
* In the manual trigger mode, this call will start the conversion sequence and then it waits for the next trigger to start next conversion sequence.
*
* \param base The pointer to the ADC instance address.
*
* \param trigger Trigger a channel. Each bit represent one channel.
*
******************************************************************************/
__STATIC_INLINE void Cy_PPCA_ADC_Trigger(ATOPSS_ADC_TYPE *base, uint16_t trigger)
{
    PPCA_ATOP_ADC_TRIGGER(base) = (uint16_t)trigger;
}

/******************************************************************************
* Function Name: Cy_PPCA_ADC_Read_ADC_Data
***************************************************************************//**
*
* Returns 12 bit ADC Data for that particular channel
*
* \param base The pointer to the ADC instance address.
*
* \param ch_num Channel number for which ADC data to be read.
*
* \return returns ADC data.
*
******************************************************************************/
__STATIC_INLINE uint16_t Cy_PPCA_ADC_Read_ADC_Data(ATOPSS_ADC_TYPE *base, uint8_t ch_num)
{
    CY_ASSERT(CY_ADC_CHANNEL(ch_num));
    return (uint16_t)_FLD2VAL(PPCA_ATOPSS_ADC_GRP_SLICE_ADC_ADC_DATA_ADC_DATA, PPCA_ATOP_ADC_DATA(base, ch_num));
}

/******************************************************************************
* Function Name: Cy_PPCA_ADC_Read_SignExtended_ADC_Data
***************************************************************************//**
*
* Returns the Sign extended ADC Data for that particular channel.
* When ADC data is negative in the sign configuration, 13 to 31 bits will be 1.
* When ADC data is positive in the sign configuration or unsigned configuration, 13 to 31 bits will be 0.
*
* \param base The pointer to the ADC instance address.
*
* \param ch_num Channel number for which ADC data to be read.
*
* \return returns ADC data.
*
******************************************************************************/
__STATIC_INLINE uint32_t Cy_PPCA_ADC_Read_SignExtended_ADC_Data(ATOPSS_ADC_TYPE *base, uint8_t ch_num)
{
    CY_ASSERT(CY_ADC_CHANNEL(ch_num));
    return PPCA_ATOP_ADC_DATA(base, ch_num);
}

/******************************************************************************
* Function Name: Cy_PPCA_ADC_Read_AUX_ADC_Data
***************************************************************************//**
*
* Returns 12 bit AUX ADC Data for that particular channel
*
* \param base The pointer to the ADC instance address.
*
* \param ch_num Channel number for which AUX ADC data to be read. \ref cy_en_aux_channel_t
*
* \return returns ADC data.
*
******************************************************************************/
__STATIC_INLINE uint16_t Cy_PPCA_ADC_Read_AUX_ADC_Data(ATOPSS_ADC_TYPE *base, cy_en_aux_channel_t ch_num)
{
    CY_ASSERT(CY_ADC_AUX_CHANNEL(ch_num));
    return (uint16_t)_FLD2VAL(PPCA_ATOPSS_ADC_GRP_SLICE_ADC_ADC_AUX_DATA_ADC_AUX_DATA, PPCA_ATOP_ADC_AUX_DATA(base, ch_num));
}

/******************************************************************************
* Function Name: Cy_PPCA_ADC_Read_SignExtended_AUX_ADC_Data
***************************************************************************//**
*
* Returns the Sign extended AUX ADC Data for that particular channel.
* When ADC data is negative in the sign configuration, 13 to 31 bits will be 1.
* When ADC data is positive in the sign configuration or unsigned configuration, 13 to 31 bits will be 0.
*
* \param base The pointer to the ADC instance address.
*
* \param ch_num Channel number for which AUX ADC data to be read. \ref cy_en_aux_channel_t
*
* \return returns ADC data.
*
******************************************************************************/
__STATIC_INLINE uint32_t Cy_PPCA_ADC_Read_SignExtended_AUX_ADC_Data(ATOPSS_ADC_TYPE *base, cy_en_aux_channel_t ch_num)
{
    CY_ASSERT(CY_ADC_AUX_CHANNEL(ch_num));
    return PPCA_ATOP_ADC_AUX_DATA(base, ch_num);
}

/******************************************************************************
* Function Name: Cy_PPCA_ADC_Read_ALT_AUX_ADC_Data
***************************************************************************//**
*
* Returns 12 bit ALT AUX ADC Data for that particular channel
*
* \param base The pointer to the ADC instance address.
*
* \param ch_num Channel number for which ALT AUX ADC data to be read. \ref cy_en_alt_aux_channel_t
*
* \return returns ADC data.
*
******************************************************************************/
__STATIC_INLINE uint16_t Cy_PPCA_ADC_Read_ALT_AUX_ADC_Data(ATOPSS_ADC_TYPE *base, cy_en_alt_aux_channel_t ch_num)
{
    CY_ASSERT(CY_ADC_ALT_AUX_CHANNEL(ch_num));
    return (uint16_t)_FLD2VAL(PPCA_ATOPSS_ADC_GRP_SLICE_ADC_ADC_AUX_DATA_ADC_AUX_DATA, PPCA_ATOP_ADC_ALT_AUX_DATA(base, ch_num));
}

/******************************************************************************
* Function Name: Cy_PPCA_ADC_Read_SignExtended_ALT_AUX_ADC_Data
***************************************************************************//**
*
* Returns the Sign extended ALT AUX ADC Data for that particular channel.
* When ADC data is negative in the sign configuration, 13 to 31 bits will be 1.
* When ADC data is positive in the sign configuration or unsigned configuration, 13 to 31 bits will be 0.
*
* \param base The pointer to the ADC instance address.
*
* \param ch_num Channel number for which ALT AUX ADC data to be read. \ref cy_en_alt_aux_channel_t
*
* \return returns ADC data.
*
******************************************************************************/
__STATIC_INLINE uint32_t Cy_PPCA_ADC_Read_SignExtended_ALT_AUX_ADC_Data(ATOPSS_ADC_TYPE *base, cy_en_alt_aux_channel_t ch_num)
{
    CY_ASSERT(CY_ADC_ALT_AUX_CHANNEL(ch_num));
    return PPCA_ATOP_ADC_ALT_AUX_DATA(base, ch_num);
}

/******************************************************************************
* Function Name: Cy_PPCA_ADC_Set_Channel_Sampling_Mask
***************************************************************************//**
*
* Sets ADC Channel sampling Mask. Each bit represent one channel.
* When the bit is set, It Mask's that particular Channel Sampling.
*
* \param base The pointer to the ADC instance address.
*
* \param ch_mask ADC Channel sampling Mask. Each bit represent one channel.
*
******************************************************************************/
__STATIC_INLINE void Cy_PPCA_ADC_Set_Channel_Sampling_Mask(ATOPSS_ADC_TYPE *base, uint16_t ch_mask)
{
    PPCA_ATOP_ADC_SAMPLING_MASK(base) = ch_mask;
}

/******************************************************************************
* Function Name: Cy_PPCA_ADC_Get_Channel_Sampling_Mask
***************************************************************************//**
*
* Sets ADC Channel sampling Mask. Each bit represent one channel.
* When the bit is set, It Mask's that particular Channel Sampling.
*
* \param base The pointer to the ADC instance address.
*
* \return returns ADC Channel sampling Mask. Each bit represent one channel.
*
******************************************************************************/
__STATIC_INLINE uint16_t Cy_PPCA_ADC_Get_Channel_Sampling_Mask(ATOPSS_ADC_TYPE *base)
{
    return (uint16_t)(PPCA_ATOP_ADC_SAMPLING_MASK(base));
}

/** ------ Interrupts    ------- */

/******************************************************************************
* Function Name: Cy_PPCA_ADC_GetInterruptStatus
***************************************************************************//**
*
* Reports the status of the interrupts
*
* \param base The pointer to the ADC instance address.
*
* \return returns the Status of the interrupts
*
******************************************************************************/
__STATIC_INLINE uint32_t Cy_PPCA_ADC_GetInterruptStatus(ATOPSS_ADC_TYPE *base)
{
    return PPCA_ATOP_ADC_INTR(base);
}

/******************************************************************************
* Function Name: Cy_PPCA_ADC_ClearInterrupt
***************************************************************************//**
*
* Clears the triggered interrupts
*
* \param base The pointer to the ADC instance address.
*
******************************************************************************/
__STATIC_INLINE void Cy_PPCA_ADC_ClearInterrupt(ATOPSS_ADC_TYPE *base)
{
    PPCA_ATOP_ADC_INTR(base) = 1u;
}

/******************************************************************************
* Function Name: Cy_PPCA_ADC_SetInterrupt
***************************************************************************//**
*
* Software option to set the required interrupts. Interrupt handler will be called. 
*
* \param base The pointer to the ADC instance address.
*
******************************************************************************/
__STATIC_INLINE void Cy_PPCA_ADC_SetInterrupt(ATOPSS_ADC_TYPE *base)
{
    PPCA_ATOP_ADC_INTR_SET(base) = 1u;
}

/******************************************************************************
* Function Name: Cy_PPCA_ADC_SetInterruptMask
***************************************************************************//**
*
* Sets one or more ADC module interrupt factor bits (sets the INTR_MASK register).
*
* \param base The pointer to the ADC instance address.
*
******************************************************************************/
__STATIC_INLINE void Cy_PPCA_ADC_SetInterruptMask(ATOPSS_ADC_TYPE *base)
{
    PPCA_ATOP_ADC_INTR_MASK(base) = 1u;
}


/******************************************************************************
* Function Name: Cy_PPCA_ADC_GetInterruptMask
***************************************************************************//**
*
* Reports the interrupt mask set
*
* \param base The pointer to the ADC instance address.
*
* \return returns the interrupt mask set
*
******************************************************************************/
__STATIC_INLINE uint32_t Cy_PPCA_ADC_GetInterruptMask(ATOPSS_ADC_TYPE *base)
{
    return PPCA_ATOP_ADC_INTR_MASK(base);
}

#if defined (LOAD_PPCA_TRIMS) || defined(CY_DOXYGEN)

/*******************************************************************************
* Function Name: Cy_PPCA_ADC_TEMP_Calc
****************************************************************************//**
*
* Calculates the temperature based on ADC reading results of
* temperature sensor.
* See the device Architecture Technical Reference Manual for more detail.
*
* \param adcOut ADC reading when the selected temp sensor is
* biased with a additional 1.0uA current.
*
* \note should be called from Main core only.
*
* \return
* Temperature value.
*
*
*******************************************************************************/
__STATIC_INLINE float Cy_PPCA_ADC_TEMP_Calc(int16_t adcOut)
{
    CY_ASSERT_L1(CY_PPCA_ADC_TEMP_VALID(adcOut));

    int16_t coeff_A = (int16_t)(SFLASH_SAR_TEMP_COEF_A);
    int16_t coeff_B = (int16_t)(SFLASH_SAR_TEMP_COEF_B);

    int32_t tempCalc = (((int32_t)adcOut * (int32_t)coeff_A) + ((int32_t)coeff_B*CY_PPCA_TWO_TOPOWEROF_TEN));

    float t_initial = ((float)(tempCalc)/(float)CY_PPCA_TWO_TOPOWEROF_SIXTEEN);
    float t_adjust;

    if(t_initial >= CY_PPCA_XC)
    {
        t_adjust = ((CY_PPCA_YC/(CY_PPCA_SAR_100C - CY_PPCA_XC)) * (CY_PPCA_SAR_100C - t_initial));
    }
    else
    {
        t_adjust = ((CY_PPCA_YC/(CY_PPCA_SAR_40C + CY_PPCA_XC)) * (CY_PPCA_SAR_40C + t_initial));
    }

    return (t_initial + t_adjust);

}

#endif /* defined (LOAD_PPCA_TRIMS) */

/** \} group_ppca_adc_functions */



#if defined(__cplusplus)
}
#endif
#endif /* CY_IP_MXS40PPSS */

#endif /* CY_PPCA_ADC_H */

