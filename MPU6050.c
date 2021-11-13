

#include "MPU6050.h"

#include "stm32f4xx_hal.h"
#include "mpu6050_map.h"
#include "math.h"
#include "stdio.h"



uint8_t TxBuffer[2];
uint8_t RxBuffer[7];
uint8_t DataBuffer[14];
int16_t DataBuffer16[7];
uint8_t MPU6050_INT_State = 0;

int16_t gyro_x_temp, gyro_y_temp, gyro_z_temp, accel_x_temp, accel_y_temp, accel_z_temp, temp_raw;
float temp, gyro_x, gyro_y, gyro_z, accel_x, accel_y, accel_z;

float deneme,deneme1;

int xAng ;
int yAng ;
int zAng ;



int minVal=265; int maxVal=402;

int x,y,z;
int size;
char data;


char str[100]="";





void initRegister(){
	TxBuffer[0] = 0x80;
	HAL_I2C_Mem_Write(&hi2c1, MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, 1, TxBuffer, 1, 1000);
	HAL_Delay(200);

	TxBuffer[0] = 0x00;
	HAL_I2C_Mem_Write(&hi2c1, MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, 1, TxBuffer, 1, 1000);
	HAL_Delay(200);

	TxBuffer[0] = 0xF8;
	HAL_I2C_Mem_Write(&hi2c1, MPU6050_DEFAULT_ADDRESS, MPU6050_RA_FIFO_EN, 1, TxBuffer, 1, 1000);
	HAL_Delay(200);

	TxBuffer[0] = 0x10;
	HAL_I2C_Mem_Write(&hi2c1, MPU6050_DEFAULT_ADDRESS, MPU6050_RA_FIFO_EN, 1, TxBuffer, 1, 1000);
	HAL_Delay(200);

	HAL_I2C_Mem_Read(&hi2c1, MPU6050_DEFAULT_ADDRESS, MPU6050_RA_ACCEL_CONFIG, I2C_MEMADD_SIZE_8BIT, RxBuffer, 1, 1000);
	HAL_Delay(200);
	RxBuffer[0] |= 0x18;
	HAL_I2C_Mem_Write(&hi2c1, MPU6050_DEFAULT_ADDRESS, MPU6050_RA_ACCEL_CONFIG, 1, RxBuffer, 1, 1000);

	HAL_I2C_Mem_Read(&hi2c1, MPU6050_DEFAULT_ADDRESS, MPU6050_RA_INT_ENABLE, I2C_MEMADD_SIZE_8BIT, RxBuffer, 1, 1000);
	HAL_Delay(200);
	RxBuffer[0] |= 0x11;
	HAL_I2C_Mem_Write(&hi2c1, MPU6050_DEFAULT_ADDRESS, MPU6050_RA_INT_ENABLE, 1, RxBuffer, 1, 1000);

	HAL_I2C_Mem_Read(&hi2c1, MPU6050_DEFAULT_ADDRESS, MPU6050_RA_INT_PIN_CFG, I2C_MEMADD_SIZE_8BIT, RxBuffer, 1, 1000);
	HAL_Delay(200);
	RxBuffer[0] |= 0x30;
	HAL_I2C_Mem_Write(&hi2c1, MPU6050_DEFAULT_ADDRESS, MPU6050_RA_INT_PIN_CFG, 1, RxBuffer, 1, 1000);

	HAL_I2C_Mem_Read(&hi2c1, MPU6050_DEFAULT_ADDRESS, MPU6050_RA_CONFIG, I2C_MEMADD_SIZE_8BIT, RxBuffer, 1, 1000);
	HAL_Delay(200);
	RxBuffer[0] |= 0x06;
	HAL_I2C_Mem_Write(&hi2c1, MPU6050_DEFAULT_ADDRESS, MPU6050_RA_CONFIG, 1, RxBuffer, 1, 1000);
}

struct MPU{
	int x_eksen;
	int y_eksen;
	int z_eksen;
	int temp;
};

void MPU6050_Extract_Readings()
{

// Extract accel readings

//	HAL_UART_Init(&huart4);

struct MPU MPU6050;

accel_x_temp = DataBuffer16[0];
accel_x = (float)accel_x_temp / 2048.0F;
accel_y_temp = DataBuffer16[1];
accel_y = (float)accel_y_temp / 2048.0F;
accel_z_temp = DataBuffer16[2];
accel_z = (float)accel_z_temp / 2048.0F;

 xAng = map(accel_x_temp,minVal,maxVal,-90,90);
 yAng = map(accel_y_temp,minVal,maxVal,-90,90);
 zAng = map(accel_z_temp,minVal,maxVal,-90,90);

// Extract temperature readings
temp_raw = DataBuffer16[3];
MPU6050.temp = temp_raw / 340.0F;


MPU6050.x_eksen= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
MPU6050.y_eksen= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
MPU6050.z_eksen= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

sprintf(str,"x acisi =%d\n y acisi =%d\n",x,y);

for(int t=0;t<=sizeof(str);t++){
	if(str[t] == '\0'){
	 size = t ;
		break;
			}
}


//MPU6050_INT_State = FALSE;
}




void MPU6050_Read_All_Values(){
	  HAL_I2C_Mem_Read(&hi2c1, MPU6050_DEFAULT_ADDRESS, MPU6050_RA_ACCEL_XOUT_H, I2C_MEMADD_SIZE_8BIT, DataBuffer, 14, 10000);
	  for(int i=0;i<7;i++)
	  {
	  DataBuffer16[i] = (int16_t)(((uint16_t)DataBuffer[2*i]<<8) | DataBuffer[2*i + 1]);
	  }
}
