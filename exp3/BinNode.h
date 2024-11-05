#pragma once
#include "BinNodeMacro.h"
#define BinNodePosi(T) BinNode<T>* //�ڵ�λ��
#define stature(p) ((p) ? (p) -> height : -1) //�ڵ�߶ȣ������ĸ߶�Ϊ-1��
typedef enum { RB_RED, RB_BLACK } RBColor;

template <typename T> struct BinNode //�������ڵ��ģ����
{
//��������������Գ�Ա���з�װ
	T data;//��ֵ
	BinNodePosi(T) parent; BinNodePosi(T) lc;BinNodePosi(T) rc;//���׽ڵ�����Һ���
	int height;
	int npl;//Null Path Length����ʽ�ѣ�Ҳ��ֱ����height���棩
	RBColor color;//�������ɫ

//���캯��
	BinNode() :
		parent(nullptr), lc(nullptr), rc(nullptr), height(0), npl(1), color(RB_RED) {}
	BinNode(T e, BinNodePosi(T) p = nullptr, BinNodePosi(T) lc = nullptr, BinNodePosi(T)rc = nullptr, int h = 0, int l = 1, RBColor c = RB_RED) :
		data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c)
	{
		if (lc) lc->parent = this;
		if (rc) rc->parent = this;
	}

//�����ӿ�
	int size();//ͳ�Ƶ�ǰ�ڵ�����������Ϊ����Ϊ���������Ĺ�ģ
	BinNodePosi(T) insertAsLC(T const&);
	BinNodePosi(T) insertAsRC(T const&);
	BinNodePosi(T) succ(); //ȡ��ǰ�ڵ��ֱ�Ӻ��
	template <typename VST> void travLevel(VST&); //������α���
	template <typename VST> void travPre(VST&); //�����������
	template <typename VST> void travIn(VST&); //�����������
	template <typename VST> void travPost(VST&); //�����������

// �Ƚ������е�����������һ���������в��䣩
	bool operator< (BinNode const& bn) { return data < bn.data; } //С��
	bool operator== (BinNode const& bn) { return data == bn.data; } //����
	bool operator> (BinNode const& bn) { return data > bn.data; } //����
};

template<typename T>
inline BinNodePosi(T) BinNode<T>::insertAsLC(T const& e)
{
	return lc = new BinNode(e, this);
}//��e��Ϊ��ǰ�ڵ�����ӽڵ����

template<typename T>
inline BinNodePosi(T) BinNode<T>::insertAsRC(T const& e)
{
	return rc = new BinNode(e, this);
}//��e��Ϊ��ǰ�ڵ���Һ��ӽڵ����


