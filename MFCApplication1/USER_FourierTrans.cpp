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
* 函数名称：Fourier()
*函数参数： 无
*返回值： 无
*说明：对输入图像进行快速傅立叶变换，要求输入图像的宽和高必须是2的幂次方
***********************************************************************/
void FourierTrans::Fourier()
{

	//申请输出图像缓冲区，并初始化为0
	m_pImgDataOut = new unsigned char[m_imgWidthOut * m_imgHeightOut];
	memset(m_pImgDataOut, 0, m_imgWidthOut * m_imgHeightOut);

	//申请傅立叶缓冲区，并初始化为0
	m_pFFTBuf = new ComplexNumber[m_imgWidthOut * m_imgHeightOut];
	memset(m_pFFTBuf, 0, sizeof(ComplexNumber) * m_imgWidthOut * m_imgHeightOut);

	//输入图像数据进行二维傅立叶变换
//	ImageFFt2D(m_pImgData, m_imgWidthOut, m_imgHeightOut, m_pImgDataOut);
}

void FourierTrans::RevFourier()
{
	//图像的二维傅立叶反变换,变换结果即是恢复的原图像，存入m_pImgDataOut
	ImageRevFFt2D(m_pImgDataOut, m_imgWidthOut, m_imgHeightOut);
}



void FourierTrans::ImageFFt1D(ComplexNumber* arrayBuf, int n)
{
	//循环变量
	int i, k, r;

	//申请临时复数缓冲区buf1，长度为n
	ComplexNumber* buf1 = new ComplexNumber[n];

	//将arrayBuf拷贝进buf1
	memcpy(buf1, arrayBuf, sizeof(ComplexNumber) * n);

	//申请临时复数缓冲区buf2，长度为n
	ComplexNumber* buf2 = new ComplexNumber[n];

	//将arrayBuf数组元素基2抽取并重新排列
	//若0、1、2、3、4、5、6、7八点序列对调后变作0、4、2、6、1、5、3、7
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


	//采用蝶型算法进行快速傅立叶变换
	//buf1是第r级的输入，buf2存放第r级的输出
	float c, s;
	for (r = 1; pow(2, r) <= n; r++)
	{
		t1 = (int)pow(2, r);
		for (k = 0; k < n / t1; k++)
		{
			for (i = t1 / 2; i < t1; i++)
			{
				//加权因子
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

		//第r级的输出存入buf1,作为下一级的输入数据
		memcpy(buf1, buf2, sizeof(ComplexNumber) * n);
	}
	//傅立叶变换的结果存入arrayBuf
	memcpy(arrayBuf, buf2, sizeof(ComplexNumber) * n);

	//释放缓冲区
	delete[]buf2;
	delete[]buf1;

}

/***********************************************************************
* 函数名称：ImageFFt2D()
* 函数参数：unsigned char* imgBuf  -图像数据指针
*           int width  -图像宽
*           int height  -图像高
*           unsigned char *imgBufOut  -傅立叶变换后的输出图像
* 返回值：  无
* 说明：图像数据二维快速傅立叶变换将图像数据变成复数形式,进行两个一维快速
*      傅立叶变换,变换后的频谱以图像形式存入imgBufOut，此处要求图像宽和高
*      都为2的幂次方
***********************************************************************/
void FourierTrans::ImageFFt2D(unsigned char* imgBuf, int width, int height,
	unsigned char* imgBufOut)
{
	//循环变量
	int i, j, u, v;

	//图像数据变成复数类型存入m_pFFTBuf
	for (i = 0; i < width * height; i++) {
		m_pFFTBuf[i].real = imgBuf[i];
		m_pFFTBuf[i].imag = 0;
	}

	//申请ComplexNumber结构体数组,长度为height
	ComplexNumber* array = new ComplexNumber[height];

	//先纵向一维快速傅立叶变换
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

	//再横向一维快速傅立叶变换
	for (v = 0; v < height; v++)
	{
		ImageFFt1D(m_pFFTBuf + v * width, width);
	}

	//将频谱图以图像形式存入imgBufOut
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
* 函数名称：ImageRevFFt2D()
*函数参数： unsigned char* imgBufOut  -输出图像数据指针
*           int width  -图像宽
*           int height  -图像高
*返回值：   无
*说明：对傅立叶变换缓冲区m_pFFTBuf里的数据,进行两个一维快速傅立叶反变换,
*      变换后的频谱即是原图像的恢复数据,将恢复数据存入imgBufOut，此处要求
*      图像宽和高均为2的幂次方
***********************************************************************/
void FourierTrans::ImageRevFFt2D(unsigned char* imgBufOut, int width, int height)
{
	//若傅立叶变换缓冲区为空,则失败返回
	if (!m_pFFTBuf)
		return;

	//变量
	int i, u, v;

	//先纵向傅立叶反变换
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

	//再横向傅立叶反变换
	for (v = 0; v < height; v++)
	{
		ImageRevFFt1D(m_pFFTBuf + v * width, width);
	}

	//求m_pFFTBuf的幅度谱,恢复图像存入imgBufOut
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
* 函数名称：ImageRevFFt1D()
* 函数参数：ComplexNumber *arrayBuf  -复数结构体类型数组
*           int n  -数组arrayBuf的长度，必须为2的幂次方
* 返回值：  无
*说明：对复数结构体数组arrayBuf进行一维快速傅立叶反变换，变换后的结果仍
*      存回arrayBuf中
***********************************************************************/
void FourierTrans::ImageRevFFt1D(ComplexNumber* arrayBuf, int n)
{
	//变量
	int i;

	//对数组arrayBuf求共轭
	for (i = 0; i < n; i++)
		arrayBuf[i].imag = -arrayBuf[i].imag;

	//一维快速傅立叶变换
	ImageFFt1D(arrayBuf, n);

	//时域数据求共轭，并除以N
	for (i = 0; i < n; i++) {
		arrayBuf[i].real = arrayBuf[i].real / n;
		arrayBuf[i].imag = -arrayBuf[i].imag / n;
	}

}
