#pragma once
//默认传入的参数x是指针类型的变量,例如 BinNodePosi(T)：BinNode<T>* 

//BinNode状态与性质的判断
#define IsRoot(x) ( !( (x) -> parent ) )
#define HasParent(x) ( (x) -> parent )
#define HasLChild(x) ( (x) -> lc )
#define HasRChild(x) ( (x) -> rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) )
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) )
#define IsLChild(x) ( HasParent(x) && ( (x) == (x)->parent->lc) )
#define IsRChild(x) ( HasParent(x) && ( (x) == (x)->parent->rc) )
#define IsLeaf(x) ( !HasChild(x) )

//与BinNode具有特定关系的节点
#define sibling(x) ( IsLChild(x) ? (x)->parent->rc : (x)->parent->lc ) //返回兄弟节点
#define uncle(x) ( sibling( (x)->parent ) ) //返回叔叔节点
#define FromParentTo( x ) (IsRoot(x) ? _root : (IsLChild(x) ? (x)->parent->lc : (x)->parent->rc) )
//直接返回父亲节点存储的lc，rc 
