#include "los_bsp_uart.h"
#include <stdarg.h>
#include <stdio.h>

#ifdef LAUNCHXL_CC2640R2
#include <stdint.h>
#endif
    
void BSP_UART_Init (void)
{  
#ifdef LAUNCHXL_CC2640R2
    *((uint32_t*)(0x40082000 + 0x6c))  |=  0x01;          // Enable uart clock
    *((uint32_t*)(0x40001000 + 0x30))  &=  0xFFFFFFFE;    // Disable Uart                   	
    *((uint32_t*)(0x40081000 + 0x0c))  =  0x10;           // DIO3 as UART0_TX         
    *((uint32_t*)(0x40081000 + 0x08))  =  0x0f;           // DIO2 as UART0_RX          		
    *((uint32_t*)(0x40001000 + 0x24))  =  0x2B;           // Set 115200              		 
    *((uint32_t*)(0x40001000 + 0x28))  =  0x1A;           // Set 115200                		 		 
    *((uint32_t*)(0x40001000 + 0x2c))  =  0x0000070;      // 8-bit ,1-stop ,no parity ,fifo on		 		 
    *((uint32_t*)(0x40001000 + 0x30))  =  0x00000301;     // Enable Uart              
#endif  
}

uint8_t byte;
void UART0IntHandler(void)
{
#ifdef LAUNCHXL_CC2640R2
    if (!((*((uint8_t*)0x40001000 + 0x18)) & 0x10))
    {
        byte = *((uint8_t*)0x40001000);
    }
#endif  
}

int fputc(int ch,FILE *f)
{
#ifdef LAUNCHXL_CC2640R2
    while(!((*((uint8_t*)0x40001000 + 0x18)) & 0x20));
    *((uint32_t*)0x40001000)  &= (0xfff0 | ch);
#endif  
    return(ch);
}

void LOS_EvbUartInit(void)
{
    BSP_UART_Init();
	
	return ;
}


/*************************************************************************************************
 *  功能：向串口1发送一个字符                                                                    *
 *  参数：(1) 需要被发送的字符                                                                   *
 *  返回：                                                                                       *
 *  说明：                                                                                       *
 *************************************************************************************************/
void LOS_EvbUartWriteByte(char c)
{
#ifdef LAUNCHXL_CC2640R2
    while(!((*((uint8_t*)0x40001000 + 0x18)) & 0x20));
    *((uint32_t*)0x40001000)  &= (0xfff0 | c);
#endif  
	return ;
}

/*************************************************************************************************
 *  功能：向串口1发送一个字符串                                                                  *
 *  参数：(1) 需要被发送的字符串                                                                 *
 *  返回：                                                                                       *
 *  说明：                                                                                       *
 *************************************************************************************************/
void LOS_EvbUartWriteStr(const char* str)
{
    while (*str)
    {
#ifdef LAUNCHXL_CC2640R2
        while(!((*((uint8_t*)0x40001000 + 0x18)) & 0x20));
        *((uint32_t*)0x40001000)  &= (0xfff0 | *str);
        str++;
#endif  
    }
    return ;
}


/*************************************************************************************************
 *  功能：从串口1接收一个字符                                                                    *
 *  参数：(1) 存储接收到的字符                                                                   *
 *  返回：                                                                                       *
 *  说明：                                                                                       *
 *************************************************************************************************/
void LOS_EvbUartReadByte(char* c)
{
#ifdef LAUNCHXL_CC2640R2
    if(!((*((uint8_t*)0x40001000 + 0x18)) & 0x10))
    {
        *c = *((uint8_t*)0x40001000);
    }
#endif  
    return ;
}

static char _buffer[128];
void LOS_EvbUartPrintf(char* fmt, ...)
{
    int i;
    va_list ap;
    va_start(ap, fmt);
    vsprintf(_buffer, fmt, ap);
    va_end(ap);

    for (i = 0; _buffer[i] != '\0'; i++)
    {
        LOS_EvbUartWriteByte(_buffer[i]);
    }
	return ;
}
