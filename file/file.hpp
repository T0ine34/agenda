#ifndef __FILE_HPP__
#define __FILE_HPP__

#include <string>
#include <vector>

#include <filesystem>
namespace fs = std::filesystem;

namespace File{
    std::string read(fs::path path);

    std::string read(fs::path path, unsigned n);

    void write(fs::path path, std::string content);

    void append(fs::path path, std::string content);

    void clear(fs::path path);

    void deletefile(fs::path path);

    std::string getline(fs::path path, unsigned line);

    fs::path setextension(fs::path path, std::string extension);

    fs::directory_iterator getFiles(fs::path path);
}

#endif