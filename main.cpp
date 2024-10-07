#include "Vector.h"
#include "Complex.h"
//#include <complex>
//#include <iostream>
//#include <stdlib.h>
//#define Complex std::complex<double>
#define CAPACITY 5000  //Ϊ����������Ч��ʱ�����Ч�ԣ�ͨ���������ݼ��ķ�ʽ����ʱ�䣬�������̫��0ʱ������

void getOrder(int& order)
{
	std::cout << "0��չʾ��ǰ�������ݣ�1��������ɣ�2�����ң�3�����ң�4�����룻5��ɾ����6��Ψһ����7��������Ƚϣ�";
	std::cout << "Please give a new order(break:-1):";
	std::cin >> order;
}

void show(Vector<Complex>& v,unsigned int size = 0)
{
	if (size == 0) size = v.size();
	for (unsigned int i = 0; i < size; i++)
	{
		//std::cout << vc[i] << std::endl;
		v[i].show();//չʾ��������
	}
}

void randomGenerate(Vector<Complex>& vc)//�������ÿ�����������ظ��
{
	for (int i = 0; i < CAPACITY; i++)
	{
		vc[i] = Complex(rand() % 100, rand() % 100);
		if (i == 3) vc[2] = vc[3];//�ֶ���3��4����ͬ
	}
	show(vc);
}

void vcUnsort(Vector<Complex>& vc)
{
	vc.unsort();
	show(vc);
}

void vcSearch(Vector<Complex>& vc)
{
	int searchReal, searchImag;
	std::cout << "The real part:";
	std::cin >> searchReal;
	std::cout << "The image part:";
	std::cin >> searchImag;
	Complex tc(searchReal, searchImag);
	int findIndex = vc.find(tc);
	if (findIndex == -1)
		std::cout << "The target complex does not exist!" << std::endl;
	else
		std::cout << "The target complex's index is:" << findIndex << std::endl;
}

void vcInsert(Vector<Complex>& vc)
{
	int insertIndex, insertReal, insertImag;
	std::cin >> insertIndex;
	std::cout << "Enter the real:";
	std::cin >> insertReal;
	std::cout << "Enter the imag:";
	std::cin >> insertImag;
	Complex ic(insertReal, insertImag);
	vc.insert(insertIndex, ic);
	show(vc);
}

void vcRemove(Vector<Complex>& vc)
{
	int removeIndex;
	std::cin >> removeIndex;
	vc.remove(removeIndex);
	show(vc);
}

void vcUniquify(Vector<Complex>& vc)
{
	vc.dedup();
	show(vc);
}

void selectSort1(Vector<Complex>& vc)
{
	//Ĭ��Ϊ˳��
	for (unsigned int i = 0; i < vc.size()-1; i++)
	{
		for (unsigned int j = i + 1; j < vc.size(); j++)
		{
			if (vc[j] < vc[i])
				std::swap(vc[j], vc[i]);
		}
	}
}
void selectSort2(Vector<Complex>& vc)
{
	//2Ϊ����
	for (unsigned int i = 0; i < vc.size()-1; i++)
	{
		for (unsigned int j = i + 1; j < vc.size(); j++)
		{
			if (vc[j] > vc[i])
				std::swap(vc[j], vc[i]);
		}
	}
}

int vcbinSearch(Vector<Complex> vc,double m,int lo,int hi)
{
	while (lo < hi) { //ÿ������������һ�αȽ��жϣ���������֧
		Rank mi = (lo + hi) >> 1; //���е�Ϊ��㣨�������۰룬��Ч������ֵ��ʾ������һλ��
		(m < vc[mi].modulus()) ? hi = mi : lo = mi + 1; //���ȽϺ�ȷ������[lo, mi)��(mi, hi)
	} //�ɹ����Ҳ�����ǰ��ֹ
	return lo - 1;//���ˣ�[lo]Ϊ����e����С�ߣ���[lo-1]��Ϊ������e�������
}//�ж������Ԫ��ʱ����������ߣ�����ʧ��ʱ������ʧ�ܵ�λ��

int main(void)
{
	Vector<Complex> vc(CAPACITY);
	Vector<Complex> vc2(CAPACITY);
	std::cout << "��ʼ����Ϊ:" << std::endl;
	randomGenerate(vc);//��Ĭ���������һ��vc
	int order,l,h;
	std::cout << "0��չʾ��ǰ�������ݣ�1��������ɣ�2�����ң�3�����ң�4�����룻5��ɾ����6��Ψһ����7��������Ƚϣ�8:�������"<<std::endl;
	std::cout << "Please enter a number(break:-1):";
	std::cin >> order;

	while(order != -1)
	{
		switch (order)
		{
		case 0://��ʾ��ǰvc����
			show(vc);
			getOrder(order);
			break;
		case 1://�������
			std::cout << "Randomly generate the Vector:" << std::endl;
			randomGenerate(vc);
			getOrder(order);
			break;
		case 2://����
			std::cout << "Unsort the Vector:" << std::endl;
			vcUnsort(vc);
			getOrder(order);
			break;
		case 3://����
			std::cout << "Enter the target complex to search:" << std::endl;
			vcSearch(vc);
			getOrder(order);
			break;
		case 4://����
			std::cout << "Enter the index you want to insert(<" << vc.size() << "):";
			vcInsert(vc);
			getOrder(order);
			break;
		case 5://ɾ��
			std::cout << "Enter the target complex's index to remove(<" << vc.size() << "):";
			vcRemove(vc);
			getOrder(order);
			break;
		case 6://Ψһ��
			std::cout << "Uniquify the Vector:" << std::endl;
			vcUniquify(vc);
			getOrder(order);
			break;
		case 7://�����㷨�ıȽ�
			randomGenerate(vc);
			std::cout << "���µ�λΪ����(ms):" << std::endl;
			//����
			std::cout << "out of order:" << std::endl;
			vc.sort();
			//˳��
			std::cout << "ascending order:" << std::endl;
			selectSort1(vc);
			vc.sort();
			//����
			std::cout << "descending order:" << std::endl;
			selectSort2(vc);
			vc.sort();
			getOrder(order);
			break;
		case 8://�������
			selectSort1(vc);//˳��
			show(vc);
			std::cout << "m1:" ;
			int m1;
			std::cin >> m1;
			std::cout << "m2:" ;
			int m2;
			std::cin >> m2;
			l = vcbinSearch(vc,m1,0,CAPACITY);
			h = vcbinSearch(vc,m2,0,CAPACITY);
			for (int i = l; i < h; i++) vc2[i] = vc[i];
			show(vc2,h);
			getOrder(order);
		default:
			order = -1;
			break;
		}
	}
	std::cout << "Break successfully!" << std::endl;
}
