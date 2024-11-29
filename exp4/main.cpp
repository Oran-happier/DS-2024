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
    gm.insert(1, 1, 0, 1); // A -1-> B
    gm.insert(1, 3, 1, 2); // B -3-> C
    gm.insert(1, 4, 0, 3); // A -4-> D
    gm.insert(1, 5, 1, 4); // B -5-> E
    gm.insert(1, 7, 3, 4); // D -7-> E
    gm.insert(1, 6, 4, 5); // E -6-> F
    std::cout << "����ͼ����:" << std::endl;
    std::cout << "     A -1-> B -3-> C" << std::endl;
    std::cout << "     ��    ��         " << std::endl;
    std::cout << "     4    5         " << std::endl;
    std::cout << "     ��    ��         " << std::endl;
    std::cout << "     D -7-> E -6-> F" << std::endl;

    // �����������������DFS��
    std::cout << "\n�Ӷ��� 'A' ��ʼ�����������:" << std::endl;
    gm.dfs(0); 

    // ���Թ������������BFS��
    std::cout << "\n\n�Ӷ��� 'A' ��ʼ�����������:" << std::endl;
    gm.bfs(0); 

    //���ȼ�������

    //����prim
    std::cout << "\n�Ӷ��� 'A' ��ʼprim����:" << std::endl;
    PrimPU<char, int> PrimPU;
    gm.pfs(0, PrimPU);
    gm.printMST();
    //prim

    std::cout << "\n�Ӷ��� 'A' ��ʼDijkstra����:" << std::endl;
    DijkPU<char, int> dijkPU;
    gm.pfs(0, dijkPU);
    gm.output_distance(0);
    //Dijska

    return 0;
}