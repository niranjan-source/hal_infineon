# ModusToolbox PSC3M8 BSP Template Library

## Overview

mtb-template-psc3m8 provides BSP template files for the BSP Assistant tool. mtb-template-psc3m8 contains files for PSC3M8 devices.

## BSP Configuration

The BSP has a few hooks that allow its behavior to be configured. Some of these items are enabled by default while others must be explicitly enabled. Items enabled by default are specified in the {{ name }}.mk file. The items that are enabled can be changed by creating a custom BSP or by editing the application makefile.

Defines:
* COMPONENT_MTB_HAL - This define, enabled by default, specifies that the HAL is intended to be used by the application. This will cause the BSP to include the applicable header file and to initialize the system level drivers.


## More information
* [Development Board Documentation](https://www.cypress.com/documentation/development-kitsboards)
* [Cypress Semiconductor, an Infineon Technologies Company](https://www.cypress.com)
* [Infineon GitHub](https://github.com/infineon)
* [ModusToolbox™](https://www.cypress.com/products/modustoolbox-software-environment)

---
© Cypress Semiconductor Corporation (an Infineon company) or an affiliate of Cypress Semiconductor Corporation, 2025.
