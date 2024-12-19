#include "Heap.h"

#define SIZE 30

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
	std::cout << vi[vi.size()-1] << " ";
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
	std::cout << vi[vi.size()-1] << " ";
	std::cout << '\n';
}


int main(void)
{
	Vector<int> vi(SIZE);

	//����
	randomGenerate(vi);//�������SIZE��С������vi
	vi.sort();         //sort()�᷵������vi��������ʽ�ĺ�ʱ
	std::cout << '\n';

	//˳��
	Vector<int> vi2(SIZE);
	randomGenerate(vi2);
	ascendSort(vi2);
	vi2.sort();
	std::cout << '\n';

	//����
	Vector<int> vi3(SIZE);
	randomGenerate(vi3);
	descendSort(vi3);
	vi3.sort();

}