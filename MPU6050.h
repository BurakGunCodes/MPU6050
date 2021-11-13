
#ifndef _MPU6050_H
#define _MPU6050_H



#define PI 3.14159265
#define HALF_PI 1.57079
#define TWO_PI 6.283185
#define DEG_TO_RAD 0.01745329
#define RAD_TO_DEG 57.2957786



void initRegister();
void MPU6050_Extract_Readings();
long map(long , long , long , long , long );
void MPU6050_Read_All_Values();

#endif 
