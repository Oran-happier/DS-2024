#pragma once
#include "BinNode.h" //引入二叉树节点类

template <typename T> class BinTree
{
protected:
	int _size; BinNodePosi(T) _root; //规模、根节点
public:
	BinTree() : _size(0), _root(nullptr) {} //构造方法
	~BinTree() { if (0 < _size) remove(_root); } //析构方法
	int size() const { return _size; }
	bool empty() const { return !_root; } //判空
	BinNodePosi(T) root() const { return _root; }
	BinNodePosi(T) insertAsRoot(T const& e);//插入根节点
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e);//插入左节点
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e);//插入右节点
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &S);//T作为x左子树接入
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &S);//T作为x右子树接入
	int remove(BinNodePosi(T) x); //删除以x为根的子树，返回原先的规模
	BinTree<T>* secede(BinNodePosi(T)); //分离以x为根的子树，并将其转化为独立的子树
	template <typename VST> //操作器
	void travLevel(VST& visit) { if (_root) _root->travLevel(visit); } //层次遍历
	template <typename VST> //操作器
	void travPre(VST& visit) { if (_root) _root->travPre(visit); } //先序遍历
	template <typename VST> //操作器
	void travIn(VST& visit) { if (_root) _root->travIn(visit); } //中序遍历
	template <typename VST> //操作器
	void travPost(VST& visit) { if (_root) _root->travPost(visit); } //后序遍历
	//比较器（其余自行补充）
	bool operator<(BinTree<T> const& t) 
	{ return _root && t._root && (*_root < *(t._root)); }
	bool operator==(BinTree<T> const& t) //判等器
	{ return _root && t._root && (_root == t._root); }//判断地址相等，真的没问题吗。。。


	//更新高度函数，为什么放在protected内？
	int maxHeight(BinNodePosi(T) x);
	virtual int updateHeight(BinNodePosi(T) x);//更新节点x的高度
	void updateHeightAbove(BinNodePosi(T) x);//更新节点x以及祖先的高度

	//release()函数如何实现？
	//从书本代码中可以看出，可以用来删除BinNodePosi(T)类型数据的内存
	//但是倘若所有的指针都是静态声明的，那么就无法实现
	//如果是动态声明的，那和delete的区别是什么？
	//亦或者是智能指针。。。？
	//目前采用的替代方式是把指针变为空指针,对相关数据的内存不作处理
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
} // e插入为x的左孩子

template<typename T>
inline BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e)
{
	_size++; x->insertAsRc(e); updateHeightAbove(x); return x->rc;
} // e插入为x的右孩子

template<typename T>
inline BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>*& S)
{
	if (x->lc = S->_root) x->lc->parent = x; //接入
	_size += S->_size; updateHeightAbove(x); //更新全树规模与x所有祖先的高度
	S->_root = nullptr; S->_size = 0; S = nullptr; return x; //释放原树，返回接入位置
}

template<typename T>
inline BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>*& S)
{
	if (x->rc = S->_root) x->rc->parent = x; //接入
	_size += S->_size; updateHeightAbove(x); //更新全树规模与x所有祖先的高度
	S->_root = nullptr; S->_size = 0; S = nullptr; return x; //释放原树，返回接入位置
}

template<typename T>
inline int BinTree<T>::remove(BinNodePosi(T) x)
{
	FromParentTo(x) = nullptr; //切断来自父节点的指针
	updateHeightAbove(x->parent);//更新祖先高度
	int n = removeAt(x); _size -= n; return n; //删除子树x，更新规模，返回删除节点总数
	return 0;
}

template<typename T>
inline BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x)
{
	FromParentTo(x) = nullptr; //切断来自父节点的指针
	updateHeightAbove(x->parent); //更新原树中所有祖先的高度
	BinTree<T>* S = new BinTree<T>; S->_root = x; x->parent = nullptr; //新树以x为根
	S->_size = x->size(); _size -= S->_size; return S; //更新规模，返回分离出来的子树
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

template <typename T> //删除二叉树中位置x处的节点及其后代，返回被删除节点的数值
static int removeAt(BinNodePosi(T)& x)
{ // assert: x为二叉树中的合法位置
	if (!x) return 0; //递归基：空树
	int n = 1 + removeAt(x->lc) + removeAt(x->rc); //递归释放左、右子树
	x=nullptr; return n; //释放被摘除节点，并返回删除节点总数
}