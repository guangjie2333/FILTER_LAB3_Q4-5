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

		int	 Grade[7]; //���⻯�ķ����������
		int* NewGrade; //�µľ��⻯����

	//function
	public:
		void HistogramEqualization(BYTE* array,int ArraySize);//ֱ��ͼ���⻯�Ľӿں���
	private:
		void SeparateRGB(BYTE* array, int ArraySize);
		void OneColorHistogramEqualization(BYTE* array, int ArraySize);
		int  Classify(int OneColor); //����һ��0-255ֵ����32����Ϊһ�飬�������
		void Normalization(int* Grade); //������⻯�ķ������飬ÿ��Ԫ�س��Ե�ͨ����ɫ����
		int* CreatNewGrade(int* Grade);
		void UnionRGB(BYTE* array, int ArraySize);

};

