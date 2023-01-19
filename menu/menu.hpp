#ifndef __CONSOLE_MENU_HPP__
#define __CONSOLE_MENU_HPP__

#include <string>
#include <vector>
#include <map>

#include "../getch/getch.hpp"

namespace Menu{

    namespace Option{
        struct Option{
            std::string name = "Option";
            Key shortcut;
            std::string value;
        };

        const std::map<char, unsigned int> keys = {
            {'a', 97},
            {'b', 98},
            {'c', 99},
            {'d', 100},
            {'e', 101},
            {'f', 102},
            {'g', 103},
            {'h', 104},
            {'i', 105},
            {'j', 106},
            {'k', 107},
            {'l', 108},
            {'m', 109},
            {'n', 110},
            {'o', 111},
            {'p', 112},
            {'q', 113},
            {'r', 114},
            {'s', 115},
            {'t', 116},
            {'u', 117},
            {'v', 118},
            {'w', 119},
            {'x', 120},
            {'y', 121},
            {'z', 122},
            {'0', 48},
            {'1', 49},
            {'2', 50},
            {'3', 51},
            {'4', 52},
            {'5', 53},
            {'6', 54},
            {'7', 55},
            {'8', 56},
            {'9', 57}
        };
    
        Option option(const std::string name, const Key shortcut, const std::string value);
        Option option(const std::string name, const Key shortcut);
        Option option(const std::string name);
        Option option();
    
        std::string getValue(const Option& option);
    }



    struct Menu{
        std::string title = "Menu";
        std::vector<Option::Option> options = {};
        unsigned selected = 0;
        bool valid_input = false;
    };

    Menu menu(const std::string title, const std::vector<Option::Option>& options);
    Menu menu(const std::string title);
    Menu menu();

    void addOption(Menu& menu, const Option::Option& option);
    void addOption(Menu& menu, const Key shortcut, std::string name);
    void addOption(Menu& menu, const Key shortcut, std::string name, std::string value);

    void removeOption(Menu& menu, const std::string name);
    void removeOption(Menu& menu, const int index);

    std::string create_Window(const Menu& menu);

    std::string show(Menu& menu);

    void erase(const Menu& menu);

    void setTitle(Menu& menu, const std::string title);

    void reset(Menu& menu);
}

namespace Input{

    const unsigned char TEXT = 0;
    const unsigned char PASSWORD = 1;
    const unsigned char INTEGER = 2;
    const unsigned char DECIMAL = 3;

    struct Input{
        std::string title = "Input (type=%t)"; // %t for type, %m for max_length
        std::string value = "";
        std::string display = "";
        unsigned char type = TEXT; // TEXT, PASSWORD, INTEGER, DECIMAL
        unsigned max_length = 50;
        unsigned cursor_position = 0;
        bool valid_input = false;

    };

    Input input(const std::string title, const unsigned char type, const unsigned max_length);
    Input input(const std::string title, const unsigned char type);
    Input input(const std::string title);
    Input input();

    std::string titleProcessor(const Input& input);

    std::string create_window(const Input& input);

    std::string show(Input& input);
    
    void addChar(Input& input, const char& c);

    std::string getTitle(const Input& input);

    std::string getRawTitle(const Input& input);

    std::string getValue(const Input& input);
}

namespace Information{
    
    struct Information{
        std::string message = "Message";
        unsigned max_width = 50;
        bool valid_input = false;
        unsigned nb_lines = 0;
    };

    Information information(const std::string message);
    Information information(const std::string message, const unsigned max_width);

    std::string create_window(Information& information);

    void show(Information& information);

    void erase(const Information& information);
}

#endif