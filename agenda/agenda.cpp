
#include "agenda.hpp"

#include "../datetime/datetime.hpp"
#include "../datetime/data.hpp"
#include "../file/file.hpp"
#include "../utility/utility.hpp"
#include "../html/html.hpp"

#include <random>
#include <queue>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;

std::string getUID(std::size_t len){
    std::string uid(len, '\0');
    std::vector<char> x = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    do{
        static std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution < > dis(0, x.size()-1);
        for (char& c: uid) {
            c = x[dis(gen)];
        }
    } while (fs::exists("data/agenda/" + uid + ".agenda"));
    return uid;
}

namespace Agenda{
    namespace Event{
        Event event(std::string name, std::string description, Datetime::Datetime start, Datetime::Datetime end){
            Event e;
            e.UID = getUID(16);
            e.name = name;
            e.description = description;
            e.start = start;
            e.end = end;
            return e;
        }
    }

    Agenda agenda(std::string name, std::string description){
        Agenda a;
        a.UID = getUID(16);
        a.name = name;
        a.description = description;
        return a;
    }

    Agenda load(std::string UID){
        std::string path = "data/agenda/" + UID + ".agenda";
        std::string s = File::read(fs::path(path));
        std::queue<std::string> lines = Utility::splitQueue(s, '\n');
        Agenda a;
        a.UID = lines.front();
        lines.pop();
        a.name = lines.front();
        lines.pop();
        a.description = lines.front();
        lines.pop();
        while (!lines.empty()){
            std::queue<std::string> event = Utility::splitQueue(lines.front(), '\t');
            Event::Event e;
            e.UID = event.front();
            event.pop();
            e.name = event.front();
            event.pop();
            e.description = event.front();
            event.pop();
            e.start = Datetime::from_string(event.front(), "%d-%m-%Y-%H-%M");
            event.pop();
            e.end = Datetime::from_string(event.front(), "%d-%m-%Y-%H-%M");
            event.pop();
            addEvent(a, e);
            lines.pop();
        }
        return a;
    }

    std::string to_string(Agenda a){
        std::string s = "UID: " + a.UID + "\nName: " + a.name + "\nDescription: " + a.description + "\nEvents: \n";
        for (Event::Event e: a.events){
            s += "\tUID: " + e.UID + "\n\tName: " + e.name + "\n\tDescription: " + e.description + "\n\tStart: " + Datetime::to_string(e.start) + "\n\tEnd: " + Datetime::to_string(e.end) + "\n";
        }
        return s;
    }

    void addEvent(Agenda& a, Event::Event e){
        a.events.push_back(e);
    }

    bool removeEvent(Agenda& a, std::string UID){
        for (std::size_t i = 0; i < a.events.size(); i++){
            if (a.events[i].UID == UID){
                a.events.erase(a.events.begin() + i);
                break;
                return true;
            }
        }
        return false;
    }

    void save(Agenda a){
        std::string path = "data/agenda/" + a.UID + ".agenda";
        std::string s = a.UID + "\n" + a.name + "\n" + a.description + "\n";
        for (Event::Event e: a.events){
            s += e.UID + "\t" + e.name + "\t" + e.description + "\t" + Datetime::format(e.start, "%d-%m-%Y-%H-%M") + "\t" + Datetime::format(e.end, "%d-%m-%Y-%H-%M") + "\n";
        }
        File::write(path, s);
    }

    Event::Event getEvent(Agenda a, std::string UID){
        for (Event::Event e: a.events){
            if (e.UID == UID){
                return e;
            }
        }
        std::cerr << "Event with UID " << UID << " not found" << std::endl;
        exit(EXIT_FAILURE);
    }

    void show(Agenda a){
        std::cout << to_string(a) << std::endl;
    }

    //open a file and get name and UID of the agenda
    std::tuple<std::string, std::string> getPrimaryData(const fs::path& path){
        std::vector<std::string> result = Utility::split(File::read(path, 2), '\n');
        return std::make_tuple(Utility::strip(result[0]), Utility::strip(result[1]));
    }

    //return 0 if the file is a agenda and is contain all required data; 1 if the file is not a regular file; 2 if the file contain less than 3 lines; 4 if the file not contain the UID; 8 if the file not contain the title
    unsigned is_file_good(const fs::path& path){
        unsigned result = 0;
        result += !fs::is_regular_file(path)*1; //verify if the file is a regular file
        result += (File::read(path, 3).size() < 3)*2; //verify if the file contain at least 3 lines
        std::vector<std::string> data = Utility::split(File::read(path, 2), '\n'); //verify if the file contain the required data
        result += (Utility::strip(data[0]).size() != 16)*4; //UID
        result += (data[1].size() == 0)*8; //title
        result += (data[2].size() == 0)*16; //description
        return result;
    }

    //return a queue of all the events in the agenda a between start and end
    std::queue<Event::Event> getEvents(const Agenda& a, const Datetime::Datetime& start, const Datetime::Datetime& end){
        std::queue<Event::Event> result;
        for (Event::Event e: a.events){
            if ((e.start >= start && e.end <= end) || (e.end >= start && e.end <= end)){
                result.push(e);
            }
        }
        return result;
    }

    //export the agenda a in a html file with path
    void exportHTML(Agenda a, fs::path& path){
        HTML::Page p;
        HTML::set_title(p, a.name);
        HTML::Title t1;
        HTML::set_title(t1, a.name);
        HTML::set_height(t1, 1);
        HTML::append(p, t1);

        HTML::Text t2;
        HTML::set_text(t2, a.description);
        HTML::append(p, t2);

        HTML::Table t;
        HTML::set_headers(t, {"Name", "Description", "Start", "End"});
        for (Event::Event e: a.events){
            HTML::add_row(t, {e.name, e.description, Datetime::format(e.start, "%d/%m/%Y %H:%M"), Datetime::format(e.end, "%d/%m/%Y %H:%M")});
        }
        HTML::append(p, t);
        path = File::setextension(path, "html");
        fs::path css = "data/html/style.css";
        HTML::add_stylesheet(p, fs::absolute(css));
        HTML::save(p, path);
    }

    unsigned deleteAgenda(std::string UID){
        File::deletefile("data/agenda/" + UID + ".agenda");
        if (fs::exists("data/agenda/" + UID + ".agenda")){
            return 1;
        }
        return 0;        
    }

}