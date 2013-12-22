#ifndef TEXT_H
#define TEXT_H

#include "QmlObject.h"

using namespace std;



class Text : public QmlObject
{
public:

	Text(void(*Pressed)(int key));
	~Text();

	void draw()
	{


	}

	void(*KeyPressed)(int key);

};


#endif