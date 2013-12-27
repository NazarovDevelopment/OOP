#include "MouseKlick.h"
#include "Factory.h"
#include "Rectangle.h"
#include "Text.h"
#include "TextInput.h"

bool MouseEvent::WhoIsPress(QmlObject* QmlO, int x_Pressed, int y_Pressed)
{
	int x = (int)QmlO->get<int>("x");
	int y = (int)QmlO->get<int>("y");
	int width = (int)QmlO->get<int>("width");
	int height = (int)QmlO->get<int>("height");

	if ((x_Pressed > x && x_Pressed < x + width) || (y_Pressed > y && y_Pressed < y + height))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MouseEvent::pressChild(QmlObject* Qml, int x, int y)
{
	for (int i = 0; i < Qml->ChildNumbers; i++)
	{
		if (WhoIsPress(Qml->Childs[i], x, y))
		{
			return true;
		}
	}
	return false;
}

int MouseEvent::mouseUser(int x, int y)
{
	for (int i = 0; i < Numbers; i++)
	{
		if (WhoIsPress(AllObject[i], x, y))
		{
			if (!pressChild(AllObject[i], x, y))
			{
				if (AllObject[i]->get<int>("canbefocused") == 1 && AllObject[i] != FocussedObject)
				{
					FocussedObject = AllObject[i];
						return 1;
				}
				switch (AllObject[i]->GetType())
				{ 
				case RECT:
					return ((Rectangle*)AllObject[i])->KeyPressed();
				case TXT:
					return ((mText*)AllObject[i])->KeyPressed();
				case TXTIN:
					return ((TextInput*)AllObject[i])->KeyPressed();

				default:
					return 1;
				}
			}
		}
	}
}
