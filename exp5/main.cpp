#include "Heap.h"

#define SIZE 5

void randomGenerate(Vector<int>& vi)//�������һ��int����
{
	//������������
	std::cout << "��������Ϊ��";
	for (int i = 0; i < SIZE; i++)
	{
		int ri = int(rand() % 100);
		vi.insert(ri);
		std::cout << vi[i] << " ";
	}
	std::cout << '\n';
}

void ascendSort(Vector<int>& vi)
{
	//������������
	std::cout << "��������Ϊ��";
	for (int i = 0; i < vi.size() - 1; i++)
	{
		for (int j = i + 1; j < vi.size(); j++)
		{
			if (vi[j] < vi[i])
				std::swap(vi[j], vi[i]);
		}
		std::cout << vi[i] << " ";
	}
	std::cout << '\n';
}

void descendSort(Vector<int>& vi)
{
	//���ɽ�������
	std::cout << "��������Ϊ��";
	for (int i = 0; i < vi.size() - 1; i++)
	{
		for (int j = i + 1; j < vi.size(); j++)
		{
			if (vi[j] > vi[i])
				std::swap(vi[j], vi[i]);
		}
		std::cout << vi[i] << " ";
	}
	std::cout << '\n';
}


int main(void)
{
	Vector<int> vi(SIZE);

	//����
	randomGenerate(vi);//�������SIZE��С������vi
	vi.sort();         //sort()�᷵������vi��������ʽ�ĺ�ʱ

	////˳��
	//ascendSort(vi);
	//vi.sort();

	////����
	//descendSort(vi);
	//vi.sort();
}