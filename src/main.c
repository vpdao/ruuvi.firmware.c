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

#include "main.h"
#include "ruuvi_interface_gpio.h"
#include "ruuvi_interface_yield.h"
#include "ruuvi_boards.h"

/**
 * @brief setup MCU peripherals and board peripherals.
 *
 */
void setup (void)
{
    rd_status_t err_code = RD_SUCCESS;
    err_code |= ri_yield_init();

    /* Init GPIO */
    err_code |= ri_gpio_init();
    RD_ERROR_CHECK(err_code, RD_SUCCESS);
}

int main (void)
{
    setup();
    
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

    /* Button, and SPI MISO lines pulled up */
    ri_gpio_configure(RB_BUTTON_1, RI_GPIO_MODE_INPUT_PULLUP);
    ri_gpio_configure(RB_SPI_MISO_PIN, RI_GPIO_MODE_INPUT_PULLUP);

    while (1)
    {
      ri_yield();
    }
}

/** @} */
