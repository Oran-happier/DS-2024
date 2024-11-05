#pragma once
#include "BinNodeMacro.h"
#define BinNodePosi(T) BinNode<T>* //节点位置
#define stature(p) ((p) ? (p) -> height : -1) //节点高度（空树的高度为-1）
typedef enum { RB_RED, RB_BLACK } RBColor;

template <typename T> struct BinNode //二叉树节点的模板类
{
//简化描述起见，不对成员进行封装
	T data;//数值
	BinNodePosi(T) parent; BinNodePosi(T) lc;BinNodePosi(T) rc;//父亲节点和左右孩子
	int height;
	int npl;//Null Path Length（左式堆，也可直接用height代替）
	RBColor color;//红黑树颜色

//构造函数
	BinNode() :
		parent(nullptr), lc(nullptr), rc(nullptr), height(0), npl(1), color(RB_RED) {}
	BinNode(T e, BinNodePosi(T) p = nullptr, BinNodePosi(T) lc = nullptr, BinNodePosi(T)rc = nullptr, int h = 0, int l = 1, RBColor c = RB_RED) :
		data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c)
	{
		if (lc) lc->parent = this;
		if (rc) rc->parent = this;
	}

//操作接口
	int size();//统计当前节点后代总数，即为以其为根的子树的规模
	BinNodePosi(T) insertAsLC(T const&);
	BinNodePosi(T) insertAsRC(T const&);
	BinNodePosi(T) succ(); //取当前节点的直接后继
	template <typename VST> void travLevel(VST&); //子树层次遍历
	template <typename VST> void travPre(VST&); //子树先序遍历
	template <typename VST> void travIn(VST&); //子树中序遍历
	template <typename VST> void travPost(VST&); //子树后序遍历

// 比较器、判等器（各列其一，其余自行补充）
	bool operator< (BinNode const& bn) { return data < bn.data; } //小于
	bool operator== (BinNode const& bn) { return data == bn.data; } //等于
	bool operator> (BinNode const& bn) { return data > bn.data; } //大于
};

template<typename T>
inline BinNodePosi(T) BinNode<T>::insertAsLC(T const& e)
{
	return lc = new BinNode(e, this);
}//把e作为当前节点的左孩子节点插入

template<typename T>
inline BinNodePosi(T) BinNode<T>::insertAsRC(T const& e)
{
	return rc = new BinNode(e, this);
}//把e作为当前节点的右孩子节点插入


