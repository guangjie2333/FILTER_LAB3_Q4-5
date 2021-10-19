#pragma once
/*
**********************************************************************
* ģ������: USER_HIS_EQU
* ժ    Ҫ: ֱ��ͼ���⻯��
* ��ǰ�汾: 1.0
* ��    ��: guangjie2333
* �������: 2021-10-19
* ��    ��:
* ע    ��: none
*********************************************************************/


/*
**********************************************************************
*                               ����ͷ�ļ�
**********************************************************************
*/
#include "USER_DEFINE.h"

/*
**********************************************************************
*                               �û��ֶ�����
**********************************************************************
*/
class USER_HIS_EQU
{
	//variable 
	private:
		BYTE* R_array; //RGB���������ֱ������⻯
		BYTE* G_array;
		BYTE* B_array;
	//function
	public:
		void HistogramEqualization(BYTE* array,int ArraySize);//ֱ��ͼ���⻯�Ľӿں���
	private:
		void SeparateRGB(BYTE* array, int ArraySize);
		void OneColorHistogramEqualization(BYTE* array, int ArraySize);
		int  Classify(int OneColorVal, float* Grade); //����һ��0-255ֵ����32����Ϊһ�飬�������
		void Normalization(float* Grade, int ArraySize); //������⻯�ķ������飬ÿ��Ԫ�س��Ե�ͨ����ɫ����
		void CreatNewGrade(float* Grade);
		void UpdateArray(BYTE* array,float* Grade, int ArraySize);
		void UnionRGB(BYTE* array, int ArraySize);

};

