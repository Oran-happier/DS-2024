#pragma once

#include "Stack.h"
#include "Queue.h"
#define Rank int
typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus; //顶点状态
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType; //边在遍历树中所属的类型

template <typename Tv, typename Te> //顶点类型、边类型
class Graph
{
private:
	void reset()
	{
		for (Rank v = 0; v < n; v++)
		{ //所有顶点的
			status(v) = UNDISCOVERED; dTime(v) = fTime(v) = -1; //状态，时间标签
			parent(v) = -1; priority(v) = INT_MAX; //（在遍历树中的）父节点，优先级数
			for (Rank u = 0; u < n; u++) //所有边的
				if (exists(v, u)) type(v, u) = UNDETERMINED; //类型
		}
	}
	void BFS(Rank, Rank&); //（连通域）广度优先搜索算法
	void DFS(Rank, Rank&); //（连通域）深度优先搜索算法
	void BCC(Rank, Rank&, Stack<Rank>&); //（连通域）基于DFS的双连通分量分解算法
	bool TSort(Rank, Rank&, Stack<Tv>*); //（连通域）基于DFS的拓扑排序算法
	template <typename PU> void PFS(Rank, PU); //（连通域）优先级搜索框架

public:
// 顶点
	Rank n; //顶点总数
	virtual Rank insert(Tv const&) = 0; //插入顶点，返回编号
	virtual Tv remove(Rank) = 0; //删除顶点及其关联边，返回该顶点信息
	virtual Tv& vertex(Rank) = 0; //顶点的数据（该顶点的确存在）
	virtual Rank inDegree(Rank) = 0; //顶点的入度（该顶点的确存在）
	virtual Rank outDegree(Rank) = 0; //顶点的出度（该顶点的确存在）
	virtual Rank firstNbr(Rank) = 0; //顶点的首个邻接顶点
	virtual Rank nextNbr(Rank, Rank) = 0; //顶点（相对当前邻居的）下一邻居
	virtual VStatus& status(Rank) = 0; //顶点的状态
	virtual Rank& dTime(Rank) = 0; //顶点的时间标签dTime
	virtual Rank& fTime(Rank) = 0; //顶点的时间标签fTime
	virtual Rank& parent(Rank) = 0; //顶点在遍历树中的父亲
	virtual int& priority(Rank) = 0; //顶点在遍历树中的优先级数
// 边：这里约定，无向边均统一转化为方向互逆的一对有向边，从而将无向图视作有向图的特例
	Rank e; //边总数
	virtual bool exists(Rank, Rank) = 0; //边(v, u)是否存在
	virtual void insert(Te const&, int, Rank, Rank) = 0; //在两个顶点之间插入指定权重的边
	virtual Te remove(Rank, Rank) = 0; //删除一对顶点之间的边，返回该边信息
	virtual EType& type(Rank, Rank) = 0; //边的类型
	virtual Te& edge(Rank, Rank) = 0; //边的数据（该边的确存在）
	virtual int& weight(Rank, Rank) = 0; //边(v, u)的权重
// 算法
	void bfs(Rank); //广度优先搜索算法
	void dfs(Rank); //深度优先搜索算法
	void bcc(Rank); //基于DFS的双连通分量分解算法
	//Stack<Tv>* tSort(Rank); //基于DFS的拓扑排序算法
	void prim(Rank); //最小支撑树Prim算法
	void dijkstra(Rank); //最短路径Dijkstra算法
	template <typename PU> void pfs(Rank, PU); //优先级搜索框架

//输出结果函数
	void output_distance(int);//输出距离信息
	void printMST();//输出最小支撑树信息

};

template <typename Tv, typename Te> //广度优先搜索BFS算法（全图）
void Graph<Tv, Te>::bfs(Rank s)
{ // s < n
	reset(); Rank dClock = 0; //全图复位
	for (Rank v = s; v < s + n; v++) //从s起顺次检查所有顶点
		if (UNDISCOVERED == status(v % n)) //一旦遇到尚未发现者
			BFS(v % n, dClock); //即从它出发启动一次BFS
}//如此可完整覆盖全图，且总体复杂度依然保持为O(n+e)

template <typename Tv, typename Te> //广度优先搜索BFS算法（单个连通域）
void Graph<Tv, Te>::BFS(Rank v, Rank& dClock) { // v < n
	Queue<Rank> Q; status(v) = DISCOVERED; Q.enqueue(v); dTime(v) = dClock++; //起点入队
	for (Rank fClock = 0; !Q.empty(); )
	{ //在Q变空之前，反复地
		if (dTime(v) < dTime(Q.front())) //dTime的增加，意味着开启新的一代，因此
			dClock++, fClock = 0; //dTime递增，fTime复位
		v = Q.dequeue(); //取出首顶点v，并
		for (Rank u = firstNbr(v); -1 != u; u = nextNbr(v, u)) //考查v的每一个邻居u
			if (UNDISCOVERED == status(u))
			{ //若u尚未被发现，则发现之
				status(u) = DISCOVERED; Q.enqueue(u); dTime(u) = dClock;
				type(v, u) = TREE; parent(u) = v; //引入树边，拓展BFS树
				std::cout << (char) (97+u) << ' ';//输出目前发现的邻居u
			}
			else //若u已被发现，或者甚至已访问完毕，则
				type(v, u) = CROSS; //将(v, u)归类于跨边
		status(v) = VISITED; fTime(v) = fClock++; //至此，v访问完毕
	}//for
}//BFS

template <typename Tv, typename Te> //深度优先搜索DFS算法（全图）
void Graph<Tv, Te>::dfs(Rank s)
{ // s < n
	reset(); Rank clock = 0; //全图复位
	for (Rank v = s; v < s + n; v++) //从s起顺次检查所有顶点
		if (UNDISCOVERED == status(v % n)) //一旦遇到尚未发现者
			DFS(v % n, clock); //即从它出发启动一次DFS
} //如此可完整覆盖全图，且总体复杂度依然保持为O(n+e)

template<typename Tv, typename Te>
inline void Graph<Tv, Te>::output_distance(int s)
{
	for (int w = s + 1; w < Graph<Tv, Te>::n; w++)
	{
		std::cout << "从顶点 " << vertex(s) << " 到达顶点 " << vertex(w) << " 的距离为 " << priority(w) << std::endl;//输出当前节点信息
	}
}

template<typename Tv, typename Te>
inline void Graph<Tv, Te>::printMST()
{
	for (int v = 0; v < this->n; ++v)
	{
		int p = this->parent(v);  // 获取父节点
		if (p != -1)
		{
			std::cout << "边 : " << vertex(p) << " ->顶点 " << vertex(v) << " 的权重为： " << this->weight(p, v) << std::endl;
		}
	}
}

template <typename Tv, typename Te> //深度优先搜索DFS算法（单个连通域）
void Graph<Tv, Te>::DFS(Rank v, Rank& clock)
{ // v < n
	dTime(v) = clock++; status(v) = DISCOVERED; //发现当前顶点v
	for (Rank u = firstNbr(v); -1 != u; u = nextNbr(v, u)) //考查v的每一个邻居u
		switch (status(u)) { //并视其状态分别处理
		case UNDISCOVERED: // u尚未发现，意味着支撑树可在此拓展
			type(v, u) = TREE; parent(u) = v; std::cout << (char)(97 + u) << ' ';DFS(u, clock);break;
		case DISCOVERED: // u已被发现但尚未访问完毕，应属被后代指向的祖先
			type(v, u) = BACKWARD;break;
		default: // u已访问完毕（VISITED，有向图），则视承袭关系分为前向边或跨边
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS; break;
		}
	status(v) = VISITED; fTime(v) = clock++; //至此，当前顶点v方告访问完毕
}

template <typename Tv, typename Te> //基于DFS的拓扑排序算法（单趟）
bool Graph<Tv, Te>::TSort(Rank v, Rank& clock, Stack<Tv>* S)
{ // v < n
	dTime(v) = ++clock; status(v) = DISCOVERED; //发现顶点v
	for (Rank u = firstNbr(v); -1 != u; u = nextNbr(v, u)) //枚举v的所有邻居u
		switch (status(u))
		{ //并视u的状态分别处理
		case UNDISCOVERED:
			parent(u) = v; type(v, u) = TREE;
			if (!TSort(u, clock, S)) //从顶点u处出发深入搜索
				return false; //若u及其后代不能拓扑排序（则全图亦必如此），故返回并报告
			break;
		case DISCOVERED:
			type(v, u) = BACKWARD; //一旦发现后向边（非DAG），则
			return false; //不必深入，故返回并报告
		default: // VISITED (digraphs only)
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
			break;
		}
	status(v) = VISITED; S->push(vertex(v)); //顶点被标记为VISITED时，随即入栈
	return true; // v及其后代可以拓扑排序
}

template <typename Tv, typename Te> template <typename PU> //优先级搜索（全图）
void Graph<Tv, Te>::pfs(Rank s, PU prioUpdater) { // s < n
	reset(); //全图复位
	for (Rank v = s; v < s + n; v++) //从s起顺次检查所有顶点
		if (UNDISCOVERED == status(v % n)) //一旦遇到尚未发现者
			PFS(v % n, prioUpdater); //即从它出发启动一次PFS
} //如此可完整覆盖全图，且总体复杂度依然保持为O(n+e)

template <typename Tv, typename Te> template <typename PU> //顶点类型、边类型、优先级更新器
void Graph<Tv, Te>::PFS(Rank v, PU prioUpdater)
{ //优先级搜索（单个连通域）
	priority(v) = 0; status(v) = VISITED; //初始化，起点v加至PFS树中
	for ( Rank k = 1 ; k < n ; k++ ) { //逐步将n-1顶点和n-1条边加至PFS树中
		for (Rank u = firstNbr(v); -1 != u; u = nextNbr(v, u)) //对v的每一个邻居u
			prioUpdater(this, v, u); //更新其优先级及其父亲
		int shortest = INT_MAX;
		for (Rank u = 0; u < n; u++) //从尚未加入遍历树的顶点中，选出下一个优先级
			if ((UNDISCOVERED == status(u)) && (shortest > priority(u))) //最高的
			{
				shortest = priority(u), v = u;
			} //顶点v
		status(v) = VISITED; type(parent(v), v) = TREE; //将v加入遍历树
	} //for
} //通过定义具体的优先级更新策略prioUpdater，即可实现不同的算法功能

template <typename Tv, typename Te> struct PrimPU 
{ //针对Prim算法的顶点优先级更新器
	virtual void operator()(Graph<Tv, Te>* g, Rank v, Rank u) {
		if (UNDISCOVERED == g->status(u)) //对于v每一尚未被发现的邻接顶点u
			if (g->priority(u) > g->weight(v, u)) { //按Prim策略做松弛
				g->priority(u) = g->weight(v, u); //更新优先级（数）
				g->parent(u) = v; //更新父节点
			}
	}
};

template <typename Tv, typename Te> struct DijkPU
{ //针对Dijkstra算法的顶点优先级更新器
	virtual void operator()(Graph<Tv, Te>* g, Rank v, Rank u)
	{
		if (UNDISCOVERED == g->status(u)) //对于v每一尚未被发现的邻接顶点u，按Dijkstra策略
			if (g->priority(u) > g->priority(v) + g->weight(v, u)) { //做松弛
				g->priority(u) = g->priority(v) + g->weight(v, u); //更新优先级（数）
				g->parent(u) = v; //并同时更新父节点
			}
	}
};
