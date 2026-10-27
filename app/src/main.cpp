#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/device.h>


const struct device *const my_device = DEVICE_DT_GET(DT_NODELABEL(our_driver0));

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);



namespace {
    void test() {
        const struct device *const driver = DEVICE_DT_GET(DT_NODELABEL(our_driver0));
        struct sensor_value val;
        auto ret = sensor_channel_get(driver, SENSOR_CHAN_AMBIENT_TEMP, &val);
        LOG_INF("Channel ret %d", ret);
    }
}

int main(void)
{
    struct sensor_value val; 

    test();
    
    if (!device_is_ready(my_device)) {
        LOG_ERR("Device our_driver0 not ready");
        return -ENODEV;
    }

    while (1) {
       int ret = sensor_sample_fetch(my_device);
       if (ret < 0) {
           LOG_ERR("Failed to fetch sensor sample: %d", ret);
       }

       k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
       ret = sensor_channel_get(my_device, SENSOR_CHAN_AMBIENT_TEMP, &val);
       if (ret < 0) {
           LOG_ERR("Failed to get sensor channel: %d", ret);
       }
       k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
    }

    
    /*
    bool led_state = true;

    if (!gpio_is_ready_dt(&led)) return 0;

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) return 0;

    while (1) {
        if (gpio_pin_toggle_dt(&led) < 0) return 0;

        led_state = !led_state;
        LOG_INF("LED state: %s", led_state ? "ON" : "OFF");
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
    }
    return 0;
    */
}
