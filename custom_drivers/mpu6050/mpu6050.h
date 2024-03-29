#ifndef MPU6050_H_
#define MPU6050_H_


/* register address values */
#define  REG_SELF_TEST_X 	13
#define  REG_SELF_TEST_Y	14
#define  REG_SELF_TEST_Z	15
#define  REG_SELF_TEST_A	16
#define  REG_SMPLRT_DIV		25
#define  REG_CONFIG		26
#define  REG_GYRO_CONFIG	27
#define  REG_ACCEL_CONFIG	28
#define  REG_FIFO_EN		35
#define  REG_I2C_MST_CTRL	36
#define  REG_I2C_SLV0_ADDR	37
#define  REG_I2C_SLV0_REG	38
#define  REG_I2C_SLV0_CTRL	39
#define  REG_I2C_SLV1_ADDR	40
#define  REG_I2C_SLV1_REG	41
#define  REG_I2C_SLV1_CTRL	42
#define  REG_I2C_SLV2_ADDR	43
#define  REG_I2C_SLV2_REG	44
#define  REG_I2C_SLV2_CTRL	45
#define  REG_I2C_SLV3_ADDR	46
#define  REG_I2C_SLV3_REG	47
#define  REG_I2C_SLV3_CTRL	48
#define  REG_I2C_SLV4_ADDR	49
#define  REG_I2C_SLV4_REG	50
#define  REG_I2C_SLV4_DO	51
#define  REG_I2C_SLV4_CTRL	52
#define  REG_I2C_SLV4_DI	53
#define  REG_I2C_MST_STATUS	54
#define  REG_INT_PIN_CFG	55
#define  REG_INT_ENABLE		56
#define  REG_INT_STATUS		58
#define  REG_ACCEL_XOUT_H	59
#define  REG_ACCEL_XOUT_L	60
#define  REG_ACCEL_YOUT_H	61
#define  REG_ACCEL_YOUT_L	62
#define  REG_ACCEL_ZOUT_H	63
#define  REG_ACCEL_ZOUT_L	64
#define  REG_TEMP_OUT_H		65
#define  REG_TEMP_OUT_L		66
#define  REG_GYRO_XOUT_H	67
#define  REG_GYRO_XOUT_L	68
#define  REG_GYRO_YOUT_H	69
#define  REG_GYRO_YOUT_L	70
#define  REG_GYRO_ZOUT_H	71
#define  REG_GYRO_ZOUT_L	72
#define  REG_EXT_SENS_DATA_00	73
#define  REG_EXT_SENS_DATA_01	74
#define  REG_EXT_SENS_DATA_02	75
#define  REG_EXT_SENS_DATA_03	76
#define  REG_EXT_SENS_DATA_04	77
#define  REG_EXT_SENS_DATA_05	78
#define  REG_EXT_SENS_DATA_06	79
#define  REG_EXT_SENS_DATA_07	80
#define  REG_EXT_SENS_DATA_08	81
#define  REG_EXT_SENS_DATA_09	82
#define  REG_EXT_SENS_DATA_10	83
#define  REG_EXT_SENS_DATA_11	84
#define  REG_EXT_SENS_DATA_12	85
#define  REG_EXT_SENS_DATA_13	86
#define  REG_EXT_SENS_DATA_14	87
#define  REG_EXT_SENS_DATA_15	88
#define  REG_EXT_SENS_DATA_16	89
#define  REG_EXT_SENS_DATA_17	90
#define  REG_EXT_SENS_DATA_18	91
#define  REG_EXT_SENS_DATA_19	92
#define  REG_EXT_SENS_DATA_20	93
#define  REG_EXT_SENS_DATA_21	94
#define  REG_EXT_SENS_DATA_22	95
#define  REG_EXT_SENS_DATA_23	96
#define  REG_I2C_SLV0_DO	99
#define  REG_I2C_SLV1_DO	100
#define  REG_I2C_SLV2_DO	101
#define  REG_I2C_SLV3_DO	102
#define  REG_I2C_MST_DELAY_CTRL	103
#define  REG_SIGNAL_PATH_RESET	104
#define  REG_USER_CTRL		106
#define  REG_PWR_MGMT_1		107
#define  REG_PWR_MGMT_2		108
#define  REG_FIFO_COUNTH	114
#define  REG_FIFO_COUNTL	115
#define  REG_FIFO_R_W		116
#define  REG_WHO_AM_I		117


#endif //MPU6050_H_
