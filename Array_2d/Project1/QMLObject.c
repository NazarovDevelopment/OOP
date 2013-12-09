#include <stdio.h>

#include "QMLObject.h"
#include "QMLObject_r.h"

#include "HashTable_r.h"
#include "HashTable.h"

#include "OneProperty_r.h"
#include "OneProperty.h"

static void * QmlObject_ctor(void * _pSelf, va_list * ppArgs)
{
	struct QmlObject * pSelf = base_ctor(QmlObject, _pSelf, ppArgs);
	char* buffer = va_arg(*ppArgs, char*);
	pSelf->ValidPropertiesString = calloc(strlen(buffer) + 1, sizeof(char));
	strcpy(pSelf->ValidPropertiesString, buffer);
	return pSelf;
}

void * QmlObject_dtor(void* _self)
{
	QMLOBJECT* self = _self;
	HashTable_dtor(&self->_);
	free(self->ValidPropertiesString);
	return self;
}

static void QmlObject_draw(const void * _pSelf)
{
	// переопределённое рисование

	const QMLOBJECT * pSelf = _pSelf;
	const HASHTABLE * pBase = _pSelf;

}

/* ----------------------------------------------------------------------------------------------- *
*      объявление переменных с мета-информацией о типе CIRCLE
*/

static HASHTABLE_CLASS QmlObject_info; // мета-информация о типе CIRCLE

/* ----------------------------------------------------------------------------------------------- *
*      инициализация "красивых" констант-указателей на мета-информацию о CIRCLE
*/

const void * QmlObject = &QmlObject_info;


void init_QmlObjectClass(void)
{
	init_HashTableClass();

	inplace_new(
		&QmlObject_info, // мета-информация о типе CIRCLE
		HashTableClass,   // мета-информация является экземпляром типа POINT_CLASS

		"QmlObject",       // символическое имя типа
		HashTable,          // мета-информация о предке (предок CIRCLE -> POINT)
		sizeof(QMLOBJECT), // размер типа в байтах

		ctor, QmlObject_ctor, // переопределено динамическое связывание ctor -> Circle_ctor
		draw, QmlObject_draw,
		dtor, QmlObject_dtor,
		0
		);
}

int Miss_All_Space(char* buffer, int* real_number)
{
	int i = *real_number;

	if (!isspace(buffer[i]))
	{
		return i;
	}

	while (buffer[i + 1] == ' ')
		i++;
	*real_number = i++;
	return i++;
}

void MyParser(struct QmlObject* QObject, FILE *pFile)
{
	int i = 0;
	int j = 0;
	int counter = 0;
	int k = 0;
	char *Name = (char*)malloc(sizeof(char)* 20);
	char *STName = (char*)malloc(sizeof(char)* 20);
	char* value = (char*)malloc(sizeof(char)* 20);
	char* buffer = (char*)malloc(sizeof(char)* 20);
	ONEPROPERTY* new_object;

	int start_box_FLAG = 0;
	int name_FLAG = 0;
	int value_FLAG = 0;
	int ddd;

	while (fgets(buffer, 50, pFile))
	{
		i = j = k = counter = 0;

		Miss_All_Space(buffer, &i);

		if (buffer[i] == '{' && start_box_FLAG == 0)
		{
			i++;
			start_box_FLAG = 1;
			continue;
		}

		if (!isspace(buffer[i]) && start_box_FLAG == 1)
		{
			name_FLAG = 1;
			Miss_All_Space(buffer, &i);
			while (!isspace(buffer[i]) && buffer[i] != ':')
			{
				Name[j++] = buffer[i++];
			}

			Miss_All_Space(buffer, &i);
			if (!isspace(buffer[i]) && buffer[i] != ':')
			{
				printf("Text file contains an error");
				return 0;
			}
			Name[j] = '\0';

			/*STName[0] = '_';
			for(counter = 0; counter < strlen(Name); counter++)
			{
			STName[counter+1] = Name[counter];
			}
			STName[strlen(Name) + 2] = '\0';*/

			/*Miss_All_Space(buffer, &i);*/
			if (strstr(QObject->ValidPropertiesString, Name))
			{
				Miss_All_Space(buffer, &i);
				if (buffer[i] == ':')
				{
					i++;
					name_FLAG = 0;
					value_FLAG = 1;

					Miss_All_Space(buffer, &i);

					while (!isspace(buffer[i]))
					{
						value[k++] = buffer[i++];
					}
					value_FLAG = 0;
					value[k] = '\0';
				}

				Miss_All_Space(buffer, &i);
				if (!isspace(buffer[i]))
				{
					printf("Text file contains an error");
					return 0;
				}

			}

			if (value && Name && (name_FLAG == NULL) && (value_FLAG == NULL))
			{
				init_OnePropertyClass();
				new_object = new(OneProperty, value);
				/*for (ddd = 0; ddd < strlen(new_object->value); ddd++)
				printf("%c", ((char*)(new_object->value))[ddd]);*/

				ht_set(&(QObject->_), Name, new_object, sizeof(struct Object));

				//delete(new_object);
			}


		}


	}
	free(value);
	free(Name);
	free(STName);
	free(buffer);
}


void GeneralDraw(void* _self)
{
	struct QmlObject* self = (struct QmlObject*)_self;

}
