//#include "Graph.h"
#include "GraphMatrix.h"

int main(void)
{
	GraphMatrix<char, int> gm;

	//���ɶ���
    gm.insert('A');
    gm.insert('B');
    gm.insert('C');
    gm.insert('D');
    gm.insert('E');
    gm.insert('F');
    //���ɱ�
    gm.insert(1, 1, 0, 1); // A -> B
    gm.insert(1, 1, 1, 2); // B -> C
    gm.insert(1, 1, 0, 3); // A -> D
    gm.insert(1, 1, 1, 4); // B -> E
    gm.insert(1, 1, 3, 4); // D -> E
    gm.insert(1, 1, 4, 5); // E -> F
    std::cout << "����ͼ����:" << std::endl;
    std::cout << "     A -> B -> C" << std::endl;
    std::cout << "     ��    ��" << std::endl;
    std::cout << "     D -> E -> F" << std::endl;

    // �����������������DFS��
    std::cout << "�Ӷ��� 'A' ��ʼ�����������:" << std::endl;
    gm.dfs(0); 

    // ���Թ������������BFS��
    std::cout << "�Ӷ��� 'A' ��ʼ�����������:" << std::endl;
    gm.bfs(0); 

    
}