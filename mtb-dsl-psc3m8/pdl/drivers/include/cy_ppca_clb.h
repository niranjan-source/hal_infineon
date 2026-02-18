/***************************************************************************//**
* \file cy_ppca_clb.h
* \version 1.00
*
* Provides the API declarations of the PPCA CLB driver.
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
* \addtogroup group_ppca_clb
* \{
*
* \defgroup group_ppca_clb_dico DICO
* \defgroup group_ppca_clb_maco MACO
* 
* \} */

/**
* \addtogroup group_ppca_clb
* \{
*
* 
* \section group_ppca_clb_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
* \defgroup group_ppca_clb_functions Functions
* \defgroup group_ppca_clb_enums Enumerations
* \defgroup group_ppca_clb_macros Macros
*
*/
#if !defined(CY_PPCA_CLB_H)
#define CY_PPCA_CLB_H

#include "cy_device.h"

#if defined (CY_IP_MXS40PPSS) || defined (CY_DOXYGEN)

#include "cy_syslib.h"
#include "cy_ppca_clb_dico.h"
#include "cy_ppca_clb_maco.h"

#if defined(__cplusplus)
extern "C" {
#endif

/***************************************
*       Macros
***************************************/

/**
* \addtogroup group_ppca_clb_macros
* \{
*/
/** The driver major version */
#define CY_PPCA_CLB_DRV_VERSION_MAJOR       1U

/** The driver minor version */
#define CY_PPCA_CLB_DRV_VERSION_MINOR       0U

/** The CORDIC driver ID */
#define CY_PPCA_CLB_ID                      CY_PDL_DRV_ID(0x96U)

/** \} group_ppca_clb_macros */


/***************************************
*       Enumerations
***************************************/
/**
* \addtogroup group_ppca_clb_enums
* \{
*/

/** CLB Output */
typedef enum
{
    CY_CLB_DICO_SEL = 0U,   /**< The line, line_compl and monitor of DICO are selected as CLB outputs */
    CY_CLB_MACO_SEL = 1U,   /**< The line, line_compl and monitor of MACO are selected as CLB outputs */
}cy_en_ppca_clb_output_sel_t;


/** \} group_ppca_clb_enums */


/***************************************
*        Function Prototypes
***************************************/

/**
* \addtogroup group_ppca_clb_functions
* \{
*/


/*******************************************************************************
* Function Name: Cy_PPCA_CLB_Select_Output
****************************************************************************//**
*
* Select CLB Output signals.
*
* \param *base
* The PPCA CLB registers structure pointer.
*
* \param outSel
* CLB Output between DICO and MACO.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_CLB_Select_Output(PPCA_CLB_Type *base, cy_en_ppca_clb_output_sel_t outSel)
{
    PPCA_CLB_CTRL(base) = _VAL2FLD(PPCA_CLB_CTRL_MACO_SEL, outSel);
}


/*******************************************************************************
* Function Name: Cy_PPCA_CLB_Enable
****************************************************************************//**
*
* Enables CLB block.
*
* \param *base
* The PPCA CLB registers structure pointer.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_CLB_Enable(PPCA_CLB_Type *base)
{
    PPCA_CLB_CTRL(base) |= PPCA_CLB_CTRL_EN_Msk;
}


/*******************************************************************************
* Function Name: Cy_PPCA_CLB_Disable
****************************************************************************//**
*
* Disables CLB block.
*
* \param *base
* The PPCA CLB registers structure pointer.
*
*******************************************************************************/
__STATIC_INLINE void Cy_PPCA_CLB_Disable(PPCA_CLB_Type *base)
{
    PPCA_CLB_CTRL(base) &= (uint32_t)~PPCA_CLB_CTRL_EN_Msk;
}


/** \} group_ppca_clb_functions */

#if defined(__cplusplus)
}
#endif

#endif /* #if defined(CY_IP_MXS40PPSS) */

#endif /* (CY_PPCA_CLB_H) */

/** \} group_ppca_clb */

/* [] END OF FILE */
