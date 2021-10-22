#pragma once
/*
**********************************************************************
* 模块名称: USER_FILTER
* 摘    要: 滤波类
* 当前版本: 1.0
* 作    者: guangjie2333
* 完成日期: 2021-10-22
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
class USER_FILTER
{
	//variable 
	public:
		BYTE* pixelArray;
		int  ArraySize;
		int  high;
		int  width;
		BYTE* R_array; //RGB三个分量分别做滤波
		BYTE* G_array;
		BYTE* B_array;

	protected:

	private:
		//低通滤波模板
		float lowFilterTemplate[9] = {1 / 9,1 / 9, 1 / 9, 
									  1 / 9, 1 / 9, 1 / 9, 
			                          1 / 9, 1 / 9, 1 / 9 };
		//高通滤波模板
		float HighFilterTemplate[9] = { 0, -1, 0,
									   -1,  5, 1,
									    0, -1, 0 };


	//function
	public:
		USER_FILTER(BYTE* array, int  h, int  w);
		~USER_FILTER();
		void LowFilter();
		void HighFilter();
		void MidFilter();
		void MaxFilter();
		void MinFilter();

	protected:
		void SeparateRGB();
		void UnionRGB();
		
	private:
		void Convolution(int flag);//图像模板卷积
		void DealLowConvolution(BYTE** matrix);
		void DealHighConvolution(BYTE** matrix);

};

