/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"               // SYS function prototypes

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
//LED_turn_on(LED_EQUIPMENT);

uint8_t bufferTx[]= {0xAA,0xFF,0x11,0x00,0x23};
static bool volatile led_status =0;

void TIMER_handler(TC_TIMER_STATUS status, uintptr_t context)
{
    led_status = true;
}

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    TC2_TimerStart();
    
    SERCOM3_USART_Write(&bufferTx,sizeof(bufferTx));
    
    TC2_TimerCallbackRegister( TIMER_handler, (uintptr_t)NULL );

    while ( true )
    {
        if(led_status)
        {
            led_status = false;
           // LED_turn_on(LED_EQUIPMENT);
            LED_Toggle();
        }
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

