/***************************************************************************//**
* Common header file to be included by the drivers.
*
********************************************************************************
* \copyright
* (c) (2016-2025), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
*
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

#ifndef _CY_DEVICE_HEADERS_H_
#define _CY_DEVICE_HEADERS_H_

#if defined (COMPONENT_SECURE_DEVICE)

#if defined (PSC3P8GFS3PAHQ1)
    #include "psc3p8gfs3pahq1_s.h"
#elif defined (PSC3M8GFS3PAHQ1)
    #include "psc3m8gfs3pahq1_s.h"
#elif defined (PSC3P8GFS3PAFQ1)
    #include "psc3p8gfs3pafq1_s.h"
#elif defined (PSC3M8GFS3PAFQ1)
    #include "psc3m8gfs3pafq1_s.h"
#elif defined (PSC3P7GES3PAFQ1)
    #include "psc3p7ges3pafq1_s.h"
#elif defined (PSC3M7GES3PAFQ1)
    #include "psc3m7ges3pafq1_s.h"
#elif defined (PSC3P8GFS3PACQ1)
    #include "psc3p8gfs3pacq1_s.h"
#elif defined (PSC3M8GFS3PACQ1)
    #include "psc3m8gfs3pacq1_s.h"
#elif defined (PSC3P8GFS3PLHQ1)
    #include "psc3p8gfs3plhq1_s.h"
#elif defined (PSC3M8GFS3PLHQ1)
    #include "psc3m8gfs3plhq1_s.h"
#elif defined (PSC3P8FES3PLHQ1)
    #include "psc3p8fes3plhq1_s.h"
#elif defined (PSC3M8FES3PLHQ1)
    #include "psc3m8fes3plhq1_s.h"
#elif defined (PSC3P7FES3PLHQ1)
    #include "psc3p7fes3plhq1_s.h"
#elif defined (PSC3M7FES3PLHQ1)
    #include "psc3m7fes3plhq1_s.h"
#elif defined (PSC3P8GFS3PABQ1)
    #include "psc3p8gfs3pabq1_s.h"
#elif defined (PSC3M8GFS3PABQ1)
    #include "psc3m8gfs3pabq1_s.h"
#elif defined (PSC3P7FES3PABQ1)
    #include "psc3p7fes3pabq1_s.h"
#elif defined (PSC3P8GFS3PLGQ1)
    #include "psc3p8gfs3plgq1_s.h"
#elif defined (PSC3M8GFS3PLGQ1)
    #include "psc3m8gfs3plgq1_s.h"
#elif defined (PSC3P8FES3PLGQ1)
    #include "psc3p8fes3plgq1_s.h"
#elif defined (PSC3M8FES3PLGQ1)
    #include "psc3m8fes3plgq1_s.h"
#elif defined (PSC3P7FES3PLGQ1)
    #include "psc3p7fes3plgq1_s.h"
#elif defined (PSC3M7FES3PLGQ1)
    #include "psc3m7fes3plgq1_s.h"
#else
    #error Undefined part number. Consider updating PDL via ModusToolbox Library Manager to resolve the issue.
#endif

#elif defined (COMPONENT_PPCA_DEVICE)

#if defined (PSC3P8GFS3PAHQ1)
    #include "psc3p8gfs3pahq1_p.h"
#elif defined (PSC3M8GFS3PAHQ1)
    #include "psc3m8gfs3pahq1_p.h"
#elif defined (PSC3P8GFS3PAFQ1)
    #include "psc3p8gfs3pafq1_p.h"
#elif defined (PSC3M8GFS3PAFQ1)
    #include "psc3m8gfs3pafq1_p.h"
#elif defined (PSC3P7GES3PAFQ1)
    #include "psc3p7ges3pafq1_p.h"
#elif defined (PSC3M7GES3PAFQ1)
    #include "psc3m7ges3pafq1_p.h"
#elif defined (PSC3P8GFS3PACQ1)
    #include "psc3p8gfs3pacq1_p.h"
#elif defined (PSC3M8GFS3PACQ1)
    #include "psc3m8gfs3pacq1_p.h"
#elif defined (PSC3P8GFS3PLHQ1)
    #include "psc3p8gfs3plhq1_p.h"
#elif defined (PSC3M8GFS3PLHQ1)
    #include "psc3m8gfs3plhq1_p.h"
#elif defined (PSC3P8FES3PLHQ1)
    #include "psc3p8fes3plhq1_p.h"
#elif defined (PSC3M8FES3PLHQ1)
    #include "psc3m8fes3plhq1_p.h"
#elif defined (PSC3P7FES3PLHQ1)
    #include "psc3p7fes3plhq1_p.h"
#elif defined (PSC3M7FES3PLHQ1)
    #include "psc3m7fes3plhq1_p.h"
#elif defined (PSC3P8GFS3PABQ1)
    #include "psc3p8gfs3pabq1_p.h"
#elif defined (PSC3M8GFS3PABQ1)
    #include "psc3m8gfs3pabq1_p.h"
#elif defined (PSC3P7FES3PABQ1)
    #include "psc3p7fes3pabq1_p.h"
#elif defined (PSC3P8GFS3PLGQ1)
    #include "psc3p8gfs3plgq1_p.h"
#elif defined (PSC3M8GFS3PLGQ1)
    #include "psc3m8gfs3plgq1_p.h"
#elif defined (PSC3P8FES3PLGQ1)
    #include "psc3p8fes3plgq1_p.h"
#elif defined (PSC3M8FES3PLGQ1)
    #include "psc3m8fes3plgq1_p.h"
#elif defined (PSC3P7FES3PLGQ1)
    #include "psc3p7fes3plgq1_p.h"
#elif defined (PSC3M7FES3PLGQ1)
    #include "psc3m7fes3plgq1_p.h"
#else
    #error Undefined part number. Consider updating PDL via ModusToolbox Library Manager to resolve the issue.
#endif

#else
#if defined (PSC3P8GFS3PAHQ1)
    #include "psc3p8gfs3pahq1.h"
#elif defined (PSC3M8GFS3PAHQ1)
    #include "psc3m8gfs3pahq1.h"
#elif defined (PSC3P8GFS3PAFQ1)
    #include "psc3p8gfs3pafq1.h"
#elif defined (PSC3M8GFS3PAFQ1)
    #include "psc3m8gfs3pafq1.h"
#elif defined (PSC3P7GES3PAFQ1)
    #include "psc3p7ges3pafq1.h"
#elif defined (PSC3M7GES3PAFQ1)
    #include "psc3m7ges3pafq1.h"
#elif defined (PSC3P8GFS3PACQ1)
    #include "psc3p8gfs3pacq1.h"
#elif defined (PSC3M8GFS3PACQ1)
    #include "psc3m8gfs3pacq1.h"
#elif defined (PSC3P8GFS3PLHQ1)
    #include "psc3p8gfs3plhq1.h"
#elif defined (PSC3M8GFS3PLHQ1)
    #include "psc3m8gfs3plhq1.h"
#elif defined (PSC3P8FES3PLHQ1)
    #include "psc3p8fes3plhq1.h"
#elif defined (PSC3M8FES3PLHQ1)
    #include "psc3m8fes3plhq1.h"
#elif defined (PSC3P7FES3PLHQ1)
    #include "psc3p7fes3plhq1.h"
#elif defined (PSC3M7FES3PLHQ1)
    #include "psc3m7fes3plhq1.h"
#elif defined (PSC3P8GFS3PABQ1)
    #include "psc3p8gfs3pabq1.h"
#elif defined (PSC3M8GFS3PABQ1)
    #include "psc3m8gfs3pabq1.h"
#elif defined (PSC3P7FES3PABQ1)
    #include "psc3p7fes3pabq1.h"
#elif defined (PSC3P8GFS3PLGQ1)
    #include "psc3p8gfs3plgq1.h"
#elif defined (PSC3M8GFS3PLGQ1)
    #include "psc3m8gfs3plgq1.h"
#elif defined (PSC3P8FES3PLGQ1)
    #include "psc3p8fes3plgq1.h"
#elif defined (PSC3M8FES3PLGQ1)
    #include "psc3m8fes3plgq1.h"
#elif defined (PSC3P7FES3PLGQ1)
    #include "psc3p7fes3plgq1.h"
#elif defined (PSC3M7FES3PLGQ1)
    #include "psc3m7fes3plgq1.h"
#else
    #error Undefined part number. Consider updating PDL via ModusToolbox Library Manager to resolve the issue.
#endif

#endif

#endif /* _CY_DEVICE_HEADERS_H_ */


/* [] END OF FILE */
