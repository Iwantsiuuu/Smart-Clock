/******************************************************************************
 * Include header files
 ******************************************************************************/
#include "cyhal.h"
#include "cycfg.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include "string.h"

/*******************************************************************************
* Macros
*******************************************************************************/

#define UART_TIMEOUT_MS (10u)      /* in milliseconds */


/*******************************************************************************
* Global Variables
*******************************************************************************/

/*******************************************************************************
* Function Prototypes
*******************************************************************************/


/*******************************************************************************
* Function Name: handle_error
********************************************************************************
* Summary:
* User defined error handling function
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void handle_error(void)
{
    /* Disable all interrupts. */
    __disable_irq();

    CY_ASSERT(0);
}

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
*   This function:
*  - Initializes the device and board peripherals
*  - Initializes RTC
*  - The loop checks for the user command and process the commands
*
* Parameters :
*  void
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    cy_rslt_t rslt;
    uint8_t cmd;

    /* Initialize the device and board peripherals */
    rslt = cybsp_init();
    if (CY_RSLT_SUCCESS != rslt)
    {
        handle_error();
    }

    /* Initialize retargeting standard IO to the debug UART port */
    rslt = cy_retarget_io_init_fc(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX,
            CYBSP_DEBUG_UART_CTS,CYBSP_DEBUG_UART_RTS,CY_RETARGET_IO_BAUDRATE);

    if (CY_RSLT_SUCCESS != rslt)
    {
        handle_error();
    }

    /* Enable global interrupts */
    __enable_irq();

    /* \x1b[2J\x1b[;H - ANSI ESC sequence for clear screen */
    printf("\x1b[2J\x1b[;H");
    printf("****************** HAL: RTC Basics ******************\r\n\n");

    for (;;)
    {

        rslt = cyhal_uart_getc(&cy_retarget_io_uart_obj, &cmd, UART_TIMEOUT_MS);
        printf("%c\r\n",cmd);
        cyhal_system_delay_ms(1000);
    }
}

/* [] END OF FILE */
