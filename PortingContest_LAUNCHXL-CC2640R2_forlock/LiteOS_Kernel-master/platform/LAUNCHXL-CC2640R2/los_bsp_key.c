#include "los_bsp_key.h"

#ifdef LAUNCHXL_CC2640R2
#include <stdint.h>
#endif

void BSP_KEY_Init(void)
{    
#ifdef LAUNCHXL_CC2640R2
    *((uint32_t*)(0x40082000 + 0x48))  |=  0x01;        // Enable gpio clock
    *((uint32_t*)(0x40081000 + 0x34))   = 0x20004000;   // Enable DIO13 input     
#endif
    return;
}

uint16_t BSP_KEY_Get(void)
{
    uint16_t KeyVal=LOS_GPIO_ERR;

#ifdef LAUNCHXL_CC2640R2	
    if(!(*((uint32_t *)(0x40081000 + 0xc0)) & 0x00002000))    //DIO13
    {
        KeyVal = 0;
    }
#endif
    return KeyVal;
}

void LOS_EvbKeyInit(void)
{
    BSP_KEY_Init();
}

/*****************************************************************************
 Function    : LOS_EvbGetKeyVal
 Description : Get GIOP Key value
 Input       : int KeyNum
 Output      : None
 Return      : KeyVal
 *****************************************************************************/
unsigned int LOS_EvbGetKeyVal(int KeyNum)
{
    unsigned int KeyVal = LOS_GPIO_ERR; 

    if(KeyNum == USER_KEY)
    {
        KeyVal = BSP_KEY_Get();
    }
	
	return KeyVal;
}

