#include "Rectangle.h"
#include "TextInput.h"
#include "Text.h"

#include "Factory.h"
class Printer
{
public:
	Printer();
	~Printer();

	static void draw(sf::RenderWindow* App)
	{
 		
		switch (AllObject[0]->GetType())
		{
		case RECT:
			((Rectangle*)AllObject[0])->draw(App);
			break;
		case TXT:
			((mText*)AllObject[0])->draw(App);
			break;
		case TXTIN:
			((TextInput*)AllObject[0])->draw(App);
			break;
		default:
			break;
		}
	}

private:

};

Printer::Printer()
{
}

Printer::~Printer()
{
}