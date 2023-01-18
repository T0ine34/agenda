// use this file for enable and disable raw mode in terminal (Windows and Linux)

#ifndef __RAW_MODE_H__
#define __RAW_MODE_H__

#ifdef _WIN32 // (Windows)
    #include <windows.h>
    DWORD original_mode_storage; // for saving original mode
#elif __linux__ // (Linux)
    #include <termios.h>
    #include <unistd.h>
    struct termios original_mode_storage; // for saving original mode
#endif


void enable_raw_mode(){
    #ifdef _WIN32
        HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE); 
        GetConsoleMode(hIn, &original_mode_storage); // saving original mode
        DWORD mode = 0;
        mode = original_mode_storage; // copying original mode
        mode &= ~ENABLE_ECHO_INPUT; //disable key printing in the console
        mode &= ~ENABLE_LINE_INPUT; //disable canonical mode, so that getchar() is taking the key as soon as you press it
        SetConsoleMode(hIn, mode);  // saving changes
    #elif __linux__
        tcgetattr(STDIN_FILENO, &original_mode_storage); // saving original mode
        struct termios mode;
        mode = original_mode_storage; // copying original mode
        mode.c_lflag &= ~ECHO;  //disable key printing in the console
        mode.c_lflag &= ~ICANON; //disable canonical mode, so that getchar() is taking the key as soon as you press it
        tcsetattr(STDIN_FILENO, TCSANOW, &mode); // saving changes
    #endif
}

void disable_raw_mode(){
    #if _WIN32
        SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), original_mode_storage); // restoring original mode
    #elif __linux__
        tcsetattr(STDIN_FILENO, TCSANOW, &original_mode_storage); // restoring original mode
    #endif
}

#endif