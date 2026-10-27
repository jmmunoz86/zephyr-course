#include <zephyr/logging/log.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>

#define DT_DRV_COMPAT our_driver

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);

struct our_driver_data {
    int led_state;
};

struct our_driver_config {
    struct gpio_dt_spec led_gpio;
};

static int our_driver_sample_fetch(const struct device *dev, enum sensor_channel chan)
{
    const struct our_driver_config *config = dev->config;
    struct our_driver_data *data = dev->data;
    int ret;

    LOG_INF("our_driver_sample_fetch called with channel %d", chan);
    
    ret = gpio_pin_set_dt(&config->led_gpio, 1);
    if (ret < 0) {
        LOG_ERR("Failed to switch LED on: %d", ret);
        return ret;
    }
    data->led_state = 1; // Update LED state to ON
    return 0;
}

static int our_driver_channel_get(const struct device *dev, enum sensor_channel chan, struct sensor_value *val)
{
    const struct our_driver_config *config = dev->config;
    struct our_driver_data *data = dev->data;
    int ret;

    LOG_INF("our_driver_channel_get called with channel %d", chan);

    ret = gpio_pin_set_dt(&config->led_gpio, 0);
    if (ret < 0) {
        LOG_ERR("Failed to switch LED off: %d", ret);
        return ret;
    }

    data->led_state = 0; // Update LED state to OFF
    if (val != NULL) {
        val->val1 = data->led_state; 
        val->val2 = 0;
    }
    return 0;
}

static DEVICE_API(sensor, our_driver_api) = {
    .sample_fetch = our_driver_sample_fetch,
    .channel_get = our_driver_channel_get,
};

// Initialize the driver
static int our_driver_init(const struct device *dev){

    const struct our_driver_config *config = dev->config;
    struct our_driver_data *data = dev->data;
    int ret;

    if (!gpio_is_ready_dt(&config->led_gpio)) {
        LOG_ERR("GPIO device not ready");
        return -ENODEV;
    }

    ret = gpio_pin_configure_dt(&config->led_gpio, GPIO_OUTPUT_INACTIVE);
    if (ret < 0) {
        LOG_ERR("Failed to configure GPIO pin");
        return ret;
    }

    data->led_state = 0; // Initialize LED state to OFF

    LOG_INF("our_driver_init called, Device INITALIZED!");
    return 0;
}

#define OUR_DRIVER_DEFINE(inst)  \
    static struct our_driver_data our_driver_data_##inst; \
    static const struct our_driver_config our_driver_config_##inst = { \
        .led_gpio = GPIO_DT_SPEC_INST_GET(inst, led_gpios), \
    }; \
    DEVICE_DT_INST_DEFINE(inst, our_driver_init, NULL, &our_driver_data_##inst,\
                          &our_driver_config_##inst, POST_KERNEL, \
                          CONFIG_SENSOR_INIT_PRIORITY, &our_driver_api);

DT_INST_FOREACH_STATUS_OKAY(OUR_DRIVER_DEFINE);