#include "Rectangle.h"

Rectangle::Rectangle(void(*Pressed)(int key)): QmlObject(5, NULL, "_id_x_y_width_height_color_canBeFocused_"){
	KeyPressed = Pressed;
}