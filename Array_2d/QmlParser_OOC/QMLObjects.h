#pragma once
#include "new.h"
#include "windows.h"

struct Button
{
	const void *TypeDescriptor;
	size_t Size;

	char caption;
	int x;
	int y;
	int Height;
	int Width;
	int Color;

	char *validPropertiesString;

	void(*Draw)();
	int(*SetProperty)();
	int(*GetProperty)();

};

struct TextBox
{
	const void *TypeDescriptor;
	size_t size;

	char caption;
	int x;
	int y;
	int Height;
	int Width;
	int ColorBack;

	char *validPropertiesString;

	void(*Draw)();
	int(*SetProperty)();
	int(*GetProperty)();
	
};

struct ImageBmp
{
	const void *TypeDescriptor;
	size_t size;
	
	char caption;
	int x;
	int y;
	int Height;
	int Width;
	
	char *validPropertiesString;

	const char* URL = "";

	void(*Draw)();
	int(*SetProperty)();
	int(*GetProperty)();

};

