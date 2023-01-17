
#include "file.hpp"

#include <string>
#include <fstream>

#include <filesystem>
namespace fs = std::filesystem;

#include <iostream>

#include "../utility/utility.hpp"
using namespace Utility;

namespace File{

    //return the file content as a string
    std::string read(fs::path path){
        std::ifstream file = std::ifstream(path);
        std::string content = "";
        while(!file.eof()){
            std::string line;
            std::getline(file, line);
            content += line + "\n";
        }
        file.close();
        return content;
    }

    //return the first n lines of the file as a string
    std::string read(fs::path path, unsigned n){
        std::ifstream file = std::ifstream(path);
        std::string content = "";
        unsigned i = 0;
        while(!file.eof() && i < n){
            std::string line;
            std::getline(file, line);
            content += line + "\n";
            ++i;
        }
        file.close();
        return content;
    }

    //write the content to the file, overwriting the previous content
    void write(fs::path path, std::string content){
        std::ofstream file = std::ofstream(path);
        file << content;
        file.close();
    }

    //write the content to the file, appending it to the previous content
    void append(fs::path path, std::string content){
        std::ofstream file = std::ofstream(path, std::ios::app);
        file << content;
        file.close();
    }

    //clear the file
    void clear(fs::path path){
        std::ofstream file = std::ofstream(path);
        file.close();
    }

    //delete the file
    void deletefile(fs::path path){
        fs::remove(path);
    }

    //return the line at the given index
    std::string getline(fs::path path, unsigned i){
        std::ifstream file = std::ifstream(path);
        while(!file.eof() && i > 0){
            std::string line;
            std::getline(file, line);
            --i;
        }
        std::string line;
        std::getline(file, line);
        file.close();
        return line;
    }

    //change the extension of the file, return true if the extension was changed
    fs::path setextension(fs::path path, std::string extension){
        if(path.extension() != extension){
            path.replace_extension(extension);
        }
        return path;
    }

    fs::directory_iterator getFiles(fs::path path){
        return fs::directory_iterator(path);
    }

}
