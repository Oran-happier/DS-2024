#include "Stack.h"
#include "Q2.h"
int main(void)
{
	std::cout << "��Ŀһ��" << std::endl;
	const char* Test = "1+(4/2-1)*5!";
	std::cout << "����������" << Test << std::endl;
	char* test = new char[50];
	char* RPN=new char[50];
	strcpy(test, Test);
	RPN[0] = '\0';
	std::cout << "���Ϊ��" << evaluate(test, RPN) << std::endl;

	std::cout << "��Ŀ����" << std::endl;
	randGenerate();
	/*int n[6] = { 2,1,5,6,2,3 };
	Vector<int> testVc(n,6);
	maxArea(testVc);*/

	return 0;
}

