/* Copyright (c) 2014 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

/** @file
 * @defgroup nrf_dev_timer_example_main main.c
 * @{
 * @ingroup nrf_dev_timer_example
 * @brief Timer Example Application main file.
 *
 * This file contains the source code for a sample application using Timer0.
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "app_uart.h"
#include "app_error.h"
#include "nrf.h"
#include "nrf_drv_timer.h"
#include "bsp.h"
#include "app_error.h"
#include "app_uart.h"
#include "nrf_delay.h"
#include "iodefine.h"

const nrf_drv_timer_t TIMER_LED = NRF_DRV_TIMER_INSTANCE(0);
const uint8_t leds_list[LEDS_NUMBER] = LEDS_LIST;
extern void timer_event(void);

void pinMode(uint32_t pin, uint32_t state)
{
  if(state == OUTPUT){
    nrf_gpio_cfg_output(pin);
  } else if (state == INPUT){
    nrf_gpio_cfg_input(pin, NRF_GPIO_PIN_NOPULL);
  }
  // TODO: implement for Pulled up/down
}

void digitalWrite(uint32_t pin, uint32_t value)
{
  nrf_gpio_pin_write(pin, value);
}

uint32_t digitalRead(uint32_t pin)
{
  return nrf_gpio_read(pin);
}

/**
 * @brief Handler for timer events.
 */
void timer_led_event_handler(nrf_timer_event_t event_type, void* p_context)
{
    static uint32_t i;
    uint32_t led_to_invert = (1 << leds_list[(i++) % LEDS_NUMBER]);

    switch (event_type)
    {
        case NRF_TIMER_EVENT_COMPARE0:
            LEDS_INVERT(led_to_invert);
	    timer_event();
            break;

        default:
            //Do nothing.
            break;
    }
}

#define UART_TX_BUF_SIZE 256                         /**< UART TX buffer size. */
#define UART_RX_BUF_SIZE 256                         /**< UART RX buffer size. */

void uart_error_handle(app_uart_evt_t * p_event)
{
    if (p_event->evt_type == APP_UART_COMMUNICATION_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_communication);
    }
    else if (p_event->evt_type == APP_UART_FIFO_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_code);
    }
}


int32_t init_uart(void)
{
  uint32_t err_code;
  const app_uart_comm_params_t comm_params = {
    RX_PIN_NUMBER,
    TX_PIN_NUMBER,
    RTS_PIN_NUMBER,
    CTS_PIN_NUMBER,
    APP_UART_FLOW_CONTROL_DISABLED,
    false,
    UART_BAUDRATE_BAUDRATE_Baud115200
  };
  
  APP_UART_FIFO_INIT(&comm_params,
		     UART_RX_BUF_SIZE,
		     UART_TX_BUF_SIZE,
		     uart_error_handle,
		     APP_IRQ_PRIORITY_LOW,
		     err_code);

  APP_ERROR_CHECK(err_code);

  return 0;
}

void setup(void);
void loop(void);

/**
 * @brief Function for main application entry.
 */
int main(void)
{
    uint32_t time_ms = 3; //Time(in miliseconds) between consecutive compare events.
    uint32_t time_ticks;
    uint32_t err_code = NRF_SUCCESS;

    //Configure all leds on board.
    LEDS_CONFIGURE(LEDS_MASK);
    LEDS_OFF(LEDS_MASK);

    init_uart();

    //Configure TIMER_LED for generating simple light effect - leds on board will invert his state one after the other.
    nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;
    err_code = nrf_drv_timer_init(&TIMER_LED, &timer_cfg, timer_led_event_handler);
    APP_ERROR_CHECK(err_code);

    time_ticks = nrf_drv_timer_ms_to_ticks(&TIMER_LED, time_ms);

    nrf_drv_timer_extended_compare(
         &TIMER_LED, NRF_TIMER_CC_CHANNEL0, time_ticks, NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, true);

    nrf_drv_timer_enable(&TIMER_LED);

    setup();
    while(1){
      loop();
    }
    
    while (1)
    {
        __WFI();
    }
}

/** @} */

void delay(uint32_t ms)
{
  nrf_delay_ms(ms);
}

void delayMicroseconds(uint32_t us)
{
  nrf_delay_us(us);
}

