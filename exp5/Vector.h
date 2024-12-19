#pragma once

#include <stdlib.h> 
#include <utility>
#include <ctime>
#include <iostream>
#include <algorithm> 
#define DEFAULT_CAPACITY  5 //Ĭ�ϵĳ�ʼ������ʵ��Ӧ���п�����Ϊ����
using Rank = int; //��


template <typename T> class Vector { //����ģ����
protected:
	Rank _size; Rank _capacity;  T* _elem; //��ģ��������������
	void copyFrom(T const* A, Rank lo, Rank hi); //������������A[lo, hi)
	void expand(); //�ռ䲻��ʱ����
	void shrink(); //װ�����ӹ�Сʱѹ��
	bool bubble(Rank lo, Rank hi); //ɨ�轻��
	void bubbleSort(Rank lo, Rank hi); //���������㷨
	void selectionSort(Rank lo, Rank hi); //ѡ�������㷨
	void merge(Rank lo, Rank mi, Rank hi); //�鲢�㷨
	void mergeSort(Rank lo, Rank hi); //�鲢�����㷨
	void heapSort(Rank lo, Rank hi); //�������Ժ�����ȫ�ѽ��⣩
	Rank partition(Rank lo, Rank hi); //��㹹���㷨
	void quickSort(Rank lo, Rank hi); //���������㷨
	void insertSort(Rank lo, Rank hi); //��������
	void shellSort(Rank lo, Rank hi); //ϣ�������㷨
public:
	// ���췽��
	Vector(Rank c = DEFAULT_CAPACITY) //����Ϊc�Ŀ�����
	{
		_elem = new T[_capacity = c]; _size = 0;//_size = 0
	}
	Vector(Rank c, Rank s, T v) //����Ϊc����ģΪs������Ԫ�س�ʼΪv��s<=c
	{
		_elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);
	}
	Vector(T const* A, Rank n) { copyFrom(A, 0, n); } //�������帴��
	Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } //����
	Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); } //�������帴��
	Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //����
	// ��������
	//~Vector() { delete[] _elem; } //�ͷ��ڲ��ռ�
	// ֻ�����ʽӿ�
	Rank size() const { return _size; } //��ģ
	bool empty() const { return !_size; } //�п�
	Rank find(T const& e) const { return find(e, 0, _size); } //���������������
	Rank find(T const& e, Rank lo, Rank hi) const; //���������������
	Rank select(Rank k) { return quickSelect(_elem, _size, k); } //�������������ҵ���k���Ԫ��
	Rank search(T const& e) const //���������������
	{
		return (0 >= _size) ? -1 : search(e, 0, _size);
	}
	Rank search(T const& e, Rank lo, Rank hi) const; //���������������
	T* ele() const { return _elem; }
	// ��д���ʽӿ�
	T& operator[] (Rank r); //�����±������������������������ʽ���ø�Ԫ��
	const T& operator[] (Rank r) const; //����������ֵ�����ذ汾
	T remove(Rank r); //ɾ����Ϊr��Ԫ��
	Rank remove(Rank lo, Rank hi); //ɾ����������[lo, hi)֮�ڵ�Ԫ��
	Rank insert(Rank r, T const& e); //����Ԫ��
	Rank insert(T const& e) { return insert(_size, e); } //Ĭ����ΪĩԪ�ز���
	void sort(Rank lo, Rank hi); //��[lo, hi)����
	void sort() { sort(0, _size); } //��������
	void unsort(Rank lo, Rank hi); //��[lo, hi)����
	void unsort() { unsort(0, _size); } //��������
	Rank dedup(); //����ȥ��
	Rank uniquify(); //����ȥ��
	// ����
	void traverse(void (*) (T&)); //������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ�
	template <typename VST> void traverse(VST&); //������ʹ�ú������󣬿�ȫ�����޸ģ�

	//extra
	Vector<T>& operator= (Vector<T> const& V);
	int disordered() const;
}; //Vector

template <typename T> //TΪ�������ͣ��������ظ�ֵ������'='
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) { //����������A[lo, hi)Ϊ������������
	_elem = new T[_capacity = (hi - lo) * 2]; //����ռ�
	for (_size = 0; lo < hi; _size++, lo++) //A[lo, hi)�ڵ�Ԫ����һ
		_elem[_size] = A[lo]; //������_elem[0, hi-lo)��TΪ�������ͣ��������ظ�ֵ������'='

} //��const���Σ���֤A�е�Ԫ�ز��±��۸ģ�����ʱ�� = O(hi-lo)

template <typename T> Vector<T>& Vector<T>::operator= (Vector<T> const& V) { //���
	if (_elem) delete[] _elem; //�ͷ�ԭ������
	copyFrom(V._elem, 0, V.size()); //���帴��
	return *this; //���ص�ǰ��������ã��Ա���ʽ��ֵ

}

template <typename T> void Vector<T>::expand() { //�����ռ䲻��ʱ����
	if (_size < _capacity) return; //��δ��Աʱ����������
	T* oldElem = _elem; copyFrom(oldElem, 0, _capacity); //�����ӱ�
	delete[] oldElem; //�ͷ�ԭ�ռ�

}

template <typename T> void Vector<T>::shrink() { //װ�����ӹ�Сʱѹ��������ռ�ռ�
	if (_capacity < DEFAULT_CAPACITY << 1) return; //����������DEFAULT_CAPACITY����
	if (_size << 2 > _capacity) return; //��25%Ϊ��
	T* oldElem = _elem; _elem = new T[_capacity >>= 1]; //��������
	for (Rank i = 0; i < _size; i++) _elem[i] = oldElem[i]; //����ԭ��������
	delete[] oldElem; //�ͷ�ԭ�ռ�
}

template <typename T> T& Vector<T>::operator[] (Rank r) //�����±������
{
	return _elem[r];
} // assert: 0 <= r < _size

template <typename T> void permute(Vector<T>& V) { //�������������ʹ��Ԫ�صȸ��ʳ����ڸ�λ��
	for (int i = V.size(); i > 0; i--) //�Ժ���ǰ
		swap(V[i - 1], V[rand() % i]); //V[i - 1]��V[0, i)��ĳһ���Ԫ�ؽ���
}

template <typename T> void Vector<T>::unsort(Rank lo, Rank hi) { //�����������[lo, hi)
	T* V = _elem + lo; //��������_elem[lo, hi)������һ����V[0, hi - lo)
	for (Rank i = hi - lo; 1 < i; --i) //�Ժ���ǰ
		std::swap(V[i - 1], V[rand() % i]); //��V[i - 1]��V[0, i)��ĳһԪ���������

}

template <typename T> static bool lt(T* a, T* b) { return lt(*a, *b); }//less than(point -> address)
template <typename T> static bool lt(T& a, T& b) { return a < b; }//less than(object)
template <typename T> static bool eq(T* a, T* b) { return eq(*a, *b); }//equal(point -> address)
template <typename T> static bool eq(T& a, T& b) { return a = b; }//equal(point -> address)



template <typename T> //������������˳�����e��0 <= lo < hi <= _size
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const { //O(hi-lo)
	while ((lo < hi--) && (e != _elem[hi])); //�Ӻ���ǰ��˳�����
	return hi; //���������ߣ���lo-1ʾ��ʧ�ܣ�lo == 0ʱ�أ���
}

template <typename T> //��e������[r]
Rank Vector<T>::insert(Rank r, T const& e) { //0 <= r <= size
	//print( e );
	expand(); //���Ҫ��������
	for (Rank i = _size; r < i; i--) //�Ժ���ǰ�����Ԫ��
		_elem[i] = _elem[i - 1]; //˳�κ���һ����Ԫ
	_elem[r] = e; _size++; //������Ԫ�ز���������
	return r; //������
}

template<typename T>
inline void Vector<T>::sort(Rank lo, Rank hi)
{
	T e[DEFAULT_CAPACITY];//����һ��_elem�ĸ���
	for (unsigned i = 0; i < _size; i++) e[i] = _elem[i];

	clock_t start = 1000 * clock(); //��һ�ζ��壬����ֱ������ʹ��
	clock_t end = 1000 * clock(); //��һ�ζ��壬����ֱ������ʹ��
	double bubbleTime = double(end - start) / CLOCKS_PER_SEC;

	//insertSort()
	_elem = e;//��ԭ
	start = 1000 * clock();
	insertSort(lo, hi);
	end = 1000 * clock();
	double insertTime = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "insertTime:" << insertTime << " ms" << std::endl;
	
	//selectSort()
	_elem = e;//��ԭ
	start = 1000 * clock();
	selectionSort(lo, hi);
	end = 1000 * clock();
	double selectTime = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "selectTime:" << selectTime << " ms" << std::endl;
	
    //mergeSort()
	_elem = e;//��ԭ����ʹ��������
	start = 1000*clock();
	mergeSort(lo, hi);
	end = 1000*clock();
	double mergeTime = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "mergeTime:" << mergeTime << " ms" << std::endl;

	//quickSort()
	_elem = e;//��ԭ
	start = 1000 * clock();
	quickSort(lo, hi);
	end = 1000 * clock();
	double quickTime = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "quickTime:" << quickTime << " ms" << std::endl;

	//heapSort()
	_elem = e;//��ԭ
	start = 1000 * clock();
	heapSort(lo, hi);
	end = 1000 * clock();
	double heapTime = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "heapTime:" << heapTime << " ms" << std::endl;

	
	_elem = e;//��ԭ
	start = 1000 * clock(); //��һ�ζ��壬����ֱ������ʹ��
	bubbleSort(lo, hi);
	end = 1000 * clock(); //��һ�ζ��壬����ֱ������ʹ��
	bubbleTime = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "bubbleTime:" << bubbleTime << " ms" << std::endl;
	//std::cout << "end:" << end << "   start:" << start << std::endl;
}

template <typename T> Rank Vector<T>::remove(Rank lo, Rank hi) { //0 <= lo <= hi <= n
	if (lo == hi) return 0; //����Ч�ʿ��ǣ����������˻����
	while (hi < _size) _elem[lo++] = _elem[hi++]; //��׺[hi, _size)˳��ǰ��hi-loλ
	_size = lo; shrink(); //���¹�ģ��lo=_size֮��������������㣻���Ҫ��������
	//���б�Ҫ��������
	return hi - lo; //���ر�ɾ��Ԫ�ص���Ŀ
}

template <typename T> T Vector<T>::remove(Rank r) { //ɾ����������Ϊr��Ԫ�أ�0 <= r < size
	T e = _elem[r]; //���ݱ�ɾ��Ԫ��
	remove(r, r + 1); //��������ɾ���㷨����Ч�ڶ�����[r, r + 1)��ɾ��
	return e; //���ر�ɾ��Ԫ��
}

template <typename T> Rank Vector<T>::dedup() { //ɾ�������������ظ�Ԫ�أ���Ч�棩
	Rank oldSize = _size; //��¼ԭ��ģ
	for (Rank i = 1; i < _size; ) //��ǰ����������_elem[1,_size)
		if (-1 == find(_elem[i], 0, i)) //��ǰ׺[0,i)��Ѱ����[i]��ͬ�ߣ�����һ������O(i)
			i++; //������ͬ���������������
		else
			remove(i); //����ɾ��[i]��O(_size-i)
	return oldSize - _size; //��ɾ��Ԫ������
}

template <typename T> void Vector<T>::traverse(void (*visit)(T&)) //��������ָ�����
{
	for (Rank i = 0; i < _size; i++) visit(_elem[i]);
} //��������

template <typename T> template <typename VST> //Ԫ�����͡�������
void Vector<T>::traverse(VST& visit) //���������������
{
	for (Rank i = 0; i < _size; i++) visit(_elem[i]);
} //��������

template <typename T> struct Increase //�������󣺵���һ��T�����
{
	virtual void operator()(T& e) { e++; }
}; //����T��ֱ�ӵ�����������++

template <typename T> void increase(Vector<T>& V) //ͳһ���������еĸ�Ԫ��
{
	V.traverse(Increase<T>());
} //��Increase<T>()Ϊ�����������б���

template <typename T> int Vector<T>::disordered() const
{
	int n = 0;
	for (int i = 1; i < _size; i++)
	{
		if (_elem[i - 1] > _elem[i]) n++;
	}
	return n;
}

template <typename T> Rank Vector<T>::uniquify()
{ //���������ظ�Ԫ���޳��㷨����Ч�棩
	Rank i = 0, j = 0; //���Ի��조���ڡ�Ԫ�ص���  
	while (++j < _size) //��һɨ�裬ֱ��ĩԪ��  
		if (_elem[i] != _elem[j]) //������ͬ��  
			_elem[++i] = _elem[j]; //���ֲ�ͬԪ��ʱ����ǰ����������ǰ���Ҳ�  
	_size = ++i; shrink(); //ֱ�ӽس�β������Ԫ��  
	return j - i; //������ģ�仯��������ɾ��Ԫ������
}

//Fibonacci����

//���ֲ����㷨���汾C��������������������[lo, hi)�ڲ���Ԫ��e��0 <= lo <= hi <= _size
template <typename T> static Rank binSearch(T* S, T const& e, Rank lo, Rank hi) {
	while (lo < hi) { //ÿ������������һ�αȽ��жϣ���������֧
		Rank mi = (lo + hi) >> 1; //���е�Ϊ��㣨�������۰룬��Ч������ֵ��ʾ������һλ��
		(e < S[mi]) ? hi = mi : lo = mi + 1; //���ȽϺ�ȷ������[lo, mi)��(mi, hi)
	} //�ɹ����Ҳ�����ǰ��ֹ
	return lo - 1; //���ˣ�[lo]Ϊ����e����С�ߣ���[lo-1]��Ϊ������e�������
} //�ж������Ԫ��ʱ����������ߣ�����ʧ��ʱ������ʧ�ܵ�λ��

template <typename T> //����������������[lo, hi)�ڣ�ȷ��������e�����һ���ڵ����  
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const
{ // 0 <= lo < hi <= _size  
	return (rand() % 2) ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
} //�ȸ��ʵ����ʹ�ö��ֲ��ҡ�Fibonacci����

template <typename T> //��������������
void Vector<T>::bubbleSort(Rank lo, Rank hi) // assert: 0 <= lo < hi <= size
{
	while (!bubble(lo, hi--));
} //������ɨ�轻��, ֱ��ȫ��

template<typename T>
inline void Vector<T>::selectionSort(Rank lo, Rank hi)
{
	for (int i = lo; i < hi-1; i++)
	{
		for (int j = i + 1; j < hi; j++)
		{
			if (_elem[j] < _elem[i])
				std::swap(_elem[j], _elem[i]);
		}
	}
}

template<typename T>//�Ը��������[lo, mi)��[mi, hi)���鲢
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)// lo < mi < hi
{
	Rank i = 0; T* A = _elem + lo; //�ϲ������������A[0, hi - lo) = _elem[lo, hi)
	Rank j = 0, lb = mi - lo; T* B = new T[lb]; //ǰ������B[0, lb) <-- _elem[lo, mi)
	for (Rank i = 0; i < lb; i++) B[i] = A[i]; //���Ƴ�A��ǰ׺
	Rank k = 0, lc = hi - mi; T* C = _elem + mi; //��׺C[0, lc) = _elem[mi, hi)�͵�
	while ((j < lb) && (k < lc)) //�����رȽ�B��C����Ԫ��
		A[i++] = (B[j] < C[k]) ? B[j++] : C[k++]; //����С�߹���A��
	while (j < lb) //��C�Ⱥľ�����
		A[i++] = B[j++]; //��B����ĺ�׺����A�С�����B�Ⱥľ��أ�
	delete[] B; //�ͷ���ʱ�ռ䣺mergeSort()�����У���α�����෴����new/delete��
}

template<typename T> //�����鲢����
void Vector<T>::mergeSort(Rank lo, Rank hi)// 0 <= lo < hi <= size
{
	if (hi - lo < 2) return; //��Ԫ��������Ȼ���򣬷���...
	Rank mi = (lo + hi) / 2; //���е�Ϊ��
	mergeSort(lo, mi); mergeSort(mi, hi); //ǰ׺����׺�ֱ�����
	merge(lo, mi, hi); //�鲢
}

template<typename T> //��㹹���㷨��ͨ������Ԫ��λ�ù�������[lo,hi]����㣬��������
inline Rank Vector<T>::partition(Rank lo, Rank hi)
{//�汾B�����Ż��������ؼ�����ͬ���˻����
	std::swap(_elem[lo], _elem[lo + rand() % (hi - lo + 1)]);//��ѡһ��Ԫ������Ԫ�ؽ���
	T pivot = _elem[lo]; //����Ԫ��Ϊ��ѡ��㡪�����������Ͻ�������Ч�����ѡȡ
	while (lo < hi)
	{//�����������˽�������м�ɨ��
		while (lo < hi)
			if (pivot < _elem[hi]) //�ڴ���pivot��ǰ����
				hi--; //������չ�Ҷ�������
			else
			{
				_elem[lo++] = _elem[hi]; break;
			}
		while (lo < hi)
			if (pivot > _elem[lo]) //�ڴ���pivot��ǰ����
				lo++; //������չ�Ҷ�������
			else
			{
				_elem[lo] = _elem[hi--]; break;
			}
	} //assert:lo==hi
	_elem[lo] = pivot;//�����ݵ�����¼����ǰ��������֮��
	return lo; //����������
}

template<typename T>
inline void Vector<T>::quickSort(Rank lo, Rank hi)
{
	if (hi - lo < 2) return;
	Rank mi = partition(lo, hi - 1);//��[lo,hi-1]�ڹ������
	quickSort(lo, mi);//��ǰ׺�ݹ�����
	quickSort(mi+1,hi);//�Ժ�׺�ݹ�����
}

template<typename T>
inline void Vector<T>::insertSort(Rank lo, Rank hi)
{
	for (Rank i = lo + 1; i < hi; ++i)
	{
		T temp = _elem[i]; // �洢��ǰԪ��
		Rank j = i;
		// ����ǰԪ�ز��뵽�Ѿ�����õĲ���
		while (j > lo && _elem[j - 1] > temp)
		{
			_elem[j] = _elem[j - 1]; // �����ƶ�Ԫ��
			--j;                     // ��������ɨ��
		}
		_elem[j] = temp; // ���뵱ǰԪ��
	}
}

template <typename T> bool Vector<T>::bubble(Rank lo, Rank hi)
{ //һ��ɨ�轻��
	bool sorted = true; //���������־
	while (++lo < hi)
	{//��������,��һ����������Ԫ��
		if (_elem[lo - 1] > _elem[lo])
		{ //������, ��
			sorted = false; //��ζ����δ��������, ����Ҫ
			std::swap(_elem[lo - 1], _elem[lo]); //ͨ������ʹ�ֲ�����
		}
	}
	return sorted; //���������־
}
