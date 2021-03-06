/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    main.c
 *  @author  KitSprout
 *  @date    22-Apr-2018
 *  @brief   
 * 
 */

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\stm32f4_system.h"
#include "modules\serial.h"
#include "modules\kSerial.h"
#include "stm32f4xx_bsp.h"

/** @addtogroup STM32_Program
 *  @{
 */

/* Define ----------------------------------------------------------------------------------*/
#define UART_POLLING      (0U)
#define UART_INTERRUPT    (1U)
#define UART_KSERIAL      (2U)
#define UAER_MODE         UART_INTERRUPT

/* Macro -----------------------------------------------------------------------------------*/
/* Typedef ---------------------------------------------------------------------------------*/
/* Variables -------------------------------------------------------------------------------*/

#if UAER_MODE == UART_KSERIAL
static uint32_t sec = 0;
static uint32_t msc = 0;
#endif

/* Prototypes ------------------------------------------------------------------------------*/

#if UAER_MODE == UART_INTERRUPT
void uart_serial_recv_event( void );
#elif UAER_MODE == UART_KSERIAL
void timer_tick_event( void );
#endif

/* Functions -------------------------------------------------------------------------------*/

int main( void )
{
  bsp_gpio_init();

#if UAER_MODE == UART_POLLING

  uint32_t i = 0;
  bsp_uart_serial_init(NULL);
  while (1) {
    uint32_t status = Serial_RecvData(hSerial.pRxBuf, 1, 500);
    if (status == KS_TIMEOUT) {
      LED_R_Toggle();
      printf("Timeout ... %d\r\n", i++);
    }
    else if (hSerial.pRxBuf[0] == 0x0D) { // if press enter
      LED_G_Toggle();
      printf("\r\n");
    }
    else {
      LED_B_Toggle();
      Serial_SendData(hSerial.pRxBuf, 1, 2000);
    }
  }


#elif UAER_MODE == UART_INTERRUPT

  bsp_uart_serial_init(uart_serial_recv_event);
#if KS_FW_UART_HAL_LIBRARY
  Serial_RecvDataIT(hSerial.pRxBuf, 1);
#endif
  while (1) {
    LED_B_Toggle();
    delay_ms(100);
  }


#elif UAER_MODE == UART_KSERIAL
#define TIMER_TICK_FREQ   1000

  bsp_timer_init(timer_tick_event, TIMER_TICK_FREQ);
  bsp_timer_enable(ENABLE);
  bsp_uart_serial_init(NULL);

  while (1) {
    LED_G_Toggle();

    int16_t buff[2];
    buff[0] = sec;
    buff[1] = msc * (1000.0f / TIMER_TICK_FREQ);
    kSerial_SendPacket(NULL, buff, 2, KS_I16);
  }


#else
  #error UAER_MODE ERROR!!!

#endif

}

#if UAER_MODE == UART_INTERRUPT
void uart_serial_recv_event( void )
{
#if KS_FW_UART_HAL_LIBRARY
  Serial_RecvDataIT(hSerial.pRxBuf, 1);
#else
  Serial_RecvData(hSerial.pRxBuf, 1, 500);
#endif

  LED_G_Toggle();
  if (*hSerial.pRxBuf == 0x0D) {
    printf("\r\n");
  }
  else {
    Serial_SendData(hSerial.pRxBuf, 1, 1000);
  }
}

#elif UAER_MODE == UART_KSERIAL
void timer_tick_event( void )
{
  if (++msc == TIMER_TICK_FREQ) {
    msc = 0;
    sec++;
  }
}

#endif

/*************************************** END OF FILE ****************************************/
