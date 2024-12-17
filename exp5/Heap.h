#pragma once

#include "PQ.h" //按照优先级队列ADT实现的
#include "Vector.h" //借助多重继承机制，基于向量

#define  Inheap(n,i)       ( ( (-1) < (i) ) && ( (i)<(n) ) )  //判断PQ[i]是否合法
#define  Parent(i)         ( ( ( i ) - 1 ) >> 1 ) //PQ[i]的父节点（floor((i-1)/2)，i无论正负）
#define  LChild(i)         ( 1 + ( ( i ) << 1 ) ) //PQ[i]的左孩子
#define  RChild(i)         ( ( 1 + ( i ) ) << 1 ) //PQ[i]的右孩子
#define  InHeap(n, i)      ( ( ( -1 ) != ( i ) ) && ( ( i ) < ( n ) ) ) //判断PQ[i]是否合法
#define  LChildValid(n, i) InHeap( n, LChild( i ) ) //判断PQ[i]是否有一个（左）孩子
#define  RChildValid(n, i) InHeap( n, RChild( i ) ) //判断PQ[i]是否有两个孩子
#define  Bigger(PQ, i, j)  ( ( PQ[i] < PQ[j] ) ? j : i ) //取大者（等时前者优先）
#define  ProperParent(PQ, n, i) /*父子（至多）三者中的大者*/ \
            ( RChildValid(n, i) ? Bigger( PQ, Bigger( PQ, i, LChild(i) ), RChild(i) ) : \
            ( LChildValid(n, i) ? Bigger( PQ, i, LChild(i) ) : i \
            ) \
            ) //相等时父节点优先，如此可避免不必要的交换



template <typename T> struct PQ_ComplHeap : public PQ<T>, public Vector<T>
{ //完全二叉堆
    PQ_ComplHeap() {} //默认构造
    PQ_ComplHeap(T* A, Rank n) { copyFrom(A, 0, n); heapify(Vector<T>::_elem, n); } //批量构造
    void insert(T); //按照比较器确定的优先级次序，插入词条
    T delMax(); //删除优先级最高的词条
    T& getMax(); //读取优先级最高的词条

}; // PQ_ComplHeap

template <typename T> void heapify(T* A, Rank n); // Floyd建堆算法
template <typename T> Rank percolateDown(T* A, Rank n, Rank i); //下滤
template <typename T> Rank percolateUp(T* A, Rank i); //上滤

template <typename T> T& PQ_ComplHeap<T>::getMax() { return Vector<T>::_elem[0]; } //取优先级最高的词条

template <typename T> void PQ_ComplHeap<T>::insert(T e)
{ //将词条插入完全二叉堆中
    Vector<T>::insert(e); //将新词条接至向量末尾
    percolateUp(Vector<T>::_elem, Vector<T>::_size - 1); //再对该词条实施上滤调整
}

template <typename T> Rank percolateUp(T* A, Rank i)
{ //对词条A[i]做上滤，0 <= i < Vector<T>::_size
    while (0 < i)
    {//在抵达堆顶之前，反复地
        Rank j = Parent(i); //考查[i]之父亲[j]
        if (!(A[j] < A[i])) break; //一旦父子顺序，上滤旋即完成；否则
        std::swap(A[i], A[j]); i = j; //父子换位，并继续考查上一层
    }
    return i; //返回上滤最终抵达的位置
}

template <typename T> T PQ_ComplHeap<T>::delMax()
{ //取出最大词条
    std::swap(Vector<T>::_elem[0], Vector<T>::_elem[--Vector<T>::_size]); //堆顶、堆尾互换（Vector<T>::_size的递减，不致引发shrink()）
    percolateDown(Vector<T>::_elem, Vector<T>::_size, 0); //新堆顶下滤
    return Vector<T>::_elem[Vector<T>::_size]; //返回原堆顶
}

template<typename T>
inline void heapify(T* A, Rank n)
{
    for (int i = Parent(n - 1); Inheap(n, i); i--) //自底而上，依次
        percolateDown(A, n, i);
}

//对向量前n个词条中的第i个实施下滤，i < n
template <typename T> Rank percolateDown(T* A, Rank n, Rank i)
{
    Rank j; // i及其（至多两个）孩子中，堪为父者
    while (i != (j = ProperParent(A, n, i))) //只要i非j，则
        std::swap(A[i], A[j]); i = j; //二者换位，并继续考查下降后的i
    return i; //返回下滤抵达的位置（亦i亦j）

}

template <typename T> void Vector<T>::heapSort(Rank lo, Rank hi)
{ // 0 <= lo < hi <= size
    T* A = Vector<T>::_elem + lo; Rank n = hi - lo; heapify(A, n); //将待排序区间建成一个完全二叉堆，O(n)
    while (0 < --n) //反复地摘除最大元并归入已排序的后缀，直至堆空
    {
        std::swap(A[0], A[n]); percolateDown(A, n, 0);
    } //堆顶与末元素对换，再下滤
}

