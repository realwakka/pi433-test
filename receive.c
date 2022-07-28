#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/ioctl.h>

#include "pi433_if.h"

int main() {
        int fd, ret;
        char c[255];

        fd = open("/dev/pi433.0", O_RDWR);

        struct pi433_rx_cfg rx_cfg;
        rx_cfg.frequency = 433920000;
        rx_cfg.bit_rate = 4800;
        rx_cfg.dev_frequency = 4250;

        rx_cfg.modulation = OOK;

        rx_cfg.rssi_threshold = 0x90;
        rx_cfg.threshold_decrement = dec_every8th;

        rx_cfg.antenna_impedance = fifty_ohm;
        rx_cfg.lna_gain = max;
        rx_cfg.bw_mantisse = mantisse24;
        rx_cfg.bw_exponent = 0;
        rx_cfg.dagc = normal_mode;

        rx_cfg.enable_sync = OPTION_ON;
        rx_cfg.enable_length_byte = OPTION_ON;
        rx_cfg.enable_address_filtering = filtering_off;
        rx_cfg.enable_crc = OPTION_ON;

        rx_cfg.sync_length = 1;
        rx_cfg.fixed_message_length = 5;
        rx_cfg.bytes_to_drop = 0;

        rx_cfg.sync_pattern[0] = 0x1;
        rx_cfg.sync_pattern[1] = 0x2;
        rx_cfg.sync_pattern[2] = 0x3;

        ret = ioctl(fd, PI433_IOC_WR_RX_CFG, &rx_cfg);
        if (ret < 0) {
                printf("ioctl failed");
                return 1;
        }

        ret = read(fd, c, 100);

        if (ret < 0) {
                printf("read failed");
	}

	close(fd);
	return 0;
}
