#include "Huffman.h"

int main(int argc,char* argv[])//Huffman�����㷨ͳһ����
{
	char filep[10] = "test.txt";
	unsigned int* freq = statistics(filep);//���������ļ���ͳ�Ƹ��ַ��ĳ���Ƶ��
	HuffForest* forest = initForest(freq); delete freq; //����Huffmanɭ��
	HuffTree* tree = generateTree(forest); delete forest;//����Huffman������
	std::cout << "��������Ľ��Ϊ��'^'ΪĬ��ռλ���ţ���" << std::endl;
	travPre_R(tree->root());
	//HuffTable* table = generateTable(tree); //��Huffman������ת��Ϊ�����
	//for (int i = 2; i < argc; i++)
	//{ //���������д����ÿһ���Ĵ�
	//	Bitmap* codeString = new Bitmap; //�����Ʊ��봮
	//	int n = encode(table, &codeString, argv[i]); //�����ݱ�������ɣ�����Ϊn��
	//	decode(tree, &codeString, n); //����Huffman���������Գ���Ϊn�Ķ����Ʊ��봮����
	//}

	//table = nullptr; tree = nullptr;

	return 0;
}
