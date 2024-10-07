#include "Vector.h"
#include "Complex.h"
//#include <complex>
//#include <iostream>
//#include <stdlib.h>
//#define Complex std::complex<double>
#define CAPACITY 5000  //为了增加排序效率时间的有效性，通过扩大数据集的方式增加时间，避免出现太多0时间的情况

void getOrder(int& order)
{
	std::cout << "0：展示当前向量内容；1：随机生成；2：置乱；3：查找；4：插入；5：删除；6：唯一化；7：各排序比较；";
	std::cout << "Please give a new order(break:-1):";
	std::cin >> order;
}

void show(Vector<Complex>& v,unsigned int size = 0)
{
	if (size == 0) size = v.size();
	for (unsigned int i = 0; i < size; i++)
	{
		//std::cout << vc[i] << std::endl;
		v[i].show();//展示向量内容
	}
}

void randomGenerate(Vector<Complex>& vc)//随机生成每个复数（带重复项）
{
	for (int i = 0; i < CAPACITY; i++)
	{
		vc[i] = Complex(rand() % 100, rand() % 100);
		if (i == 3) vc[2] = vc[3];//手动令3，4项相同
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
	//默认为顺序
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
	//2为逆序
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
	while (lo < hi) { //每步迭代仅需做一次比较判断，有两个分支
		Rank mi = (lo + hi) >> 1; //以中点为轴点（区间宽度折半，等效于其数值表示的右移一位）
		(m < vc[mi].modulus()) ? hi = mi : lo = mi + 1; //经比较后确定深入[lo, mi)或(mi, hi)
	} //成功查找不能提前终止
	return lo - 1;//至此，[lo]为大于e的最小者，故[lo-1]即为不大于e的最大者
}//有多个命中元素时，返回最靠后者；查找失败时，返回失败的位置

int main(void)
{
	Vector<Complex> vc(CAPACITY);
	Vector<Complex> vc2(CAPACITY);
	std::cout << "初始向量为:" << std::endl;
	randomGenerate(vc);//先默认随机生成一个vc
	int order,l,h;
	std::cout << "0：展示当前向量内容；1：随机生成；2：置乱；3：查找；4：插入；5：删除；6：唯一化；7：各排序比较；8:区间查找"<<std::endl;
	std::cout << "Please enter a number(break:-1):";
	std::cin >> order;

	while(order != -1)
	{
		switch (order)
		{
		case 0://显示当前vc向量
			show(vc);
			getOrder(order);
			break;
		case 1://随机生成
			std::cout << "Randomly generate the Vector:" << std::endl;
			randomGenerate(vc);
			getOrder(order);
			break;
		case 2://置乱
			std::cout << "Unsort the Vector:" << std::endl;
			vcUnsort(vc);
			getOrder(order);
			break;
		case 3://查找
			std::cout << "Enter the target complex to search:" << std::endl;
			vcSearch(vc);
			getOrder(order);
			break;
		case 4://插入
			std::cout << "Enter the index you want to insert(<" << vc.size() << "):";
			vcInsert(vc);
			getOrder(order);
			break;
		case 5://删除
			std::cout << "Enter the target complex's index to remove(<" << vc.size() << "):";
			vcRemove(vc);
			getOrder(order);
			break;
		case 6://唯一化
			std::cout << "Uniquify the Vector:" << std::endl;
			vcUniquify(vc);
			getOrder(order);
			break;
		case 7://排序算法的比较
			randomGenerate(vc);
			std::cout << "以下单位为毫秒(ms):" << std::endl;
			//乱序：
			std::cout << "out of order:" << std::endl;
			vc.sort();
			//顺序：
			std::cout << "ascending order:" << std::endl;
			selectSort1(vc);
			vc.sort();
			//逆序：
			std::cout << "descending order:" << std::endl;
			selectSort2(vc);
			vc.sort();
			getOrder(order);
			break;
		case 8://区间查找
			selectSort1(vc);//顺序
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
