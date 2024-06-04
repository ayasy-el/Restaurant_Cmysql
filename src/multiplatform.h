#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#include <conio.h>
#define CLEAR "cls"
#define SLEEP(x) Sleep(x / 1000)
#define SET_CONSOLE() SetConsoleOutputCP(CP_UTF8)
#define ENTER 13
#else
#include <termios.h>
#include <unistd.h>
#define CLEAR "clear"
#define ENTER 10
#define SET_CONSOLE()
#define SLEEP(x) usleep((x))
#endif