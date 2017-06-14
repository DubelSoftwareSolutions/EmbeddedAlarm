#include "i2c.h"
#include "gpio.h"
#include "debug.h"
#include "Accelerometer.h"

/*
 * Self Axis Test: X disabled, Y disabled, Z disabled
 * Full scale range for Accelerometer: +/- 16g
 */
uint8_t g_MPU6050_AccelerometerSettings[1] = { 0b00011000 };

/*
 * Active high, push-pull, pulse mode off,
 * Clear on any read,
 */
uint8_t g_MPU6050_InterruptSettings[1] = { 0b00100000 };

/*
 * Motion Interrupt enabled, other disabled
 */
uint8_t g_MPU6050_InterruptEnableSettings[1] = { 0b01000000 };

uint8_t g_MPU6050_MotionInterruptThreshold[1] = { ACC_MOTION_THRESHOLD_mg
		/ ACC_MOTION_THRESHOLD_RESOLUTION_mg };

uint8_t g_MPU6050_MotionInterruptDuration[1] = { ACC_MOTION_DURATION_ms
		/ ACC_MOTION_DURATION_RESOLUTION_ms };

void Debug_StartSendingPosition() {
	while (1) {
		printf("[DBG] SENDING FAKE POSITION\n\r");
		HAL_Delay(300);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == MPU6050_INT_Pin) {
		g_MotionFlag = !g_MotionFlag; //popraw
		//GPS_StartGettingPosition();
		//Debug_StartSendingPosition();
		printf("[DBG] MOTION CALLBACK\n\r");
		HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
	}
}

HAL_StatusTypeDef AccelerometerConfigure() {
	HAL_StatusTypeDef TransmissionStatus;
	TransmissionStatus = HAL_I2C_Mem_Write(&ACC_I2C_HANDLE,
	MPU6050_DEVICE_ADDRESS,
	MPU6050_ACC_CONFIG, 1, g_MPU6050_AccelerometerSettings, 1,
	ACC_I2C_TIMEOUT);
	return TransmissionStatus;
}

/*
HAL_StatusTypeDef AccelerometerMotionIntConfigure(){
	uint8_t val = 0x07;
	uint8_t address = MPU6050_I2C_ADDR | MPU6050_Device_0;

	HAL_I2C_Mem_Write(&ACC_I2C_HANDLE, (uint16_t)address, 0x68, 1, &val, 1, 1000);
}*/

HAL_StatusTypeDef AccelerometerMotionIntConfigure()
{
	HAL_StatusTypeDef TransmissionStatus;
	uint8_t val;
	uint8_t address = MPU6050_I2C_ADDR | MPU6050_Device_0;

	val = 0x07;
	TransmissionStatus = HAL_I2C_Mem_Write(&ACC_I2C_HANDLE,	(uint16_t)address,
				0x68,1,&val,1, ACC_I2C_TIMEOUT); // signal paths reset
	if (TransmissionStatus != HAL_OK)
		return TransmissionStatus;

	TransmissionStatus = HAL_I2C_Mem_Write(&ACC_I2C_HANDLE,	(uint16_t)address,
				MPU6050_INT_PIN_CFG,1,g_MPU6050_InterruptSettings,1, ACC_I2C_TIMEOUT); // active high
	if (TransmissionStatus != HAL_OK)
		return TransmissionStatus;

	val = 0x01;
	TransmissionStatus = HAL_I2C_Mem_Write(&ACC_I2C_HANDLE,	(uint16_t)address,
				0x1C,1,&val,1, ACC_I2C_TIMEOUT); // HighPass 5Hz
	if (TransmissionStatus != HAL_OK)
		return TransmissionStatus;

	val=20;
	TransmissionStatus = HAL_I2C_Mem_Write(&ACC_I2C_HANDLE,	(uint16_t)address,
				MPU6050_MOT_THR,1,&val/*g_MPU6050_MotionInterruptThreshold*/,1,ACC_I2C_TIMEOUT);
	if (TransmissionStatus != HAL_OK)
		return TransmissionStatus;

	val=40;
	TransmissionStatus = HAL_I2C_Mem_Write(&ACC_I2C_HANDLE,	(uint16_t)address,
				MPU6050_MOT_DUR,1,&val/*g_MPU6050_MotionInterruptDuration*/,1,ACC_I2C_TIMEOUT);
	if (TransmissionStatus != HAL_OK)
		return TransmissionStatus;

	val=0x15;
	TransmissionStatus = HAL_I2C_Mem_Write(&ACC_I2C_HANDLE,	(uint16_t)address,
				0x69,1,&val,1, ACC_I2C_TIMEOUT);
	if (TransmissionStatus != HAL_OK)
		return TransmissionStatus;

	val=0x40;
	TransmissionStatus = HAL_I2C_Mem_Write(&ACC_I2C_HANDLE,	(uint16_t)address,
				MPU6050_INT_ENABLE,1,&val/*g_MPU6050_InterruptEnableSettings*/,1, ACC_I2C_TIMEOUT);
	if (TransmissionStatus != HAL_OK)
		return TransmissionStatus;

	return TransmissionStatus;
}

HAL_StatusTypeDef MPU6050_EnableInterrupts() {
	uint8_t received;
	uint8_t reg[2] = {MPU6050_INT_ENABLE,0x21};
	uint8_t address = MPU6050_I2C_ADDR | MPU6050_Device_0;

	/* Enable interrupts for data ready and motion detect */
	while(HAL_I2C_Master_Transmit(&ACC_I2C_HANDLE, (uint16_t)address, reg, 2, 1000) != HAL_OK);

	uint8_t mpu_reg= MPU6050_INT_PIN_CFG;
	/* Clear IRQ flag on any read operation */
	while(HAL_I2C_Master_Transmit(&ACC_I2C_HANDLE, (uint16_t)address, &mpu_reg, 1, 1000) != HAL_OK);

	while(HAL_I2C_Master_Receive(&ACC_I2C_HANDLE, (uint16_t)address, &received, 14, 1000) != HAL_OK);
	received |= 0x10;
	reg[0] = MPU6050_INT_PIN_CFG;
	reg[1] = received;
	while(HAL_I2C_Master_Transmit(&ACC_I2C_HANDLE, (uint16_t)address, reg, 2, 1000) != HAL_OK);

		/* Return OK */
	return HAL_OK;
}

HAL_StatusTypeDef MPU6050_ReadInterrupts() {
	uint8_t read;

	/* Reset structure */
	interruptStatus = 0;
	uint8_t reg = MPU6050_INT_STATUS;
	uint8_t address = MPU6050_I2C_ADDR | MPU6050_Device_0;

	while(HAL_I2C_Master_Transmit(&ACC_I2C_HANDLE, (uint16_t)address, &reg, 1, 1000) != HAL_OK);
	while(HAL_I2C_Master_Receive(&ACC_I2C_HANDLE, (uint16_t)address, &read, 14, 1000) != HAL_OK);

	/* Fill value */
	interruptStatus = read;
	/* Return OK */
	return HAL_OK;
}

HAL_StatusTypeDef GetAccelerometerData(MPU_6050* mpu)
{
	uint8_t data[6];
	uint8_t reg = MPU6050_ACC_XOUT_H;
	uint8_t address = MPU6050_I2C_ADDR | MPU6050_Device_0;

	/* Read accelerometer data */
	while(HAL_I2C_Master_Transmit(&ACC_I2C_HANDLE, (uint16_t)address, &reg, 1, 1000) != HAL_OK);

	while(HAL_I2C_Master_Receive(&ACC_I2C_HANDLE, (uint16_t)address, data, 6, 1000) != HAL_OK);

	/* Format */
	mpu->acc_x = (int16_t)(data[0] << 8 | data[1]);
	mpu->acc_y = (int16_t)(data[2] << 8 | data[3]);
	mpu->acc_z = (int16_t)(data[4] << 8 | data[5]);

	/* Return OK */
	return HAL_OK;
}

HAL_StatusTypeDef GetGyroData(MPU_6050* mpu)
{
	uint8_t data[6];
	uint8_t reg = MPU6050_GYRO_XOUT_H;;
	uint8_t address = MPU6050_I2C_ADDR | MPU6050_Device_0;

	/* Read accelerometer data */
	while(HAL_I2C_Master_Transmit(&ACC_I2C_HANDLE, (uint16_t)address, &reg, 1, 1000) != HAL_OK);

	while(HAL_I2C_Master_Receive(&ACC_I2C_HANDLE, (uint16_t)address, data, 6, 1000) != HAL_OK);

	/* Format */
	mpu->gyro_x = (int16_t)(data[0] << 8 | data[1]);
	mpu->gyro_y = (int16_t)(data[2] << 8 | data[3]);
	mpu->gyro_z = (int16_t)(data[4] << 8 | data[5]);

	/* Return OK */
	return HAL_OK;
}

HAL_StatusTypeDef AccelerometerInit() {
	uint8_t reg = 0x00;
	uint8_t received = 0x00;
	uint8_t d[2];

	uint8_t WHO_AM_I = MPU6050_WHO_AM_I;
	uint8_t address = MPU6050_I2C_ADDR | MPU6050_Device_0;

	/* Check who am I */
	//------------------
	/* Send address */
	if (HAL_I2C_Master_Transmit(&ACC_I2C_HANDLE, address, &WHO_AM_I, 1, 1000)
			!= HAL_OK) {
		printf("[DEBUG] Whoami address send error. \n\r");
	}
	/* Receive multiple byte */
	if (HAL_I2C_Master_Receive(&ACC_I2C_HANDLE, address, &received, 1, 1000)
			!= HAL_OK) {
		printf("[DEBUG] Receive whoami error. \n\r");
	}
	/* Checking */
	if (received != MPU6050_I_AM) {
		/* Return error */
		printf("[DEBUG / CRITICAL MASSIVE ASSERTION ERROR] I DONT KNOW WHO AM I. \n\r");
	}
	//------------------
	/* Wakeup MPU6050 */
	//------------------
	/* Format array to send */
	//uint8_t address = MPU6050_PWR_MGMT1 | MPU6050_Device_0;
	d[0] = MPU6050_PWR_MGMT1;
	d[1] = 0x00;
	/* Try to transmit via I2C */
	if (HAL_I2C_Master_Transmit(&ACC_I2C_HANDLE, (uint16_t) address, (uint8_t *) d, 2, 1000) != HAL_OK) {
		printf("[DEBUG] Wakeup error. \n\r");
	}
	//------------------
	/* Set sample rate to 1kHz */
	/* Format array to send */
	d[0] = MPU6050_SMPLRT_DIV;
	d[1] = MPU6050_DataRate_1KHz;
	while (HAL_I2C_Master_Transmit(&ACC_I2C_HANDLE, (uint16_t) address, (uint8_t *) d, 2, 1000) != HAL_OK);

	/* Config accelerometer */
	reg =(uint8_t )MPU6050_ACC_CONFIG;
	while(HAL_I2C_Master_Transmit(&ACC_I2C_HANDLE, (uint16_t)address, &reg, 1, 1000) != HAL_OK);
	while(HAL_I2C_Master_Receive(&ACC_I2C_HANDLE, (uint16_t)address, &received, 1, 1000) != HAL_OK);
	received = (received & 0xE7) | (uint8_t)MPU6050_Accelerometer_2G << 3;
	while(HAL_I2C_Master_Transmit(&ACC_I2C_HANDLE, (uint16_t)address, &received, 1, 1000) != HAL_OK);

	gsens = (float)1 / MPU6050_GYRO_SENS_250;
	asens = (float)1 / MPU6050_ACCE_SENS_2;

	/* Config Gyroscope */
	reg =(uint8_t )MPU6050_GYRO_CONFIG;
	while(HAL_I2C_Master_Transmit(&ACC_I2C_HANDLE, (uint16_t)address,&reg, 1, 1000) != HAL_OK);
	while(HAL_I2C_Master_Receive(&ACC_I2C_HANDLE, (uint16_t)address, &received, 1, 1000) != HAL_OK);
	received = (received & 0xE7) | (uint8_t)MPU6050_Gyroscope_250s << 3;
	while(HAL_I2C_Master_Transmit(&ACC_I2C_HANDLE, (uint16_t)address,&received, 1, 1000) != HAL_OK);

	/* Return OK */
	return HAL_OK;
}

void ComplementaryFilter(MPU_6050* mpu, float *pitch, float *roll)
{
    float pitchAcc, rollAcc;
    // Integrate the gyroscope data -> int(angularSpeed) = angle
    *pitch += (float)mpu->gyro_x * gsens * dt; // Angle around the X-axis
    *roll -= (float)mpu->gyro_y * gsens * dt;    // Angle around the Y-axis

    // Compensate for drift with accelerometer data if !bullshit
    // Sensitivity = -2 to 2 G at 16Bit -> 2G = 32768 && 0.5G = 8192
    int forceMagnitudeApprox = abs(mpu->acc_x) + abs(mpu->acc_y) + abs(mpu->acc_z);
    if (forceMagnitudeApprox > 8192 && forceMagnitudeApprox < 32768)
    {
	// Turning around the X axis results in a vector on the Y-axis
        pitchAcc = atan2f((float)mpu->acc_y, (float)mpu->acc_z) * 180 / M_PI;
        *pitch = *pitch * 0.98 + pitchAcc * 0.02;

	// Turning around the Y axis results in a vector on the X-axis
        rollAcc = atan2f((float)mpu->acc_x, (float)mpu->acc_z) * 180 / M_PI;
        *roll = *roll * 0.98 + rollAcc * 0.02;
    }
}
