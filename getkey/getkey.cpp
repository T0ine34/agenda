#include "key.h"
#include "getkey.hpp"

#include <iostream>
#include <fstream>

#include <string>

#include <unistd.h> //for isatty()
#include <stdio.h> //for fileno()

#include <ios>

#include <filesystem>
namespace fs = std::filesystem;



namespace Getkey{
    
    std::ifstream file_input;
    bool use_file_input = false;
    bool is_temp_file = false;
    unsigned waiting_time = 0;

    bool is_input_from_file(int argc, char** argv){
        if (argc > 1){
            if(fs::is_regular_file(fs::path(argv[1]))){
                file_input = std::ifstream(argv[1]);
                use_file_input = true;
            }
            else{
                use_file_input = false;
            }
        }
        else{
            //The code below is for transfering the redirected input to a temporary file, but I can't find a way to detect if the input is redirected from a file or not
            
            //verify if the user redirect the input from a file; if yes, use it
            if(!isatty(fileno(stdin))){
                std::string temp_file_path = fs::temp_directory_path().string() + "/getkey_temp_file";
                std::ofstream temp_file(temp_file_path);
                while(std::cin){
                    std::string line;
                    std::getline(std::cin, line);
                    temp_file << line << std::endl;
                }
                while (std::cin.get() != EOF);
                temp_file.close();
                file_input = std::ifstream(temp_file_path);
                use_file_input = true;
                is_temp_file = true;
            }
            else{
                use_file_input = false;
            }
        }
        return use_file_input;
    }

    Key analyse_key(std::string cmd){
        if(cmd == "ARROW_DOWN") return Key::ARROW_DOWN;
        else if(cmd == "ARROW_UP") return Key::ARROW_UP;
        else if(cmd == "ARROW_LEFT") return Key::ARROW_LEFT;
        else if(cmd == "ARROW_RIGHT") return Key::ARROW_RIGHT;
        else if(cmd == "ENTER") return Key::ENTER;
        else if(cmd == "ESCAPE") return Key::ESCAPE;
        else if(cmd == "BACKSPACE") return Key::BACKSPACE;
        else if(cmd == "SPACE") return Key::SPACE;
        else if(cmd == "TAB") return Key::TAB;
        else if(cmd == "DELETE") return Key::_DELETE;
        else if(cmd == "INSERT") return Key::INSERT;
        else if(cmd == "HOME") return Key::HOME;
        else if(cmd == "END") return Key::END;
        else if(cmd == "PAGE_UP") return Key::PAGE_UP;
        else if(cmd == "PAGE_DOWN") return Key::PAGE_DOWN;
        else if(cmd == "F1") return Key::F1;
        else if(cmd == "F2") return Key::F2;
        else if(cmd == "F3") return Key::F3;
        else if(cmd == "F4") return Key::F4;
        else if(cmd == "F5") return Key::F5;
        else if(cmd == "F6") return Key::F6;
        else if(cmd == "F7") return Key::F7;
        else if(cmd == "F8") return Key::F8;
        else if(cmd == "F9") return Key::F9;
        else if(cmd == "F10") return Key::F10;
        else if(cmd == "F11") return Key::F11;
        else if(cmd == "F12") return Key::F12;
        else if(cmd == "A") return Key::A;
        else if(cmd == "B") return Key::B;
        else if(cmd == "C") return Key::C;
        else if(cmd == "D") return Key::D;
        else if(cmd == "E") return Key::E;
        else if(cmd == "F") return Key::F;
        else if(cmd == "G") return Key::G;
        else if(cmd == "H") return Key::H;
        else if(cmd == "I") return Key::I;
        else if(cmd == "J") return Key::J;
        else if(cmd == "K") return Key::K;
        else if(cmd == "L") return Key::L;
        else if(cmd == "M") return Key::M;
        else if(cmd == "N") return Key::N;
        else if(cmd == "O") return Key::O;
        else if(cmd == "P") return Key::P;
        else if(cmd == "Q") return Key::Q;
        else if(cmd == "R") return Key::R;
        else if(cmd == "S") return Key::S;
        else if(cmd == "T") return Key::T;
        else if(cmd == "U") return Key::U;
        else if(cmd == "V") return Key::V;
        else if(cmd == "W") return Key::W;
        else if(cmd == "X") return Key::X;
        else if(cmd == "Y") return Key::Y;
        else if(cmd == "Z") return Key::Z;
        else if(cmd == "a") return Key::a;
        else if(cmd == "b") return Key::b;
        else if(cmd == "c") return Key::c;
        else if(cmd == "d") return Key::d;
        else if(cmd == "e") return Key::e;
        else if(cmd == "f") return Key::f;
        else if(cmd == "g") return Key::g;
        else if(cmd == "h") return Key::h;
        else if(cmd == "i") return Key::i;
        else if(cmd == "j") return Key::j;
        else if(cmd == "k") return Key::k;
        else if(cmd == "l") return Key::l;
        else if(cmd == "m") return Key::m;
        else if(cmd == "n") return Key::n;
        else if(cmd == "o") return Key::o;
        else if(cmd == "p") return Key::p;
        else if(cmd == "q") return Key::q;
        else if(cmd == "r") return Key::r;
        else if(cmd == "s") return Key::s;
        else if(cmd == "t") return Key::t;
        else if(cmd == "u") return Key::u;
        else if(cmd == "v") return Key::v;
        else if(cmd == "w") return Key::w;
        else if(cmd == "x") return Key::x;
        else if(cmd == "y") return Key::y;
        else if(cmd == "z") return Key::z;
        else if(cmd == "0") return Key::ZERO;
        else if(cmd == "1") return Key::ONE;
        else if(cmd == "2") return Key::TWO;
        else if(cmd == "3") return Key::THREE;
        else if(cmd == "4") return Key::FOUR;
        else if(cmd == "5") return Key::FIVE;
        else if(cmd == "6") return Key::SIX;
        else if(cmd == "7") return Key::SEVEN;
        else if(cmd == "8") return Key::EIGHT;
        else if(cmd == "9") return Key::NINE;
        else if(cmd == "NUMPAD_0") return Key::NUMPAD_ZERO;
        else if(cmd == "NUMPAD_1") return Key::NUMPAD_ONE;
        else if(cmd == "NUMPAD_2") return Key::NUMPAD_TWO;
        else if(cmd == "NUMPAD_3") return Key::NUMPAD_THREE;
        else if(cmd == "NUMPAD_4") return Key::NUMPAD_FOUR;
        else if(cmd == "NUMPAD_5") return Key::NUMPAD_FIVE;
        else if(cmd == "NUMPAD_6") return Key::NUMPAD_SIX;
        else if(cmd == "NUMPAD_7") return Key::NUMPAD_SEVEN;
        else if(cmd == "NUMPAD_8") return Key::NUMPAD_EIGHT;
        else if(cmd == "NUMPAD_9") return Key::NUMPAD_NINE;
        else if(cmd == "NUMPAD_PLUS") return Key::NUMPAD_PLUS;
        else if(cmd == "NUMPAD_MINUS") return Key::NUMPAD_MINUS;
        else if(cmd == "NUMPAD_MULTIPLY") return Key::NUMPAD_MULTIPLY;
        else if(cmd == "NUMPAD_DIVIDE") return Key::NUMPAD_DIVIDE;
        else if(cmd == "NUMPAD_ENTER") return Key::NUMPAD_ENTER;
        else if(cmd == "NUMPAD_DOT") return Key::NUMPAD_DOT;
        else return Key::UNKNOWN;
    }


    #ifdef _WIN32
        #include <conio.h>

    //transform the key from the windows getch() function to a Key enum
        Key analyse_key(int key){
            switch(key){
                case 224:{
                    switch(getch()){
                        case 72: return Key::ARROW_UP;
                        case 80: return Key::ARROW_DOWN;
                        case 75: return Key::ARROW_LEFT;
                        case 77: return Key::ARROW_RIGHT;
                        case 71: return Key::HOME;
                        case 79: return Key::END;
                        case 73: return Key::PAGE_UP;
                        case 81: return Key::PAGE_DOWN;
                        case 82: return Key::INSERT;
                        case 83: return Key::_DELETE;
                        case 59: return Key::F1;
                        case 60: return Key::F2;
                        case 61: return Key::F3;
                        case 62: return Key::F4;
                        case 63: return Key::F5;
                        case 64: return Key::F6;
                        case 65: return Key::F7;
                        case 66: return Key::F8;
                        case 67: return Key::F9;
                        case 68: return Key::F10;
                        case 133: return Key::F11;
                        case 134: return Key::F12;
                        default: return Key::UNKNOWN;
                    }
                }
                case 0:{
                    switch(getch()){
                        case 59: return Key::F1;
                        case 60: return Key::F2;
                        case 61: return Key::F3;
                        case 62: return Key::F4;
                        case 63: return Key::F5;
                        case 64: return Key::F6;
                        case 65: return Key::F7;
                        case 66: return Key::F8;
                        case 67: return Key::F9;
                        case 68: return Key::F10;
                        case 133: return Key::F11;
                        case 134: return Key::F12;
                        case 71: return Key::HOME;
                        case 72: return Key::NUMPAD_ARROW_UP;
                        case 73: return Key::PAGE_UP;
                        case 75: return Key::NUMPAD_ARROW_LEFT;
                        case 77: return Key::NUMPAD_ARROW_RIGHT;
                        case 79: return Key::END;
                        case 80: return Key::NUMPAD_ARROW_DOWN;
                        case 81: return Key::PAGE_DOWN;
                        case 82: return Key::INSERT;
                        case 83: return Key::_DELETE;
                        default: return Key::UNKNOWN;
                    }
                }

                case 97: return Key::a; case 65: return Key::A;
                case 98: return Key::b; case 66: return Key::B;
                case 99: return Key::c; case 67: return Key::C;
                case 100: return Key::d; case 68: return Key::D;
                case 101: return Key::e; case 69: return Key::E;
                case 102: return Key::f; case 70: return Key::F;
                case 103: return Key::g; case 71: return Key::G;
                case 104: return Key::h; case 72: return Key::H;
                case 105: return Key::i; case 73: return Key::I;
                case 106: return Key::j; case 74: return Key::J;
                case 107: return Key::k; case 75: return Key::K;
                case 108: return Key::l; case 76: return Key::L;
                case 109: return Key::m; case 77: return Key::M;
                case 110: return Key::n; case 78: return Key::N;
                case 111: return Key::o; case 79: return Key::O;
                case 112: return Key::p; case 80: return Key::P;
                case 113: return Key::q; case 81: return Key::Q;
                case 114: return Key::r; case 82: return Key::R;
                case 115: return Key::s; case 83: return Key::S;
                case 116: return Key::t; case 84: return Key::T;
                case 117: return Key::u; case 85: return Key::U;
                case 118: return Key::v; case 86: return Key::V;
                case 119: return Key::w; case 87: return Key::W;
                case 120: return Key::x; case 88: return Key::X;
                case 121: return Key::y; case 89: return Key::Y;
                case 122: return Key::z; case 90: return Key::Z;

                case 8: return Key::BACKSPACE;
                case 9: return Key::TAB;
                case 13: return Key::ENTER;
                case 27: return Key::ESCAPE;
                case 32: return Key::SPACE;

                case 95: return Key::UNDERSCORE;
                case 45: return Key::DASH;
                case 43: return Key::PLUS;
                case 42: return Key::ASTERISK;
                case 37: return Key::PERCENT;
                case 33: return Key::EXCLAMATION;
                case 63: return Key::QUESTION;
                case 64: return Key::AT;
                case 35: return Key::POUND;
                case 36: return Key::DOLLAR;
                case 38: return Key::AMPERSAND;
                case 124: return Key::PIPE;
                case 39: return Key::QUOTE;



                default: return Key::UNKNOWN;

            }
        }

        Key getkey(){
            if(use_file_input){
                Key k = analyse_key(file_input.get());
                if(file_input.eof()){
                    file_input.close();
                    if(is_temp_file)
                        fs::remove(fs::temp_directory_path().string() + "/getkey_temp_file");
                    use_file_input = false;
                    return k;
                }
                else{
                    std::string command;
                    do{ //ignore comments
                        command = "";
                        file_input >> command;
                    }while (command[0] == '#');
                    return analyse_key(command);
                }
            }
            else{
                int c = getch();
                return analyse_key(c);
            }
        }

    #elif __linux__
        #include <stdio.h>

        //transform the key from the linux getchar() function to a Key enum value
        Key analyse_key(int key){
            switch(key){
                case 27:{
                    key = ::getchar();
                    switch(key){
                        case 91:{
                            key = ::getchar();
                            switch(key){
                                case 65: return Key::ARROW_UP;
                                case 66: return Key::ARROW_DOWN;
                                case 67: return Key::ARROW_RIGHT;
                                case 68: return Key::ARROW_LEFT;
                                case 72: return Key::HOME;
                                case 70: return Key::END;
                                case 53: return Key::PAGE_UP;
                                case 54: return Key::PAGE_DOWN;
                                case 50: return Key::INSERT;
                                case 51: return Key::_DELETE;

                                default: return Key::UNKNOWN;
                            }
                            break;
                        }
                        default: return Key::ESCAPE;
                    }
                    break;
                }

                case 97: return Key::a; case 65: return Key::A;
                case 98: return Key::b; case 66: return Key::B;
                case 99: return Key::c; case 67: return Key::C;
                case 100: return Key::d; case 68: return Key::D;
                case 101: return Key::e; case 69: return Key::E;
                case 102: return Key::f; case 70: return Key::F;
                case 103: return Key::g; case 71: return Key::G;
                case 104: return Key::h; case 72: return Key::H;
                case 105: return Key::i; case 73: return Key::I;
                case 106: return Key::j; case 74: return Key::J;
                case 107: return Key::k; case 75: return Key::K;
                case 108: return Key::l; case 76: return Key::L;
                case 109: return Key::m; case 77: return Key::M;
                case 110: return Key::n; case 78: return Key::N;
                case 111: return Key::o; case 79: return Key::O;
                case 112: return Key::p; case 80: return Key::P;
                case 113: return Key::q; case 81: return Key::Q;
                case 114: return Key::r; case 82: return Key::R;
                case 115: return Key::s; case 83: return Key::S;
                case 116: return Key::t; case 84: return Key::T;
                case 117: return Key::u; case 85: return Key::U;
                case 118: return Key::v; case 86: return Key::V;
                case 119: return Key::w; case 87: return Key::W;
                case 120: return Key::x; case 88: return Key::X;
                case 121: return Key::y; case 89: return Key::Y;
                case 122: return Key::z; case 90: return Key::Z;

                case 127: return Key::BACKSPACE;
                case 9: return Key::TAB;
                case 10: return Key::ENTER;
                case 32: return Key::SPACE;
                case 46: return Key::_POINT;
                case 44: return Key::COMMA;
                case 59: return Key::SEMICOLON;
                case 39: return Key::QUOTE;

                case 48: return Key::ZERO;
                case 49: return Key::ONE;
                case 50: return Key::TWO;
                case 51: return Key::THREE;
                case 52: return Key::FOUR;
                case 53: return Key::FIVE;
                case 54: return Key::SIX;
                case 55: return Key::SEVEN;
                case 56: return Key::EIGHT;
                case 57: return Key::NINE;

                case 95: return Key::UNDERSCORE;
                case 45: return Key::DASH;
                case 61: return Key::PLUS;
                case 42: return Key::ASTERISK;
                case 37: return Key::PERCENT;
                case 33: return Key::EXCLAMATION;
                case 63: return Key::QUESTION;
                case 64: return Key::AT;
                case 35: return Key::POUND;
                case 36: return Key::DOLLAR;
                case 38: return Key::AMPERSAND;
                case 124: return Key::PIPE;

                case 195:{
                    key = ::getchar();
                    switch(key){
                        case 160: return Key::a_GRAVE;
                        case 161: return Key::a_ACUTE;
                        case 162: return Key::a_CIRCUMFLEX;
                        case 163: return Key::a_TILDE;
                        case 164: return Key::a_UMLAUT;
                        case 166: return Key::c_CEDILLA;
                        case 167: return Key::e_GRAVE;
                        case 168: return Key::e_ACUTE;
                        case 169: return Key::e_CIRCUMFLEX;
                        case 170: return Key::e_UMLAUT;
                        case 171: return Key::i_GRAVE;
                        case 172: return Key::i_ACUTE;
                        case 173: return Key::i_CIRCUMFLEX;
                        case 174: return Key::i_UMLAUT;
                        case 177: return Key::o_GRAVE;
                        case 178: return Key::o_ACUTE;
                        case 179: return Key::o_CIRCUMFLEX;
                        case 180: return Key::o_TILDE;
                        case 181: return Key::o_UMLAUT;
                        case 183: return Key::u_GRAVE;
                        case 184: return Key::u_ACUTE;
                        case 185: return Key::u_CIRCUMFLEX;
                        case 186: return Key::u_UMLAUT;

                        case 128: return Key::A_GRAVE;
                        case 129: return Key::A_ACUTE;
                        case 130: return Key::A_CIRCUMFLEX;
                        case 131: return Key::A_TILDE;
                        case 132: return Key::A_UMLAUT;
                        case 134: return Key::C_CEDILLA;
                        case 135: return Key::E_GRAVE;
                        case 136: return Key::E_ACUTE;
                        case 137: return Key::E_CIRCUMFLEX;
                        case 138: return Key::E_UMLAUT;
                        case 139: return Key::I_GRAVE;
                        case 140: return Key::I_ACUTE;
                        case 141: return Key::I_CIRCUMFLEX;
                        case 142: return Key::I_UMLAUT;
                        case 145: return Key::O_GRAVE;
                        case 146: return Key::O_ACUTE;
                        case 147: return Key::O_CIRCUMFLEX;
                        case 148: return Key::O_TILDE;
                        case 149: return Key::O_UMLAUT;
                        case 151: return Key::U_GRAVE;
                        case 152: return Key::U_ACUTE;
                        case 153: return Key::U_CIRCUMFLEX;
                        case 154: return Key::U_UMLAUT;

                        default: return Key::UNKNOWN;
                    }
                }

                default: return Key::UNKNOWN;

            }
        }
        
        Key getkey(){
            if(use_file_input){
                if(file_input.eof()){
                    file_input.close();
                    if(is_temp_file){
                        remove((fs::temp_directory_path().string() + std::string("/getkey_temp_file")).c_str());
                    }
                    use_file_input = false;
                    is_temp_file = false;
                    return getkey();
                }
                else{
                    std::string line;
                    std::getline(file_input, line);
                    line = line.substr(0, line.size() - 1);
                    Key k = analyse_key(line);
                    return k;
                }
            }
            else{
                Key a = analyse_key(::getchar());
                return a;
            }
        }
    #endif

    int getchar(Key key){
        switch(key){
            case Key::A: return 'A';
            case Key::B: return 'B';
            case Key::C: return 'C';
            case Key::D: return 'D';
            case Key::E: return 'E';
            case Key::F: return 'F';
            case Key::G: return 'G';
            case Key::H: return 'H';
            case Key::I: return 'I';
            case Key::J: return 'J';
            case Key::K: return 'K';
            case Key::L: return 'L';
            case Key::M: return 'M';
            case Key::N: return 'N';
            case Key::O: return 'O';
            case Key::P: return 'P';
            case Key::Q: return 'Q';
            case Key::R: return 'R';
            case Key::S: return 'S';
            case Key::T: return 'T';
            case Key::U: return 'U';
            case Key::V: return 'V';
            case Key::W: return 'W';
            case Key::X: return 'X';
            case Key::Y: return 'Y';
            case Key::Z: return 'Z';
            case Key::a: return 'a';
            case Key::b: return 'b';
            case Key::c: return 'c';
            case Key::d: return 'd';
            case Key::e: return 'e';
            case Key::f: return 'f';
            case Key::g: return 'g';
            case Key::h: return 'h';
            case Key::i: return 'i';
            case Key::j: return 'j';
            case Key::k: return 'k';
            case Key::l: return 'l';
            case Key::m: return 'm';
            case Key::n: return 'n';
            case Key::o: return 'o';
            case Key::p: return 'p';
            case Key::q: return 'q';
            case Key::r: return 'r';
            case Key::s: return 's';
            case Key::t: return 't';
            case Key::u: return 'u';
            case Key::v: return 'v';
            case Key::w: return 'w';
            case Key::x: return 'x';
            case Key::y: return 'y';
            case Key::z: return 'z';
            case Key::NUMPAD_ZERO: return '0';
            case Key::NUMPAD_ONE: return '1';
            case Key::NUMPAD_TWO: return '2';
            case Key::NUMPAD_THREE: return '3';
            case Key::NUMPAD_FOUR: return '4';
            case Key::NUMPAD_FIVE: return '5';
            case Key::NUMPAD_SIX: return '6';
            case Key::NUMPAD_SEVEN: return '7';
            case Key::NUMPAD_EIGHT: return '8';
            case Key::NUMPAD_NINE: return '9';
            case Key::NUMPAD_PLUS: return '+';
            case Key::NUMPAD_MINUS: return '-';
            case Key::NUMPAD_MULTIPLY: return '*';
            case Key::NUMPAD_DIVIDE: return '/';
            case Key::NUMPAD_DOT: return '.';
            case Key::ZERO: return '0';
            case Key::ONE: return '1';
            case Key::TWO: return '2';
            case Key::THREE: return '3';
            case Key::FOUR: return '4';
            case Key::FIVE: return '5';
            case Key::SIX: return '6';
            case Key::SEVEN: return '7';
            case Key::EIGHT: return '8';
            case Key::NINE: return '9';
            case Key::SPACE: return ' ';
            case Key::TAB: return '\t';
            case Key::ENTER: return '\n';
            case Key::UNDEFINED: return ' ';

            case Key::SEMICOLON: return ';';
            case Key::COMMA: return ',';
            case Key::_POINT: return '.';


            case Key::UNDERSCORE: return '_';
            case Key::DASH: return '-';
            case Key::PLUS: return '+';
            case Key::ASTERISK: return '*';
            case Key::PERCENT: return '%';
            case Key::EXCLAMATION: return '!';
            case Key::QUESTION: return '?';
            case Key::AT: return '@';
            case Key::POUND: return '#';
            case Key::DOLLAR: return '$';
            case Key::AMPERSAND: return '&';
            case Key::PIPE: return '|';
            case Key::QUOTE: return '\'';


            //! accent is not working for now
            /*
            case Key::A_GRAVE: return 'À';
            case Key::A_ACUTE: return 'Á';
            case Key::A_CIRCUMFLEX: return 'Â';
            case Key::A_TILDE: return 'Ã';
            case Key::A_UMLAUT: return 'Ä';
            case Key::E_GRAVE: return 'È';
            case Key::E_ACUTE: return 'É';
            case Key::E_CIRCUMFLEX: return 'Ê';
            case Key::E_UMLAUT: return 'Ë';
            case Key::I_GRAVE: return 'Ì';
            case Key::I_ACUTE: return 'Í';
            case Key::I_CIRCUMFLEX: return 'Î';
            case Key::I_UMLAUT: return 'Ï';
            case Key::O_GRAVE: return 'Ò';
            case Key::O_ACUTE: return 'Ó';
            case Key::O_CIRCUMFLEX: return 'Ô';
            case Key::O_TILDE: return 'Õ';
            case Key::O_UMLAUT: return 'Ö';
            case Key::U_GRAVE: return 'Ù';
            case Key::U_ACUTE: return 'Ú';
            case Key::U_CIRCUMFLEX: return 'Û';
            case Key::U_UMLAUT: return 'Ü';
            case Key::C_CEDILLA: return 'Ç';
            case Key::AE: return 'Æ';
            case Key::OE: return 'Œ';
            
            case Key::a_GRAVE: return 'à';
            case Key::a_ACUTE: return 'á';
            case Key::a_CIRCUMFLEX: return 'â';
            case Key::a_TILDE: return 'ã';
            case Key::a_UMLAUT: return 'ä';
            case Key::e_GRAVE: return 'è';
            case Key::e_ACUTE: return 'é';
            case Key::e_CIRCUMFLEX: return 'ê';
            case Key::e_UMLAUT: return 'ë';
            case Key::i_GRAVE: return 'ì';
            case Key::i_ACUTE: return 'í';
            case Key::i_CIRCUMFLEX: return 'î';
            case Key::i_UMLAUT: return 'ï';
            case Key::o_GRAVE: return 'ò';
            case Key::o_ACUTE: return 'ó';
            case Key::o_CIRCUMFLEX: return 'ô';
            case Key::o_TILDE: return 'õ';
            case Key::o_UMLAUT: return 'ö';
            case Key::u_GRAVE: return 'ù';
            case Key::u_ACUTE: return 'ú';
            case Key::u_CIRCUMFLEX: return 'û';
            case Key::u_UMLAUT: return 'ü';
            case Key::c_CEDILLA: return 'ç';
            case Key::ae: return 'æ';
            case Key::oe: return 'œ';
            */

            default: return '\0';
        }
    }
}

