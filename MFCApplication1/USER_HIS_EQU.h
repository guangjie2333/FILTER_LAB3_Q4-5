#pragma once
#include "USER_DEFINE.h"
class USER_HIS_EQU
{
	//variable 
	private:
		BYTE* R_array; //RGB三个分量分别做均衡化
		BYTE* G_array;
		BYTE* B_array;

		int	 Grade[7]; //第一次均衡化的分组
		int* NewGrade; //新的均衡化分组

	//function
	public:
		void HistogramEqualization(BYTE* array);//直方图均衡化的接口函数
	private:
		int  Classify(int OneColor); //输入一个0-255值，以32长度为一组，输出组数
		void Normalization(int* array); //输入均衡化的分组数组，每个元素除以单通道颜色总数
		int* CreatNewGrade(int* Grade);

};

