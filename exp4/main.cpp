//#include "Graph.h"
#include "GraphMatrix.h"

int main(void)
{
	GraphMatrix<char, int> gm;

	//生成顶点
    gm.insert('A');
    gm.insert('B');
    gm.insert('C');
    gm.insert('D');
    gm.insert('E');
    gm.insert('F');
    //生成边
    gm.insert(1, 1, 0, 1); // A -> B
    gm.insert(1, 1, 1, 2); // B -> C
    gm.insert(1, 1, 0, 3); // A -> D
    gm.insert(1, 1, 1, 4); // B -> E
    gm.insert(1, 1, 3, 4); // D -> E
    gm.insert(1, 1, 4, 5); // E -> F
    std::cout << "测试图如下:" << std::endl;
    std::cout << "     A -> B -> C" << std::endl;
    std::cout << "     ↓    ↓" << std::endl;
    std::cout << "     D -> E -> F" << std::endl;

    // 测试深度优先搜索（DFS）
    std::cout << "从顶点 'A' 开始深度优先搜索:" << std::endl;
    gm.dfs(0); 

    // 测试广度优先搜索（BFS）
    std::cout << "从顶点 'A' 开始广度优先搜索:" << std::endl;
    gm.bfs(0); 

    
}