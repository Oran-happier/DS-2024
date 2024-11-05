#pragma once
#include "BinTree.h"
#include "List.h"
#include "Bitmap.h"
#include <iostream>

#define  N_CHAR  (122-97+1) //���Կɴ�ӡ�ַ�Ϊ��
struct HuffChar
{   //Huffman�������ַ�
	char ch; unsigned int weight; //�ַ���Ƶ��
	HuffChar(char c = '^', int w = 0) : ch(c), weight(w) {};
	HuffChar(HuffChar const& hc) : ch(hc.ch), weight(hc.weight) {};
	// �Ƚ������е�����������һ���������в��䣩
	bool operator< (HuffChar const& hc) { return weight > hc.weight; } //�˴������С�ߵ�
	bool operator== (HuffChar const& hc) { return weight == hc.weight; }
};

#define HuffTree BinTree<HuffChar> //Huffman������BinTree�������ڵ�����ΪHuffChar

typedef List<HuffTree*> HuffForest;//Huffmanɭ��

typedef Bitmap HuffCode;//Huffman�����Ʊ���

unsigned int* statistics(char* sample_text_file)
{   //ͳ���ַ�����Ƶ��
	unsigned int* freq = new unsigned int[N_CHAR];  //����ͳ����������ʣ����������¼���ַ����ִ���
	memset(freq, 0, sizeof(int) * N_CHAR); //����
	FILE* fp = fopen(sample_text_file, "r"); //assert: �ļ������ҿ���ȷ��
	for (char ch; 0 < fscanf(fp, "%c", &ch); ) //���ɨ�������ļ��е�ÿ���ַ�
	{
		if ((97 <= ch) && (ch <= 122)) freq[ch - 97]++; //�ۼƶ�Ӧ�ĳ��ִ���
		if ((65 <= ch) && (ch <= 90)) freq[ch - 65]++; //�ۼƶ�Ӧ�ĳ��ִ���
	}
	fclose(fp); return freq;
}

HuffForest* initForest(unsigned int* freq)
{   //����Ƶ��ͳ�Ʊ�Ϊÿ���ַ�����һ����
	HuffForest* forest = new HuffForest; //��Listʵ��Huffmanɭ��
	for (int i = 0; i < N_CHAR; i++)
	{   //Ϊÿ���ַ�
		forest->insertLast(new HuffTree); //����һ�����������ַ�����Ƶ��
		forest->last()->data->insertAsRoot(HuffChar(97 + i, freq[i])); //��������
	}
	return forest;
}

HuffTree* minHChar(HuffForest* forest)//��Huffmanɭ�����ҳ�Ȩ����С�ģ������ַ�
{
	ListNodePosi(HuffTree*) p = forest->first();//���׽ڵ��������
	ListNodePosi(HuffTree*) minChar = p;//��СHuffman�����ڵĽڵ�λ��
	int minweight = p->data->root()->data.weight;//Ŀǰ����СȨ��
	while(forest->valid(p=p->succ))//�������нڵ�
		if(minweight > p->data->root()->data.weight)//����ǰ�ڵ���������С����
		{ minweight = p->data->root()->data.weight; minChar = p; }//���¼�¼
	return forest->remove(minChar);//����ѡ����Huffman����ɭ����ժ����������
}

HuffTree* generateTree(HuffForest* forest)
{   //Huffman�����㷨
	while (1 < forest->size())
	{
		HuffTree* T1 = minHChar(forest); HuffTree* T2 = minHChar(forest);
		HuffTree* S = new HuffTree();
		S->insertAsRoot(HuffChar('^', T1->root()->data.weight + T2->root()->data.weight));
		S->attachAsLC(S->root(), T1);S->attachAsRC(S->root(), T2);
		forest->insertLast(S);
	}//ѭ������ʱ��ɭ����Ψһ���б��׽ڵ��У����ǿ�����Huffman������
	return forest->first()->data;
}

void travPre_R(BinNodePosi(HuffChar) x)
{
	if (!x) return;
	std::cout << x->data.ch << ' ';
	travPre_R(x->lc);
	travPre_R(x->rc);
}