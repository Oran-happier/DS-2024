#pragma once

template <typename T> struct PQ
{ //���ȼ�����PQ�ӿ�
	virtual void insert(T) = 0; //���ձȽ���ȷ�������ȼ�����������
	virtual T delMax() = 0; //ɾ�����ȼ���ߵĴ���
	virtual T& getMax() = 0; //ȡ�����ȼ���ߵĴ���
};