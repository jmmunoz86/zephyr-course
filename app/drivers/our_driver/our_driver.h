#ifndef OUR_DRIVER_H
#define OUR_DRIVER_H /* OUR_DRIVER_H */

#include <zephyr/device.h>

#ifdef __cplusplus
extern "C" {
#endif

int our_driver_set_timer_increment(const struct device *dev, uint32_t *timer_value);

#ifdef __cplusplus
}
#endif

#endif /* OUR_DRIVER_H */