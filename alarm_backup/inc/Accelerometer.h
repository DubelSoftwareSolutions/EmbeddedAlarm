#include "stm32f4xx_hal.h"
#include "main.h"

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#define GRAVITATIONAL_ACCELERATION 9.80665
#define ACCELEROMETER_SENSITIVITY 8192.0
#define GYROSCOPE_SENSITIVITY 65.536

#define MPU6050_GYRO_SENS_250		((float) 131)
#define MPU6050_ACCE_SENS_2			((float) 16384)

#define M_PI 3.14159265359

#define dt 0.01

#define ACC_I2C_HANDLE hi2c1
#define ACC_I2C_TIMEOUT 100
#define ACC_AXIS_COUNT 3
#define ACC_RESOLUTION_G 2
#define ACC_MOTION_THRESHOLD_mg 100
#define ACC_MOTION_THRESHOLD_RESOLUTION_mg 2
#define ACC_MOTION_DURATION_ms 100
#define ACC_MOTION_DURATION_RESOLUTION_ms 1

#define MPU6050_DEVICE_ADDRESS	0x68

#define MPU6050_I2C_ADDR		0xD0

#define MPU6050_I_AM			0x68

#define MPU6050_Device_0		0x00
#define MPU6050_Device_1		0x02

#define MPU6050_SMPLRT_DIV		0x19
#define MPU6050_PWR_MGMT1 		0x6B
#define MPU6050_PWR_MGMT2 		0x6C
#define MPU6050_CONFIG        	0x1A
#define MPU6050_GYRO_CONFIG		0x1B
#define MPU6050_ACC_CONFIG 		0x1C
#define MPU6050_MOT_THR        	0x1F
#define MPU6050_MOT_DUR        	0x20
#define MPU6050_INT_PIN_CFG		0x37
#define MPU6050_INT_ENABLE		0x38
#define MPU6050_DMP_INT_STATUS	0x39
#define MPU6050_INT_STATUS		0x3A
#define MPU6050_ACC_XOUT_H		0x3B
#define MPU6050_ACC_XOUT_L		0x3C
#define MPU6050_ACC_YOUT_H		0x3D
#define MPU6050_ACC_YOUT_L		0x3E
#define MPU6050_ACC_ZOUT_H		0x3F
#define MPU6050_ACC_ZOUT_L		0x40
#define MPU6050_GYRO_XOUT_H		0x43
#define MPU6050_GYRO_XOUT_L		0x44
#define MPU6050_GYRO_YOUT_H		0x45
#define MPU6050_GYRO_YOUT_L		0x46
#define MPU6050_GYRO_ZOUT_H		0x47
#define MPU6050_GYRO_ZOUT_L		0x48
#define MPU6050_WHO_AM_I		0x75

#define MPU6050_DataRate_1KHz		7
#define MPU6050_Accelerometer_2G 0x00
#define MPU6050_Gyroscope_250s	 0x00

typedef struct  {
	/* Private */
	uint8_t Address;         /*!< I2C address of device. */
	float gsens;         /*!< Gyroscope corrector from raw data to "degrees/s". Only for private use */
	float asens;         /*!< Accelerometer corrector from raw data to "g". Only for private use */
	/* Public */
	int16_t acc_x; /*!< Accelerometer value X axis */
	int16_t acc_y; /*!< Accelerometer value Y axis */
	int16_t acc_z; /*!< Accelerometer value Z axis */
	int16_t gyro_x;     /*!< Gyroscope value X axis */
	int16_t gyro_y;     /*!< Gyroscope value Y axis */
	int16_t gyro_z;     /*!< Gyroscope value Z axis */
	//I2C_HandleTypeDef* I2Cx;
} MPU_6050;

uint16_t g_AxisMeasurements[ACC_AXIS_COUNT];
float g_AggregatedAxisMeasurements[ACC_AXIS_COUNT];
uint8_t g_MotionFlag;
uint8_t interruptStatus;

float pitch, roll, yaw;
float gsens, asens;

HAL_StatusTypeDef AccelerometerInit();
HAL_StatusTypeDef AccelerometerConfigure();
HAL_StatusTypeDef AccelerometerMotionIntConfigure();

HAL_StatusTypeDef GetAccelerometerData(MPU_6050*);
HAL_StatusTypeDef GetGyroData(MPU_6050*);
HAL_StatusTypeDef MPU6050_EnableInterrupts();
HAL_StatusTypeDef MPU6050_ReadInterrupts();

void AggregateAccelerometerMeasurementsTo_g();
void ComplementaryFilter(MPU_6050*, float*, float*);

#endif /* ACCELEROMETER_H_ */
