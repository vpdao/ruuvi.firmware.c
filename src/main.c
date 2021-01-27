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

/**
 * @brief setup MCU peripherals and board peripherals.
 *
 */
void setup (void)
{
    rd_status_t err_code = RD_SUCCESS;
    err_code |= ri_log_init(APP_LOG_LEVEL);
    ri_log(APP_LOG_LEVEL, "Log module started\r\n");

    /* Initialize yield module */
    ri_log(APP_LOG_LEVEL, "Initialize yield module\r\n");
    err_code |= ri_yield_init();

    /* Initialize gpio module */
    ri_log(APP_LOG_LEVEL, "Initialize gpio module\r\n");
    err_code |= ri_gpio_init();

    RD_ERROR_CHECK (err_code, RD_SUCCESS);
}

void config_gpios(void)
{
  /* Turn off sensors */
  ri_gpio_configure(RB_SPI_SS_ACCELEROMETER_PIN, RI_GPIO_MODE_OUTPUT_STANDARD);
  ri_gpio_write(RB_SPI_SS_ACCELEROMETER_PIN, RI_GPIO_HIGH);
  ri_gpio_configure(RB_SPI_SS_ENVIRONMENTAL_PIN, RI_GPIO_MODE_OUTPUT_STANDARD);
  ri_gpio_write(RB_SPI_SS_ENVIRONMENTAL_PIN, RI_GPIO_HIGH);

  /* Put SPI lines into HIGH state to avoid power leaks */
  ri_gpio_configure(RB_SPI_SCLK_PIN, RI_GPIO_MODE_OUTPUT_STANDARD);
  ri_gpio_write(RB_SPI_SCLK_PIN, RI_GPIO_HIGH);
  ri_gpio_configure(RB_SPI_MOSI_PIN, RI_GPIO_MODE_OUTPUT_STANDARD);
  ri_gpio_write(RB_SPI_MOSI_PIN, RI_GPIO_HIGH);

  /* LEDs high / inactive */
  ri_gpio_configure(RB_LED_RED, RI_GPIO_MODE_OUTPUT_HIGHDRIVE);
  ri_gpio_write(RB_LED_RED, RI_GPIO_HIGH);
  ri_gpio_configure(RB_LED_GREEN, RI_GPIO_MODE_OUTPUT_HIGHDRIVE);
  ri_gpio_write(RB_LED_GREEN, RI_GPIO_HIGH);

  /* BUtton, and SPI MISO lines pulled up */
  ri_gpio_configure(RB_BUTTON_1, RI_GPIO_MODE_INPUT_PULLUP);
  ri_gpio_configure(RB_SPI_MISO_PIN, RI_GPIO_MODE_INPUT_PULLUP);
}

int main (void)
{

    setup();

    do
    {
      ri_log(APP_LOG_LEVEL, "Going to sleep\r\n");
      ri_yield();
      ri_log(APP_LOG_LEVEL, "Waking up\r\n");
    } while (LOOP_FOREVER);

    // Intentionally non-reachable code unless unit testing.
    return -1;
}

/** @} */
