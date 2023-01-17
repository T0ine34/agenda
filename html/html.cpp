#include "html.hpp"

#include "../file/file.hpp"

#include <string>
#include <vector>
#include <filesystem>

#include <iostream>

namespace fs = std::filesystem;

namespace HTML{
    std::string to_string(const Table& t){
        std::string s = R"(<table><caption>)" + t.title + R"(</caption><tr>)";
        for(const auto& header : t.headers){
            s += R"(<th>)" + header + R"(</th>)";
        }
        s += "</tr>";
        for(const auto& row : t.rows){
            s += "<tr>";
            for(const auto& cell : row){
                s += R"(<td>)" + cell + R"(</td>)";
            }
            s += "</tr>";
        }
        s += "</table>";
        return s;
    }

    std::string to_string(const List& l){
        std::string s = R"(<)" + std::string(l.ordered ? "ol" : "ul") + R"(><caption>)" + l.title + R"(</caption>)";
        for(const auto& item : l.items){
            s += R"(<li>)" + item + R"(</li>)";
        }
        s += R"(</)" + std::string(l.ordered ? "ol" : "ul") + ">";
        return s;
    }

    std::string to_string(const Image& i){
        std::string s = R"(<figure><img src=")" + i.path.string() + R"(" alt=")" + i.description + R"("><figcaption>)" + i.title + R"(</figcaption></figure>)";
        return s;
    }

    std::string to_string(const Text& t){
        std::string s = R"(<p><h2>)" + t.title + R"(</h2>)" + t.text + "</p>";
        return s;
    }

    std::string to_string(const Link& l){
        std::string s = R"(<a href=")" + l.url + R"(">)" + l.title + "</a>";
        return s;
    }

    std::string to_string(const Page& p){
        std::string s = R"(<!DOCTYPE html><html lang="en"><head><meta charset="UTF-8"><meta name="viewport" content="width=device-width, initial-scale=1.0"><meta http-equiv="X-UA-Compatible" content="ie=edge"><title>)" + p.title + R"(</title>)";
        for(const std::string& stylesheet : p.stylesheets){
            s += R"(<link rel="stylesheet" href=")" + stylesheet + R"(">)";
        }
        for(const std::string& script : p.scripts){
            s += R"(<script src=")" + script + R"("></script>)";
        }
        s += R"(<link rel="icon" href=")" + p.icon.string() + R"("><meta name="author" content=")" + p.author + R"("></head><body>)" + p.body + "</body></html>";
        return s;
    }

    std::string to_string(const Title& t){
        std::string s = R"(<h)" + std::to_string(t.height) + ">" + t.title + R"(</h)" + std::to_string(t.height) + ">";
        return s;
    }

    void append(Page& p, const Table& t){
        p.body += to_string(t);
    }

    void append(Page& p, const List& l){
        p.body += to_string(l);
    }

    void append(Page& p, const Image& i){
        p.body += to_string(i);
    }

    void append(Page& p, const Text& t){
        p.body += to_string(t);
    }

    void append(Page& p, const Link& l){
        p.body += to_string(l);
    }
    
    void append(Page& p, const std::string& s){
        p.body += s;
    }

    void append(Page& p, const Title& t){
        p.body += to_string(t);
    }

    void add_row(Table& t, const std::vector<std::string>& row){
        t.rows.push_back(row);
    }

    void set_ordered(List& l, const bool ordered){
        l.ordered = ordered;
    }

    void add_stylesheet(Page& p, const std::string& stylesheet){
        p.stylesheets.push_back(stylesheet);
    }

    void add_stylesheet(Page& p, const fs::path& stylesheet){
        std::cerr << stylesheet << std::endl;
        p.stylesheets.push_back(File::read(stylesheet));
    }

    void add_script(Page& p, const std::string& script){
        p.scripts.push_back(script);
    }

    void add_script(Page& p, const fs::path& script){
        p.scripts.push_back(File::read(script));
    }

    void set_author(Page& p, const std::string& author){
        p.author = author;
    }
    void set_icon(Page& p, const fs::path& icon){
        p.icon = icon;
    }


    void set_title(Table& t, const std::string& title){
        t.title = title;
    }

    void set_title(List& l, const std::string& title){
        l.title = title;
    }

    void set_title(Image& i, const std::string& title){
        i.title = title;
    }

    void set_title(Text& t, const std::string& title){
        t.title = title;
    }

    void set_title(Link& l, const std::string& title){
        l.title = title;
    }

    void set_title(Page& p, const std::string& title){
        p.title = title;
    }

    void set_title(Title& l, const std::string& title){
        l.title = title;
    }
    
    void set_description(Image& i, const std::string& description){
        i.description = description;
    }

    void set_text(Text& t, const std::string& text){
        t.text = text;
    }

    void set_url(Link& l, const std::string& url){
        l.url = url;
    }

    void set_path(Image& i, const fs::path& path){
        i.path = path;
    }

    void set_headers(Table& t, const std::vector<std::string>& headers){
        t.headers = headers;
    }

    void set_height(Title& t, const unsigned char height){
        t.height = height;
    }

    void save(const Page& p, const fs::path& path){
        File::write(path, to_string(p));
    }
}