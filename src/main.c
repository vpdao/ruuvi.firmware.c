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
#include "app_led.h"
#include "main.h"
#include "ruuvi_interface_log.h"
#include "ruuvi_interface_yield.h"
#include "ruuvi_interface_gpio_interrupt.h"
#include "ruuvi_task_led.h"
#include "ruuvi_task_button.h"

void on_button(const ri_gpio_evt_t event);

static const ri_gpio_id_t button_pins[] = RB_BUTTONS_LIST;

static const ri_gpio_state_t button_active[] = RB_BUTTONS_ACTIVE_STATE;

static const rt_button_fp_t app_button_handlers[RB_BUTTONS_NUMBER] = 
{
#if RB_BUTTONS_NUMBER > 0
  &on_button,
#endif
};

static rt_button_init_t m_init_data = 
{
  .p_button_pins = button_pins,
  .p_button_active = button_active,
  .p_button_handlers = app_button_handlers,
  .num_buttons = RB_BUTTONS_NUMBER
};

/**
 * @brief setup MCU peripherals and board peripherals.
 *
 */
void setup (void)
{
    rd_status_t err_code = RD_SUCCESS;

    /** Logging to terminal */
    err_code |= ri_log_init(APP_LOG_LEVEL);
    err_code |= ri_yield_init();
    err_code |= rt_gpio_init();
    RD_ERROR_CHECK(err_code, RD_SUCCESS);
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

  /* Button, and SPI MISO lines pulled up */
  err_code |= ri_gpio_configure(RB_SPI_MISO_PIN, RI_GPIO_MODE_INPUT_PULLUP);

  RD_ERROR_CHECK(err_code, RD_SUCCESS);
}

void on_button(const ri_gpio_evt_t event)
{
  ri_log(APP_LOG_LEVEL, "button\r\n");
}

void config_buttons(void)
{
  rd_status_t err_code = RD_SUCCESS;

  err_code |= rt_button_init(&m_init_data);

  RD_ERROR_CHECK(err_code, RD_SUCCESS);

}

int main (void)
{
    rd_status_t err_code = RD_SUCCESS;

    setup();

    config_gpios();
    
    config_buttons();

    do
    {
      ri_yield();
    } while (LOOP_FOREVER);

    // Intentionally non-reachable code unless unit testing.
    return -1;
}

/** @} */
