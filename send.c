#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/ioctl.h>

#include "pi433_if.h"

int main() {
	int fd, ret;
	char c[255];

	fd = open("/dev/pi433.0", O_RDWR);

	struct pi433_tx_cfg tx_cfg;
	tx_cfg.frequency = 433920000;
	tx_cfg.bit_rate = 4800;
	tx_cfg.dev_frequency = 4250;

	tx_cfg.modulation = OOK;
	tx_cfg.mod_shaping = SHAPING_OFF;
	tx_cfg.pa_ramp = ramp40;

	tx_cfg.tx_start_condition = fifo_not_empty;
	
	tx_cfg.enable_preamble = OPTION_ON;
	tx_cfg.enable_sync = OPTION_ON;
	tx_cfg.enable_length_byte = OPTION_ON;
	tx_cfg.enable_address_byte = OPTION_OFF;
	tx_cfg.enable_crc = OPTION_ON;

	tx_cfg.preamble_length = 0x3;
	tx_cfg.sync_length = 0x1;
	tx_cfg.fixed_message_length = 0;

	tx_cfg.sync_pattern[0] = 0x1;
	tx_cfg.sync_pattern[1] = 0x2;
	tx_cfg.sync_pattern[2] = 0x3;

	// tx_cfg.address_byte = 1;

	ret = ioctl(fd, PI433_IOC_WR_TX_CFG, &tx_cfg);
	if (ret < 0) {
		printf("ioctl failed");
		return 1;
	}

	/* ret = read(fd, c, 100); */
	ret = write(fd, "abcde", 5);

	if (ret < 0) {
		printf("read failed");
		return 1;
	}
	close(fd);
	return 0;
}
