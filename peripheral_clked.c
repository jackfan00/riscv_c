#include "peripheral.h"

void peripheral_clked()
{
    device_reg_clked = device_reg;
    peripheral_read_clked = peripheral_read;

}