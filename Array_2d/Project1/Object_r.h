#ifndef OBJECT_R
#define OBJECT_R

typedef struct Object OBJECT;
typedef struct ObjectClass OBJECT_CLASS;
typedef void(*PFUNC)(void);  // абстрактный указатель на функцию

/* ----------------------------------------------------------------------------------------------- *
*      OBJECT : базовый тип, корень иерархии наследования
*      все остальные типы являются наследниками OBJECT и содержат в начале себя указатель на
*      мета-информацию
*/

struct Object
{
	const OBJECT_CLASS * pClass; // мета-информация о типе
};

/* ----------------------------------------------------------------------------------------------- *
*      OBJECT_CLASS : мета-информация описывающая тип OBJECT
*      все остальные типы хранящие мета-информацию являются наследниками OBJECT_CLASS и
*      отличаются от него только "хвостом" массива указателей на методы
*/

struct ObjectClass
{
	const OBJECT  _; // OBJECT_CLASS является наследником OBJECT =>
	// каждый экземпляр OBJECT_CLASS содержит в начале себя OBJECT

	const char *         name;       // строковая константа с именем описываемого типа данных
	const OBJECT_CLASS * pBaseClass; // мета-информация о предке описываемого типа данных
	size_t               size;       // размер описываемого типа данных в байтах

	// таблица методов типа OBJECT: ...

	void * (*pfnCtor)   (void * pSelf, va_list * ppArgs);          // конструктор
	void * (*pfnDtor)   (void * pSelf);                            // деструктор
	int(*pfnDiffer) (const void * pSelf, const void * pOther); // сравнение
	int(*pfnPrint)  (const void * pSelf, FILE * pStream);      // печать
};

/* ----------------------------------------------------------------------------------------------- *
*      вспомогательные функции вызывающие методы базового типа
*              допустим вызов этих 4 функций для наследников OBJECT, т.е. у всех типов в иерархии
*/

void * base_ctor(const void * _pClass, void * _pSelf, va_list * ppArgs);
void * base_dtor(const void * _pClass, void * _pSelf);
int base_differ(const void * _pClass, const void * _pSelf, const void * _pOther);
int base_print(const void * _pClass, const void * _pSelf, FILE * pStream);

#endif