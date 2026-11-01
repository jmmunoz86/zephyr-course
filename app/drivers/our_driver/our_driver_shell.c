#include <zephyr/shell/shell.h>
#include <zephyr/drivers/sensor.h>

/// from lecture

static int cmd_channel_get_handler(const struct shell *sh, size_t argc, char **argv) {
    const struct device *const device = shell_device_get_binding(argv[1]);
    if (!device) {
        shell_error(sh, "Device not found: %s", argv[1]);
        return -EFAULT;
    }

    struct sensor_value val;
    int ret = sensor_channel_get(device, SENSOR_CHAN_AMBIENT_TEMP, &val);
    if (ret != 0) {
        shell_error(sh, "Failed to get channel value, got: %d", ret);
        return -EFAULT;
    }

    shell_info(sh, "Hello from channel get handler cmd: %d", val.val1);
    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(our_driver_subcmd,
    SHELL_CMD_ARG(channel_get, NULL, "Get channel value of our_driver", cmd_channel_get_handler, 2, 0),
    SHELL_SUBCMD_SET_END,
);

SHELL_CMD_REGISTER(our_driver, &our_driver_subcmd, "Set of commands for our_driver", NULL);


/// task l7-1
static int cmd_fetch_handler(const struct shell *sh, size_t argc, char **argv) {
    const struct device *const device = shell_device_get_binding(argv[1]);
    if (!device) {
        shell_error(sh, "Device not found: %s", argv[1]);
        return -EFAULT;
    }
    
    int ret = sensor_sample_fetch(device);
    if (ret != 0) {
        shell_error(sh, "Failed to fetch channel value, got: %d", ret);
        return -EFAULT;
    }

    shell_info(sh, "Hello from channel fetch handler cmd (sensor_sample_fetch)");
    return 0;
}

static int cmd_read_handler(const struct shell *sh, size_t argc, char **argv) {
    const struct device *const device = shell_device_get_binding(argv[1]);
    if (!device) {
        shell_error(sh, "Device not found: %s", argv[1]);
        return -EFAULT;
    }

    struct sensor_value val;
    int ret = sensor_channel_get(device, SENSOR_CHAN_AMBIENT_TEMP, &val);
    if (ret != 0) {
        shell_error(sh, "Failed to get channel value, got: %d", ret);
        return -EFAULT;
    }

    shell_info(sh, "Hello from channel get handler cmd (sensor_channel_get): val1 = %d, val2 = %d", val.val1, val.val2);
    return 0;
}

static int cmd_info_handler(const struct shell *sh, size_t argc, char **argv) {
    const struct device *const device = shell_device_get_binding(argv[1]);
    if (!device) {
        shell_error(sh, "Device not found: %s", argv[1]);
        return -EFAULT;
    }

    shell_info(sh, "Device name: %s, Device state: %d", device->name, device->state->init_res);
    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sensor_subcmd,
    SHELL_CMD_ARG(fetch, NULL, "Fetch channel value of our_driver", cmd_fetch_handler, 2, 0),
    SHELL_CMD_ARG(read, NULL, "Get channel value of our_driver", cmd_read_handler, 2, 0),
    SHELL_CMD_ARG(info, NULL, "Get channel value of our_driver", cmd_info_handler, 2, 0),
    SHELL_SUBCMD_SET_END,
);
SHELL_CMD_REGISTER(sensor, &sensor_subcmd, "set of sensor commands", NULL);
