#include "pch.h"
#include "USER_HIS_EQU.h"
/*
********************************************************************************
********************************************************************************
*                               接口函数
********************************************************************************
********************************************************************************
*/

/*
******************************************************************************
* 函数名称:	HistogramEqualization
* 函数功能: 直方图均衡化的接口函数
* 输入参数:	array ：bmp图像的RGB三通道数据,  ArraySize ：array的长度
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-19日
* 注    意:
*******************************************************************************
*/

void USER_HIS_EQU::HistogramEqualization(BYTE* array,int ArraySize)
{
	//分离RGB
	SeparateRGB(array, ArraySize);
	//RGB分别直方图均衡化
	OneColorHistogramEqualization(R_array, ArraySize / 3);
	OneColorHistogramEqualization(G_array, ArraySize / 3);
	OneColorHistogramEqualization(B_array, ArraySize / 3);
	//更新图像数据
	UnionRGB(array, ArraySize);

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
* 输入参数:	array ：bmp图像的RGB三通道数据,  ArraySize ：array的长度
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-19日
* 注    意:  
*******************************************************************************
*/


void USER_HIS_EQU :: SeparateRGB(BYTE* array, int ArraySize)
{
	int j = 0;
	for (int i = 0; i < ArraySize; i = i + 3)
	{
		R_array[j] = array[i + 2];
		G_array[j] = array[i + 1];
		B_array[j] = array[i + 0];

		j++;
	}
}

/*
******************************************************************************
* 函数名称:	OneColorHistogramEqualization
* 函数功能: 单通道直方图均衡化
* 输入参数:	array ：bmp图像的单通道数据,  ArraySize ：array的长度
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-19日
* 注    意: 
*******************************************************************************
*/

void USER_HIS_EQU::OneColorHistogramEqualization(BYTE* array, int ArraySize)
{
	float Grade[7] = {0}; //均衡化的分组计数数组

	//分级
	for (int i = 0; i < ArraySize; i++)
	{
		Classify(array[i], Grade);
	}
	//归一化
	Normalization(Grade,ArraySize);
	//新的分级
	CreatNewGrade(Grade);
	//更新灰度值
	UpdateArray(array, Grade, ArraySize);
	
}

/*
******************************************************************************
* 函数名称:	Classify
* 函数功能: 将0-255的图像分成8个等级
* 输入参数:	OneColorVal:0-255的 R/G/B值   * Grade:均衡化的分组计数数组
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-19日
* 注    意:
*******************************************************************************
*/
int USER_HIS_EQU :: Classify(int OneColorVal, float* Grade)
{
	for (int i = 0; i < 8; i++)
	{
		if ((OneColorVal >= 32 * i) && (OneColorVal < 32*i + 32))
		{
			Grade[i]++;
		}
	}
}
/*
******************************************************************************
* 函数名称:	Normalization
* 函数功能: 归一化
* 输入参数: 分级数组Grade
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-19日
* 注    意:
*******************************************************************************
*/
void USER_HIS_EQU :: Normalization(float* Grade,int ArraySize)
{
	for (int i = 0; i < 8; i++)
	{
		Grade[i] /= ArraySize;
	}
}

/*
******************************************************************************
* 函数名称:	CreatNewGrade
* 函数功能: 将Grade数组的内容变成灰度值
* 输入参数: 分级数组Grade
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-19日
* 注    意: 创建新的分级,i代表 分级数组的下标，j代表0-8的分级，经过两个循环，Grade的内容就变成了灰度值
			这个函数可能脑洞比较大
*******************************************************************************
*/
void USER_HIS_EQU::CreatNewGrade(float* Grade)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			float tmp = Grade[i] * 7;
			if ((tmp >= j) && (tmp < j + 1))
			{
				//Grade内容原来是百分比，现在改成了均衡化后的灰度值
				Grade[i] = (int)((32 * round(tmp)) + (32 * round(tmp) + 32)) / 2;
			}
		}

	}
}
/*
******************************************************************************
* 函数名称:	UpdateArray
* 函数功能: 更新RGB单通道的值
* 输入参数: 分级数组Grade
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-19日
* 注    意: 创建新的分级,i代表 分级数组的下标，j代表0-8的分级，经过两个循环，Grade的内容就变成了灰度值
			这个函数可能脑洞比较大
*******************************************************************************
*/
void USER_HIS_EQU::UpdateArray(BYTE* array, float* Grade, int ArraySize)
{
	for (int i = 0; i < ArraySize; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((array[i] >= 32 * j) && (array[i] < 32 * j + 32))
			{
				array[i] = (int)Grade[j];
			}
		}

	}
}

/*
******************************************************************************
* 函数名称:	UnionRGB
* 函数功能: RGB均衡化后的分量整合
* 输入参数: 分级数组Grade
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-19日
* 注    意:
*******************************************************************************
*/
void USER_HIS_EQU ::UnionRGB(BYTE* array, int ArraySize)
{
	int j = 0;
	for (int i = 0; i < ArraySize; i = i + 3)
	{
		array[i + 2] = R_array[j];
		array[i + 1] = G_array[j];
		array[i + 0] = B_array[j];

		j++;
	}
}