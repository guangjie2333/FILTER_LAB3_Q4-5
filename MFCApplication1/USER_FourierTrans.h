// FourierTrans.h: interface for the FourierTrans class.
//
//copy from others

#if !defined(AFX_FOURIERTRANS_H__112C5DA9_2D2E_474D_BDE0_43B6ECC89A73__INCLUDED_)
#define AFX_FOURIERTRANS_H__112C5DA9_2D2E_474D_BDE0_43B6ECC89A73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//复数类型结构体
struct ComplexNumber
{
	float imag;// imaginary虚部
	float real;//实部
};


class FourierTrans
{

public:

	//输出图像每像素位数
	int m_nBitCountOut;

	//输出图像位图数据指针
	unsigned char* m_pImgDataOut;

	//输出图像的宽
	int m_imgWidthOut;

	//输出图像的高
	int m_imgHeightOut;

	//输出图像颜色表长度
	int m_nColorTableLengthOut;

	//傅立叶变换缓冲区
	ComplexNumber* m_pFFTBuf;

	//图像是否被扩展的标志变量
	bool m_isExpanded;
public:
	FourierTrans();
	virtual ~FourierTrans();
	//以像素为单位返回输出图像的宽和高
	CSize GetDimensions();


	//图像傅立叶变换
	void Fourier();

	//傅立叶反变换
	void RevFourier();

public:
	//一维快速傅立叶正变换
	void ImageFFt1D(ComplexNumber* arrayBuf, int n);

	//一维快速傅立叶反变换
	void ImageRevFFt1D(ComplexNumber* arrayBuf, int n);

	//二维快速傅立叶变换
	void ImageFFt2D(unsigned char* imgBuf, int width, int height, unsigned char* imgBufOut);

	//二维快速傅立叶变换
	void ImageRevFFt2D(unsigned char* imgBufOut, int width, int height);
};

#endif // !defined(AFX_FOURIERTRANS_H__112C5DA9_2D2E_474D_BDE0_43B6ECC89A73__INCLUDED_)
