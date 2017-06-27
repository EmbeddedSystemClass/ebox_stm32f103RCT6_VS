#ifndef __MPU9250_H
#define __MPU9250_H

#include "ebox.h"
#include <math.h>

////////////////////////////////////////////////////////////////////////////////// 	
//���AD0��(9��)�ӵ�,IIC��ַΪ0X68(���������λ).
//�����V3.3,��IIC��ַΪ0X69(���������λ).
#define MPU6500_ADDRESS            0xD0  //MPU6500������IIC��ַ 0X68<<1
#define MPU6500_ID				0X71  	//MPU6500������ID
#define MPU6555_ID				0X73

//MPU9250�ڲ���װ��һ��AK8963������,��ַ��ID����:
#define AK8963_ADDRESS				0x18	//AK8963��I2C��ַ 0X0C<<1
#define AK8963_ID				0X48	//AK8963������ID


//AK8963���ڲ��Ĵ���
#define AK8963_WHO_AM_I		0x00	//AK8963������ID�Ĵ�����ַ should return 0x48
#define AK8963_INFO      0x01
#define AK8963_ST1       0x02  // data ready status bit 0
#define AK8963_XOUT_L    0x03  // data
#define AK8963_XOUT_H    0x04
#define AK8963_YOUT_L    0x05
#define AK8963_YOUT_H    0x06
#define AK8963_ZOUT_L    0x07
#define AK8963_ZOUT_H    0x08
#define AK8963_ST2       0x09  // Data overflow bit 3 and data read error status bit 2
#define AK8963_CNTL          	  	0X0A    // Power down (0000), single-measurement (0001), self-test (1000) and Fuse ROM (1111) modes on bits 3:0
#define AK8963_ASTC      0x0C  // Self test control
#define AK8963_I2CDIS    0x0F  // I2C disable
#define AK8963_ASAX      0x10  // Fuse ROM x-axis sensitivity adjustment value
#define AK8963_ASAY      0x11  // Fuse ROM y-axis sensitivity adjustment value
#define AK8963_ASAZ      0x12  // Fuse ROM z-axis sensitivity adjustment value

//MPU6500���ڲ��Ĵ���
#define MPU6500_SELF_TESTX_REG		0X0D	//�Լ�Ĵ���X
#define MPU6500_SELF_TESTY_REG		0X0E	//�Լ�Ĵ���Y
#define MPU6500_SELF_TESTZ_REG		0X0F	//�Լ�Ĵ���Z
#define MPU6500_SELF_TESTA_REG		0X10	//�Լ�Ĵ���A
#define MPU6500_SAMPLE_RATE_REG		0X19	//����Ƶ�ʷ�Ƶ��
#define MPU6500_CFG_REG				0X1A	//���üĴ���
#define MPU6500_GYRO_CFG_REG		0X1B	//���������üĴ���
#define MPU6500_ACCEL_CFG_REG		0X1C	//���ٶȼ����üĴ���
#define MPU6500_MOTION_DET_REG		0X1F	//�˶���ֵⷧ���üĴ���
#define MPU6500_FIFO_EN_REG			0X23	//FIFOʹ�ܼĴ���
#define MPU6500_I2CMST_CTRL_REG		0X24	//IIC�������ƼĴ���
#define MPU6500_I2CSLV0_ADDR_REG	0X25	//IIC�ӻ�0������ַ�Ĵ���
#define MPU6500_I2CSLV0_REG			0X26	//IIC�ӻ�0���ݵ�ַ�Ĵ���
#define MPU6500_I2CSLV0_CTRL_REG	0X27	//IIC�ӻ�0���ƼĴ���
#define MPU6500_I2CSLV1_ADDR_REG	0X28	//IIC�ӻ�1������ַ�Ĵ���
#define MPU6500_I2CSLV1_REG			0X29	//IIC�ӻ�1���ݵ�ַ�Ĵ���
#define MPU6500_I2CSLV1_CTRL_REG	0X2A	//IIC�ӻ�1���ƼĴ���
#define MPU6500_I2CSLV2_ADDR_REG	0X2B	//IIC�ӻ�2������ַ�Ĵ���
#define MPU6500_I2CSLV2_REG			0X2C	//IIC�ӻ�2���ݵ�ַ�Ĵ���
#define MPU6500_I2CSLV2_CTRL_REG	0X2D	//IIC�ӻ�2���ƼĴ���
#define MPU6500_I2CSLV3_ADDR_REG	0X2E	//IIC�ӻ�3������ַ�Ĵ���
#define MPU6500_I2CSLV3_REG			0X2F	//IIC�ӻ�3���ݵ�ַ�Ĵ���
#define MPU6500_I2CSLV3_CTRL_REG	0X30	//IIC�ӻ�3���ƼĴ���
#define MPU6500_I2CSLV4_ADDR_REG	0X31	//IIC�ӻ�4������ַ�Ĵ���
#define MPU6500_I2CSLV4_REG			0X32	//IIC�ӻ�4���ݵ�ַ�Ĵ���
#define MPU6500_I2CSLV4_DO_REG		0X33	//IIC�ӻ�4д���ݼĴ���
#define MPU6500_I2CSLV4_CTRL_REG	0X34	//IIC�ӻ�4���ƼĴ���
#define MPU6500_I2CSLV4_DI_REG		0X35	//IIC�ӻ�4�����ݼĴ���

#define MPU6500_I2CMST_STA_REG		0X36	//IIC����״̬�Ĵ���
#define MPU6500_INTBP_CFG_REG		0X37	//�ж�/��·���üĴ���
#define MPU6500_INT_EN_REG			0X38	//�ж�ʹ�ܼĴ���
#define MPU6500_INT_STA_REG			0X3A	//�ж�״̬�Ĵ���

#define MPU6500_ACCEL_XOUTH_REG		0X3B	//���ٶ�ֵ,X���8λ�Ĵ���
#define MPU6500_ACCEL_XOUTL_REG		0X3C	//���ٶ�ֵ,X���8λ�Ĵ���
#define MPU6500_ACCEL_YOUTH_REG		0X3D	//���ٶ�ֵ,Y���8λ�Ĵ���
#define MPU6500_ACCEL_YOUTL_REG		0X3E	//���ٶ�ֵ,Y���8λ�Ĵ���
#define MPU6500_ACCEL_ZOUTH_REG		0X3F	//���ٶ�ֵ,Z���8λ�Ĵ���
#define MPU6500_ACCEL_ZOUTL_REG		0X40	//���ٶ�ֵ,Z���8λ�Ĵ���

#define MPU6500_TEMP_OUTH_REG		0X41	//�¶�ֵ�߰�λ�Ĵ���
#define MPU6500_TEMP_OUTL_REG		0X42	//�¶�ֵ��8λ�Ĵ���

#define MPU6500_GYRO_XOUTH_REG		0X43	//������ֵ,X���8λ�Ĵ���
#define MPU6500_GYRO_XOUTL_REG		0X44	//������ֵ,X���8λ�Ĵ���
#define MPU6500_GYRO_YOUTH_REG		0X45	//������ֵ,Y���8λ�Ĵ���
#define MPU6500_GYRO_YOUTL_REG		0X46	//������ֵ,Y���8λ�Ĵ���
#define MPU6500_GYRO_ZOUTH_REG		0X47	//������ֵ,Z���8λ�Ĵ���
#define MPU6500_GYRO_ZOUTL_REG		0X48	//������ֵ,Z���8λ�Ĵ���

#define MPU6500_I2CSLV0_DO_REG		0X63	//IIC�ӻ�0���ݼĴ���
#define MPU6500_I2CSLV1_DO_REG		0X64	//IIC�ӻ�1���ݼĴ���
#define MPU6500_I2CSLV2_DO_REG		0X65	//IIC�ӻ�2���ݼĴ���
#define MPU6500_I2CSLV3_DO_REG		0X66	//IIC�ӻ�3���ݼĴ���

#define MPU6500_I2CMST_DELAY_REG	0X67	//IIC������ʱ����Ĵ���
#define MPU6500_SIGPATH_RST_REG		0X68	//�ź�ͨ����λ�Ĵ���
#define MPU6500_MDETECT_CTRL_REG	0X69	//�˶������ƼĴ���
#define MPU6500_USER_CTRL_REG		0X6A	//�û����ƼĴ���
#define MPU6500_PWR_MGMT1_REG		0X6B	//��Դ����Ĵ���1
#define MPU6500_PWR_MGMT2_REG		0X6C	//��Դ����Ĵ���2 
#define MPU6500_FIFO_CNTH_REG		0X72	//FIFO�����Ĵ����߰�λ
#define MPU6500_FIFO_CNTL_REG		0X73	//FIFO�����Ĵ����Ͱ�λ
#define MPU6500_FIFO_RW_REG			0X74	//FIFO��д�Ĵ���
#define MPU6500_DEVICE_ID_REG		0X75	//����ID�Ĵ���

typedef enum
{
	MPU6500_Model_6500,
	MPU6500_Model_6555
}MPU6500_Model_Typedef;

typedef enum
{
	MPU6500_Gyro_Full_Scale_250dps=0,
	MPU6500_Gyro_Full_Scale_500dps =1,
	MPU6500_Gyro_Full_Scale_1000dps = 2,
	MPU6500_Gyro_Full_Scale_2000dps = 3
}MPU6500_Gyro_Full_Scale_Typedef;

typedef enum
{
	MPU6500_Accel_Full_Scale_2g = 0,
	MPU6500_Accel_Full_Scale_4g = 1,
	MPU6500_Accel_Full_Scale_8g = 2,
	MPU6500_Accel_Full_Scale_16g = 3
}MPU6500_Accel_Full_Scale_Typedef;

class MPU9250
{
protected:
	I2c* i2c;
	uint32_t speed;
	u8 model;
	u8 mpuID;
	u16 sampleRate;
	u8 gyroFsrReg;
	u8 accelFsrReg;
	uint16_t gyroFsr, accelFsr;
	static const uint16_t gyroFsrList[];
	static const uint8_t accelFsrList[];

	//IICдһ���ֽ� 
	//devaddr:����IIC��ַ
	//reg:�Ĵ�����ַ
	//data:����
	//����ֵ:0,����
	//    ����,�������
	u8 writeByte(u8 addr, u8 reg, u8 data);

	//IIC��һ���ֽ� 
	//reg:�Ĵ�����ַ 
	//����ֵ:����������
	u8 readByte(u8 addr, u8 reg);

	//IIC������
	//addr:������ַ
	//reg:Ҫ��ȡ�ļĴ�����ַ
	//len:Ҫ��ȡ�ĳ���
	//buf:��ȡ�������ݴ洢��
	//����ֵ:0,����
	//    ����,�������
	u8 readBytes(u8 addr, u8 reg, u8 len, u8 *buf);

	//IIC����д
	//addr:������ַ 
	//reg:�Ĵ�����ַ
	//len:д�볤��
	//buf:������
	//����ֵ:0,����
	//    ����,�������
	u8 writeBytes(u8 addr, u8 reg, u8 len, u8 *buf);

public:
	MPU9250(I2c* i2c,MPU6500_Model_Typedef model=MPU6500_Model_6500);

	u8 begin(uint32_t speed = 400000, uint16_t sampleRate = 100,
		MPU6500_Gyro_Full_Scale_Typedef gyroFsr=MPU6500_Gyro_Full_Scale_2000dps, 
		MPU6500_Accel_Full_Scale_Typedef accelFsr = MPU6500_Accel_Full_Scale_8g);

	//����MPU9250�����Ǵ����������̷�Χ
	//fsr:0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
	//����ֵ:0,���óɹ�
	//    ����,����ʧ�� 
	u8 setGyroFsr(u8 fsr);

	//����MPU9250���ٶȴ����������̷�Χ
	//fsr:0,��2g;1,��4g;2,��8g;3,��16g
	//����ֵ:0,���óɹ�
	//    ����,����ʧ�� 
	u8 setAccelFsr(u8 fsr);

	//����MPU9250�����ֵ�ͨ�˲���
	//lpf:���ֵ�ͨ�˲�Ƶ��(Hz)
	//����ֵ:0,���óɹ�
	//    ����,����ʧ�� 
	u8 setLPF(u16 lpf);

	//����MPU9250�Ĳ�����(�ٶ�Fs=1KHz)
	//rate:4~1000(Hz)
	//����ֵ:0,���óɹ�
	//    ����,����ʧ�� 
	u8 setSampleRate(u16 sampleRate);

	//�õ��¶�ֵ
	//����ֵ:�¶�ֵ(������100��)
	float getTemperature(void);

	//�õ�������ֵ(ԭʼֵ)
	//gx,gy,gz:������x,y,z���ԭʼ����(������)
	//����ֵ:0,�ɹ�
	//    ����,�������
	u8 getGyroscope(short *gx, short *gy, short *gz);
	u8 getGyroscope(float *gx, float *gy, float *gz);

	//�õ����ٶ�ֵ(ԭʼֵ)
	//gx,gy,gz:������x,y,z���ԭʼ����(������)
	//����ֵ:0,�ɹ�
	//    ����,�������
	u8 getAccelerometer(short *ax, short *ay, short *az);
	u8 getAccelerometer(float *ax, float *ay, float *az);

	//�õ�������ֵ(ԭʼֵ)
	//mx,my,mz:������x,y,z���ԭʼ����(������)
	//����ֵ:0,�ɹ�
	//    ����,�������
	u8 getMagnetometer(short *mx, short *my, short *mz);
	u8 getMagnetometer(float *mx, float *my, float *mz);

	//��ȡ������
	u16 getSampleRate();

};



class MahonyAHRS9
{
protected:
	float q0, q1, q2, q3;	// quaternion of sensor frame relativ
	float exInt, eyInt, ezInt;
	float Ki, Kp;
	float halfT;
	float sampleFreq;

	//������ƽ����
	float invSqrt(float x)
	{
		float halfx = 0.5f * x;
		float y = x;
		long i = *(long*)&y;
		i = 0x5f3759df - (i >> 1);
		y = *(float*)&i;
		y = y * (1.5f - (halfx * y * y));
		return y;
	}


public:
	MahonyAHRS9(float sampleFreq = 100, float kp = 10, float ki = 0) :
		Kp(kp),Ki(ki),
		q0(1), q1(0), q2(0), q3(0),
		exInt(0), eyInt(0), ezInt(0)
	{
		setSampleRate(sampleFreq);
	}

	virtual void update(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz)
	{
		float norm;
		float q0q0, q0q1, q0q2, q0q3, q1q1, q1q2, q1q3, q2q2, q2q3, q3q3;
		float hx, hy, hz, bx, bz;
		float vx, vy, vz, wx, wy, wz;
		float ex, ey, ez;
		float qa, qb, qc;
		if (!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f)))
		{

			// Normalise accelerometer measurement
			//�������ļ��ٶȲ���ֵ
			norm = invSqrt(ax * ax + ay * ay + az * az);
			ax *= norm;
			ay *= norm;
			az *= norm;

			// Normalise magnetometer measurement
			//�������Ĵ����Ʋ���ֵ
			norm = invSqrt(mx * mx + my * my + mz * mz);
			mx *= norm;
			my *= norm;
			mz *= norm;

			//Ԥ�Ƚ�����Ԫ���������㣬�Ա����ظ����������Ч�����⡣
			// Auxiliary variables to avoid repeated arithmetic
			q0q0 = q0 * q0;
			q0q1 = q0 * q1;
			q0q2 = q0 * q2;
			q0q3 = q0 * q3;
			q1q1 = q1 * q1;
			q1q2 = q1 * q2;
			q1q3 = q1 * q3;
			q2q2 = q2 * q2;
			q2q3 = q2 * q3;
			q3q3 = q3 * q3;

			hx = 2.0f * (mx * (0.5f - q2q2 - q3q3) + my * (q1q2 - q0q3) + mz * (q1q3 + q0q2));
			hy = 2.0f * (mx * (q1q2 + q0q3) + my * (0.5f - q1q1 - q3q3) + mz * (q2q3 - q0q1));
			hz = 2.0f * (mx * (q1q3 - q0q2) + my * (q2q3 + q0q1) + mz * (0.5f - q1q1 - q2q2));
			bx = sqrt(hx * hx + hy * hy);
			bz = hz;

			vx = q1q3 - q0q2;
			vy = q0q1 + q2q3;
			vz = q0q0 - 0.5f + q3q3;
			wx = bx * (0.5f - q2q2 - q3q3) + bz * (q1q3 - q0q2);
			wy = bx * (q1q2 - q0q3) + bz * (q0q1 + q2q3);
			wz = bx * (q0q2 + q1q3) + bz * (0.5f - q1q1 - q2q2);

			//ʹ�ò�������������͵ش���
			// Error is sum of cross product between estimated direction and measured direction of field vectors
			ex = (ay * vz - az * vy) + (my * wz - mz * wy);
			ey = (az * vx - ax * vz) + (mz * wx - mx * wz);
			ez = (ax * vy - ay * vx) + (mx * wy - my * wx);

			//�������л���
			exInt += Ki * ex * (1.0f / sampleFreq); // integral error scaled by Ki
			eyInt += Ki * ey * (1.0f / sampleFreq);
			ezInt += Ki * ez * (1.0f / sampleFreq);

			//����ʵ�ļ��ٶȲ���ֵ��һ�����������������ǣ�0������ȫ���������ǣ�1������ȫ���μ��ٶȣ�����1��
			gx = gx + Kp*ex + exInt;
			gy = gy + Kp*ey + eyInt;
			gz = gz + Kp*ez + ezInt;

			qa = q0;
			qb = q1;
			qc = q2;
			q0 += (-qb * gx - qc * gy - q3 * gz)*halfT;
			q1 += (qa * gx + qc * gz - q3 * gy)*halfT;
			q2 += (qa * gy - qb * gz + q3 * gx)*halfT;
			q3 += (qa * gz + qb * gy - qc * gx)*halfT;

			// Normalise quaternion

			norm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
			q0 *= norm;
			q1 *= norm;
			q2 *= norm;
			q3 *= norm;
			
		}

	}

	void setSampleRate(float sampleRate)
	{
		this->sampleFreq = sampleRate;
		halfT = 1 / (2 * sampleFreq);
	}

	virtual void getAngle(float* Pitch, float* Roll, float* Yaw)
	{
		//��Ԫ��ת����ŷ����
		*Pitch = asin(2 * q0*q2 - 2 * q1*q3) / 3.14 * 180;
		*Roll = atan2(2 * q0*q1 + 2 * q2*q3, 1 - 2 * q1*q1 - 2 * q2*q2) / 3.14 * 180;
		*Yaw = atan2(2 * q0*q3 + 2 * q1*q2, 1 - 2 * q2*q2 - 2 * q3*q3) / 3.14 * 180;
	}

	virtual void getQuaternion(float* q0, float* q1, float* q2, float* q3)
	{
		*q0 = this->q0;
		*q1 = this->q1;
		*q2 = this->q2;
		*q3 = this->q3;
	}
};

class MPU9250AHRS :public MPU9250, private MahonyAHRS9
{
protected:
	void update()
	{
		float g[3], a[3], m[3];
		getGyroscope(g, g + 1, g + 2);
		getAccelerometer(a, a + 1, a + 2);
		getMagnetometer(m, m + 1, m + 2);
		MahonyAHRS9::update(
			g[0], g[1], g[2],
			a[0], a[1], a[2],
			m[0], m[1], m[2]);
	}
public:
	MPU9250AHRS(I2c* i2c, MPU6500_Model_Typedef model = MPU6500_Model_6500) :
		MPU9250(i2c, model),
		MahonyAHRS9(100, 10, 0.05)
	{

	}

	void begin(uint32_t speed = 400000, uint16_t sampleRate = 100,
		MPU6500_Gyro_Full_Scale_Typedef gyroFsr = MPU6500_Gyro_Full_Scale_2000dps,
		MPU6500_Accel_Full_Scale_Typedef accelFsr = MPU6500_Accel_Full_Scale_8g)
	{
		MPU9250::begin(speed, sampleRate, gyroFsr, accelFsr);
		MahonyAHRS9::setSampleRate(sampleRate);
	}



	virtual void getAngle(float* pitch, float* roll, float* yaw)
	{
		update();
		MahonyAHRS9::getAngle(pitch, roll, yaw);
	}

	virtual void getQuaternion(float* q0, float* q1, float* q2, float* q3)
	{
		update();
		MahonyAHRS9::getQuaternion(q0, q1, q2, q3);
	}
};



#endif
