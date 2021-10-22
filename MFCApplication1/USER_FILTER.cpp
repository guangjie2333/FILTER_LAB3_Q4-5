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
	ArraySize = high * width * 3;

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
	SeparateRGB();//分离RGB分别做滤波
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
	SeparateRGB();//分离RGB分别做滤波
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
	SeparateRGB();//分离RGB分别做滤波
	Convolution(2);//1代表低通滤波卷积
	UnionRGB();
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
	SeparateRGB();//分离RGB分别做滤波
	Convolution(3);//1代表低通滤波卷积
	UnionRGB();
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
	SeparateRGB();//分离RGB分别做滤波
	Convolution(4);//1代表低通滤波卷积
	UnionRGB();
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
* 注    意:中值，max，min的本质在于排序算法
		   尽管数据量不大，但是我认为排序算法的选取很重要，优秀的工程师拒绝冒泡 
		   我新建了一个类叫算法类，里面有我大三时候写的快速排序的算法（现在具体实现忘记了hhh）
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

	//模板卷积 &MAX &MIN &MID滤波
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
		case 2:
			DealMidConvolution(matrixR); 
			DealMidConvolution(matrixG);
			DealMidConvolution(matrixB);
			break;
		case 3:
			DealMaxConvolution(matrixR);
			DealMaxConvolution(matrixG);
			DealMaxConvolution(matrixB);
			break;
		case 4:
			DealMinConvolution(matrixR);
			DealMinConvolution(matrixG);
			DealMinConvolution(matrixB);
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
	//动态建立二维数组
	BYTE** matrixNew;
	matrixNew = new BYTE * [high];
	for (int j = 0; j < high; j++)
	{
		matrixNew[j] = new BYTE[width];

	}

	//初始化
	for (int i = 0; i < high; i++)
	{
		for (int j = 0; j < width; j++)
		{
			matrixNew[i][j] = matrix[i][j];

		}
	}

	//卷积
	for (int i = 1; i < high - 1 ; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			matrix[i][j] =  matrixNew[i - 1][j - 1] * lowFilterTemplate[0] +
							matrixNew[i - 1][j - 0] * lowFilterTemplate[1] +
							matrixNew[i - 1][j + 1] * lowFilterTemplate[2] +
							matrixNew[i - 0][j - 1] * lowFilterTemplate[3] +
							matrixNew[i - 0][j - 0] * lowFilterTemplate[4] +
							matrixNew[i - 0][j + 1] * lowFilterTemplate[5] +
							matrixNew[i + 1][j - 1] * lowFilterTemplate[6] +
							matrixNew[i + 1][j - 0] * lowFilterTemplate[7] +
							matrixNew[i + 1][j + 1] * lowFilterTemplate[8] ;
			matrix[i][j] /= 9;
			matrix[i][j] = matrix[i][j] < 0 ? 0 : matrix[i][j];
			matrix[i][j] = matrix[i][j] > 255 ? 255 : matrix[i][j];
		}
	}

	//释放
	for (int j = 0; j < high; j++)
	{
		delete[] matrixNew[j];
	}
	delete[] matrixNew;

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
	//动态建立二维数组
	BYTE** matrixNew;
	matrixNew = new BYTE * [high];
	for (int j = 0; j < high; j++)
	{
		matrixNew[j] = new BYTE[width];

	}

	//初始化
	for (int i = 0; i < high; i++)
	{
		for (int j = 0; j < width; j++)
		{
			matrixNew[i][j] = matrix[i][j];

		}
	}

	//卷积
	for (int i = 1; i < high - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			matrix[i][j] =  matrixNew[i - 1][j - 1] * HighFilterTemplate[0] +
							matrixNew[i - 1][j - 0] * HighFilterTemplate[1] +
							matrixNew[i - 1][j + 1] * HighFilterTemplate[2] +
							matrixNew[i - 0][j - 1] * HighFilterTemplate[3] +
							matrixNew[i - 0][j - 0] * HighFilterTemplate[4] +
							matrixNew[i - 0][j + 1] * HighFilterTemplate[5] +
							matrixNew[i + 1][j - 1] * HighFilterTemplate[6] +
							matrixNew[i + 1][j - 0] * HighFilterTemplate[7] +
							matrixNew[i + 1][j + 1] * HighFilterTemplate[8] ;

			matrix[i][j] = matrix[i][j] < 0 ? 0 : matrix[i][j];
			matrix[i][j] = matrix[i][j] > 255 ? 255 : matrix[i][j];
		}
	}

	//释放
	for (int j = 0; j < high; j++)
	{
		delete[] matrixNew[j];
	}
	delete[] matrixNew;
}


/*
******************************************************************************
* 函数名称:	DealMidConvolution
* 函数功能: 处理中值滤波
* 输入参数:  matrix：二维矩阵
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-22日
* 注    意:
*******************************************************************************
*/
void USER_FILTER::DealMidConvolution(BYTE** matrix)
{
	//动态建立二维数组
	BYTE** matrixNew;
	matrixNew = new BYTE * [high];
	for (int j = 0; j < high; j++)
	{
		matrixNew[j] = new BYTE[width];

	}

	//初始化
	for (int i = 0; i < high; i++)
	{
		for (int j = 0; j < width; j++)
		{
			matrixNew[i][j] = matrix[i][j];

		}
	}

	//卷积
	for (int i = 1; i < high - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			int TmpArray[9] = {
								matrixNew[i - 1][j - 1],
								matrixNew[i - 1][j - 0],
								matrixNew[i - 1][j + 1],
								matrixNew[i - 0][j - 1],
								matrixNew[i - 0][j - 0],
								matrixNew[i - 0][j + 1],
								matrixNew[i + 1][j - 1],
								matrixNew[i + 1][j - 0],
								matrixNew[i + 1][j + 1]
			};
			//排序
			USER_ALG user_alg;
			user_alg.QuickSort(TmpArray,9);
			//中位数
			matrix[i][j] = TmpArray[(int)9/2];

		}
	}

	//释放
	for (int j = 0; j < high; j++)
	{
		delete[] matrixNew[j];
	}
	delete[] matrixNew;
}

/*
******************************************************************************
* 函数名称:	DealMaxConvolution
* 函数功能: 处理最大值滤波
* 输入参数:  matrix：二维矩阵
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-22日
* 注    意:
*******************************************************************************
*/
void USER_FILTER::DealMaxConvolution(BYTE** matrix)
{
	//动态建立二维数组
	BYTE** matrixNew;
	matrixNew = new BYTE * [high];
	for (int j = 0; j < high; j++)
	{
		matrixNew[j] = new BYTE[width];

	}

	//初始化
	for (int i = 0; i < high; i++)
	{
		for (int j = 0; j < width; j++)
		{
			matrixNew[i][j] = matrix[i][j];

		}
	}

	//卷积
	for (int i = 1; i < high - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			int TmpArray[9] = {
								matrixNew[i - 1][j - 1],
								matrixNew[i - 1][j - 0],
								matrixNew[i - 1][j + 1],
								matrixNew[i - 0][j - 1],
								matrixNew[i - 0][j - 0],
								matrixNew[i - 0][j + 1],
								matrixNew[i + 1][j - 1],
								matrixNew[i + 1][j - 0],
								matrixNew[i + 1][j + 1]
			};
			//排序
			USER_ALG user_alg;
			user_alg.QuickSort(TmpArray, 9);
			//最大值
			matrix[i][j] = TmpArray[8];

		}
	}

	//释放
	for (int j = 0; j < high; j++)
	{
		delete[] matrixNew[j];
	}
	delete[] matrixNew;
}

/*
******************************************************************************
* 函数名称:	DealMinConvolution
* 函数功能: 处理最小值滤波
* 输入参数:  matrix：二维矩阵
* 输出参数:	none
* 返 回 值:  void
* 创建日期:  2021年-10月-22日
* 注    意:
*******************************************************************************
*/
void USER_FILTER::DealMinConvolution(BYTE** matrix)
{
	//动态建立二维数组
	BYTE** matrixNew;
	matrixNew = new BYTE * [high];
	for (int j = 0; j < high; j++)
	{
		matrixNew[j] = new BYTE[width];

	}

	//初始化
	for (int i = 0; i < high; i++)
	{
		for (int j = 0; j < width; j++)
		{
			matrixNew[i][j] = matrix[i][j];

		}
	}

	//卷积
	for (int i = 1; i < high - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			int TmpArray[9] = {
								matrixNew[i - 1][j - 1],
								matrixNew[i - 1][j - 0],
								matrixNew[i - 1][j + 1],
								matrixNew[i - 0][j - 1],
								matrixNew[i - 0][j - 0],
								matrixNew[i - 0][j + 1],
								matrixNew[i + 1][j - 1],
								matrixNew[i + 1][j - 0],
								matrixNew[i + 1][j + 1]
			};
			//排序
			USER_ALG user_alg;
			user_alg.QuickSort(TmpArray, 9);
			//最小值
			matrix[i][j] = TmpArray[0];

		}
	}

	//释放
	for (int j = 0; j < high; j++)
	{
		delete[] matrixNew[j];
	}
	delete[] matrixNew;
}