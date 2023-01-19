#ifndef __LINUX_GETCH_H__
#define __LINUX_GETCH_H__

#include <fstream>
#include "key.h"

namespace Getkey{
    bool is_input_from_file(int argc, char** argv);
    Key getkey();
    int getchar(Key key);
}

#endif