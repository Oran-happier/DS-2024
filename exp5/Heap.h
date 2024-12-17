#pragma once

#include "PQ.h" //�������ȼ�����ADTʵ�ֵ�
#include "Vector.h" //�������ؼ̳л��ƣ���������

#define  Inheap(n,i)       ( ( (-1) < (i) ) && ( (i)<(n) ) )  //�ж�PQ[i]�Ƿ�Ϸ�
#define  Parent(i)         ( ( ( i ) - 1 ) >> 1 ) //PQ[i]�ĸ��ڵ㣨floor((i-1)/2)��i����������
#define  LChild(i)         ( 1 + ( ( i ) << 1 ) ) //PQ[i]������
#define  RChild(i)         ( ( 1 + ( i ) ) << 1 ) //PQ[i]���Һ���
#define  InHeap(n, i)      ( ( ( -1 ) != ( i ) ) && ( ( i ) < ( n ) ) ) //�ж�PQ[i]�Ƿ�Ϸ�
#define  LChildValid(n, i) InHeap( n, LChild( i ) ) //�ж�PQ[i]�Ƿ���һ�����󣩺���
#define  RChildValid(n, i) InHeap( n, RChild( i ) ) //�ж�PQ[i]�Ƿ�����������
#define  Bigger(PQ, i, j)  ( ( PQ[i] < PQ[j] ) ? j : i ) //ȡ���ߣ���ʱǰ�����ȣ�
#define  ProperParent(PQ, n, i) /*���ӣ����ࣩ�����еĴ���*/ \
            ( RChildValid(n, i) ? Bigger( PQ, Bigger( PQ, i, LChild(i) ), RChild(i) ) : \
            ( LChildValid(n, i) ? Bigger( PQ, i, LChild(i) ) : i \
            ) \
            ) //���ʱ���ڵ����ȣ���˿ɱ��ⲻ��Ҫ�Ľ���



template <typename T> struct PQ_ComplHeap : public PQ<T>, public Vector<T>
{ //��ȫ�����
    PQ_ComplHeap() {} //Ĭ�Ϲ���
    PQ_ComplHeap(T* A, Rank n) { copyFrom(A, 0, n); heapify(Vector<T>::_elem, n); } //��������
    void insert(T); //���ձȽ���ȷ�������ȼ����򣬲������
    T delMax(); //ɾ�����ȼ���ߵĴ���
    T& getMax(); //��ȡ���ȼ���ߵĴ���

}; // PQ_ComplHeap

template <typename T> void heapify(T* A, Rank n); // Floyd�����㷨
template <typename T> Rank percolateDown(T* A, Rank n, Rank i); //����
template <typename T> Rank percolateUp(T* A, Rank i); //����

template <typename T> T& PQ_ComplHeap<T>::getMax() { return Vector<T>::_elem[0]; } //ȡ���ȼ���ߵĴ���

template <typename T> void PQ_ComplHeap<T>::insert(T e)
{ //������������ȫ�������
    Vector<T>::insert(e); //���´�����������ĩβ
    percolateUp(Vector<T>::_elem, Vector<T>::_size - 1); //�ٶԸô���ʵʩ���˵���
}

template <typename T> Rank percolateUp(T* A, Rank i)
{ //�Դ���A[i]�����ˣ�0 <= i < Vector<T>::_size
    while (0 < i)
    {//�ڵִ�Ѷ�֮ǰ��������
        Rank j = Parent(i); //����[i]֮����[j]
        if (!(A[j] < A[i])) break; //һ������˳������������ɣ�����
        std::swap(A[i], A[j]); i = j; //���ӻ�λ��������������һ��
    }
    return i; //�����������յִ��λ��
}

template <typename T> T PQ_ComplHeap<T>::delMax()
{ //ȡ��������
    std::swap(Vector<T>::_elem[0], Vector<T>::_elem[--Vector<T>::_size]); //�Ѷ�����β������Vector<T>::_size�ĵݼ�����������shrink()��
    percolateDown(Vector<T>::_elem, Vector<T>::_size, 0); //�¶Ѷ�����
    return Vector<T>::_elem[Vector<T>::_size]; //����ԭ�Ѷ�
}

template<typename T>
inline void heapify(T* A, Rank n)
{
    for (int i = Parent(n - 1); Inheap(n, i); i--) //�Ե׶��ϣ�����
        percolateDown(A, n, i);
}

//������ǰn�������еĵ�i��ʵʩ���ˣ�i < n
template <typename T> Rank percolateDown(T* A, Rank n, Rank i)
{
    Rank j; // i���䣨���������������У���Ϊ����
    while (i != (j = ProperParent(A, n, i))) //ֻҪi��j����
        std::swap(A[i], A[j]); i = j; //���߻�λ�������������½����i
    return i; //�������˵ִ��λ�ã���i��j��

}

template <typename T> void Vector<T>::heapSort(Rank lo, Rank hi)
{ // 0 <= lo < hi <= size
    T* A = Vector<T>::_elem + lo; Rank n = hi - lo; heapify(A, n); //�����������佨��һ����ȫ����ѣ�O(n)
    while (0 < --n) //������ժ�����Ԫ������������ĺ�׺��ֱ���ѿ�
    {
        std::swap(A[0], A[n]); percolateDown(A, n, 0);
    } //�Ѷ���ĩԪ�ضԻ���������
}

