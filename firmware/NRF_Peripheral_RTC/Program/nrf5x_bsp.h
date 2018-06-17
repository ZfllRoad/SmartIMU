/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    nrf5x_bsp.h
 *  @author  KitSprout
 *  @date    16-Jun-2018
 *  @brief   
 * 
 */

/* Define to prevent recursive inclusion ---------------------------------------------------*/
#ifndef __NRF5X_BSP_H
#define __NRF5X_BSP_H

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\nrf5x_system.h"

/* Define ----------------------------------------------------------------------------------*/
/* Macro -----------------------------------------------------------------------------------*/
/* Typedef ---------------------------------------------------------------------------------*/
/* Extern ----------------------------------------------------------------------------------*/
/* Functions -------------------------------------------------------------------------------*/
void      bsp_gpio_init( void );
void      bsp_rng_init( pFunc event );
void      bsp_timer_init( pFunc event, uint32_t freq );
void      bsp_timer_enable( uint32_t state );
void      bsp_rtc_init( pFunc tick_event, pFunc compare_event, uint32_t freq );
void      bsp_rtc_enable( uint32_t state );
void      bsp_serial_init( pFunc event );

#ifdef __cplusplus
}
#endif

#endif

/*************************************** END OF FILE ****************************************/