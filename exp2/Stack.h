#pragma once
#define _CRT_SECURE_NO_WARNINGS ;
#include "Vector.h"
#include <string.h>
#include <cmath>
#define N_OPTR 9 //运算符总数
typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator;//运算符集合
//加、减、乘、除、乘方、阶乘、左括号、右括号、起始符与终止符

void append(char*& RPN, float tp);
float calcu(float p1, char op, float p2);
float calcu(char op, float p);
float evaluate(char* S, char* RPN);//表达式求值，逆波兰（RPN）
char priority(char tp, char s);
int opIndex(char op);
const char pri[N_OPTR][N_OPTR] =
{
	/*              |-------------------- 当 前 运 算 符 --------------------| */
	/*              +      -      *      /      ^      !      (      )      \0 */
	/* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
	/* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
	/* 栈  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
	/* 顶  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
	/* 运  ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
	/* 算  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
	/* 符  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '~',   ' ',
	/* |   ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
	/* -- \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '~'
};
//void convert(Stack<char>& S, __int64 n, int base);//进制转换算法，迭代版
//bool paren(const char exp[], Rank lo, Rank hi);//括号匹配算法，迭代版

template <typename T> class Stack :public Vector<T>
{
public://开放式接口，直接使用
	
	void push(T const& e) { Vector<T>::insert(e); }//入栈：将新元素作为向量的末元素插入
	T pop() { return Vector<T>::remove(Vector<T>::size() - 1); }//出栈
	T& top() { return (*this)[Vector<T>::size() - 1]; }//取顶：直接返回向量的末元素
	
	friend void readNumber(char* S, Stack<float>& opnd);
};

void convert(Stack<char>& S, __int64 n, int base)
{
	//新进制下的数位符号
	static char digit[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	while (n > 0)
	{
		int remainder = (int)(n % base); S.push(digit[remainder]);//余数（当前位）入栈
		n /= base;//更新为去位后
	}
}//最终形成新的进制，自顶而下被存入栈中

bool paren(const char exp[], Rank lo, Rank hi)
{
	//表达式括号匹配检查,可兼顾三种括号
	Stack<char>S;//使用栈记录已发现但尚未匹配的左括号
	for (Rank i = lo; i <= hi; i++)/* 逐一检查当前字符 */
		switch (exp[i])
		{//左括号直接进栈;右括号若与栈顶失配,则表达式必不匹配
		case '(': case ' [': case '{': S.push(exp[i]); break;
		case ')': if ((S.empty()) || ('(' != S.pop())) return false; break;
		case ']': if ((S.empty()) || ('[' != S.pop())) return false; break;
		case '}': if ((S.empty()) || ('{' != S.pop())) return false; break;
		default: break;//非括号字符一律忽略
		}
	return S.empty();//最终栈空,当且仅当匹配
}

float evaluate(char* S, char* RPN)
{	//对(已剔除白空格的)表达式s求值,并转换为逆波兰式RPN
	Stack<float>opnd; Stack<char>optr;//运算数栈、运算符栈
	optr.push('\0');//尾哨兵'\0'也作为头哨兵首先入栈
	while (!optr.empty()) {//在运算符栈非空之前,逐个处理表达式中各字符
		if (isdigit(*S)) {//若当前字符为操作数,则
			readNumber(S, opnd);
			append(RPN, opnd.top());//读入操作数,并将其接至RPN末尾
			S++;
		}
		else //若当前字符为运算符,则
			switch (priority(optr.top(), *S))
			{	//视其与栈顶运算符之间优先级高低分别处理
				case'<'://栈顶运算符优先级更低时
					optr.push(*S); S++;//计算推迟,当前运算符进栈
					break;
				case'>': {//栈顶运算符优先级更高时,可实施相应的计算,并将结果重新入栈
					char op = optr.pop(); append(RPN, op);//栈顶运算符出栈并续接至RPN末尾
					if ('!' == op)//若属于一元运算符
						opnd.push(calcu(op, opnd.pop()));//则取一个操作数,计算结果入栈
					else
						{//对于其它(二元)运算符
							float opnd2 = opnd.pop(), opnd1 = opnd.pop();//取出后、前操作数
							opnd.push(calcu(opnd1, op, opnd2));//实施二元计算,结果入栈
						}
					break;
					}
				case'~'://匹配的运算符(括号或’\0')时
					optr.pop(); S++;//脱括号并转至下一字符
					break;
				default:exit(-1);//逢语法错误,不做处理直接退出
			}//switch
	}//while
	return opnd.pop();//弹出并返回最后的计算结果
}

float calcu(float p1, char op, float p2)
{
	switch (op)
	{
	case '+':return p1 + p2;
	case '-':return p1 - p2;
	case '*':return p1 * p2;
	case '/':return p1 / p2;
	case '^':return pow(p1,p2);
	default:
		break;
	}
}

float calcu(char op, float p)
{
	float np = 1.0;
	while (p > 1.0) { np *= p--; }//事实上小数的阶乘不是这样的，但是考虑到数据其实是.0的形式，就算了
	return np;
}

char priority(char tp, char s)
{
	
	return pri[opIndex(tp)][opIndex(s)];
}

int opIndex(char op)
{
	switch (op)
	{
	case '+':
		return ADD;
	case '-':
		return SUB;
	case '*':
		return MUL;
	case '/':
		return DIV;
	case '^':
		return POW;
	case '!':
		return FAC;
	case '(':
		return L_P;
	case ')':
		return R_P;
	case '\0':
		return EOE;
	default:
		break;
	}
	return 0;
}

void readNumber(char* S, Stack<float>& opnd)
{
	opnd.push(*S - '0');
}

void append(char*& RPN, float tp)
{
	//方便起见，只处理所有字符串在20以内的大小，事实上是不合理不安全的
	//另外要求RPN足够大，不然缓冲区会溢出
	char newtp[20];
	sprintf(newtp, "%.2f", tp);
	strcat(RPN, newtp);
}
