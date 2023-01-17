#include "utility.hpp"

#include <string>
#include <vector>


namespace Utility{

    //replace all occurences of a string with another string
    std::string replace(std::string s, std::string old, std::string new_){
        std::string buffer;
        while (s.size()){
            if (s.substr(0, old.size()) == old){
                buffer += new_;
                s = s.substr(old.size());
            }
            else{
                buffer += s[0];
                s = s.substr(1);
            }
        }
        return buffer;
    }

    //split a string into a vector of strings
    std::vector<std::string> split(std::string s, char delim){
        std::vector<std::string> elems;
        std::string buffer;
        while (s.size()) {
            if (s[0] != delim){
                buffer += s[0];
            }
            else if (buffer.size()){
                elems.push_back(buffer);
                buffer = "";
            }
            else{
                elems.push_back("");
            }
            s = s.substr(1);
        }
        if (buffer.size()){
            elems.push_back(buffer);
        }
        return elems;
    }
    std::vector<std::string> split(std::string s, size_t max_length){
        std::vector<std::string> elems;
        std::string buffer;
        while (s.size()) {
            if (buffer.size() < max_length){
                buffer += s[0];
            }
            else if (buffer.size()){
                elems.push_back(buffer);
                buffer = "";
            }
            s = s.substr(1);
        }
        if (buffer.size()){
            elems.push_back(buffer);
        }
        return elems;
    }
    
    // Split a string into a vector of strings, but split on spaces, if a word has to be split, split on the space before the word
    std::vector<std::string> split_on_spaces(std::string s, size_t max_length){
        std::vector<std::string> elems;
        std::string buffer;
        std::size_t last_space = 0;
        while (s.size()){
            if (buffer.size() < max_length){
                buffer += s[0];
                if(s[0] == ' '){
                    last_space = buffer.size();
                }
            }
            else if (buffer.size()){
                if(last_space > 0){
                    elems.push_back(buffer.substr(0, last_space));
                    buffer = buffer.substr(last_space);
                    last_space = 0;
                }else{
                    elems.push_back(buffer);
                    buffer = "";
                }
            }
            s = s.substr(1);
        }
        if (buffer.size()){
            elems.push_back(buffer);
        }
        return elems;
    }


    //split a string into a queue of strings
    std::queue<std::string> splitQueue(std::string s, char delim){
        std::queue<std::string> elems;
        std::string buffer;
        while (s.size()) {
            if (s[0] != delim){
                buffer += s[0];
            }
            else if (buffer.size()){
                elems.push(buffer);
                buffer = "";
            }
            s = s.substr(1);
        }
        if (buffer.size()){
            elems.push(buffer);
        }
        return elems;
    }

    //remove all occurences of space, tab, newline and carriage return at the end and beginning of a string
    std::string strip(std::string s){
        const std::vector<char> chars = {' ', '\t', '\n', '\r'};
        bool found = false; //end of string found
        while(!found){
            found = true;
            for(std::size_t i = 0; i < chars.size(); i++){
                if(s[s.size() - 1] == chars[i]){
                    s = s.substr(0, s.size() - 1);
                    found = false;
                }
            }
        }
        found = false;
        while(!found){
            found = true;
            for(std::size_t i = 0; i < chars.size(); i++){
                if(s[0] == chars[i]){
                    s = s.substr(1);
                    found = false;
                }
            }
        }
        return s;
    }

    // Extend a string with a character; if the string is longer than the length, the string is returned
    std::string extend(std::string str, size_t length, char c, bool center){
        if(str.length() < length){
            if(center){
                int left = (length - str.length()) / 2;
                int right = length - str.length() - left;
                for(int i = 0; i < left; i++){
                    str = c + str;
                }
                for(int i = 0; i < right; i++){
                    str = str + c;
                }
            }else{
                for(size_t i = 0; i < length - str.length(); i++){
                    str = str + c;
                }
            }
        }
        return str;
    }

    std::string format(int i, unsigned length){
        std::string s = std::to_string(i);
        while(s.length() < length){
            s = "0" + s;
        }
        return s;
    }

    // Get the number of characters in a string, count multibyte characters as one
    unsigned getNbchars(std::string s){
        unsigned nbchars = 0;
        for(unsigned i = 0; i < s.length(); i++){
            if((s[i] & 0xC0) != 0x80){
                nbchars++;
            }
        }
        return nbchars;
    }

    char lower(char c){
        if(c >= 'A' && c <= 'Z') c += 32;
        return c;
    }

    std::string lower(std::string s){
        for(std::size_t i = 0; i < s.size(); i++){
            lower(s[i]);
        }
        return s;
    }

    std::string min_size(const std::vector<std::string>& v){
        std::string min = v[0];
        for(std::size_t i = 1; i < v.size(); i++){
            if(v[i].size() < min.size()){
                min = v[i];
            }
        }
        return min;
    }

    //split a in b parts, return a vector of the parts
    std::vector<int> divide(int a, int b){
        size_t crt = 0;
        std::vector<int> parts;
        for (int i = 0; i < b; i++){
            parts.push_back(0);
        }
        for (int i = 0; i < a; i++){
            parts[crt]++;
            crt++;
            crt %= b;
        }
        return parts;
    }
}
