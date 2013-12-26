#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>

#include "Factory.h"
#include "Rectangle.h"
#include "Text.h"
#include "TextInput.h"

class MouseEvent
{
public:

	static bool WhoIsPress(QmlObject* QmlO, int x_Pressed, int y_Pressed);

	static int mouseUser(int x, int y);

	static bool pressChild(QmlObject* Qml, int x, int y);
private:

};