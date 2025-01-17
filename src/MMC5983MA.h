/* 06/14/2020 Copyright Tlera Corporation

    Created by Kris Winer

  This sketch uses SDA/SCL on pins 21/20 (Ladybug default), respectively, and it uses the Ladybug STM32L432 Breakout Board.
  The MMC5983MA is a low power magnetometer, here used as 3 DoF in a 9 DoF absolute orientation solution.

  Library may be used freely and without limit with attribution.

*/

#ifndef MMC5983MA_h
#define MMC5983MA_h

#include <zephyr/types.h>
#include <zephyr/drivers/i2c.h>

//Register map for MMC5983MA'
//http://www.memsic.com/userfiles/files/DataSheets/Magnetic-Sensors-Datasheets/MMC5983MA_Datasheet.pdf
#define MMC5983MA_XOUT_0        0x00
#define MMC5983MA_XOUT_1        0x01
#define MMC5983MA_YOUT_0        0x02
#define MMC5983MA_YOUT_1        0x03
#define MMC5983MA_ZOUT_0        0x04
#define MMC5983MA_ZOUT_1        0x05
#define MMC5983MA_XYZOUT_2      0x06
#define MMC5983MA_TOUT          0x07
#define MMC5983MA_STATUS        0x08
#define MMC5983MA_CONTROL_0     0x09
#define MMC5983MA_CONTROL_1     0x0A
#define MMC5983MA_CONTROL_2     0x0B
#define MMC5983MA_CONTROL_3     0x0C
#define MMC5983MA_PRODUCT_ID    0x2F

#define MMC5983MA_ADDRESS       0x30

// Sample rates
#define MODR_ONESHOT   0x00
#define MODR_1Hz       0x01
#define MODR_10Hz      0x02
#define MODR_20Hz      0x03
#define MODR_50Hz      0x04
#define MODR_100Hz     0x05
#define MODR_200Hz     0x06 // BW = 0x01 only
#define MODR_1000Hz    0x07 // BW = 0x11 only

//Bandwidths
#define MBW_100Hz 0x00  // 8 ms measurement time
#define MBW_200Hz 0x01  // 4 ms
#define MBW_400Hz 0x02  // 2 ms
#define MBW_800Hz 0x03  // 0.5 ms

// Set/Reset as a function of measurements
#define MSET_1     0x00 // Set/Reset each data measurement
#define MSET_25    0x01 // each 25 data measurements
#define MSET_75    0x02
#define MSET_100   0x03
#define MSET_250   0x04
#define MSET_500   0x05
#define MSET_1000  0x06
#define MSET_2000  0x07

uint8_t mmc_getChipID(struct i2c_dt_spec dev_i2c);
void mmc_init(struct i2c_dt_spec dev_i2c, uint8_t MODR, uint8_t MBW, uint8_t MSET);
void mmc_offsetBias(struct i2c_dt_spec dev_i2c, float * dest1, float * dest2);
void mmc_reset(struct i2c_dt_spec dev_i2c);
uint8_t mmc_status(struct i2c_dt_spec dev_i2c);
void mmc_clearInt(struct i2c_dt_spec dev_i2c);
void mmc_selfTest(struct i2c_dt_spec dev_i2c);
void mmc_readData(struct i2c_dt_spec dev_i2c, uint32_t * destination);
uint8_t mmc_readTemperature(struct i2c_dt_spec dev_i2c);
void mmc_SET(struct i2c_dt_spec dev_i2c);
void mmc_RESET(struct i2c_dt_spec dev_i2c);
void mmc_getOffset(struct i2c_dt_spec dev_i2c, float * destination);
void mmc_powerDown(struct i2c_dt_spec dev_i2c);
void mmc_powerUp(struct i2c_dt_spec dev_i2c, uint8_t MODR);

#endif
