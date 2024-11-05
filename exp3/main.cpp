#include "Huffman.h"

int main(int argc,char* argv[])//Huffman编码算法统一测试
{
	char filep[10] = "test.txt";
	unsigned int* freq = statistics(filep);//根据样本文件，统计各字符的出现频率
	HuffForest* forest = initForest(freq); delete freq; //创建Huffman森林
	HuffTree* tree = generateTree(forest); delete forest;//构造Huffman编码树
	std::cout << "先序遍历的结果为（'^'为默认占位符号）：" << std::endl;
	travPre_R(tree->root());
	//HuffTable* table = generateTable(tree); //将Huffman编码树转换为编码表
	//for (int i = 2; i < argc; i++)
	//{ //对于命令行传入的每一明文串
	//	Bitmap* codeString = new Bitmap; //二进制编码串
	//	int n = encode(table, &codeString, argv[i]); //将根据编码表生成（长度为n）
	//	decode(tree, &codeString, n); //利用Huffman编码树，对长度为n的二进制编码串解码
	//}

	//table = nullptr; tree = nullptr;

	return 0;
}
