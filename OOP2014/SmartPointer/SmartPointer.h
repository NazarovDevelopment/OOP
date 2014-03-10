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

	T& operator*() const;

	T* operator->() const;



	void Reset(T * ptr = NULL); // устанавливает умный указатель на новый объект (на ptr)

	void Swap(SmartPointer<T, C> * smartPtr); // меняет указатели местами

	long UseCount() const; // возвращает кол-во ссылок на “сырой указатель”

	bool Unique() const; // возвращает равно ли кол-во ссылок на “сырой указатель” 1

	T* Get(); // возвращает "сырой указатель"

};