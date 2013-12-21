#ifndef CONSOLE_H
#define CONSOLE_H

#include <conio.h>

/*
 * You can init "color pairs": tuple of foreground color and
 * background color. This pairs can be set before any drawing
 * which use corresponding colors.
 */



#define CON_KEY_UP          -72
#define CON_KEY_LEFT        -75
#define CON_KEY_RIGHT       -77
#define CON_KEY_DOWN        -80
#define CON_KEY_ESCAPE      27
#define CON_KEY_INSERT      -82
#define CON_KEY_DEL         -83
#define CON_KEY_BACKSPACE   '\b'
#define CON_KEY_ENTER       '\r'
#define CON_KEY_HOME        -71
#define CON_KEY_END         -79
#define CON_KEY_PAGEUP      -73
#define CON_KEY_PAGEDOWN    -81

#define CON_COLOR_BLACK     0x0000
#define CON_COLOR_BLUE      0x0001
#define CON_COLOR_GREEN     0x0002
#define CON_COLOR_RED       0x0004
#define CON_COLOR_YELLOW    CON_COLOR_RED |CON_COLOR_GREEN
#define CON_COLOR_MAGENTA   CON_COLOR_RED | CON_COLOR_BLUE
#define CON_COLOR_CYAN      CON_COLOR_GREEN | CON_COLOR_BLUE
#define CON_COLOR_WHITE     CON_COLOR_GREEN | CON_COLOR_BLUE | CON_COLOR_RED

#define CON_MAX_COLORS      64

extern int      con_initPair(short n, short fg, short bg);
extern int      con_setColor(short n);

extern void     con_init();
extern void     con_deinit();

extern void     con_showCursor();
extern void     con_hideCursor();

extern int      con_gotoXY(int x, int y);
extern int      con_getXY(int *px, int *py);
extern int      con_getMaxXY(int *px, int *py);
extern int      con_clearScr();

extern int      con_outTxt(const char *format, ...);

extern int      con_keyPressed();
extern int      con_getKey();

#endif


