#pragma once
#include "List.h"//��ListΪ������������
template <typename T> class Queue : public List<T> {//����ģ����
public: //ԭ�нӿ�һ������
	void enqueue(T const& e) { List<T>::insertLast(e); }//���:β������
	T dequeue() { return List<T>::remove(first()); }//����:�ײ�ɾ��
	T& front() { return List<T>::first()->data; } //����

};