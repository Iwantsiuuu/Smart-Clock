# Smart Clock PSoC CYBLE-416045

Samrt clock development menggunakan CYBLE-416045 adalah sebuah project untuk mengimplementasikan smart clock menggunakan CYBLE-416045 dengan memanfaatkan fiture-fiture yang terdapat pada CYBLE-416045. Dalam project ini, terdapat dua module yang di gunakan yaitu CYBLE-416045-EVAL dan CY8CKIT-028-SENSE serta terdapat button tambahan yang di gunakan dalam project ini. Pengebangan smart clock ini berupa penambahan pendeteksian kondisi lingkungan yang terdapat di sekitar device, kualitas udara, voice command, dan monitoring menggunakan bluetooth.

## Requirements

- [ModusToolbox&trade;](https://www.infineon.com/modustoolbox)
- Board support package (BSP): PSoC CYBLE-416045-EVAL
- Programming language       : C
- Shield HMI 		     : CY8CKIT-028-SENS
- Others                     : 4 Button, project board, dan kabel jumper

## Supported toolchains (make variable 'TOOLCHAIN')

- GNU Arm&reg; Embedded Compiler v11.3.1 (`GCC_ARM`) - Default value of `TOOLCHAIN`
- Arm&reg; Compiler v6.16 (`ARM`)
- IAR C/C++ Compiler v9.30.1 (`IAR`)

## Supported kits (make variable 'TARGET')

- [EZ-BLE Arduino Evaluation Board](https://www.infineon.com/cms/en/product/evaluation-boards/cyble-416045-eval/) (`CYBLE-416045-EVAL`)

## Hardware setup

This example uses the kit’s default configuration. See the respective kit guide to ensure that the kit is configured correctly.

**Note:** The AIROC&trade; CYW20829 Bluetooth&reg; kit (CYW920829M2EVK-02) ships with KitProg3 version 2.21 installed. The ModusToolbox&trade; software requires KitProg3 with latest version 2.40. Before using this code example, make sure that the board is upgraded to KitProg3. The tool and instructions are available in the [Firmware Loader](https://github.com/Infineon/Firmware-loader) GitHub repository. If you do not upgrade, you will see an error such as "unable to find CMSIS-DAP device" or "KitProg firmware is out of date".

## Related resources


Resources  | Links
-----------|----------------------------------
Application notes  | [AN228571](https://www.infineon.com/AN228571) – Getting started with PSoC&trade; 6 MCU on ModusToolbox&trade; software <br>  [AN238254](https://www.infineon.com/dgdl/Infineon-AN238254_Getting_started_with_AIROC_CYW20829_Bluetooth_LE_on_ModusToolbox-ApplicationNotes-v01_00-EN.pdf?fileId=8ac78c8c8929aa4d018a3fe0cbc05aba) – Getting started with AIROC&trade; CYW20829 Bluetooth&reg; LE on ModusToolbox&trade; <br>  [AN215656](https://www.infineon.com/AN215656) – PSoC&trade; 6 MCU: Dual-CPU system design <br> [AN234334](https://www.infineon.com/AN234334) – Getting started with XMC&trade; 7000 MCU on ModusToolbox&trade; software
Code examples  | [Using ModusToolbox&trade;](https://github.com/Infineon/Code-Examples-for-ModusToolbox-Software) on GitHub <br> [Using PSoC&trade; Creator](https://www.infineon.com/cms/en/design-support/software/code-examples/psoc-3-4-5-code-examples-for-psoc-creator/)
Device documentation | [PSoC&trade; 6 MCU datasheets](https://www.infineon.com/cms/en/search.html#!view=downloads&term=psoc6&doc_group=Data%20Sheet) <br> [PSoC&trade; 6 technical reference manuals](https://www.infineon.com/cms/en/search.html#!view=downloads&term=psoc6&doc_group=Additional%20Technical%20Information) <br> [AIROC&trade; CYW20829 Bluetooth&reg; LE SoC](https://www.infineon.com/dgdl/Infineon-CYW20829_AIROC_TM_Bluetooth_R_LE_5_4_MCU-DataSheet-v07_00-EN.pdf?fileId=8ac78c8c86919021018709cc79af3afd&da=t)
Development kits | Select your kits from the [Evaluation board finder](https://www.infineon.com/cms/en/design-support/finder-selection-tools/product-finder/evaluation-board) page
Libraries on GitHub  | [mtb-pdl-cat1](https://github.com/Infineon/mtb-pdl-cat1) – PSoC&trade; 6 Peripheral Driver Library (PDL)  <br> [mtb-hal-cat1](https://github.com/Infineon/mtb-hal-cat1) – Hardware Abstraction Layer (HAL) library <br> [retarget-io](https://github.com/Infineon/retarget-io) – Utility library to retarget STDIO messages to a UART port
Middleware on GitHub  | [capsense](https://github.com/Infineon/capsense) – CAPSENSE&trade; library and documents <br> [psoc6-middleware](https://github.com/Infineon/modustoolbox-software#psoc-6-middleware-libraries) – Links to all PSoC&trade; 6 MCU middleware
Tools  | [Eclipse IDE for ModusToolbox&trade;](https://www.infineon.com/modustoolbox) – ModusToolbox&trade; software is a collection of easy-to-use software and tools enabling rapid development with Infineon MCUs, covering applications from embedded sense and control to wireless and cloud-connected systems using AIROC&trade; Wi-Fi and Bluetooth&reg; connectivity devices.

<br>

## Other resources

Infineon provides a wealth of data at www.infineon.com to help you select the right device, and quickly and effectively integrate it into your design.

For PSoC&trade; 6 MCU devices, see [How to design with PSoC&trade; 6 MCU - KBA223067](https://community.infineon.com/docs/DOC-14644) in the Infineon Developer community.


## Document history

Document title: *CE228742* – *Empty application template*
