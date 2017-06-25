#include "mpu9250.h"


u8 MPU9250::writeByte(u8 addr, u8 reg, u8 data)
{
	u8 err = 0;
	i2c->take_i2c_right(speed);
	err = i2c->write_byte(addr, reg, data);
	i2c->release_i2c_right();
	return err;
}

u8 MPU9250::readByte(u8 addr, u8 reg)
{
	u8 data;
	i2c->take_i2c_right(speed);
	i2c->read_byte(addr, reg, &data);
	i2c->release_i2c_right();
	return data;
}

u8 MPU9250::readLen(u8 addr, u8 reg, u8 len, u8 *buf)
{
	u8 err = 0;
	i2c->take_i2c_right(speed);
	//err = i2c->read_byte(addr, reg, buf, len);
	for (int i = 0; i < len; i++)
	{
		err = i2c->read_byte(addr, reg + i, buf + i);
	}
	i2c->release_i2c_right();
	return err;
}

u8 MPU9250::writeLen(u8 addr, u8 reg, u8 len, u8 *buf)
{
	u8 err = 0;
	i2c->take_i2c_right(speed);
	//err = i2c->write_byte(addr, reg, buf, len);
	for (int i = 0; i < len; i++)
	{
		err = i2c->write_byte(addr, reg, buf[i]);
	}
	i2c->release_i2c_right();
	return err;
}

MPU9250::MPU9250(I2c* i2c, MPU9250_Model_Typedef model/*=Mpu9250_Model_9250*/) :
	i2c(i2c),
	model(model)
{
	if (model == MPU9250_Model_9250)
	{
		mpuID = MPU6500_ID;
	}
	else if (model == MPU9250_Model_9255)
	{
		mpuID = MPU6555_ID;
	}
}

u8 MPU9250::begin(uint32_t speed /*= 400000*/, uint16_t sampleRate /*= 100*/,
	MPU9250_Gyro_Full_Scale_Typedef gyroFsr/* = MPU9250_Gyro_Full_Scale_2000dps*/,
	MPU9250_Accel_Full_Scale_Typedef accelFsr/* = MPU9250_Accel_Full_Scale_8g*/)
{
	this->gyroFsrReg = gyroFsr;
	switch (gyroFsrReg)
	{
	case MPU9250_Gyro_Full_Scale_250dps:
		this->gyroFsr = 250;
		break;
	case MPU9250_Gyro_Full_Scale_500dps:
		this->gyroFsr = 500;
		break;
	case MPU9250_Gyro_Full_Scale_1000dps:
		this->gyroFsr = 1000;
		break;
	case MPU9250_Gyro_Full_Scale_2000dps:
		this->gyroFsr = 2000;
		break;
	default:
		break;
	}
	this->accelFsrReg = accelFsr;
	switch (accelFsrReg)
	{
	case MPU9250_Accel_Full_Scale_2g:
		this->accelFsr = 2;
		break;
	case MPU9250_Accel_Full_Scale_4g:
		this->accelFsr = 4;
		break;
	case MPU9250_Accel_Full_Scale_8g:
		this->accelFsr = 8;
		break;
	case MPU9250_Accel_Full_Scale_16g:
		this->accelFsr = 16;
		break;
	default:
		break;
	}
	this->sampleRate = sampleRate;
	this->speed = speed;
	i2c->take_i2c_right(speed);
	i2c->begin(speed);
	i2c->release_i2c_right();

	u8 res = 0;
	writeByte(MPU9250_ADDR, MPU_PWR_MGMT1_REG, 0X80);//��λMPU9250
	delay_ms(100);  //��ʱ100ms
	writeByte(MPU9250_ADDR, MPU_PWR_MGMT1_REG, 0X00);//����MPU9250
	setGyroFsr(gyroFsr);					        	//�����Ǵ�����,��2000dps
	setAccelFsr(accelFsr);					       	 	//���ٶȴ�����,��2g
	setSampleRate(sampleRate);						       	 	//���ò�����50Hz
	writeByte(MPU9250_ADDR, MPU_INT_EN_REG, 0X00);   //�ر������ж�
	writeByte(MPU9250_ADDR, MPU_USER_CTRL_REG, 0X00);//I2C��ģʽ�ر�
	writeByte(MPU9250_ADDR, MPU_FIFO_EN_REG, 0X00);	//�ر�FIFO
	writeByte(MPU9250_ADDR, MPU_INTBP_CFG_REG, 0X82);//INT���ŵ͵�ƽ��Ч������bypassģʽ������ֱ�Ӷ�ȡ������
	res = readByte(MPU9250_ADDR, MPU_DEVICE_ID_REG);  //��ȡMPU6500��ID
	if (res == mpuID) //����ID��ȷ
	{
		writeByte(MPU9250_ADDR, MPU_PWR_MGMT1_REG, 0X01);  	//����CLKSEL,PLL X��Ϊ�ο�
		writeByte(MPU9250_ADDR, MPU_PWR_MGMT2_REG, 0X00);  	//���ٶ��������Ƕ�����
		setSampleRate(sampleRate);						       	//���ò�����Ϊ50Hz   
	}
	else return 1;

	res = readByte(AK8963_ADDR, MAG_WIA);    			//��ȡAK8963 ID   
	if (res == AK8963_ID)
	{
		writeByte(AK8963_ADDR, MAG_CNTL1, 0X11);		//����AK8963Ϊ���β���ģʽ
	}
	else return 1;

	return 0;
}

//u8 MPU9250::setGyroFsr(u8 fsr)
//{
//	return writeByte(MPU9250_ADDR, MPU_GYRO_CFG_REG, fsr << 3);//���������������̷�Χ
//}

u8 MPU9250::setGyroFsr(u8 fsr)
{
	return writeByte(MPU9250_ADDR, MPU_GYRO_CFG_REG, fsr << 3);//���������������̷�Χ
}

u8 MPU9250::setAccelFsr(u8 fsr)
{
	return writeByte(MPU9250_ADDR, MPU_ACCEL_CFG_REG, fsr << 3);//���ü��ٶȴ����������̷�Χ
}

u8 MPU9250::setLPF(u16 lpf)
{
	u8 data = 0;
	if (lpf >= 188)data = 1;
	else if (lpf >= 98)data = 2;
	else if (lpf >= 42)data = 3;
	else if (lpf >= 20)data = 4;
	else if (lpf >= 10)data = 5;
	else data = 6;
	return writeByte(MPU9250_ADDR, MPU_CFG_REG, data);//�������ֵ�ͨ�˲���
}

u8 MPU9250::setSampleRate(u16 rate)
{
	u8 data;
	if (rate > 1000)rate = 1000;
	if (rate < 4)rate = 4;
	data = 1000 / rate - 1;
	data = writeByte(MPU9250_ADDR, MPU_SAMPLE_RATE_REG, data);	//�������ֵ�ͨ�˲���
	return setLPF(rate / 2);	//�Զ�����LPFΪ�����ʵ�һ��
}

short MPU9250::getTemperature(void)
{
	u8 buf[2];
	short raw;
	float temp;
	readLen(MPU9250_ADDR, MPU_TEMP_OUTH_REG, 2, buf);
	raw = ((u16)buf[0] << 8) | buf[1];
	temp = 21 + ((double)raw) / 333.87;
	return temp * 100;
}

u8 MPU9250::getGyroscope(short *gx, short *gy, short *gz)
{
	u8 buf[6], res;
	res = readLen(MPU9250_ADDR, MPU_GYRO_XOUTH_REG, 6, buf);
	if (res == 0)
	{
		*gx = ((u16)buf[0] << 8) | buf[1];
		*gy = ((u16)buf[2] << 8) | buf[3];
		*gz = ((u16)buf[4] << 8) | buf[5];
	}
	return res;
}

u8 MPU9250::getAccelerometer(short *ax, short *ay, short *az)
{
	u8 buf[6], res;
	res = readLen(MPU9250_ADDR, MPU_ACCEL_XOUTH_REG, 6, buf);
	if (res == 0)
	{
		*ax = ((u16)buf[0] << 8) | buf[1];
		*ay = ((u16)buf[2] << 8) | buf[3];
		*az = ((u16)buf[4] << 8) | buf[5];
	}
	return res;
}

u8 MPU9250::getMagnetometer(short *mx, short *my, short *mz)
{
	u8 buf[6], res;
	res = readLen(AK8963_ADDR, MAG_XOUT_L, 6, buf);
	if (res == 0)
	{
		*mx = ((u16)buf[1] << 8) | buf[0];
		*my = ((u16)buf[3] << 8) | buf[2];
		*mz = ((u16)buf[5] << 8) | buf[4];
	}
	writeByte(AK8963_ADDR, MAG_CNTL1, 0X11); //AK8963ÿ�ζ����Ժ���Ҫ��������Ϊ���β���ģʽ
	return res;
}

u16 MPU9250::getSampleRate()
{
	return sampleRate;
}
