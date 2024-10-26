#include "Stack.h"
#include "Q2.h"
int main(void)
{
	std::cout << "题目一：" << std::endl;
	const char* Test = "1+(4/2-1)*5!";
	std::cout << "测试样例：" << Test << std::endl;
	char* test = new char[50];
	char* RPN=new char[50];
	strcpy(test, Test);
	RPN[0] = '\0';
	std::cout << "结果为：" << evaluate(test, RPN) << std::endl;

	std::cout << "题目二：" << std::endl;
	randGenerate();
	/*int n[6] = { 2,1,5,6,2,3 };
	Vector<int> testVc(n,6);
	maxArea(testVc);*/

	return 0;
}

