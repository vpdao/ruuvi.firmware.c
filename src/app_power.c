// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "app_power.h"
#include "ruuvi_boards.h"
#include "ruuvi_driver_error.h"
#include "ruuvi_interface_power.h"

rd_status_t app_dc_dc_init (void)
{
    ri_power_regulators_t reg = {0};
#if RB_DCDC_INTERNAL_INSTALLED
    reg.DCDC_INTERNAL = 1;
#endif
#if RB_DCDC_HV_INSTALLED
    reg.DCDC_HV = 1;
#endif
    return ri_power_regulators_enable (reg);
}
