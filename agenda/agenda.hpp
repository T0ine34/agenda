#ifndef __AGENDA_HPP__
#define __AGENDA_HPP__

#include "../datetime/datetime.hpp"
#include "../file/file.hpp"

#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <filesystem>
namespace fs = std::filesystem;

std::string getUID(std::size_t len);

namespace Agenda{
    namespace Event{
        struct Event{
            std::string UID;
            std::string name;
            std::string description;
            Datetime::Datetime start;
            Datetime::Datetime end;
        };

        Event event(std::string name, std::string description, Datetime::Datetime start, Datetime::Datetime end);

    }

    struct Agenda{
        std::string UID;
        std::string name;
        std::string description;
        std::vector<Event::Event> events;
    };

    Agenda agenda(std::string name, std::string description);

    Agenda load(std::string UID);

    std::string to_string(Agenda a);

    void addEvent(Agenda& a, Event::Event e);
    bool removeEvent(Agenda& a, std::string UID);

    void save(Agenda a);

    Event::Event getEvent(Agenda a, std::string UID);

    void show(Agenda a);

    std::tuple<std::string, std::string> getPrimaryData(const fs::path& path);

    unsigned is_file_good(const fs::path& path);

    std::queue<Event::Event> getEvents(const Agenda& a, const Datetime::Datetime& start, const Datetime::Datetime& end);

    void exportHTML(Agenda a, fs::path& path);

    unsigned deleteAgenda(std::string UID);
}

#endif