#ifndef _UTILS_H_
#define _UTILS_H_

#define HEART   "\x03"

// you must have a config file, both for windows and for compiling on Linux (MAMA)
// BUT, you need to change the content of the config!
#include "config.h"
#include "enums.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>

using std::map;

void gotoxy(int x, int y);
void setTextColor(Color);
void hideCursor();
void clear_screen();
char getDirChar(Direction dir);
Direction getDirEnum(char dir);
FlagsMode getMode(int argc, char* argv[]);

#ifndef WINDOWS	
int _getch(void);
int _kbhit(void);
void Sleep(unsigned long);
#else
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#endif

#endif