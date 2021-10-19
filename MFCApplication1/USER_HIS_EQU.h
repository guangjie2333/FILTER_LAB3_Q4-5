#pragma once
/*
**********************************************************************
* 模块名称: USER_HIS_EQU
* 摘    要: 直方图均衡化类
* 当前版本: 1.0
* 作    者: guangjie2333
* 完成日期: 2021-10-19
* 内    容:
* 注    意: none
*********************************************************************/


/*
**********************************************************************
*                               包含头文件
**********************************************************************
*/
#include "USER_DEFINE.h"

/*
**********************************************************************
*                               用户字定义类
**********************************************************************
*/
class USER_HIS_EQU
{
	//variable 
	private:
		BYTE* R_array; //RGB三个分量分别做均衡化
		BYTE* G_array;
		BYTE* B_array;
		BYTE* array;
		int	  ArraySize;
	//function
	public:
		USER_HIS_EQU(BYTE* ARRAY, int ARRAYSIZE);
		~USER_HIS_EQU();
	public:
		void HistogramEqualization();//直方图均衡化的接口函数
	private:
		void SeparateRGB(BYTE* array, int ArraySize);
		void OneColorHistogramEqualization(BYTE* array, int ArraySize);
		void Classify(int OneColorVal, float* Grade); //输入一个0-255值，以32长度为一组，输出组数
		void Normalization(float* Grade, int ArraySize); //输入均衡化的分组数组，每个元素除以单通道颜色总数
		void CreatNewGrade(float* Grade);
		void UpdateArray(BYTE* array,float* Grade, int ArraySize);
		void UnionRGB(BYTE* array, int ArraySize);
		float Array_N_Sum(float* array, int N);//求数组前N项和
};

