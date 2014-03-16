#pragma once

#include <map>

class FooConter
{
public:
	void add_ptr(void *crude_ptr);
	bool remove_ptr(void *crude_ptr);

private:
	std::map<void*, unsigned int> mapa;
};

void FooConter::add_ptr(void *crude_ptr)
{
	mapa[crude_ptr] ++;
}

bool FooConter::remove_ptr(void *crude_ptr)
{
	
}


template <class T, class C> class SmartPointer
{
public:
	SmartPointer();
	SmartPointer(T * ptr);
	SmartPointer(const SmartPointer<T, C> & smartPtr);
	SmartPointer(const std::auto_ptr<T> & smartPtr);

	~SmartPointer();

	SmartPointer<T, C> & operator= (const SmartPointer<T, C> & smartPtr);
	SmartPointer<T, C> & operator= (const std::auto_ptr<T> & smartPtr);
	T& operator*() const { return *crude_ptr; };
	T* operator->() const { return crude_ptr; };

	void Reset(T * ptr = NULL); // ������������� ����� ��������� �� ����� ������ (�� ptr)
	void Swap(SmartPointer<T, C> * smartPtr); // ������ ��������� �������
	long UseCount() const; // ���������� ���-�� ������ �� ������ ����������
	bool Unique() const; // ���������� ����� �� ���-�� ������ �� ������ ���������� 1
	T* Get(); // ���������� "����� ���������"

private:
	T* crude_ptr;

};

template <class T, class C>
SmartPointer<T, C> & SmaprtPointer::operator= (const SmartPointer<T, C> & smartPtr)
{

}

template <class T, class C>
SmartPointer<T, C> & SmaprtPointer::operator= (const std::auto_ptr<T> & smartPtr)
{

}