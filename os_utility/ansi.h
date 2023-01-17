// Include this file in your project to enable ANSI support.

#ifndef __ANSI_H__
#define __ANSI_H__

//#pragma execution_character_set("utf-8")

#ifdef _WIN32 // (Windows)
    #include <windows.h>
#endif

void enableANSI(){
    #ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD mode = 0;
        GetConsoleMode(hOut, &mode);
        mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, mode);
    #endif
    //linux have a native support for ANSI, so no need to do anything
}

#endif