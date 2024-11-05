#pragma once
//Ĭ�ϴ���Ĳ���x��ָ�����͵ı���,���� BinNodePosi(T)��BinNode<T>* 

//BinNode״̬�����ʵ��ж�
#define IsRoot(x) ( !( (x) -> parent ) )
#define HasParent(x) ( (x) -> parent )
#define HasLChild(x) ( (x) -> lc )
#define HasRChild(x) ( (x) -> rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) )
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) )
#define IsLChild(x) ( HasParent(x) && ( (x) == (x)->parent->lc) )
#define IsRChild(x) ( HasParent(x) && ( (x) == (x)->parent->rc) )
#define IsLeaf(x) ( !HasChild(x) )

//��BinNode�����ض���ϵ�Ľڵ�
#define sibling(x) ( IsLChild(x) ? (x)->parent->rc : (x)->parent->lc ) //�����ֵܽڵ�
#define uncle(x) ( sibling( (x)->parent ) ) //��������ڵ�
#define FromParentTo( x ) (IsRoot(x) ? _root : (IsLChild(x) ? (x)->parent->lc : (x)->parent->rc) )
//ֱ�ӷ��ظ��׽ڵ�洢��lc��rc 
