#ifndef __HTML_PARTS_HPP__
#define __HTML_PARTS_HPP__

#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

namespace HTML{
    struct Page{
        std::string title;
        fs::path icon;
        std::vector<std::string> stylesheets;
        std::vector<std::string> scripts;
        std::string author;
        std::string body;
    };

    struct Table{
        std::string title;
        std::vector<std::string> headers;
        std::vector<std::vector<std::string>> rows;
    };

    struct List{
        std::string title;
        bool ordered = false;
        std::vector<std::string> items;
    };

    struct Image{
        std::string title;
        fs::path path;
        std::string description;
    };

    struct Text{
        std::string title;
        std::string text;
    };

    struct Link{
        std::string title;
        std::string url;
    };

    struct Title{
        std::string title;
        unsigned char height;
    };


    std::string to_string(const Table& t);
    std::string to_string(const List& l);
    std::string to_string(const Image& i);
    std::string to_string(const Text& t);
    std::string to_string(const Link& l);
    std::string to_string(const Page& p);
    std::string to_string(const Title& t);

    void append(Page& p, const Table& t);
    void append(Page& p, const List& l);
    void append(Page& p, const Image& i);
    void append(Page& p, const Text& t);
    void append(Page& p, const Link& l);
    void append(Page& p, const std::string& s);
    void append(Page& p, const Title& t);

    void add_row(Table& t, const std::vector<std::string>& row);
    void set_ordered(List& l, const bool ordered);

    void add_stylesheet(Page& p, const std::string& stylesheet);
    void add_stylesheet(Page& p, const fs::path& stylesheet);
    void add_script(Page& p, const std::string& script);
    void add_script(Page& p, const fs::path& script);

    void set_author(Page& p, const std::string& author);
    void set_icon(Page& p, const fs::path& icon);


    void set_title(Table& t, const std::string& title);
    void set_title(List& l, const std::string& title);
    void set_title(Image& i, const std::string& title);
    void set_title(Text& t, const std::string& title);
    void set_title(Link& l, const std::string& title);
    void set_title(Page& p, const std::string& title);
    void set_title(Title& t, const std::string& title);

    void set_description(Image& i, const std::string& description);
    void set_text(Text& t, const std::string& text);
    void set_url(Link& l, const std::string& url);
    void set_path(Image& i, const fs::path& path);
    void set_height(Title& t, const unsigned char height);

    void set_headers(Table& t, const std::vector<std::string>& headers);

    void save(const Page& p, const fs::path& path);
}


#endif