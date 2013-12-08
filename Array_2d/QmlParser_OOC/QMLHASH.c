#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "QMLHASH.h"
#include "new.h"
#include "list_in_ht.h"
#include "HashTable_ooc.h"

int Miss_All_Space(char* buffer, int* real_number)
{	
	int i = *real_number;

	if(!isspace(buffer[i]))
	{
		return i;
	}

	while (buffer[i + 1] == ' ')
		i++;
	*real_number = i++;
	return i++;
}

char* SearchInTheFile(FILE *pfile, char* buffer)
{
	int i = 0;
	char* value;

	while (1)
	{
		if (fgetc(pfile) == buffer[i])
		{
			
		}
	}
}

static Pointer QML_Ob_init(Pointer _self, va_list *app)
{
	struct QmlObject *self = (struct QmlObject*)((const struct TypeDescriptor *)HashTable)->ctor(_self, app);

	/*self->ParseFunction = va_arg(*app, Parse);
	
	if (self->ParseFunction == NULL)
	{
		self->ParseFunction = MyParser;
	}*/
	
	self->ValidPropertiesString = va_arg(*app, char*);
	return self;
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
	struct Object* new_object;

	int start_box_FLAG = 0;
	int name_FLAG = 0;
	int value_FLAG = 0;
	int ddd;

	while(fgets(buffer, 50, pFile))
	{
		i = j = k = counter = 0;

		Miss_All_Space(buffer, &i);
		
		if(buffer[i] == '{' && start_box_FLAG == 0)
		{
			i++;
			start_box_FLAG = 1;
			continue;			 
		}
		
		if(!isspace(buffer[i]) && start_box_FLAG == 1)
		{
			name_FLAG = 1;
			Miss_All_Space(buffer, &i);
			while(!isspace(buffer[i]) && buffer[i] != ':')
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
			if(strstr(QObject->ValidPropertiesString, Name))
			{
				Miss_All_Space(buffer, &i);
				if(buffer[i] == ':')
				{
					i++;
					name_FLAG = 0;
					value_FLAG = 1;

					Miss_All_Space(buffer, &i);

					while(!isspace(buffer[i]))
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
				new_object = new(Object, value);
				/*for (ddd = 0; ddd < strlen(new_object->value); ddd++)
					printf("%c", ((char*)(new_object->value))[ddd]);*/
								
				ht_set(&(QObject->InternalHashTable), Name, new_object, sizeof(struct Object));
				
				//delete(new_object);
			}


		}


	}
	free(value);
	free(Name);
	free(STName);
	free(buffer);
}


void GeneralDraw(Pointer _self)
{
	struct QmlObject* self = (struct QmlObject*)_self;
		
}

static Pointer QML_Ob_destroy(Pointer _self)
{
	struct QmlObject *self = (struct QmlObject *)((const struct TypeDescriptor *)HashTable)->dtor(_self);
	return(self);
}

static const struct TypeDescriptor _QmlObject = {
	sizeof(struct QmlObject),
	QML_Ob_init,
	QML_Ob_destroy,
	/*NULL*/
};
const void *QmlObject = &_QmlObject;
