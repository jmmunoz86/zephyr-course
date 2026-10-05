#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/device.h>

void board_late_init_hook(void) 
{
    printk("Board Initialized\n");

}