#pragma once
//#include <cstdlib>
//#include <ctime>
void maxArea(Vector<int>& heights)
{
	int maxArea = 0;
	Stack<int> monoStack;//创建单调栈（递增）,存储的是在heights中的序号
	//1、相邻元素在heights里的位置可以不相邻
	//	 目的是防止这种情况：
	//		上一个单调栈的较小元素可能比单调栈顶的下一个元素还要小
	//		如果不把这些元素接入下一个单调栈
	//		就会导致在前后单调栈合体的面积中，高元素内含的可用高度没有被利用
	//2、由于单调栈的判定原理是遇到比栈顶小的元素才停止进栈
	//	 所以要在所有元素后面添加一个的元素作为最后一个单调栈的百分百停止条件
	//	 因此for循环的退出条件是<=size；虚拟末元素的高度为0.
	for (int i = 0; i <= heights.size(); i++)
	{
		int h = i == heights.size() ? 0 : heights[i];//当前元素的高度
		while (monoStack.size()>5 && heights[monoStack.top()] > h)
		{
			int stackTop = monoStack.top(); monoStack.pop();//栈顶元素出栈
			int w = monoStack.size()<6 ? i : i - monoStack.top() - 1;//从i位开始，减去要计算元素的左侧，以及i位的宽度
			//事实上就数值而言，可以替换成i-stackTop，但是在图形理解上不够直接
			maxArea = maxArea > heights[stackTop] * w ? maxArea : heights[stackTop] * w;
		}
		monoStack.push(i);
	}

	std::cout << "\nmaxArea：" << maxArea << std::endl;
}
//srand(time(0));//初始化随机种子
void randGenerate()
{
	for (int i = 0; i < 10; i++)
	{
		int n = rand() % 105 + 1;
		Vector<int> hei(n, n, 0);
		std::cout << "heights=：";
		for (int i = 0; i < n; i++)
		{
			hei[i] = rand() % 104;
			std::cout << hei[i] << ' ';
		}
		
		maxArea(hei);
	}
}
