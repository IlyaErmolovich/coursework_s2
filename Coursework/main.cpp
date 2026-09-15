#include <iostream>
#include <Windows.h>
#include "menu.h"

using namespace std;

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    menu();
    return 0;
}
