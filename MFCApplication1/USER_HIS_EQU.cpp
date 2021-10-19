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
	
}

/*
******************************************************************************
* 函数名称:	Classify
* 函数功能: 将0-255的图像分成8个等级
* 输入参数:	0-255的 R/G/B值
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-19日
* 注    意:
*******************************************************************************
*/
int USER_HIS_EQU :: Classify(int OneColor)
{

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
void USER_HIS_EQU :: Normalization(int* Grade)
{



}
/*
******************************************************************************
* 函数名称:	CreatNewGrade
* 函数功能: 创建新的分组
* 输入参数: 分级数组Grade
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-19日
* 注    意:
*******************************************************************************
*/
int* USER_HIS_EQU::CreatNewGrade(int* Grade)
{


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