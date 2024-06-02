#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#include <conio.h>
#define CLEAR "cls"
#define SLEEP(x) Sleep(x)
#define ENTER 13
#else
#include <termios.h>
#include <unistd.h>
#define CLEAR "clear"
#define ENTER 10
#define SLEEP(x) usleep((x) * 1000)
#endif