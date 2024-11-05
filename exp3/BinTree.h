#pragma once
#include "BinNode.h" //����������ڵ���

template <typename T> class BinTree
{
protected:
	int _size; BinNodePosi(T) _root; //��ģ�����ڵ�
public:
	BinTree() : _size(0), _root(nullptr) {} //���췽��
	~BinTree() { if (0 < _size) remove(_root); } //��������
	int size() const { return _size; }
	bool empty() const { return !_root; } //�п�
	BinNodePosi(T) root() const { return _root; }
	BinNodePosi(T) insertAsRoot(T const& e);//������ڵ�
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e);//������ڵ�
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e);//�����ҽڵ�
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &S);//T��Ϊx����������
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &S);//T��Ϊx����������
	int remove(BinNodePosi(T) x); //ɾ����xΪ��������������ԭ�ȵĹ�ģ
	BinTree<T>* secede(BinNodePosi(T)); //������xΪ����������������ת��Ϊ����������
	template <typename VST> //������
	void travLevel(VST& visit) { if (_root) _root->travLevel(visit); } //��α���
	template <typename VST> //������
	void travPre(VST& visit) { if (_root) _root->travPre(visit); } //�������
	template <typename VST> //������
	void travIn(VST& visit) { if (_root) _root->travIn(visit); } //�������
	template <typename VST> //������
	void travPost(VST& visit) { if (_root) _root->travPost(visit); } //�������
	//�Ƚ������������в��䣩
	bool operator<(BinTree<T> const& t) 
	{ return _root && t._root && (*_root < *(t._root)); }
	bool operator==(BinTree<T> const& t) //�е���
	{ return _root && t._root && (_root == t._root); }//�жϵ�ַ��ȣ����û�����𡣡���


	//���¸߶Ⱥ�����Ϊʲô����protected�ڣ�
	int maxHeight(BinNodePosi(T) x);
	virtual int updateHeight(BinNodePosi(T) x);//���½ڵ�x�ĸ߶�
	void updateHeightAbove(BinNodePosi(T) x);//���½ڵ�x�Լ����ȵĸ߶�

	//release()�������ʵ�֣�
	//���鱾�����п��Կ�������������ɾ��BinNodePosi(T)�������ݵ��ڴ�
	//�����������е�ָ�붼�Ǿ�̬�����ģ���ô���޷�ʵ��
	//����Ƕ�̬�����ģ��Ǻ�delete��������ʲô��
	//�����������ָ�롣������
	//Ŀǰ���õ������ʽ�ǰ�ָ���Ϊ��ָ��,��������ݵ��ڴ治������
};

template<typename T>
inline BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e)
{ 
	_size = 1;
	return _root = new BinNode<T>(e);
}

template<typename T>
inline BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e)
{
	_size++; x->insertAsLc(e); updateHeightAbove(x); return x->lc;
} // e����Ϊx������

template<typename T>
inline BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e)
{
	_size++; x->insertAsRc(e); updateHeightAbove(x); return x->rc;
} // e����Ϊx���Һ���

template<typename T>
inline BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>*& S)
{
	if (x->lc = S->_root) x->lc->parent = x; //����
	_size += S->_size; updateHeightAbove(x); //����ȫ����ģ��x�������ȵĸ߶�
	S->_root = nullptr; S->_size = 0; S = nullptr; return x; //�ͷ�ԭ�������ؽ���λ��
}

template<typename T>
inline BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>*& S)
{
	if (x->rc = S->_root) x->rc->parent = x; //����
	_size += S->_size; updateHeightAbove(x); //����ȫ����ģ��x�������ȵĸ߶�
	S->_root = nullptr; S->_size = 0; S = nullptr; return x; //�ͷ�ԭ�������ؽ���λ��
}

template<typename T>
inline int BinTree<T>::remove(BinNodePosi(T) x)
{
	FromParentTo(x) = nullptr; //�ж����Ը��ڵ��ָ��
	updateHeightAbove(x->parent);//�������ȸ߶�
	int n = removeAt(x); _size -= n; return n; //ɾ������x�����¹�ģ������ɾ���ڵ�����
	return 0;
}

template<typename T>
inline BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x)
{
	FromParentTo(x) = nullptr; //�ж����Ը��ڵ��ָ��
	updateHeightAbove(x->parent); //����ԭ�����������ȵĸ߶�
	BinTree<T>* S = new BinTree<T>; S->_root = x; x->parent = nullptr; //������xΪ��
	S->_size = x->size(); _size -= S->_size; return S; //���¹�ģ�����ط������������
}

template<typename T>
inline int BinTree<T>::maxHeight(BinNodePosi(T) x)
{ return stature(x->lc) > stature(x->rc) ? stature(x->lc) : stature(x->rc); }

template<typename T>
inline int BinTree<T>::updateHeight(BinNodePosi(T) x)
{ return x->height = 1 + maxHeight(x); }

template<typename T>
inline void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{ for (; x; x = x->parent) updateHeight(x); }

template <typename T> //ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
static int removeAt(BinNodePosi(T)& x)
{ // assert: xΪ�������еĺϷ�λ��
	if (!x) return 0; //�ݹ��������
	int n = 1 + removeAt(x->lc) + removeAt(x->rc); //�ݹ��ͷ���������
	x=nullptr; return n; //�ͷű�ժ���ڵ㣬������ɾ���ڵ�����
}