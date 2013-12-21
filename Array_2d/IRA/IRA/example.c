//#include <assert.h>
//#include "console.h"
//
//#include <stdio.h>
//#include <stdlib.h>
//
//#define COLOR_PRINT 1
//int main() {
//	int x;
//	
//	con_init();
//	con_hideCursor();
//
//	con_initPair(COLOR_PRINT, CON_COLOR_WHITE, CON_COLOR_YELLOW);
//	con_setColor(CON_COLOR_RED);
//
//	for (x = 30; x < 100; x++)
//	{
//		con_gotoXY(x, 50);
//		con_setColor(COLOR_PRINT);
//	}
//	con_initPair(COLOR_PRINT, CON_COLOR_RED, CON_COLOR_RED);
//
//	for (x = 30; x < 100; x++)
//	{
//		con_gotoXY(x, 100);
//		con_setColor(COLOR_PRINT);
//	}
//
//	con_gotoXY(200, 200);
//	system("pause");
//	con_deinit();
//	return 0;
//}
//
