// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
/**
 * @defgroup main Program main
 *
 */
/** @{ */
/**
 * @file main.c
 * @author Otso Jousimaa <otso@ojousima.net>
 * @date 2020-07-13
 * @copyright Ruuvi Innovations Ltd, license BSD-3-Clause.
 */
#include "app_config.h"
#include "main.h"
#include "ruuvi_interface_log.h"
#include "ruuvi_interface_yield.h"
#include "ruuvi_task_led.h"

/**
 * @brief setup MCU peripherals and board peripherals.
 *
 */
void setup (void)
{
    rd_status_t err_code = RD_SUCCESS;

    err_code |= ri_log_init (APP_LOG_LEVEL); // Logging to terminal.
    err_code |= ri_yield_init();
    err_code |= rt_gpio_init();
    err_code |= app_led_init();
    RD_ERROR_CHECK (err_code, RD_SUCCESS);
}

void config_gpios(void)
{
  rd_status_t err_code = RD_SUCCESS;
  
  /* Turn off sensors */
  err_code |= ri_gpio_configure(RB_SPI_SS_ACCELEROMETER_PIN, RI_GPIO_MODE_OUTPUT_STANDARD);
  err_code |= ri_gpio_write(RB_SPI_SS_ACCELEROMETER_PIN, RI_GPIO_HIGH);
  err_code |= ri_gpio_configure(RB_SPI_SS_ENVIRONMENTAL_PIN, RI_GPIO_MODE_OUTPUT_STANDARD);
  err_code |= ri_gpio_write(RB_SPI_SS_ENVIRONMENTAL_PIN, RI_GPIO_HIGH);

  /* Put SPI lines into HIGH state to avoid power leaks */
  err_code |= ri_gpio_configure(RB_SPI_SCLK_PIN, RI_GPIO_MODE_OUTPUT_STANDARD);
  err_code |= ri_gpio_write(RB_SPI_SCLK_PIN, RI_GPIO_HIGH);
  err_code |= ri_gpio_configure(RB_SPI_MOSI_PIN, RI_GPIO_MODE_OUTPUT_STANDARD);
  err_code |= ri_gpio_write(RB_SPI_MOSI_PIN, RI_GPIO_HIGH);


  /* BUtton, and SPI MISO lines pulled up */
  err_code |= ri_gpio_configure(RB_BUTTON_1, RI_GPIO_MODE_INPUT_PULLUP);
  err_code |= ri_gpio_configure(RB_SPI_MISO_PIN, RI_GPIO_MODE_INPUT_PULLUP);
}

int main (void)
{
    rd_status_t err_code = RD_SUCCESS;

    setup();

    do
    {
      /* Turn on Red led */
      app_led_activate(RB_LED_RED);

      /* Turn on Green led */
      app_led_activate(RB_LED_GREEN);

      /* Delay */
      ri_delay_ms(1000);

      app_led_deactivate(RB_LED_RED);

      app_led_deactivate(RB_LED_GREEN);

      /* Delay */
      ri_delay_ms(1000);
      
    } while (LOOP_FOREVER);

    // Intentionally non-reachable code unless unit testing.
    return -1;
}

/** @} */
