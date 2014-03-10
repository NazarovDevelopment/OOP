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



	void Reset(T * ptr = NULL); // ������������� ����� ��������� �� ����� ������ (�� ptr)

	void Swap(SmartPointer<T, C> * smartPtr); // ������ ��������� �������

	long UseCount() const; // ���������� ���-�� ������ �� ������ ����������

	bool Unique() const; // ���������� ����� �� ���-�� ������ �� ������ ���������� 1

	T* Get(); // ���������� "����� ���������"

};