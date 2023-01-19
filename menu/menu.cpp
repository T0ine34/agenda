#include "menu.hpp"

#include <iostream>
#include <stdio.h> //for getch()
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

#include <chrono>

#include <fstream>

#include "../utility/utility.hpp"
#include "../getch/getch.hpp"



namespace Menu{

    namespace Option{
        Option option (const std::string name, const Key shortcut, const std::string value){
            Option option;
            option.name = name;
            option.shortcut = shortcut;
            option.value = value;
            return option;
        }
        
        Option option(const std::string name, const Key shortcut){
            Option option;
            option.name = name;
            option.shortcut = shortcut;
            option.value = name;
            return option;
        }

        Option option(const std::string name){
            Option option;
            option.name = name;
            option.shortcut = Key::UNDEFINED;
            option.value = name;
            return option;
        }

        Option option(){
            Option option;
            option.name = "Option";
            option.shortcut = Key::UNDEFINED;
            option.value = "";
            return option;
        }

        std::string getValue(const Option& option){
            return option.value;
        }
    }

    Menu menu(const std::string title, const std::vector<Option::Option>& options){
        Menu menu;
        menu.title = title;
        menu.options = options;
        return menu;
    }

    Menu menu(const std::string title){
        Menu menu;
        menu.title = title;
        return menu;
    }

    Menu menu(){
        Menu menu;
        menu.title = "Menu";
        return menu;
    }

    void addOption(Menu& menu, const Option::Option& option){
        menu.options.push_back(option);
    }

    void addOption(Menu& menu, const Key shortcut, std::string name){
        Option::Option option;
        option.name = name;
        option.shortcut = shortcut;
        option.value = name;
        menu.options.push_back(option);
    }

    void addOption(Menu& menu, const Key shortcut, std::string name, std::string value){
        Option::Option option;
        option.name = name;
        option.shortcut = shortcut;
        option.value = value;
        menu.options.push_back(option);
    }

    void removeOption(Menu& menu, const std::string name){
        for(std::size_t i = 0; i < menu.options.size(); i++){
            if(menu.options[i].name == name){
                menu.options.erase(menu.options.begin() + i);
            }
        }
    }

    void removeOption(Menu& menu, const int index){
        menu.options.erase(menu.options.begin() + index);
    }

    //return true if we continue the loop, false if we exit the loop (escape key)
    bool action(Menu& menu, const Key& c1){
            switch (c1){
                case Key::ARROW_UP:{
                    if(menu.selected > 0){
                        menu.selected--;
                    }
                    break;                            
                }
                case Key::ARROW_DOWN:{
                    if(menu.selected < menu.options.size() - 1){
                        menu.selected++;
                    }
                    break;
                }
                case Key::ENTER:{
                    menu.valid_input = true;
                    break;
                }
                case Key::ESCAPE:{
                    return false;
                }
                default:{ //if the input is a shortcut
                    for(std::size_t i = 0; i < menu.options.size(); i++){
                        if(menu.options[i].shortcut == c1){
                            menu.selected = i;
                            menu.valid_input = true;
                            break;
                        }
                    }
                }
            }
            return true;
        }

    std::string create_Window(const Menu& menu){
        std::string window = "";

        unsigned width = Utility::getNbchars(menu.title);
        for(std::size_t i = 0; i < menu.options.size(); i++){
            if(menu.options[i].name.size() > width){
                width = Utility::getNbchars(menu.options[i].name);
            }
        }
        width += 6;

        //make a rectangle around the menu
        window += "┌";
        for(std::size_t i = 0; i < width; i++){
            window += "─";
        }
        window += "┐\n";

        //print the title
        window += "│ ";

        unsigned short spaces = round(double(width - Utility::getNbchars(menu.title) - 2)/2);
        for(std::size_t i = 0; i < spaces; i++){
            window += " ";
        }

        window += menu.title + " ";
        for(std::size_t i = 0; i < width-(spaces+Utility::getNbchars(menu.title))-2; i++){
            window += " ";
        }
        window += "│\n";

        window += "├───┬";
        for(std::size_t i = 0; i < width-4; i++){
            window += "─";
        }
        window += "┤\n";

        //print the options
        unsigned short options_num = menu.options.size();
        for(std::size_t i = 0; i < options_num; i++){
            window += "│ ";
            window += Getkey::getchar(menu.options[i].shortcut);
            window += " │ ";
            if(i == menu.selected){
                window += "\x1B[7m\x1B[37m";
            }
            window += menu.options[i].name;
            if(i == menu.selected){
                window += "\x1B[0m";
            }
            window += " ";


            unsigned short missing_char = width - Utility::getNbchars(menu.options[i].name)- 6;
            for(std::size_t j = 0; j < missing_char; j++){
                window += " ";
            }
            window += "│\n";
        }
        window += "└───┴";
        for(std::size_t i = 0; i < width-4; i++){
            window += "─";
        }
        window += "┘\n";

        return window;
    }

    std::string show(Menu& menu){
        bool continue_loop = true;
        do{
            std::cout << create_Window(menu) << std::flush;
            Key c = Getkey::getkey();
            continue_loop = action(menu, c);
            erase(menu);
            if (!continue_loop){
                return "";
            }
        }while (!menu.valid_input && continue_loop);
        return menu.options[menu.selected].value;
    }
        
    void erase(const Menu& menu){
        std::cout << "\x1B[" << menu.options.size() + 4 << "A" << "\x1B[0J" << std::flush;
    }

    void setTitle(Menu& menu, const std::string title){
        menu.title = title;
    }

    void reset(Menu& menu){
        menu.selected = 0;
        menu.valid_input = false;
    }
}

namespace Input{
    
    Input input(const std::string title, const unsigned char type, const unsigned max_length){
        Input input;
        input.title = title;
        input.type = type;
        input.max_length = max_length;
        return input;
    }

    Input input(const std::string title, const unsigned char type){
        Input input;
        input.title = title;
        input.type = type;
        return input;
    }

    Input input(const std::string title){
        Input input;
        input.title = title;
        return input;
    }

    Input input(){
        Input input;
        return input;
    }

    // return the title of the input, with values in the title replaced by the value of the input,
    // it does not modify the title of the input
    // %t is replaced by type of the input
    // %m is replaced by max_length of the input
    std::string titleProcessor(const Input& input){
        std::string title = input.title;
        for (std::size_t i = 0; i < Utility::getNbchars(input.title); ++i){
            if (title[i] == '%'){
                if (title[i + 1] == 't'){
                    switch (input.type){
                        case TEXT:
                            title.replace(i, 2, "text");
                            break;
                        case PASSWORD:
                            title.replace(i, 2, "password");
                            break;
                        case INTEGER:
                            title.replace(i, 2, "number");
                            break;
                        case DECIMAL:
                            title.replace(i, 2, "decimal");
                            break;

                    }
                }
                else if (title[i + 1] == 'm'){
                    title.replace(i, 2, std::to_string(input.max_length));

                }
            }
        }
        return title;
    }

    std::string create_window(const Input& input){
        //width of the window is max_length + 2 + 4
        std::string window = "";
        window += "┌";
        for (std::size_t i = 0; i < input.max_length + 2; i++){
            window += "─";
        }
        window += "┐\n│ ";

        std::string title = titleProcessor(input);
        window += Utility::extend(title, input.max_length + 1, ' ', true);

        window += "│\n│ ";
        //write input.display, with the cursor at cursor_position; add underscore to fill the rest of the window; keep 4 spaces at the beginning and at the end
        for (std::size_t i = 0; i < input.max_length; i++){
            if (i == input.cursor_position){ // cursor, invert colors
                window += "\x1B[7m";
                if(i < Utility::getNbchars(input.display)){
                    window += input.display[i];
                }
                else{
                    window += "_";
                }
                window += "\x1B[0m";
            }
            else{
                if(i < Utility::getNbchars(input.display)){
                    window += input.display[i];
                }
                else{
                    window += "_";
                }
            }
        }
        
        window += " │\n└";
        for (std::size_t i = 0; i < input.max_length + 2; i++){
            window += "─";
        }
        window += "┘";
        return window;
    }

    //add c to the input, if it is valid, at the cursor_position
    void addChar(Input& input, const char& c){
        if(input.value.size() < input.max_length){
            switch (input.type){
                case TEXT:{
                    input.value.insert(input.cursor_position, 1, c);
                    input.display.insert(input.cursor_position, 1, c);
                    input.cursor_position++;
                    break;
                }
                case PASSWORD:{
                    input.value.insert(input.cursor_position, 1, c);
                    input.display.insert(input.cursor_position, 1, '*');
                    input.cursor_position++;
                    break;
                }
                case INTEGER:{
                    if (c >= '0' && c <= '9'){
                        input.value.insert(input.cursor_position, 1, c);
                        input.display.insert(input.cursor_position, 1, c);
                        input.cursor_position++;
                    }
                    break;
                }
                case DECIMAL:{
                    if (((c >= '0' && c <= '9') || c == '.') && (input.value.find('.') == std::string::npos || c != '.')){
                        input.value.insert(input.cursor_position, 1, c);
                        input.display.insert(input.cursor_position, 1, c);
                        input.cursor_position++;
                    }
                    break;
                }
            }
        }
    }

    void deleteChar(Input& input, unsigned pos){
        input.value.erase(pos, 1);
        input.display.erase(pos, 1);
        input.value.shrink_to_fit();
        input.display.shrink_to_fit();
    }

    // return if we don't get back (escape key) (false for escape)
    bool analyse_input(Input& input, const Key& c1){
        switch (c1){
            case Key::BACKSPACE:{
                if(input.cursor_position > 0){
                    deleteChar(input, input.cursor_position - 1);
                    input.cursor_position--;
                }
                break;
            }
            case Key::ENTER:{
                input.valid_input = true;
                if(Utility::getNbchars(input.value) == 0){
                    input.value = input.value = ' ';
                    input.display = ' ';
                }
                break;
            }
            case Key::ARROW_LEFT:{
                if(input.cursor_position > 0){
                    input.cursor_position--;
                }
                break;
            }
            case Key::ARROW_RIGHT:{
                if(input.cursor_position < Utility::getNbchars(input.display)){
                    input.cursor_position++;
                }
                break;
            }
            case Key::_DELETE:{
                if(input.cursor_position < Utility::getNbchars(input.display)&& input.cursor_position >= 0){
                    deleteChar(input, input.cursor_position);
                }
                break;
            }
            case Key::ESCAPE:{ //escape
                return false;
            }
            default:{ //add the char
                int c = Getkey::getchar(c1);
                addChar(input, c);
                break;
            }
        }
        return true;
    }

    void erase(const Input& input){
        std::cout << "\x1B[4A\x1B[0J" << std::flush;
    }

    std::string show(Input& input){
        bool continue_input = true;
        do{
            std::cout << create_window(input) << std::endl;
            Key c1 = Getkey::getkey();
            continue_input = analyse_input(input, c1);
            erase(input);
            if(!continue_input){
                return "";
            }
        }while(!input.valid_input);
        return getValue(input);
    }

    std::string getTitle(const Input& input){
        return titleProcessor(input);
    }

    std::string getRawTitle(const Input& input){
        return input.title;
    }

    std::string getValue(const Input& input){
        return input.value;
    }

}

namespace Information{

    Information information(const std::string message){
        Information information;
        information.message = message;
        return information;
    }
    Information information(const std::string message,const unsigned max_width){
        Information information;
        information.message = message;
        information.max_width = max_width;
        return information;
    }

    std::string create_window(Information& information){
        // display the message on multiple lines if it is too long (information.max_width), but reduce the width of the window if it is too long
        std::vector<std::string> lines = Utility::split_on_spaces(information.message, information.max_width);
        information.nb_lines = lines.size();
        unsigned width = Utility::getNbchars(Utility::max_size(lines));

        for (std::size_t i = 0; i < lines.size(); i++){
            lines[i] = Utility::extend(lines[i], width, ' ', true);
        }
        std::string window = "┌";
        for (std::size_t i = 0; i < width + 2; i++){
            window += "─";
        }
        window += "┐\n";

        for (std::size_t i = 0; i < lines.size(); i++){
            window += "│ "+lines[i] + " │\n";
        }

        window += "└";
        for (std::size_t i = 0; i < width + 2; i++){
            window += "─";
        }
        window += "┘";

        return window;
    }

    void show(Information& information){
        std::cout << create_window(information) << std::endl;
        Getkey::getkey(); //wait for any key to be pressed
        erase(information);
    }

    void erase(const Information& information){
        std::cout << "\x1B[" << information.nb_lines+2 << "A\x1B[0J" << std::flush;
    }
}

namespace Choice{
    Choice choice(std::string title, std::string option1, std::string option2, bool default_value = 0){
        Choice c;
        c.title = title;
        c.option1 = option1;
        c.option2 = option2;
        c.is_2_selected = default_value;
        return c;
    }

    Choice choice(std::string title, bool default_value = 0){
        Choice c;
        c.title = title;
        c.option1 = "Yes";
        c.option2 = "No";
        c.is_2_selected = default_value;
        return c;
    }

    std::string create_window(const Choice& choice){
        unsigned width = Utility::getNbchars(choice.title);
        width < (Utility::getNbchars(choice.option1) + 3 + Utility::getNbchars(choice.option2)) ?
        width = Utility::getNbchars(choice.option1) + 3 + Utility::getNbchars(choice.option2) :
        width = width;

        unsigned width_opt1 = (width-3)/2;
        unsigned width_opt2 = width-3-width_opt1;

        std::string window = "┌";
        for (std::size_t i = 0; i < width + 2; i++){
            window += "─";
        }
        window += "┐\n";

        window += "│ "+Utility::extend(choice.title, width, ' ', true) + " │\n";

        window += "│ ";
        if(!choice.is_2_selected){
            window += "\x1B[7m\x1B[37m";
        }
        window += Utility::extend(choice.option1, width_opt1, ' ', true);
        if(!choice.is_2_selected){
            window += "\x1B[0m";
        }
        window += " │ ";
        if(choice.is_2_selected){
            window += "\x1B[7m\x1B[37m";
        }
        window += Utility::extend(choice.option2, width_opt2, ' ', true);
        if(choice.is_2_selected){
            window += "\x1B[0m";
        }
        window += " │\n";

        window += "└";
        for (std::size_t i = 0; i < width + 2; i++){
            window += "─";
        }
        window += "┘";

        return window;
    }

    // return 0 if the first option is selected, 1 if the second option is selected
    bool show(Choice& choice){
        bool continue_choice = true;
        do{
            std::cout << create_window(choice) << std::endl;
            Key c1 = Getkey::getkey();
            switch (c1){
                case Key::ARROW_LEFT:{
                    choice.is_2_selected = false;
                    break;
                }
                case Key::ARROW_RIGHT:{
                    choice.is_2_selected = true;
                    break;
                }
                case Key::ESCAPE:{ //escape
                    return false;
                }
                case Key::ENTER:{
                    continue_choice = false;
                    break;
                }
                default:{
                    break;
                }
            }
            erase(choice);
        }while(continue_choice);
        return choice.is_2_selected;
    }

    void erase(const Choice& choice){
        std::cout << "\x1B[4A\x1B[0J" << std::flush;
    }
}