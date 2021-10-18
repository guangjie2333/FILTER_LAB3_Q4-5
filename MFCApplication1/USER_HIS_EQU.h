#pragma once
#include "USER_DEFINE.h"
class USER_HIS_EQU
{
	//variable 
	private:
		BYTE* R_array; //RGB���������ֱ������⻯
		BYTE* G_array;
		BYTE* B_array;

		int	 Grade[7]; //��һ�ξ��⻯�ķ���
		int* NewGrade; //�µľ��⻯����

	//function
	public:
		void HistogramEqualization(BYTE* array);//ֱ��ͼ���⻯�Ľӿں���
	private:
		int  Classify(int OneColor); //����һ��0-255ֵ����32����Ϊһ�飬�������
		void Normalization(int* array); //������⻯�ķ������飬ÿ��Ԫ�س��Ե�ͨ����ɫ����
		int* CreatNewGrade(int* Grade);

};

