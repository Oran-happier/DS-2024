#pragma once
#include "BinTree.h"
#include "List.h"
#include "Bitmap.h"
#include <iostream>

#define  N_CHAR  (122-97+1) //仅以可打印字符为例
struct HuffChar
{   //Huffman（超）字符
	char ch; unsigned int weight; //字符、频率
	HuffChar(char c = '^', int w = 0) : ch(c), weight(w) {};
	HuffChar(HuffChar const& hc) : ch(hc.ch), weight(hc.weight) {};
	// 比较器、判等器（各列其一，其余自行补充）
	bool operator< (HuffChar const& hc) { return weight > hc.weight; } //此处故意大小颠倒
	bool operator== (HuffChar const& hc) { return weight == hc.weight; }
};

#define HuffTree BinTree<HuffChar> //Huffman树，由BinTree派生，节点类型为HuffChar

typedef List<HuffTree*> HuffForest;//Huffman森林

typedef Bitmap HuffCode;//Huffman二进制编码

unsigned int* statistics(char* sample_text_file)
{   //统计字符出现频率
	unsigned int* freq = new unsigned int[N_CHAR];  //以下统计需随机访问，故以数组记录各字符出现次数
	memset(freq, 0, sizeof(int) * N_CHAR); //清零
	FILE* fp = fopen(sample_text_file, "r"); //assert: 文件存在且可正确打开
	for (char ch; 0 < fscanf(fp, "%c", &ch); ) //逐个扫描样本文件中的每个字符
	{
		if ((97 <= ch) && (ch <= 122)) freq[ch - 97]++; //累计对应的出现次数
		if ((65 <= ch) && (ch <= 90)) freq[ch - 65]++; //累计对应的出现次数
	}
	fclose(fp); return freq;
}

HuffForest* initForest(unsigned int* freq)
{   //根据频率统计表，为每个字符创建一棵树
	HuffForest* forest = new HuffForest; //以List实现Huffman森林
	for (int i = 0; i < N_CHAR; i++)
	{   //为每个字符
		forest->insertLast(new HuffTree); //生成一棵树，并将字符及其频率
		forest->last()->data->insertAsRoot(HuffChar(97 + i, freq[i])); //存入其中
	}
	return forest;
}

HuffTree* minHChar(HuffForest* forest)//在Huffman森林中找出权重最小的（超）字符
{
	ListNodePosi(HuffTree*) p = forest->first();//从首节点出发查找
	ListNodePosi(HuffTree*) minChar = p;//最小Huffman树所在的节点位置
	int minweight = p->data->root()->data.weight;//目前的最小权重
	while(forest->valid(p=p->succ))//遍历所有节点
		if(minweight > p->data->root()->data.weight)//若当前节点所含树更小，则
		{ minweight = p->data->root()->data.weight; minChar = p; }//更新记录
	return forest->remove(minChar);//将挑选出的Huffman树从森林中摘除，并返回
}

HuffTree* generateTree(HuffForest* forest)
{   //Huffman编码算法
	while (1 < forest->size())
	{
		HuffTree* T1 = minHChar(forest); HuffTree* T2 = minHChar(forest);
		HuffTree* S = new HuffTree();
		S->insertAsRoot(HuffChar('^', T1->root()->data.weight + T2->root()->data.weight));
		S->attachAsLC(S->root(), T1);S->attachAsRC(S->root(), T2);
		forest->insertLast(S);
	}//循环结束时，森林中唯一（列表首节点中）的那棵树即Huffman编码树
	return forest->first()->data;
}

void travPre_R(BinNodePosi(HuffChar) x)
{
	if (!x) return;
	std::cout << x->data.ch << ' ';
	travPre_R(x->lc);
	travPre_R(x->rc);
}