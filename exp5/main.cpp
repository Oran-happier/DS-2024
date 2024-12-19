#include "Heap.h"

#define SIZE 30

void randomGenerate(Vector<int>& vi)//随机生成一个int向量
{
	//生成乱序向量
	std::cout << "乱序向量为：";
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
	//生成升序向量
	std::cout << "升序向量为：";
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
	//生成降序向量
	std::cout << "降序向量为：";
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

	//乱序
	randomGenerate(vi);//随机生成SIZE大小的向量vi
	vi.sort();         //sort()会返回向量vi各种排序方式的耗时
	std::cout << '\n';

	//顺序
	Vector<int> vi2(SIZE);
	randomGenerate(vi2);
	ascendSort(vi2);
	vi2.sort();
	std::cout << '\n';

	//逆序
	Vector<int> vi3(SIZE);
	randomGenerate(vi3);
	descendSort(vi3);
	vi3.sort();

}