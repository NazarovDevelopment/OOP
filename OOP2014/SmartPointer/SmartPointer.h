
#pragma once

#include <map>

class FooCounter
{
public:
	void add_ptr(void *crude_ptr);
	bool remove_ptr(void *crude_ptr);
	long get_num(void* crude_ptr);
private:
	std::map<void*, long> mapa;
};
long FooCounter::get_num(void* crude_ptr)
{
	if (mapa.find(crude_ptr) == mapa.end())
		return 0;
	return mapa[crude_ptr];
}
void FooCounter::add_ptr(void *crude_ptr)
{
	if (mapa.find(crude_ptr) == mapa.end())
		mapa[crude_ptr] = NULL;
	if (crude_ptr != NULL)
		mapa[crude_ptr] ++;
}
bool FooCounter::remove_ptr(void *crude_ptr)
{
	mapa[crude_ptr]--;
	return true ? mapa[crude_ptr] == 0 : false;
}

template <class T, class C> 
class SmartPointer
{
public:
	SmartPointer();
	SmartPointer(T * ptr);
	SmartPointer(const SmartPointer<T, C> & smartPtr);
	SmartPointer(const std::auto_ptr<T> & smartPtr);

	~SmartPointer();

	SmartPointer<T, C> & operator= (const SmartPointer<T, C> & smartPtr);
	SmartPointer<T, C> & operator= (const std::auto_ptr<T> & smartPtr);
	T& operator*() const { return *crude_ptr; }
	T* operator->() const { return crude_ptr; }

	bool operator == (const SmartPointer<T, C> & smartPtr){
		return *crude_ptr == *smartPtr;
	}
	bool operator == (const std::auto_ptr<T> & smartPtr){
		return *crude_ptr == *smartPtr;
	}
	bool operator == (const T* smartPtr){
		return *crude_ptr == *smartPtr;
	}

	bool operator != (const SmartPointer<T, C> & smartPtr){
		return *crude_ptr != *smartPtr;
	}
	bool operator != (const std::auto_ptr<T> & smartPtr){
		return *crude_ptr != *smartPtr;
	}
	bool operator != (const T* smartPtr){
		return *crude_ptr != *smartPtr;
	}

	bool operator > (const SmartPointer<T, C> & smartPtr){
		return *crude_ptr > *smartPtr;
	}
	bool operator > (const std::auto_ptr<T> & smartPtr){
		return *crude_ptr > *smartPtr;
	}
	bool operator > (const T* smartPtr){
		return *crude_ptr > *smartPtr;
	}

	bool operator < (const SmartPointer<T, C> & smartPtr){
		return *crude_ptr < *smartPtr;
	}
	bool operator < (const std::auto_ptr<T> & smartPtr){
		return *crude_ptr < *smartPtr;
	}
	bool operator < (const T* smartPtr){
		return *crude_ptr < *smartPtr;
	}

	bool operator >=(const SmartPointer<T, C> & smartPtr){
		return *crude_ptr >= *smartPtr;
	}
	bool operator >=(const std::auto_ptr<T> & smartPtr){
		return *crude_ptr >= *smartPtr;
	}
	bool operator >= (const T* smartPtr){
		return *crude_ptr >= *smartPtr;
	}

	bool operator <= (const SmartPointer<T, C> & smartPtr){
		return *crude_ptr <= *smartPtr;
	}
	bool operator <= (const std::auto_ptr<T> & smartPtr){
		return *crude_ptr <= *smartPtr;
	}
	bool operator <= (const T* smartPtr){
		return *crude_ptr <= *smartPtr;
	}

	friend std::ostream & operator << (std::ostream & is, const SmartPointer<T, C> & smartPtr);

	void Reset(T * ptr = NULL); // устанавливает умный указатель на новый объект (на ptr)
	void Swap(SmartPointer<T, C> * smartPtr); // меняет указатели местами
	
	long UseCount() const; // возвращает кол-во ссылок на “сырой указатель”
	bool Unique() const; // возвращает равно ли кол-во ссылок на “сырой указатель” 1
	
	T* Get(){return crude_ptr} // возвращает "сырой указатель"
private:
	void CheckAndRemove();
private:
	T* crude_ptr;
	static FooCounter fcntr;
};

template<class T, class C>
long SmartPointer<T,C>::UseCount() const
{
	return fcntr.get_num(this->crude_ptr);
}

template<class T, class C>
void SmartPointer<T, C>::Swap(SmartPointer<T, C> * smartPtr)
{
	T* ptr = smartPtr->crude_ptr;
	smartPtr->Reset(this->crude_ptr);

	Reset(ptr);
}

template<class T, class C>
bool SmartPointer<T, C>::Unique() const
{
	return fcntr.get_num(this->crude_ptr) == 1;
}

template<class T, class C>
void SmartPointer<T, C>::Reset(T * ptr = NULL)
{
	CheckAndRemove();
	fcntr.add_ptr(ptr);
	this->crude_ptr = ptr;
}

template<class T, class C>
SmartPointer<T,C>::SmartPointer()
{
	crude_ptr = NULL;
}

template<class T, class C>
SmartPointer<T, C>::SmartPointer(T * ptr)
{
	fcntr.add_ptr(ptr);
}

template<class T, class C>
SmartPointer<T, C>::SmartPointer(const SmartPointer<T, C> & smartPtr)
{
	this->crude_ptr = smartPtr;
	fcntr.add_ptr(smartPtr);
}

template<class T, class C>
SmartPointer<T, C>::SmartPointer(const std::auto_ptr<T> & smartPtr)
{
	CheckAndRemove();
	fcntr.add_ptr(smartPtr.get());
	this->crude_ptr = smartPtr;
}

template <class T, class C>
SmartPointer<T, C> & SmartPointer<T, C>::operator = (const SmartPointer<T, C> & smartPtr)
{
	CheckAndRemove();
	fcntr.add_ptr(smartPtr.crude_ptr);
	this->crude_ptr = smartPtr.crude_ptr;
	return *this;
}

template <class T, class C>
SmartPointer<T, C>::~SmartPointer()
{
	CheckAndRemove();
}

template <class T, class C>
SmartPointer<T, C> & SmartPointer<T, C>::operator = (const std::auto_ptr<T> & smartPtr)
{
	CheckAndRemove();
	fcntr.add_ptr(smartPtr.get());
	this->crude_ptr = smartPtr.get();
	return *this;
}

template<class T, class C>
void SmartPointer<T, C>::CheckAndRemove()
{
	if (this->crude_ptr != NULL)
	if (fcntr.remove_ptr(this->crude_ptr))
	{
		delete this->crude_ptr;
		this->crude_ptr = NULL;
	}
}


//-------------------operators----------------------
template<class T, class C>
bool operator == (const std::auto_ptr<T> & smartPtrL, const SmartPointer<T, C> & smartPtrR){
	return *smartPtrL == *smartPtrR;
}
template<class T, class C>
bool operator == (const T* smartPtrL, const SmartPointer<T, C> & smartPtrR){
	return *smartPtrL == *smartPtrR;
}

template<class T, class C>
bool operator != (const std::auto_ptr<T> & smartPtrL, const SmartPointer<T, C> & smartPtrR){
	return *smartPtrL != *smartPtrR;
}
template<class T, class C>
bool operator != (const T* smartPtrL, const SmartPointer<T, C> & smartPtrR){
	return *smartPtrL != *smartPtrR;
}

template<class T, class C>
bool operator > (const std::auto_ptr<T> & smartPtrL, const SmartPointer<T, C> & smartPtrR){
	return *smartPtrL > *smartPtrR;
}
template<class T, class C>
bool operator > (const T* smartPtrL, const SmartPointer<T, C> & smartPtrR){
	return *smartPtrL > *smartPtrR;
}

template<class T, class C>
bool operator < (const std::auto_ptr<T> & smartPtrL, const SmartPointer<T, C> & smartPtrR){
	return *smartPtrL < *smartPtrR;
}
template<class T, class C>
bool operator < (const T* smartPtrL, const SmartPointer<T, C> & smartPtrR){
	return *smartPtrL < *smartPtrR;
}

template<class T, class C>
bool operator >=(const std::auto_ptr<T> & smartPtrL, const SmartPointer<T, C> & smartPtrR){
	return *smartPtrL >= *smartPtrR;
}
template<class T, class C>
bool operator >= (const T* smartPtrL, const SmartPointer<T, C> & smartPtrR){
	return *smartPtrL >= *smartPtrR;
}

template<class T, class C>
bool operator <= (const std::auto_ptr<T> & smartPtrL, const SmartPointer<T, C> & smartPtrR){
	return *smartPtrL <= *smartPtrR;
}
template<class T, class C>
bool operator <= (const T* smartPtrL, const SmartPointer<T, C> & smartPtrR){
	return *smartPtrL <= *smartPtrR;
}

template<class T, class C>
std::ostream & operator << (std::ostream & is, const SmartPointer<T, C> & smartPtr){
	is << smartPtr.crude_ptr;
	return is;
}