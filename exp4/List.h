#pragma once
#include "ListNode.h"//�����б�ڵ���

template <typename T> class List
{//�б�ģ����
private:
	int _size; ListNodePosi(T) head;ListNodePosi(T) tail;//��ģ��ͷ�ڱ���β�ڱ�

protected:
	void init();//�б���ʱ�ĳ�ʼ��
	Rank clear();//������нڵ�
	void copyNodes(ListNodePosi(T), Rank);//�����б�����λ��p���n��
	ListNodePosi(T) merge(ListNodePosi(T), Rank, List<T>&, ListNodePosi(T), Rank); //#
	void mergeSort(ListNodePosi(T)&, Rank);//�Դ�p��ʼ������n���ڵ�鲢����
	void selectionSort(ListNodePosi(T), Rank);//�Դ�p��ʼ������n���ڵ�ѡ������
	void insertionSort(ListNodePosi(T), Rank);//�Դ�p��ʼ������n���ڵ��������
	void radixSort(ListNodePosi(T), Rank);//�Դ�p��ʼ������n���ڵ��������

public:
	// ���췽��
	List() { init(); }//Ĭ��
	List(List<T>const& L);//���帴���б�L
	List(List<T> const& L, Rank r, Rank n);//�����б�L���Ե�r�����n��
	List(ListNodePosi(T) p, Rank n);//�����б�����λ��p���n��
	// ��������
	~List();//�ͷ�(����ͷ��β�ڱ����ڵ�)���нڵ�
	//ֻ�����ʽӿ�
	Rank size() const { return _size; }//��ģ
	bool empty() const { return _size <= 0; }//�п�
	ListNodePosi(T)operator[](Rank r)const;//����,֧��ѭ�ȷ���(Ч�ʵ�)
	ListNodePosi(T) first()const { return head->succ; }//�׽ڵ�λ��
	ListNodePosi(T) last() const { return tail->pred; }//ĩ�ڵ�λ��
	bool valid(ListNodePosi(T)p)//�ж�λ��p�Ƿ����Ϸ�
	{
		return p && (tail != p) && (head != p);
	}//��ͷ��β�ڵ��ͬ��NULL
	ListNodePosi(T) find(T const& e)const //�����б����
	{
		return find(e, _size, tail);
	}
	ListNodePosi(T) find(T const& e, Rank n, ListNodePosi(T) p)const;//�����������
	ListNodePosi(T) search(T const& e)const //�����б����
	{
		return search(e, size, tail);
	}
	ListNodePosi(T) search(T const& e, Rank n, ListNodePosi(T) p)const;//�����������
	ListNodePosi(T) selectMax(ListNodePosi(T) p, Rank n);//��p����n-1�������ѡ�������
	ListNodePosi(T) selectMax() { return selectMax(head->succ, _size); }//���������
	// ��д���ʽӿ�
	ListNodePosi(T) insertFirst(T const& e);//��e�����׽ڵ����
	ListNodePosi(T) insertLast(T const& e);//��e����ĩ�ڵ����
	ListNodePosi(T) insertA(ListNodePosi(T) p, T const& e);//��e����p�ĺ�̲���
	ListNodePosi(T) insertB(T const& e, ListNodePosi(T)p);//��e����p��ǰ������
	T remove(ListNodePosi(T)p);//ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�
	void merge(List<T>& L) { merge(head->succ, _size, L, L.head->succ, L._size); }//ȫ�б�鲢
	void sort(ListNodePosi(T), Rank);//�б���������
	void sort() { sort(first(), _size); }//�б���������
	Rank dedup();//����ȥ��
	Rank uniquify();//����ȥ��
	void reverse();//ǰ����(ϰ��)
	// ����
	void traverse(void(*)(T&));//����ʵʩvisit����(����ָ��)
	template<typename VST>void traverse(VST&);//����ʵʩvisit����(��������)
}; //List

template <typename T>void List<T> ::init() {//�б��ʼ��,�ڴ����б����ʱͳһ����
	head = new ListNode<T>; tail = new ListNode<T>;//����ͷ��β�ڱ��ڵ�
	head->succ = tail; head->pred = NULL;//��ǰ����
	tail->pred = head; tail->succ = NULL; //�������
	_size = 0; //��¼��ģ
}

template<typename T>//�����±������,��ͨ����ֱ�ӷ����б�ڵ�(0(r)Ч��,�䷽��,�����)
ListNodePosi(T) List<T>:: operator[] (Rank r) const { // 0 <= r < size
	ListNodePosi(T)p = first();//���׽ڵ����
	while (0 < r--)p = p->succ;//˳����r���ڵ㼴��
	return p;//Ŀ��ڵ�
}

template<typename T>//�������б��ڽڵ�p(������tail)��n��(��)ǰ����,�ҵ�����e�������
ListNodePosi(T) List<T>::find(T const& e, Rank n, ListNodePosi(T) p) const {
	while (0 < n--)//(0 <= n <= Rank(p) <_size)����p�������n��ǰ��,��������
		if (e == (p = p->pred)->data)return p; //����ȶ�,ֱ�����л�ΧԽ��
	return NULL;//pԽ����߽���ζ�������ڲ���e,����ʧ��
}//ʧ��ʱ,����NULL

template <typename T> ListNodePosi(T) List<T>:: insertFirst(T const& e)
{
	_size++; return head->insertSucc(e);
} // e�����׽ڵ����

template <typename T> ListNodePosi(T) List<T>:: insertLast(T const& e)
{
	_size++; return tail->insertPred(e);
} // e����ĩ�ڵ����

template <typename T> ListNodePosi(T) List<T>:: insertA(ListNodePosi(T) p, T const& e)
{
	_size++; return p->insertSucc(e);
} // e����p�ĺ�̲���

template <typename T> ListNodePosi(T) List<T>::insertB(T const& e, ListNodePosi(T) p)
{
	_size++; return p->insertPred(e); 
} // e����p��ǰ������

template<typename T>//��e������ǰ�ڵ�֮ǰ�����ڵ�ǰ�ڵ������б�(�����ڱ�head)
ListNodePosi(T) ListNode<T> ::insertPred(T const& e) {
	ListNodePosi(T) x = new ListNode(e, pred, this);//�����½ڵ�
	pred->succ = x; pred = x;//������������
	return x;//�����½ڵ��λ��
}

template<typename T>//��e���浱ǰ�ڵ�֮������ڵ�ǰ�ڵ������б�(�����ڱ�tail)
ListNodePosi(T) ListNode<T> ::insertSucc(T const& e) {
	ListNodePosi(T) x = new ListNode(e, this, succ);//�����½ڵ�
	succ->pred = x; succ = x;//������������
	return x;//�����½ڵ��λ��
}

template<typename T>//�б��ڲ�����:�����б�����λ��p���n��
void List<T>::copyNodes(ListNodePosi(T) p, Rank n) {//p�Ϸ�,��������n-1������
	init();//����ͷ��β�ڱ��ڵ㲢����ʼ��
	while (n--) { insertLast(p->data); p = p->succ; }//������p��n��������Ϊĩ�ڵ����
}

template<typename T>//�����б�����λ��p���n��(assert:pΪ�Ϸ�λ��,��������n-1����̽ڵ�)
List<T>::List(ListNodePosi(T) p, Rank n) { copyNodes(p, n); }

template <typename T>//���帴���б�L
List<T>::List(List<T> const& L) { copyNodes(L.first(), L._size); }

template<typename T>//����L���Ե�r�����n��(assert: r+n <= L._size)
List<T>::List(List<T> const& L, Rank r, Rank n) {
	ListNodePosi(T) p = L.first();
	while (0 < r--) p = p->succ;
	copyNodes(p, n);
}

template <typename T> T List<T>::remove(ListNodePosi(T) p) { //ɾ���Ϸ��ڵ�p
	T e = p->data;//���ݴ�ɾ���ڵ����ֵ(�ٶ�T���Ϳ�ֱ�Ӹ�ֵ)
	p->pred->succ = p->succ; p->succ->pred = p->pred;//��·����
	delete p; _size--; //�ͷŽڵ�,���¹�ģ
	return e;//���ر��ݵ���ֵ
} //0(1)

template <typename T> List<T>::~List() //�б�������
{ clear(); delete head; delete tail; } //����б��ͷ�ͷ��β�ڱ��ڵ�

template <typename T> Rank List<T>::clear() {//����б�
	Rank oldSize = _size;
	while (0 < _size)remove(head->succ);//����ɾ���׽ڵ�,ֱ���б���
	return oldSize;
}

template <typename T> Rank List<T>::dedup() {
	Rank oldSize = _size; ListNodePosi(T) p = first();
	for (Rank r = 0; p != tail; p = p->succ) //0(n)
		if (ListNodePosi(T) q = find(p->data, r, p))
			remove(q);//��ʱq��p���,��ɾ��ǰ�߸�Ϊ����
		else r++; //rΪ����ǰ׺�ĳ���
	return oldSize - _size;//ɾ��Ԫ������
}

template <typename T> void List<T>::traverse(void(*visit)(T&))//��������ָ����Ʊ���
{
	for (ListNodePosi(T) p = head->succ; p != tail; p = p->succ) visit(p->data);
}

template<typename T> template<typename VST>//Ԫ�����͡�������
void List<T>::traverse(VST& visit)//��������������Ʊ���
{
	for (ListNodePosi(T) p = head->succ; p != tail; p = p->succ) visit(p->data);
}

template <typename T>Rank List<T>::uniquify() {//�����޳��ظ�Ԫ��,Ч�ʸ���
	if (_size < 2)return 0;//ƽ���б�,��Ȼ�������Ԫ��
	Rank oldSize = _size;//��¼ԭ��ģ
	ListNodePosi(T) p = first(); ListNodePosi(T)q;//pΪ���������,qΪ����
	while (tail != (q = p->succ))//����������ڵĽڵ��(p,q)
		if (p->data != q->data)p = q;//������,��ת����һ����
		else remove(q);//����(���)ֱ��ɾ������,����������������ӵ����ɾ��
	return oldSize - _size;//�б��ģ�仯��,����ɾ��Ԫ������
}

template<typename T>//�������б��ڽڵ�p(������tail)��n����ǰ����,�ҵ�������e�������
ListNodePosi(T) List<T> ::search(T const& e, Rank n, ListNodePosi(T) p) const {
	do {//��ʼ��:0 <= n <= rank(p) <_size;�˺�,n���ǵ���p�ڲ��������ڵ���
		p = p->pred; n--; //��������
	} while ((-1 != n) && (e < p->data));//����Ƚ�,ֱ��Խ�������
	return p; //��������ֹͣ��λ��
}//ʧ��ʱ����������߽��ǰ��(������head)-�����߿ɾݴ��жϲ����Ƿ�ɹ�

template<typename T>//���б�����ʼ��λ��p�����Ϊn����������������
void List<T>::insertionSort(ListNodePosi(T) p, Rank n) { // valid(p) && Rank(p) + n <= size
	for (Rank r = 0; r < n; r++) {//��һΪ���ڵ�
		insert(search(p->data, r, p), p->data);//�����ʵ���λ�ò�����
		p = p->succ; remove(p->pred);//ת����һ�ڵ�
	}
}

template <typename T>//���б�����ʼ��λ��p�����Ϊn��������ѡ������
void List<T> ::selectionSort(ListNodePosi(T) p, Rank n) { // valid(p) && Rank(p) + n <= size
	ListNodePosi(T)h = p->pred; //����������Ϊ(h,t)
	ListNodePosi(T) t = p; for (Rank i = 0; i < n; i++) t = t->succ;
	while (1 < n) {//�����ٻ�ʣ�����ڵ�֮ǰ,�ڴ�����������
		ListNodePosi(T) max = selectMax(h->succ, n);//�ҳ������(����ʱ��������)
		insert(remove(max), t);//����������������ĩβ(��Ϊ���������µ���Ԫ��)
		t = t->pred; n--;
	}
}

template<typename T>//����ʼ��λ��p��n��Ԫ����ѡ�������
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, Rank n) {
	ListNodePosi(T) max = p; //������ݶ�Ϊ�׽ڵ�p
	for (ListNodePosi(T) cur = p; 1 < n; n--)//���׽ڵ�p����,�������ڵ���һ��max�Ƚ�
		if (!((cur = cur->succ)->data < max->data))//����ǰԪ�ز�С��max,��
			max = cur;//�������Ԫ��λ�ü�¼
	return max;//�������ڵ�λ��
}

template<typename T>//�����б�Ĺ鲢:��ǰ�б�����p���n��Ԫ��,���б�L����q���m��Ԫ�ع鲢
ListNodePosi(T) List<T>::merge(ListNodePosi(T) p, Rank n,
	List<T>& L, ListNodePosi(T) q, Rank m) {
	// this.valid(p) && Rank(p) + n <= size && this.sorted(p, n)
	// L.valid(q) && Rank(q) + m <= L._size && L.sorted(q, m)
	// ע��:�ڱ�mergeSort()����ʱ,this == &L && Rank(p)+n= Rank(q)
	ListNodePosi(T)pp = p->pred;//�鲢֮��p���ܲ���ָ���׽ڵ�,�����ȼ���,�Ա��ڷ���ǰ����
	while ((0 < m) && (q != p))//q��δ����(����mergeSort()��,p����δ����)֮ǰ
		if ((0 < n) && (p->data <= q->data))//��p��δ������v(p) <= v(q),��
		{
			p = p->succ; n--;
		}//pֱ�Ӻ���,����ɹ���
		else//����,��qת����p֮ǰ,����ɹ���
		{
			insert(L.remove((q = q->succ)->pred), p); m--;
		}
	return pp->succ;//���µ��׽ڵ�
}

template<typename T>//�б�Ĺ鲢�����㷨:����ʼ��λ��p��n��Ԫ������
void List<T>::mergeSort(ListNodePosi(T)& p, Rank n) { // valid(p) && Rank(p) + n <= size
	if (n < 2)return;//��������Χ���㹻С,��ֱ�ӷ���;���� ..
	Rank m = n >> 1;//���е�Ϊ��
	ListNodePosi(T) q = p; for (Rank i = 0; i < m; i++)q = q->succ; //�ҵ������б����
	mergeSort(p, m); mergeSort(q, n - m);//ǰ�������б���ֱ�����
	p = merge(p, m, *this, q, n - m);//�鲢
}//ע��:�����,p��Ȼָ��鲢�������(��)���

