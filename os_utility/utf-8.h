// Include this file in your project to enable UTF-8 support.

#ifndef __UTF_8_H__
#define __UTF_8_H__

//#pragma execution_character_set("utf-8")

#ifdef _WIN32 // (Windows)
    #include <windows.h>
    u_int storage;
#elif __linux__ // (Linux)
    #include <locale.h>
    #include <cstring>
    char* storage;
#endif

void enableUTF8(){
    #if _WIN32
        storage = GetConsoleOutputCP();
        SetConsoleOutputCP(CP_UTF8); // (Windows)
    #elif __linux__
        storage = setlocale(LC_ALL, ""); //  (Linux)
    #endif
}

void disableUTF8(){
    #if _WIN32
        SetConsoleOutputCP(storage); // (Windows)
    #elif __linux__
        setlocale(LC_ALL, storage); //  (Linux)
    #endif
}

#endif