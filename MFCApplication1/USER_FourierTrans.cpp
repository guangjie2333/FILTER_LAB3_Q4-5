#include "pch.h"
#include "USER_FourierTrans.h"
// FourierTrans.cpp: implementation of the FourierTrans class.
//
//////////////////////////////////////////////////////////////////////

#include "math.h"
#define PI 3.1415926

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FourierTrans::FourierTrans()
{

}

FourierTrans::~FourierTrans()
{

}


/***********************************************************************
* �������ƣ�Fourier()
*���������� ��
*����ֵ�� ��
*˵����������ͼ����п��ٸ���Ҷ�任��Ҫ������ͼ��Ŀ�͸߱�����2���ݴη�
***********************************************************************/
void FourierTrans::Fourier()
{

	//�������ͼ�񻺳���������ʼ��Ϊ0
	m_pImgDataOut = new unsigned char[m_imgWidthOut * m_imgHeightOut];
	memset(m_pImgDataOut, 0, m_imgWidthOut * m_imgHeightOut);

	//���븵��Ҷ������������ʼ��Ϊ0
	m_pFFTBuf = new ComplexNumber[m_imgWidthOut * m_imgHeightOut];
	memset(m_pFFTBuf, 0, sizeof(ComplexNumber) * m_imgWidthOut * m_imgHeightOut);

	//����ͼ�����ݽ��ж�ά����Ҷ�任
//	ImageFFt2D(m_pImgData, m_imgWidthOut, m_imgHeightOut, m_pImgDataOut);
}

void FourierTrans::RevFourier()
{
	//ͼ��Ķ�ά����Ҷ���任,�任������ǻָ���ԭͼ�񣬴���m_pImgDataOut
	ImageRevFFt2D(m_pImgDataOut, m_imgWidthOut, m_imgHeightOut);
}



void FourierTrans::ImageFFt1D(ComplexNumber* arrayBuf, int n)
{
	//ѭ������
	int i, k, r;

	//������ʱ����������buf1������Ϊn
	ComplexNumber* buf1 = new ComplexNumber[n];

	//��arrayBuf������buf1
	memcpy(buf1, arrayBuf, sizeof(ComplexNumber) * n);

	//������ʱ����������buf2������Ϊn
	ComplexNumber* buf2 = new ComplexNumber[n];

	//��arrayBuf����Ԫ�ػ�2��ȡ����������
	//��0��1��2��3��4��5��6��7�˵����жԵ������0��4��2��6��1��5��3��7
	int t1, t2;
	for (r = 1; pow(2, r) < n; r++)
	{
		t1 = (int)pow(2, r);
		t2 = (int)pow(2, r - 1);
		for (k = 0; k < t1; k++)
		{
			for (i = 0; i < n / t1; i++)
			{
				buf2[k * n / t1 + i].real = buf1[k / 2 * n / t2 + i * 2 + k % 2].real;
				buf2[k * n / t1 + i].imag = buf1[k / 2 * n / t2 + i * 2 + k % 2].imag;
			}
		}
		memcpy(buf1, buf2, sizeof(ComplexNumber) * n);
	}


	//���õ����㷨���п��ٸ���Ҷ�任
	//buf1�ǵ�r�������룬buf2��ŵ�r�������
	float c, s;
	for (r = 1; pow(2, r) <= n; r++)
	{
		t1 = (int)pow(2, r);
		for (k = 0; k < n / t1; k++)
		{
			for (i = t1 / 2; i < t1; i++)
			{
				//��Ȩ����
				c = (float)cos(-2 * PI * (i - t1 / 2) / t1);
				s = (float)sin(-2 * PI * (i - t1 / 2) / t1);
				buf1[k * t1 + i].real = buf2[k * t1 + i].real * c - buf2[k * t1 + i].imag * s;
				buf1[k * t1 + i].imag = buf2[k * t1 + i].imag * c + buf2[k * t1 + i].real * s;
			}
		}
		for (k = 0; k < n / t1; k++)
		{
			for (i = 0; i < t1 / 2; i++)
			{
				buf2[k * t1 + i].real = buf1[k * t1 + i].real + buf1[k * t1 + i + t1 / 2].real;
				buf2[k * t1 + i].imag = buf1[k * t1 + i].imag + buf1[k * t1 + i + t1 / 2].imag;
			}
			for (i = t1 / 2; i < t1; i++)
			{
				buf2[k * t1 + i].real = buf1[k * t1 + i - t1 / 2].real - buf1[k * t1 + i].real;
				buf2[k * t1 + i].imag = buf1[k * t1 + i - t1 / 2].imag - buf1[k * t1 + i].imag;
			}
		}

		//��r�����������buf1,��Ϊ��һ������������
		memcpy(buf1, buf2, sizeof(ComplexNumber) * n);
	}
	//����Ҷ�任�Ľ������arrayBuf
	memcpy(arrayBuf, buf2, sizeof(ComplexNumber) * n);

	//�ͷŻ�����
	delete[]buf2;
	delete[]buf1;

}

/***********************************************************************
* �������ƣ�ImageFFt2D()
* ����������unsigned char* imgBuf  -ͼ������ָ��
*           int width  -ͼ���
*           int height  -ͼ���
*           unsigned char *imgBufOut  -����Ҷ�任������ͼ��
* ����ֵ��  ��
* ˵����ͼ�����ݶ�ά���ٸ���Ҷ�任��ͼ�����ݱ�ɸ�����ʽ,��������һά����
*      ����Ҷ�任,�任���Ƶ����ͼ����ʽ����imgBufOut���˴�Ҫ��ͼ���͸�
*      ��Ϊ2���ݴη�
***********************************************************************/
void FourierTrans::ImageFFt2D(unsigned char* imgBuf, int width, int height,
	unsigned char* imgBufOut)
{
	//ѭ������
	int i, j, u, v;

	//ͼ�����ݱ�ɸ������ʹ���m_pFFTBuf
	for (i = 0; i < width * height; i++) {
		m_pFFTBuf[i].real = imgBuf[i];
		m_pFFTBuf[i].imag = 0;
	}

	//����ComplexNumber�ṹ������,����Ϊheight
	ComplexNumber* array = new ComplexNumber[height];

	//������һά���ٸ���Ҷ�任
	for (u = 0; u < width; u++)
	{
		for (v = 0; v < height; v++)
		{
			array[v].real = m_pFFTBuf[v * width + u].real;
			array[v].imag = m_pFFTBuf[v * width + u].imag;
		}
		ImageFFt1D(array, height);
		for (v = 0; v < height; v++) {
			m_pFFTBuf[v * width + u].real = array[v].real;
			m_pFFTBuf[v * width + u].imag = array[v].imag;
		}
	}
	delete[]array;

	//�ٺ���һά���ٸ���Ҷ�任
	for (v = 0; v < height; v++)
	{
		ImageFFt1D(m_pFFTBuf + v * width, width);
	}

	//��Ƶ��ͼ��ͼ����ʽ����imgBufOut
	float t;
	int i0, j0;
	for (i = 0; i < height; i++)
	{
		//i0 = i;
		//j0 = j;
		for (j = 0; j < width; j++)
		{
			if (i < height / 2)
				i0 = i + height / 2;
			else
				i0 = i - height / 2;
			if (j < width / 2)
				j0 = j + width / 2;
			else
				j0 = j - width / 2;

			t = (float)sqrt(m_pFFTBuf[i0 * width + j0].real * m_pFFTBuf[i0 * width + j0].real
				+ m_pFFTBuf[i0 * width + j0].imag * m_pFFTBuf[i0 * width + j0].imag);
			t = t / 500;
			if (t > 255)
				imgBufOut[i * width + j] = 255;
			else
				imgBufOut[i * width + j] = (unsigned char)t;
		}
	}

}



/***********************************************************************
* �������ƣ�ImageRevFFt2D()
*���������� unsigned char* imgBufOut  -���ͼ������ָ��
*           int width  -ͼ���
*           int height  -ͼ���
*����ֵ��   ��
*˵�����Ը���Ҷ�任������m_pFFTBuf�������,��������һά���ٸ���Ҷ���任,
*      �任���Ƶ�׼���ԭͼ��Ļָ�����,���ָ����ݴ���imgBufOut���˴�Ҫ��
*      ͼ���͸߾�Ϊ2���ݴη�
***********************************************************************/
void FourierTrans::ImageRevFFt2D(unsigned char* imgBufOut, int width, int height)
{
	//������Ҷ�任������Ϊ��,��ʧ�ܷ���
	if (!m_pFFTBuf)
		return;

	//����
	int i, u, v;

	//��������Ҷ���任
	ComplexNumber* array = new ComplexNumber[height];
	for (u = 0; u < width; u++)
	{
		for (v = 0; v < height; v++)
		{
			array[v].real = m_pFFTBuf[v * width + u].real;
			array[v].imag = m_pFFTBuf[v * width + u].imag;
		}
		ImageRevFFt1D(array, height);
		for (v = 0; v < height; v++)
		{
			m_pFFTBuf[v * width + u].real = array[v].real;
			m_pFFTBuf[v * width + u].imag = array[v].imag;
		}
	}
	delete[]array;

	//�ٺ�����Ҷ���任
	for (v = 0; v < height; v++)
	{
		ImageRevFFt1D(m_pFFTBuf + v * width, width);
	}

	//��m_pFFTBuf�ķ�����,�ָ�ͼ�����imgBufOut
	float t;
	for (i = 0; i < width * height; i++)
	{
		t = (float)sqrt(m_pFFTBuf[i].real * m_pFFTBuf[i].real
			+ m_pFFTBuf[i].imag * m_pFFTBuf[i].imag);
		if (t > 255)
			imgBufOut[i] = 255;
		else imgBufOut[i] = (unsigned char)t;
	}
}

/***********************************************************************
* �������ƣ�ImageRevFFt1D()
* ����������ComplexNumber *arrayBuf  -�����ṹ����������
*           int n  -����arrayBuf�ĳ��ȣ�����Ϊ2���ݴη�
* ����ֵ��  ��
*˵�����Ը����ṹ������arrayBuf����һά���ٸ���Ҷ���任���任��Ľ����
*      ���arrayBuf��
***********************************************************************/
void FourierTrans::ImageRevFFt1D(ComplexNumber* arrayBuf, int n)
{
	//����
	int i;

	//������arrayBuf����
	for (i = 0; i < n; i++)
		arrayBuf[i].imag = -arrayBuf[i].imag;

	//һά���ٸ���Ҷ�任
	ImageFFt1D(arrayBuf, n);

	//ʱ���������������N
	for (i = 0; i < n; i++) {
		arrayBuf[i].real = arrayBuf[i].real / n;
		arrayBuf[i].imag = -arrayBuf[i].imag / n;
	}

}
