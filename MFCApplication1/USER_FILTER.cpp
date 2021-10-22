#include "pch.h"
#include "USER_FILTER.h"

/*
********************************************************************************
********************************************************************************
*                               构造&析构函数
********************************************************************************
********************************************************************************
*/

/*
******************************************************************************
* 函数名称:	USER_FILTER
* 函数功能: 构造（初始化）函数
* 输入参数:	array ：bmp图像的RGB三通道数据, h ：图像高  w:图像宽
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-19日
* 注    意:
*******************************************************************************
*/
USER_FILTER::USER_FILTER(BYTE* array, int  h, int  w)
{
	pixelArray = array;
	high = h;
	width = w;
	ArraySize = high * width;

	R_array = (BYTE*)new char[ArraySize / 3 + 1];
	G_array = (BYTE*)new char[ArraySize / 3 + 1];
	B_array = (BYTE*)new char[ArraySize / 3 + 1];
}
/*
******************************************************************************
* 函数名称:	~USER_HIS_EQU
* 函数功能: 析构函数，将动态开辟的空间清除
* 输入参数:	none
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-19日
* 注    意:
*******************************************************************************
*/
USER_FILTER::~USER_FILTER()
{
	delete[] R_array;
	delete[] G_array;
	delete[] B_array;
}


/*
********************************************************************************
********************************************************************************
*                               接口函数
********************************************************************************
********************************************************************************
*/

/*
******************************************************************************
* 函数名称:	LowFilter
* 函数功能: 实现一幅图像的低通滤波
* 输入参数: none
* 输出参数:	none
* 返 回 值: void
* 创建日期: 2021年-10月-22日
* 注    意:
*******************************************************************************
*/
void USER_FILTER::LowFilter()
{
	//分离RGB分别做滤波
	SeparateRGB();
	Convolution(0);//0代表低通滤波卷积
	UnionRGB();
}

/*
******************************************************************************
* 函数名称:	HighFilter
* 函数功能: 实现一幅图像的高通滤波
* 输入参数: none
* 输出参数:	none
* 返 回 值: void
* 创建日期: 2021年-10月-22日
* 注    意:
*******************************************************************************
*/
void USER_FILTER::HighFilter()
{
	//分离RGB分别做滤波
	SeparateRGB();
	Convolution(1);//1代表低通滤波卷积
	UnionRGB();
}

/*
******************************************************************************
* 函数名称:	MidFilter
* 函数功能: 实现一幅图像的中值滤波
* 输入参数: none
* 输出参数:	none
* 返 回 值: void
* 创建日期: 2021年-10月-22日
* 注    意:
*******************************************************************************
*/
void USER_FILTER::MidFilter()
{

}

/*
******************************************************************************
* 函数名称:	MaxFilter
* 函数功能: 实现一幅图像的最大值滤波
* 输入参数: none
* 输出参数:	none
* 返 回 值: void
* 创建日期: 2021年-10月-22日
* 注    意:
*******************************************************************************
*/
void USER_FILTER::MaxFilter()
{

}

/*
******************************************************************************
* 函数名称:	MinFilter
* 函数功能: 实现一幅图像的最小值滤波
* 输入参数: none
* 输出参数:	none
* 返 回 值: void
* 创建日期: 2021年-10月-22日
* 注    意:
*******************************************************************************
*/
void USER_FILTER::MinFilter()
{

}


/*
********************************************************************************
********************************************************************************
*                               功能函数
********************************************************************************
********************************************************************************
*/


/*
******************************************************************************
* 函数名称:	SeparateRGB
* 函数功能: 分离RGB分量
* 输入参数:	array ：bmp图像的RGB三通道数据, ArraySize：array数据大小
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-19日
* 注    意:
*******************************************************************************
*/

void USER_FILTER::SeparateRGB()
{
	int j = 0;
	for (int i = 0; i < ArraySize; i = i + 3)
	{
		R_array[j] = pixelArray[i + 2];
		G_array[j] = pixelArray[i + 1];
		B_array[j] = pixelArray[i + 0];

		j++;
	}
}

/*
******************************************************************************
* 函数名称:	UnionRGB
* 函数功能: RGB均衡化后的分量整合
* 输入参数: array : 图像数据   ArraySize：数据大小
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-19日
* 注    意:
*******************************************************************************
*/
void USER_FILTER::UnionRGB()
{
	int j = 0;
	for (int i = 0; i < ArraySize; i = i + 3)
	{
		pixelArray[i + 2] = R_array[j];
		pixelArray[i + 1] = G_array[j];
		pixelArray[i + 0] = B_array[j];

		j++;
	}
}

/*
******************************************************************************
* 函数名称:	Convolution
* 函数功能: RGB 实现图像卷积
* 输入参数: flag ： 0 低通滤波模板卷积 
*				    1 高通滤波模板卷积 
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-22日
* 注    意:
*******************************************************************************
*/
void USER_FILTER::Convolution(int flag)
{
	//动态建立二维数组
	BYTE** matrixR;
	BYTE** matrixG;
	BYTE** matrixB;
	matrixR = new BYTE * [high];
	matrixG = new BYTE * [high];
	matrixB = new BYTE * [high];
	for (int j = 0; j < high; j++)
	{
		matrixR[j] = new BYTE[width];
		matrixG[j] = new BYTE[width];
		matrixB[j] = new BYTE[width];
	}

	//初始化
	int k = 0;
	for (int i = 0; i < high; i++)
	{
		for (int j = 0; j < width; j++)
		{
			matrixR[i][j] = R_array[k];
			matrixG[i][j] = G_array[k];
			matrixB[i][j] = B_array[k];
			k++;
		}
	}

	//模板卷积
	switch (flag)
	{
		case 0 :
			DealLowConvolution(matrixR); //其实用一个函数实现也可以，但是我想保留函数的纯粹性
			DealLowConvolution(matrixG);
			DealLowConvolution(matrixB);
			break;
		case 1 :
			DealHighConvolution(matrixR);
			DealHighConvolution(matrixG);
			DealHighConvolution(matrixB);
			break;
		default:
			break;
	}

	//卷积结果回传
    k = 0;
	for (int i = 0; i < high; i++)
	{
		for (int j = 0; j < width; j++)
		{
			R_array[k] = matrixR[i][j];
			G_array[k] = matrixG[i][j];
			B_array[k] = matrixB[i][j];
			k++;
		}
	}


	//释放
	for (int j = 0; j < high; j++)
	{
		delete[] matrixR[j];
		delete[] matrixG[j];
		delete[] matrixB[j];
	}
	delete[] matrixR;
	delete[] matrixG;
	delete[] matrixB;
}

/*
******************************************************************************
* 函数名称:	DealLowConvolution
* 函数功能: 处理低通滤波
* 输入参数:  matrix：二维矩阵
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-22日
* 注    意:
*******************************************************************************
*/
void USER_FILTER :: DealLowConvolution(BYTE** matrix)
{
	for (int i = 1; i < high - 1 ; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			matrix[i][j] =(BYTE) matrix[i - 1][j - 1] * lowFilterTemplate[0] +
								 matrix[i - 1][j - 0] * lowFilterTemplate[1] +
								 matrix[i - 1][j + 1] * lowFilterTemplate[2] +
								 matrix[i - 0][j - 1] * lowFilterTemplate[3] +
								 matrix[i - 0][j - 0] * lowFilterTemplate[4] +
								 matrix[i - 0][j + 1] * lowFilterTemplate[5] +
								 matrix[i + 1][j - 1] * lowFilterTemplate[6] +
								 matrix[i + 1][j - 0] * lowFilterTemplate[7] +
								 matrix[i + 1][j + 1] * lowFilterTemplate[8] ;
		}
	}
}

/*
******************************************************************************
* 函数名称:	DealHighConvolution
* 函数功能: 处理高通滤波
* 输入参数:  matrix：二维矩阵
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-22日
* 注    意:
*******************************************************************************
*/
void USER_FILTER::DealHighConvolution(BYTE** matrix)
{
	for (int i = 1; i < high - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			matrix[i][j] = (BYTE)matrix[i - 1][j - 1] * HighFilterTemplate[0] +
								 matrix[i - 1][j - 0] * HighFilterTemplate[1] +
								 matrix[i - 1][j + 1] * HighFilterTemplate[2] +
								 matrix[i - 0][j - 1] * HighFilterTemplate[3] +
								 matrix[i - 0][j - 0] * HighFilterTemplate[4] +
								 matrix[i - 0][j + 1] * HighFilterTemplate[5] +
								 matrix[i + 1][j - 1] * HighFilterTemplate[6] +
								 matrix[i + 1][j - 0] * HighFilterTemplate[7] +
								 matrix[i + 1][j + 1] * HighFilterTemplate[8] ;
		}
	}
}