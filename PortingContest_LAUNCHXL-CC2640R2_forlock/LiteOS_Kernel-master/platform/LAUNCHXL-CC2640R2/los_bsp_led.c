#include "los_bsp_led.h"

#ifdef LAUNCHXL_CC2640R2
#include <stdint.h>
#endif

void BSP_LED_Init(uint8_t led)
{	
#ifdef LAUNCHXL_CC2640R2
   
    *((uint32_t*)(0x40082000 + 0x48))  |=  0x01;        // Enable gpio clock
    switch(led)
    {
        case LED1: 
            *((uint32_t*)(0x40022000 + 0xd0)) |= 0x40;   // Enable DIO6 output    
            *((uint32_t*)(0x40022000 + 0x90)) |= 0x40;   // Set DIO6   
            break; 
        case LED2: 
            *((uint32_t*)(0x40022000 + 0xd0)) |= 0x80;   // Enable DIO7 output   
            *((uint32_t*)(0x40022000 + 0x90)) |= 0x80;   // Set DIO7        
            break;
        default:
            break;
    }  
#endif
}


void BSP_LED_On(uint8_t led)
{
    switch(led)
    {
        case LED1:
            *((uint32_t*)(0x40022000 + 0xa0)) |= 0x40;   // Set DIO6   
            break; 
        case LED2:
            *((uint32_t*)(0x40022000 + 0xa0)) |= 0x80;   // Set DIO7
            break;
        default:
            break;
    }
}


void BSP_LED_Off(uint8_t led)
{
    switch(led)
    {
        case LED1:
            *((uint32_t*)(0x40022000 + 0x90)) |= 0x40;   // Set DIO6   
            break; 
        case LED2:
            *((uint32_t*)(0x40022000 + 0x90)) |= 0x80;   // Set DIO7
            break;
        default:
            break;
    }
}

void LOS_EvbLedInit(void)
{
    BSP_LED_Init(LED1);
    BSP_LED_Init(LED2);
	return ;
}

/*************************************************************************************************
 *  function£ºcontrol led on off                                                                 *
 *  param (1) index Led's index                                                                  *
 *        (2) cmd   Led on or off                                                                *
 *  return : None                                                                                *
 *  discription:                                                                                 *
**************************************************************************************************/
void LOS_EvbLedControl(int index, int cmd)
{
    switch (index)
    {
        case LOS_LED1:
        {
            if (cmd == LED_ON)
            {
                BSP_LED_On(LED1); 
            }
            else
            {
                BSP_LED_Off(LED1);
            }
            break;
        }
        case LOS_LED2:
        {
            if (cmd == LED_ON)
            {
                BSP_LED_On(LED2);
            }
            else
            {
                BSP_LED_Off(LED2);
            }
            break;
        }
        default:
        {
            break;
        }
    }
    
	return ;
}


