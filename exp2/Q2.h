#pragma once
//#include <cstdlib>
//#include <ctime>
void maxArea(Vector<int>& heights)
{
	int maxArea = 0;
	Stack<int> monoStack;//��������ջ��������,�洢������heights�е����
	//1������Ԫ����heights���λ�ÿ��Բ�����
	//	 Ŀ���Ƿ�ֹ���������
	//		��һ������ջ�Ľ�СԪ�ؿ��ܱȵ���ջ������һ��Ԫ�ػ�ҪС
	//		���������ЩԪ�ؽ�����һ������ջ
	//		�ͻᵼ����ǰ�󵥵�ջ���������У���Ԫ���ں��Ŀ��ø߶�û�б�����
	//2�����ڵ���ջ���ж�ԭ����������ջ��С��Ԫ�ز�ֹͣ��ջ
	//	 ����Ҫ������Ԫ�غ������һ����Ԫ����Ϊ���һ������ջ�İٷְ�ֹͣ����
	//	 ���forѭ�����˳�������<=size������ĩԪ�صĸ߶�Ϊ0.
	for (int i = 0; i <= heights.size(); i++)
	{
		int h = i == heights.size() ? 0 : heights[i];//��ǰԪ�صĸ߶�
		while (monoStack.size()>5 && heights[monoStack.top()] > h)
		{
			int stackTop = monoStack.top(); monoStack.pop();//ջ��Ԫ�س�ջ
			int w = monoStack.size()<6 ? i : i - monoStack.top() - 1;//��iλ��ʼ����ȥҪ����Ԫ�ص���࣬�Լ�iλ�Ŀ��
			//��ʵ�Ͼ���ֵ���ԣ������滻��i-stackTop��������ͼ������ϲ���ֱ��
			maxArea = maxArea > heights[stackTop] * w ? maxArea : heights[stackTop] * w;
		}
		monoStack.push(i);
	}

	std::cout << "\nmaxArea��" << maxArea << std::endl;
}
//srand(time(0));//��ʼ���������
void randGenerate()
{
	for (int i = 0; i < 10; i++)
	{
		int n = rand() % 105 + 1;
		Vector<int> hei(n, n, 0);
		std::cout << "heights=��";
		for (int i = 0; i < n; i++)
		{
			hei[i] = rand() % 104;
			std::cout << hei[i] << ' ';
		}
		
		maxArea(hei);
	}
}
