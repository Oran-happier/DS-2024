#include "Stack.h"

int main(void)
{
	const char* Test = "1+(4/2-3)*5!";
	char* test = new char[50];
	char* RPN=new char[50];
	strcpy(test, Test);
	RPN[0] = '\0';
	std::cout << evaluate(test, RPN) << std::endl;

	return 0;
}