#include "agenda_window.hpp"

#include "datetime/deltatime.hpp"
#include "datetime/datetime.hpp"
#include "datetime/data.hpp"

#include "menu/menu.hpp"
#include "agenda/agenda.hpp"

#include "utility/utility.hpp"

#include <cmath>
#include <iostream>
#include <string>
#include "getch/getch.hpp"


namespace Agenda_window{

    void addEvent(Agenda::Agenda& a){
        //ask for the name of the event, the datetime of the start and the end, and the description
        Input::Input input = Input::input("nom de l'évènement");
        std::string name = Input::show(input);

        Datetime_Input::Date_Input date_input = Datetime_Input::date_input("date de début");
        Datetime::Datetime start = Datetime_Input::show(date_input, "fr");
        Datetime_Input::Time_Input time_input = Datetime_Input::time_input("heure de début");
        start += Datetime_Input::show(time_input, "fr");

        date_input = Datetime_Input::date_input("date de fin");
        Datetime::Datetime end = Datetime_Input::show(date_input, "fr");
        time_input = Datetime_Input::time_input("heure de fin");
        end += Datetime_Input::show(time_input, "fr");
        
        input = Input::input("description");
        std::string description = Input::show(input);

        //create the event
        Agenda::Event::Event event = Agenda::Event::event(name, description, start, end);

        //add the event to the agenda
        Agenda::addEvent(a, event);
    }

    // this function is used to remove an event from an agenda
    void removeEvent(Agenda::Agenda& a){
        Menu::Menu menu = Menu::menu("supprimer un évènement");
        for(std::size_t i = 0; i < a.events.size(); i++){
            Menu::addOption(menu, Key::UNDEFINED, a.events[i].name, a.events[i].UID);
        }
        Menu::addOption(menu, Key::q, "retour", "q");
        std::string UID = Menu::show(menu);
        if (UID != "q"){
            Agenda::removeEvent(a, UID);
        }
        else{
            return;
        }
    }

    //this fuction is used to create a new agenda, return the UID of the new agenda
    std::string create_agenda(){
        //ask for the name and the description of the agenda
        Input::Input input = Input::input("nom de l'agenda");
        std::string name = Input::show(input);
        if(name == ""){
            return "q";
        }

        input = Input::input("description");
        std::string description = Input::show(input);
        if(description == ""){
            return "q";
        }

        //create the agenda
        Agenda::Agenda agenda = Agenda::agenda(name, description);

        //save the agenda
        Agenda::save(agenda);

        //return the UID of the agenda
        return agenda.UID;
    }

    //this function is used to show a menu to select an agenda, return the UID of the selected agenda
    std::string load_agenda(){
        //get the list of all agendas
        fs::directory_iterator agendas = File::getFiles("data/agenda/");

        //create a menu to select an agenda
        Menu::Menu menu = Menu::menu("choisir un agenda");
        for(fs::path p : agendas){
            unsigned r = Agenda::is_file_good(p);
            if(r == 0){
                std::tuple<std::string, std::string> data = Agenda::getPrimaryData(p);
                Menu::addOption(menu, Key::UNDEFINED, std::get<1>(data), std::get<0>(data));
            }
            else{
                std::cerr << "le fichier " << fs::absolute(p) << " n'est pas un fichier agenda valide (code d'erreur : " << r << ")" << std::endl;
            }
        }
        Menu::addOption(menu, Key::q, "retour", "q");

        //show the menu and return the UID of the selected agenda
        return Menu::show(menu);
    }

    //this function is used to delete an agenda, return the UID of the deleted agenda
    std::string delete_agenda(){
        //get the list of all agendas
        fs::directory_iterator agendas = File::getFiles("data/agenda/");

        //create a menu to select an agenda
        Menu::Menu menu = Menu::menu("choisir un agenda");
        for(fs::path p : agendas){
            unsigned r = Agenda::is_file_good(p);
            if(r == 0){ // if the file is a valid agenda
                std::tuple<std::string, std::string> data = Agenda::getPrimaryData(p);
                Menu::addOption(menu, Key::UNDEFINED, std::get<1>(data), std::get<0>(data));
            }
            else{ // if the file is not a valid agenda
                std::cerr << "le fichier " << fs::absolute(p) << " n'est pas un fichier agenda valide (code d'erreur : " << r << ")" << std::endl;
            }
        }
        Menu::addOption(menu, Key::q, "retour", "q");

        //show the menu and return the UID of the selected agenda
        std::string UID = Menu::show(menu);
        if (UID != "q"){
            File::deletefile("data/agenda/" + UID + ".agenda");
        }
        return UID;
    }

    namespace Display_Agenda{

        Display_Agenda display_agenda(Agenda::Agenda a){
            Display_Agenda d = Display_Agenda();
            d.agenda = a;
            d.selected_date = Datetime::now();
            return d;
        }

        std::string create_window(const Display_Agenda& d){
            unsigned int width = 34;
            Utility::getNbchars(d.agenda.name) > width ? width = Utility::getNbchars(d.agenda.name) : width = width;

            std::string s = "┌";
            for (unsigned i = 0; i < width; i++)
                s += "─";
            s += "┐\n│" + Utility::extend(d.agenda.name, width, ' ', true) + "│\n";

            s += "├";
            for (unsigned i = 0; i < width; i++)
                s += "─";
            s += "┤\n";

            //display a table with one case for each day, in the selected month and language
            //we also can selected a day to display the events of this day
            //set one week per line, first column is monday, last column is sunday
            int nb_days = Datetime::days_in_month(d.selected_date.year, d.selected_date.month);
            // first_day is the day of the week of the first day of the month
            int first_day = Datetime::day_of_week(d.selected_date.year, d.selected_date.month, 1);
            int nb_weeks = ceil(float(nb_days + first_day) / 7);
            int day = 1;


            s += "│ <--" + Utility::extend(Datetime::format(d.selected_date, "%B %Y", d.lang), width-8, ' ', true) + "--> │\n";

            s += "├";
            for (unsigned i = 0; i < width; i++)
                s += "─";
            s += "┤\n";

            for(int i = 0; i < nb_weeks; i++){
                for(int j = 0; j < 7; j++){
                    if (i == 0 && j < first_day){
                        s += "│" + Utility::extend(" ", 4, ' ', true);
                    }
                    else if (day <= nb_days){
                        if (j == d.x && i == d.y){
                            
                            s += "│\033[7m" + Utility::extend(std::to_string(day), 4, ' ', true) + "\033[27m";
                        }
                        else{
                            s += "│" + Utility::extend(std::to_string(day), 4, ' ', true);
                        }
                        day++;
                    }
                    else{
                        s += "│" + Utility::extend(" ", 4, ' ', true);
                    }
                }
                s += "│\n";
            }

            s += "├";
            for (unsigned i = 0; i < width; i++)
                s += "─";
            s += "┤\n";

            s += "│" + Utility::extend("press 'q' for exit", width, ' ', true) + "│\n";

            s += "└";
            for (unsigned i = 0; i < width; i++)
                s += "─";
            s += "┘\n";

            return s;
        }

        void erase(const Display_Agenda& d){
            int height = 9;

            int nb_days = Datetime::days_in_month(d.selected_date.month, d.selected_date.year);
            int first_day = Datetime::day_of_week(d.selected_date.year, d.selected_date.month, 1);
            int nb_weeks = ceil(float(nb_days + first_day) / 7);
            

            height += nb_weeks;

            std::cout << "\033[" << height << "A\033[0J";
        }

        void action(Display_Agenda& d, const Key& c){
            int nb_days = Datetime::days_in_month(d.selected_date.month, d.selected_date.year);
            int first_day = Datetime::day_of_week(d.selected_date);
            int nb_weeks = ceil(float(nb_days + first_day - 1) / 7);
            switch (c){
                case Key::ARROW_LEFT:{ //if is_selected_date is true, go to the previous month
                    if(d.is_selected_date){
                        d.selected_date -= Deltatime::months(1);
                    }else{
                        if(d.x > 0){
                            d.x--;
                            d.selected_date = d.selected_date - Deltatime::days(1);
                        }
                        else if (d.y > 0){
                            d.y--;
                            d.x = 6;
                            d.selected_date = d.selected_date - Deltatime::days(7);
                        }
                    }
                    break;
                }
                case Key::ARROW_RIGHT:{ //if is_selected_date is true, go to the next month
                    if(d.is_selected_date){
                        d.selected_date += Deltatime::months(1);
                    }else{
                        if(d.x < 6){
                            d.x++;
                            d.selected_date = d.selected_date + Deltatime::days(1);
                        }
                        else if (d.y < nb_weeks){
                            d.y++;
                            d.x = 0;
                            d.selected_date = d.selected_date + Deltatime::days(7);
                        }
                    }
                    break;
                }
                case Key::ARROW_UP:{ //select the case above, if we are on the first line, select the date above the table (to allow to change the month)
                    if(d.y > 0){
                        d.y--;
                        d.selected_date = d.selected_date - Deltatime::days(7);
                    }
                    else{
                        d.is_selected_date = true;
                    }
                    break;
                }
                case Key::ARROW_DOWN:{ //select the case below, if we are on the date above the table, go to the first line of the table (to allow to change the day)
                    if(d.y < nb_weeks){
                        d.y++;
                        d.selected_date = d.selected_date + Deltatime::days(7);
                    }
                    break;
                }
                case Key::q:{
                    d.valid_input = true;
                    break;
                }
                case Key::ENTER:{
                    if(d.is_selected_date){
                        d.is_selected_date = false;
                    }else{
                        d.valid_input = true;
                    }
                    break;
                }

                default: //other
                    break;
            }
        }

        void show(Display_Agenda& d){
            do{
                std::cout << create_window(d) << std::flush;
                Key c = Getkey::getkey();
                action(d, c);
                erase(d);
            }while(!d.valid_input);
        }
    
        void addEvent(Agenda::Agenda& a){
            //get the name, the description, the start date and time and the end date and time
            Input::Input input_name = Input::input("Entrez le nom de l'évènement : ");
            std::string name = Input::show(input_name);
            if(name == ""){ //if the user pressed 'escape' 
                return;
            }
            Input::Input input_description = Input::input("Entrez la description de l'évènement : ");
            std::string description = Input::show(input_description);
            if(description == ""){ //if the user pressed 'escape' 
                return;
            }
            Datetime_Input::Date_Input input_start_date = Datetime_Input::date_input("Entrez la date de début de l'évènement : ");
            Datetime::Datetime start_date = Datetime_Input::show(input_start_date, "fr");
            if(start_date == Datetime::empty_datetime){ //if the user pressed 'escape' 
                return;
            }
            Datetime_Input::Time_Input input_start_time = Datetime_Input::time_input("Entrez l'heure de début de l'évènement : ");
            Deltatime::Deltatime start_time = Datetime_Input::show(input_start_time, "fr");
            if(start_time == Deltatime::empty_deltatime){ //if the user pressed 'escape' 
                std::cerr << Deltatime::to_string(start_time) << '\n' << Deltatime::to_string(Deltatime::empty_deltatime) << std::endl;
                return;
            }
            Datetime_Input::Date_Input input_end_date = Datetime_Input::date_input("Entrez la date de fin de l'évènement : ");
            Datetime::Datetime end_date = Datetime_Input::show(input_end_date, "fr");
            if(end_date == Datetime::empty_datetime){ //if the user pressed 'escape' 
                return;
            }
            Datetime_Input::Time_Input input_end_time = Datetime_Input::time_input("Entrez l'heure de fin de l'évènement : ");
            Deltatime::Deltatime end_time = Datetime_Input::show(input_end_time, "fr");
            if(end_time == Deltatime::empty_deltatime){ //if the user pressed 'escape' 
                return;
            }
            Datetime::Datetime start = start_date + start_time;
            Datetime::Datetime end = end_date + end_time;
            if(start > end){
                Information::Information info = Information::information("The start date and time must be before the end date and time.");
                Information::show(info);
                return;
            }

            Agenda::addEvent(a, Agenda::Event::event(name, description, start, end));
            Agenda::save(a);
            Information::Information info = Information::information("L'évènement '" + name + "' a été ajouté.");
            Information::show(info);
        }

        void removeEvent(Agenda::Agenda& a){
            //display a list of all events, and ask the user to select one (use the menu function)
            Menu::Menu m = Menu::menu("Select an event to remove : ");
            for(size_t i = 0; i < a.events.size(); i++){
                Menu::addOption(m, Key::UNDEFINED, a.events[i].name, a.events[i].UID);
            }
            Menu::addOption(m, Key::q, "Cancel", "");
            std::string UID = Menu::show(m);
            if(UID == ""){
                return;
            }
            Agenda::removeEvent(a, UID);
            Agenda::save(a);
            Information::Information info = Information::information("The event" + Agenda::getEvent(a, UID).name + "has been removed.");
            Information::show(info);
        }
    }

    void exportHTML(Agenda::Agenda a){
        Input::Input input = Input::input("Enter the name of the file : ");
        std::string r = Input::show(input);
        if(r == ""){
            return;
        }
        fs::path filename = fs::path(r);
        Agenda::exportHTML(a, filename);
        Information::Information info = Information::information("The file has been exported to '" + filename.string() + "'.");
        Information::show(info);
    }
}

namespace Datetime_Input{

    Date_Input date_input(std::string title){
        Date_Input date_input;
        date_input.title = title;
        date_input.day = 1;
        date_input.month = 1;
        date_input.year = 2020;
        date_input.max_day = 31;
        date_input.selected = 0;
        return date_input;
    }

    Time_Input time_input(std::string title){
        Time_Input time_input;
        time_input.title = title;
        time_input.hour = 0;
        time_input.minute = 0;
        return time_input;
    }
    
    //return a Datetime object from user input
    std::string create_window(Datetime_Input::Date_Input& date_input, std::string lang){
        unsigned width = 27;
        (date_input.title.size() > width) ? width = date_input.title.size() : width = width;
        std::vector<int> spaces = Utility::divide(width-5, 6); //corresponds to the number of spaces between each column
        std::string output = "┌";
        for(unsigned i = 0; i < width; i++){
            output += "─";
        }
        output += "┐\n│";
        for(int i = 0; i < round(float(width - Utility::getNbchars(date_input.title)) / 2); i++){
            output += " ";
        }
        output += date_input.title;
        for(int i = 0; i < round(float(width - Utility::getNbchars(date_input.title)) / 2)-1; i++){
            output += " ";
        }
        output += "│\n├";
        for(int i = 0; i < spaces[0]+1+spaces[1]; i++){
            output += "─";
        }
        output += "┬";
        for(int i = 0; i < spaces[2]+1+spaces[3]; i++){
            output += "─";
        }
        output += "┬";
        for(int i = 0; i < spaces[4]+1+spaces[5]; i++){
            output += "─";
        }
        output += "┤\n│ ";
        output += Utility::extend(Date_Data::year.at(lang), spaces[0]+1+spaces[1], ' ', true) + "│" + Utility::extend(Date_Data::month.at(lang), spaces[2]+1+spaces[3], ' ', true) + "│" + Utility::extend(Date_Data::day.at(lang), spaces[4]+1+spaces[5], ' ', true) + "│";
        output += "\n│";
        for(int i = 0; i < spaces[0]+1+spaces[1]; i++){
            output += " ";
        }
        output += "│";
        for(int i = 0; i < spaces[2]+1+spaces[3]; i++){
            output += " ";
        }
        output += "│";
        for(int i = 0; i < spaces[4]+1+spaces[5]; i++){
            output += " ";
        }
        output += "│";

        output += "\n│";
        for(int i = 0; i < spaces[0]; i++){
            output += " ";
        }
        output += "ꓥ";
        for(int i = 0; i < spaces[1]; i++){
            output += " ";
        }
        output += "│";
        for(int i = 0; i < spaces[2]; i++){
            output += " ";
        }
        output += "ꓥ";
        for(int i = 0; i < spaces[3]; i++){
            output += " ";
        }
        output += "│";
        for(int i = 0; i < spaces[4]; i++){
            output += " ";
        }
        output += "ꓥ";
        for(int i = 0; i < spaces[5]; i++){
            output += " ";
        }
        output += "│\n│";
        for(int i = 0; i < spaces[0]-1; i++){
            output += " ";
        }

        if (int(date_input.selected) == 0){
            output += "\033[30;47m";
        }
        output += Utility::format(date_input.year, 4);
        if (int(date_input.selected) == 0){
            output += "\033[0m";
        }
        for(int i = 0; i < spaces[1]-2; i++){
            output += " ";
        }
        output += "│";
        for(int i = 0; i < spaces[2]; i++){
            output += " ";
        }
        if (int(date_input.selected) == 1){
            output += "\033[30;47m";
        }
        output += Utility::format(date_input.month, 2);
        if (int(date_input.selected) == 1){
            output += "\033[0m";
        }
        for(int i = 0; i < spaces[3]-1; i++){
            output += " ";
        }
        output += "│";
        for(int i = 0; i < spaces[4]-1; i++){
            output += " ";
        }
        if (int(date_input.selected) == 2){
            output += "\033[30;47m";
        }
        output += Utility::format(date_input.day, 2);
        if (int(date_input.selected) == 2){
            output += "\033[0m";
        }
        for(int i = 0; i < spaces[5]; i++){
            output += " ";
        }
        output += "│\n│";
        //"   ꓦ    │   ꓦ    │    ꓦ    │\n└";
        for(int i = 0; i < spaces[0]; i++){
            output += " ";
        }
        output += "ꓦ";
        for(int i = 0; i < spaces[1]; i++){
            output += " ";
        }
        output += "│";
        for(int i = 0; i < spaces[2]; i++){
            output += " ";
        }
        output += "ꓦ";
        for(int i = 0; i < spaces[3]; i++){
            output += " ";
        }
        output += "│";
        for(int i = 0; i < spaces[4]; i++){
            output += " ";
        }
        output += "ꓦ";
        for(int i = 0; i < spaces[5]; i++){
            output += " ";
        }
        output += "│\n└";
        for(int i = 0; i < spaces[0]+1+spaces[1]; i++){
            output += "─";
        }
        output += "┴";
        for(int i = 0; i < spaces[2]+1+spaces[3]; i++){
            output += "─";
        }
        output += "┴";
        for(int i = 0; i < spaces[4]+1+spaces[5]; i++){
            output += "─";
        }
        output += "┘\n";

        return output;
    }

    //return a Datetime object from user input
    std::string create_window(Datetime_Input::Time_Input& time_input, std::string lang){
        unsigned width = 19;
        (time_input.title.size() > width) ? width = time_input.title.size() : width = width;
        std::string output = "┌";
        for(unsigned i = 0; i < width; i++){
            output += "─";
        }
        output += "┐\n│";
        for(int i = 0; i < round(float(width - time_input.title.size()) / 2); i++){
            output += " ";
        }
        output += time_input.title;
        for(int i = 0; i < round(float(width - time_input.title.size()) / 2)-1; i++){
            output += " ";
        }
        output += "│\n├─────────┬─────────┤\n│";
        output += Utility::extend(Date_Data::hour.at(lang), 9, ' ', true) + "│" + Utility::extend(Date_Data::minute.at(lang), 9, ' ', true) + "│";
        output += "\n│         │         │";
        output += "\n│    ꓥ    │    ꓥ    │\n│    ";
        if (int(time_input.is_hour_selected)){
            output += "\033[30;47m";
        }
        output += Utility::format(time_input.hour, 2);
        if (int(time_input.is_hour_selected)){
            output += "\033[0m";
        }
        output += "   │    ";
        if (!int(time_input.is_hour_selected)){
            output += "\033[30;47m";
        }
        output += Utility::format(time_input.minute, 2);
        if (!int(time_input.is_hour_selected)){
            output += "\033[0m";
        }
        output += "   │\n│    ꓦ    │    ꓦ    │\n└";
        output += "─────────┴─────────┘\n";

        return output;
    }


    void erase(const Datetime_Input::Date_Input& date_input){
        std::cout << "\033[9A\033[0J" << std::flush;
    }

    void erase(const Datetime_Input::Time_Input& time_input){
        std::cout << "\033[9A\033[0J" << std::flush;
    }


    // return true if we continue to get input, false if we are quiting the input (escape key pressed)
    bool action(Datetime_Input::Date_Input& date_input, const Key& c){
        switch (c){
            case Key::ARROW_LEFT:{
                if (date_input.selected == 0){
                    date_input.selected = 2;
                } else {
                    date_input.selected--;
                }
                break;
            }
            case Key::ARROW_RIGHT:{ 
                if (date_input.selected == 2){
                    date_input.selected = 0;
                } else {
                    date_input.selected++;
                }
                break;
            }
            case Key::ARROW_DOWN:{ 
                switch (date_input.selected){
                    case 0:{ // year
                        if (date_input.year > 0){
                            date_input.year--;
                        }
                        break;
                    }
                    case 1:{ // month
                        if (date_input.month > 1){
                            date_input.month--;
                        } else {
                            date_input.month = 12;
                        }
                        break;
                    }
                    case 2:{ // day
                        if (date_input.day > 1){
                            date_input.day--;
                        } else {
                            date_input.day = date_input.max_day;
                        }
                        break;
                    }
                }
                date_input.max_day = Datetime::days_in_month(Datetime::datetime(date_input.year, date_input.month, 1));
                        if (date_input.day > date_input.max_day){
                            date_input.day = date_input.max_day;
                        }
                break;
            }
            case Key::ARROW_UP:{
                switch (date_input.selected){
                    case 0:{ // year
                        date_input.year++;
                        break;
                    }
                    case 1:{ // month
                        if (date_input.month < 12){
                            date_input.month++;
                        } else {
                            date_input.month = 1;
                        }
                        break;
                    }
                    case 2:{ // day
                        if (date_input.day < date_input.max_day){
                            date_input.day++;
                        } else {
                            date_input.day = 1;
                        }
                        break;
                    }
                }
                date_input.max_day = Datetime::days_in_month(Datetime::datetime(date_input.year, date_input.month, 1));
                        if (date_input.day > date_input.max_day){
                            date_input.day = date_input.max_day;
                        }
                break;
            }
            case Key::ENTER:{
                date_input.valid_input = true;
                break;
            }
            case Key::ESCAPE:{
                return false;
            }
            default:{
                // do nothing
                break;
            }
        }
        return true;
    }

    // return true if we continue to get input, false if we are quiting the input (escape key pressed)
    bool action(Datetime_Input::Time_Input& time_input, const Key& c){
        switch (c){
            case Key::ARROW_UP:{
                if (time_input.is_hour_selected){
                    if (time_input.hour < 23){
                        time_input.hour++;
                    } else {
                        time_input.hour = 0;
                    }
                } else {
                    if (time_input.minute < 59){
                        time_input.minute++;
                    } else {
                        time_input.minute = 0;
                    }
                }
                break;
            }
            case Key::ARROW_DOWN:{
                if (time_input.is_hour_selected){
                    if (time_input.hour > 0){
                        time_input.hour--;
                    } else {
                        time_input.hour = 23;
                    }
                } else {
                    if (time_input.minute > 0){
                        time_input.minute--;
                    } else {
                        time_input.minute = 59;
                    }
                }
                break;
            }
            case Key::ARROW_LEFT:{
                time_input.is_hour_selected = true;
                break;
            }
            case Key::ARROW_RIGHT:{
                time_input.is_hour_selected = false;
                break;
            }
            case Key::ENTER:{
                time_input.valid_input = true;
                break;
            }
            case Key::ESCAPE:{
                return false;
            }
            default:{
                // do nothing
                break;
            }
        }
        return true;
    }


    Datetime::Datetime show(Datetime_Input::Date_Input& date_input, std::string lang){
        bool continue_input = true;
        while (!date_input.valid_input && continue_input){
            std::cout << create_window(date_input, lang) << std::flush;
            Key c = Getkey::getkey();
            continue_input = action(date_input, c);
            erase(date_input);
            if(!continue_input){
                return Datetime::empty_datetime;
            }
        }
        Datetime::Datetime output;
        output.year = date_input.year;
        output.month = date_input.month;
        output.day = date_input.day;
        return output;
    }

    Deltatime::Deltatime show(Datetime_Input::Time_Input& time_input, std::string lang){
        bool continue_input = true;
        while (!time_input.valid_input && continue_input){
            std::cout << create_window(time_input, lang) << std::flush;
            Key c = Getkey::getkey();
            continue_input = action(time_input, c);
            erase(time_input);
            if(!continue_input){
                return Deltatime::empty_deltatime;
            }
        }
        return Deltatime::deltatime(time_input.hour, time_input.minute, 0);
    }
}