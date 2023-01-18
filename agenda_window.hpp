#ifndef __AGENDA_WINDOW_HPP__
#define __AGENDA_WINDOW_HPP__

#include "menu/menu.hpp"
#include "agenda/agenda.hpp"

#include <string>

namespace Agenda_window{
    void addEvent(Agenda::Agenda& a);

    void removeEvent(Agenda::Agenda& a);

    // return the UID of the agenda
    std::string create_agenda();

    // return the UID of the agenda
    std::string load_agenda();

    // return the UID of the agenda
    std::string delete_agenda();

    namespace Display_Agenda{
        struct Display_Agenda{
            Agenda::Agenda agenda;
            std::string lang = "en";
            Datetime::Datetime selected_date = Datetime::now();
            bool is_selected_date = false;
            unsigned nb_events = 0;
            bool valid_input = false;
        };

        Display_Agenda display_agenda(Agenda::Agenda a);

        std::string create_window(const Display_Agenda& d);

        void erase(const Display_Agenda& d);

        void action(Display_Agenda& d, const int& c);

        void show(Display_Agenda& d);

        void addEvent(Agenda::Agenda& a);

        void removeEvent(Agenda::Agenda& a);
    }

    void exportHTML(Agenda::Agenda a);
}


namespace Datetime_Input{
    struct Date_Input{
        std::string title;
        unsigned int day;
        unsigned int month;
        unsigned int year;
        unsigned char selected = 0; // 0 = year, 1 = month, 2 = day
        bool valid_input = false;
        unsigned int max_day = 31;
    };

    struct Time_Input{
        std::string title;
        int hour;
        int minute;
        bool valid_input = false;
        bool is_hour_selected = true;
    };

    Date_Input date_input(std::string title);

    Time_Input time_input(std::string title);

    //return a Datetime object from user input
    std::string create_window(Datetime_Input::Date_Input& date_input, std::string lang = "en");
    std::string create_window(Datetime_Input::Time_Input& time_input, std::string lang = "en");

    void erase(const Datetime_Input::Date_Input& date_input);
    void erase(const Datetime_Input::Time_Input& time_input);

    void action(Datetime_Input::Date_Input& date_input, unsigned c);
    void action(Datetime_Input::Time_Input& time_input, unsigned c);

    Datetime::Datetime show(Datetime_Input::Date_Input& date_input, std::string lang = "en");
    Deltatime::Deltatime show(Datetime_Input::Time_Input& time_input, std::string lang = "en");
}




#endif