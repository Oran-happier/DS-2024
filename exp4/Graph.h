#pragma once

#include "Stack.h"
#include "Queue.h"
#define Rank int
typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus; //����״̬
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType; //���ڱ�����������������

template <typename Tv, typename Te> //�������͡�������
class Graph
{
private:
	void reset()
	{
		for (Rank v = 0; v < n; v++)
		{ //���ж����
			status(v) = UNDISCOVERED; dTime(v) = fTime(v) = -1; //״̬��ʱ���ǩ
			parent(v) = -1; priority(v) = INT_MAX; //���ڱ������еģ����ڵ㣬���ȼ���
			for (Rank u = 0; u < n; u++) //���бߵ�
				if (exists(v, u)) type(v, u) = UNDETERMINED; //����
		}
	}
	void BFS(Rank, Rank&); //����ͨ�򣩹�����������㷨
	void DFS(Rank, Rank&); //����ͨ��������������㷨
	void BCC(Rank, Rank&, Stack<Rank>&); //����ͨ�򣩻���DFS��˫��ͨ�����ֽ��㷨
	bool TSort(Rank, Rank&, Stack<Tv>*); //����ͨ�򣩻���DFS�����������㷨
	template <typename PU> void PFS(Rank, PU); //����ͨ�����ȼ��������

public:
// ����
	Rank n; //��������
	virtual Rank insert(Tv const&) = 0; //���붥�㣬���ر��
	virtual Tv remove(Rank) = 0; //ɾ�����㼰������ߣ����ظö�����Ϣ
	virtual Tv& vertex(Rank) = 0; //��������ݣ��ö����ȷ���ڣ�
	virtual Rank inDegree(Rank) = 0; //�������ȣ��ö����ȷ���ڣ�
	virtual Rank outDegree(Rank) = 0; //����ĳ��ȣ��ö����ȷ���ڣ�
	virtual Rank firstNbr(Rank) = 0; //������׸��ڽӶ���
	virtual Rank nextNbr(Rank, Rank) = 0; //���㣨��Ե�ǰ�ھӵģ���һ�ھ�
	virtual VStatus& status(Rank) = 0; //�����״̬
	virtual Rank& dTime(Rank) = 0; //�����ʱ���ǩdTime
	virtual Rank& fTime(Rank) = 0; //�����ʱ���ǩfTime
	virtual Rank& parent(Rank) = 0; //�����ڱ������еĸ���
	virtual int& priority(Rank) = 0; //�����ڱ������е����ȼ���
// �ߣ�����Լ��������߾�ͳһת��Ϊ�������һ������ߣ��Ӷ�������ͼ��������ͼ������
	Rank e; //������
	virtual bool exists(Rank, Rank) = 0; //��(v, u)�Ƿ����
	virtual void insert(Te const&, int, Rank, Rank) = 0; //����������֮�����ָ��Ȩ�صı�
	virtual Te remove(Rank, Rank) = 0; //ɾ��һ�Զ���֮��ıߣ����ظñ���Ϣ
	virtual EType& type(Rank, Rank) = 0; //�ߵ�����
	virtual Te& edge(Rank, Rank) = 0; //�ߵ����ݣ��ñߵ�ȷ���ڣ�
	virtual int& weight(Rank, Rank) = 0; //��(v, u)��Ȩ��
// �㷨
	void bfs(Rank); //������������㷨
	void dfs(Rank); //������������㷨
	void bcc(Rank); //����DFS��˫��ͨ�����ֽ��㷨
	//Stack<Tv>* tSort(Rank); //����DFS�����������㷨
	void prim(Rank); //��С֧����Prim�㷨
	void dijkstra(Rank); //���·��Dijkstra�㷨
	template <typename PU> void pfs(Rank, PU); //���ȼ��������

//����������
	void output_distance(int);//���������Ϣ
	void printMST();//�����С֧������Ϣ

};

template <typename Tv, typename Te> //�����������BFS�㷨��ȫͼ��
void Graph<Tv, Te>::bfs(Rank s)
{ // s < n
	reset(); Rank dClock = 0; //ȫͼ��λ
	for (Rank v = s; v < s + n; v++) //��s��˳�μ�����ж���
		if (UNDISCOVERED == status(v % n)) //һ��������δ������
			BFS(v % n, dClock); //��������������һ��BFS
}//��˿���������ȫͼ�������帴�Ӷ���Ȼ����ΪO(n+e)

template <typename Tv, typename Te> //�����������BFS�㷨��������ͨ��
void Graph<Tv, Te>::BFS(Rank v, Rank& dClock) { // v < n
	Queue<Rank> Q; status(v) = DISCOVERED; Q.enqueue(v); dTime(v) = dClock++; //������
	for (Rank fClock = 0; !Q.empty(); )
	{ //��Q���֮ǰ��������
		if (dTime(v) < dTime(Q.front())) //dTime�����ӣ���ζ�ſ����µ�һ�������
			dClock++, fClock = 0; //dTime������fTime��λ
		v = Q.dequeue(); //ȡ���׶���v����
		for (Rank u = firstNbr(v); -1 != u; u = nextNbr(v, u)) //����v��ÿһ���ھ�u
			if (UNDISCOVERED == status(u))
			{ //��u��δ�����֣�����֮
				status(u) = DISCOVERED; Q.enqueue(u); dTime(u) = dClock;
				type(v, u) = TREE; parent(u) = v; //�������ߣ���չBFS��
				std::cout << (char) (97+u) << ' ';//���Ŀǰ���ֵ��ھ�u
			}
			else //��u�ѱ����֣����������ѷ�����ϣ���
				type(v, u) = CROSS; //��(v, u)�����ڿ��
		status(v) = VISITED; fTime(v) = fClock++; //���ˣ�v�������
	}//for
}//BFS

template <typename Tv, typename Te> //�����������DFS�㷨��ȫͼ��
void Graph<Tv, Te>::dfs(Rank s)
{ // s < n
	reset(); Rank clock = 0; //ȫͼ��λ
	for (Rank v = s; v < s + n; v++) //��s��˳�μ�����ж���
		if (UNDISCOVERED == status(v % n)) //һ��������δ������
			DFS(v % n, clock); //��������������һ��DFS
} //��˿���������ȫͼ�������帴�Ӷ���Ȼ����ΪO(n+e)

template<typename Tv, typename Te>
inline void Graph<Tv, Te>::output_distance(int s)
{
	for (int w = s + 1; w < Graph<Tv, Te>::n; w++)
	{
		std::cout << "�Ӷ��� " << vertex(s) << " ���ﶥ�� " << vertex(w) << " �ľ���Ϊ " << priority(w) << std::endl;//�����ǰ�ڵ���Ϣ
	}
}

template<typename Tv, typename Te>
inline void Graph<Tv, Te>::printMST()
{
	for (int v = 0; v < this->n; ++v)
	{
		int p = this->parent(v);  // ��ȡ���ڵ�
		if (p != -1)
		{
			std::cout << "�� : " << vertex(p) << " ->���� " << vertex(v) << " ��Ȩ��Ϊ�� " << this->weight(p, v) << std::endl;
		}
	}
}

template <typename Tv, typename Te> //�����������DFS�㷨��������ͨ��
void Graph<Tv, Te>::DFS(Rank v, Rank& clock)
{ // v < n
	dTime(v) = clock++; status(v) = DISCOVERED; //���ֵ�ǰ����v
	for (Rank u = firstNbr(v); -1 != u; u = nextNbr(v, u)) //����v��ÿһ���ھ�u
		switch (status(u)) { //������״̬�ֱ���
		case UNDISCOVERED: // u��δ���֣���ζ��֧�������ڴ���չ
			type(v, u) = TREE; parent(u) = v; std::cout << (char)(97 + u) << ' ';DFS(u, clock);break;
		case DISCOVERED: // u�ѱ����ֵ���δ������ϣ�Ӧ�������ָ�������
			type(v, u) = BACKWARD;break;
		default: // u�ѷ�����ϣ�VISITED������ͼ�������ӳ�Ϯ��ϵ��Ϊǰ��߻���
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS; break;
		}
	status(v) = VISITED; fTime(v) = clock++; //���ˣ���ǰ����v����������
}

template <typename Tv, typename Te> //����DFS�����������㷨�����ˣ�
bool Graph<Tv, Te>::TSort(Rank v, Rank& clock, Stack<Tv>* S)
{ // v < n
	dTime(v) = ++clock; status(v) = DISCOVERED; //���ֶ���v
	for (Rank u = firstNbr(v); -1 != u; u = nextNbr(v, u)) //ö��v�������ھ�u
		switch (status(u))
		{ //����u��״̬�ֱ���
		case UNDISCOVERED:
			parent(u) = v; type(v, u) = TREE;
			if (!TSort(u, clock, S)) //�Ӷ���u��������������
				return false; //��u��������������������ȫͼ�����ˣ����ʷ��ز�����
			break;
		case DISCOVERED:
			type(v, u) = BACKWARD; //һ�����ֺ���ߣ���DAG������
			return false; //�������룬�ʷ��ز�����
		default: // VISITED (digraphs only)
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
			break;
		}
	status(v) = VISITED; S->push(vertex(v)); //���㱻���ΪVISITEDʱ���漴��ջ
	return true; // v������������������
}

template <typename Tv, typename Te> template <typename PU> //���ȼ�������ȫͼ��
void Graph<Tv, Te>::pfs(Rank s, PU prioUpdater) { // s < n
	reset(); //ȫͼ��λ
	for (Rank v = s; v < s + n; v++) //��s��˳�μ�����ж���
		if (UNDISCOVERED == status(v % n)) //һ��������δ������
			PFS(v % n, prioUpdater); //��������������һ��PFS
} //��˿���������ȫͼ�������帴�Ӷ���Ȼ����ΪO(n+e)

template <typename Tv, typename Te> template <typename PU> //�������͡������͡����ȼ�������
void Graph<Tv, Te>::PFS(Rank v, PU prioUpdater)
{ //���ȼ�������������ͨ��
	priority(v) = 0; status(v) = VISITED; //��ʼ�������v����PFS����
	for ( Rank k = 1 ; k < n ; k++ ) { //�𲽽�n-1�����n-1���߼���PFS����
		for (Rank u = firstNbr(v); -1 != u; u = nextNbr(v, u)) //��v��ÿһ���ھ�u
			prioUpdater(this, v, u); //���������ȼ����丸��
		int shortest = INT_MAX;
		for (Rank u = 0; u < n; u++) //����δ����������Ķ����У�ѡ����һ�����ȼ�
			if ((UNDISCOVERED == status(u)) && (shortest > priority(u))) //��ߵ�
			{
				shortest = priority(u), v = u;
			} //����v
		status(v) = VISITED; type(parent(v), v) = TREE; //��v���������
	} //for
} //ͨ�������������ȼ����²���prioUpdater������ʵ�ֲ�ͬ���㷨����

template <typename Tv, typename Te> struct PrimPU 
{ //���Prim�㷨�Ķ������ȼ�������
	virtual void operator()(Graph<Tv, Te>* g, Rank v, Rank u) {
		if (UNDISCOVERED == g->status(u)) //����vÿһ��δ�����ֵ��ڽӶ���u
			if (g->priority(u) > g->weight(v, u)) { //��Prim�������ɳ�
				g->priority(u) = g->weight(v, u); //�������ȼ�������
				g->parent(u) = v; //���¸��ڵ�
			}
	}
};

template <typename Tv, typename Te> struct DijkPU
{ //���Dijkstra�㷨�Ķ������ȼ�������
	virtual void operator()(Graph<Tv, Te>* g, Rank v, Rank u)
	{
		if (UNDISCOVERED == g->status(u)) //����vÿһ��δ�����ֵ��ڽӶ���u����Dijkstra����
			if (g->priority(u) > g->priority(v) + g->weight(v, u)) { //���ɳ�
				g->priority(u) = g->priority(v) + g->weight(v, u); //�������ȼ�������
				g->parent(u) = v; //��ͬʱ���¸��ڵ�
			}
	}
};
