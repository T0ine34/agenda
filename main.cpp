#include "datetime/datetime.hpp"

#define LANG "fr" // "en", "fr", "de", "pt", "es", "it"

#include <iostream>

#include "os_utility/utf-8.h"
#include "os_utility/ansi.h"
#include "os_utility/raw_mode.h"

#include "agenda/agenda.hpp"
#include "menu/menu.hpp"

#include "agenda_window.hpp"

#include "getkey/key.h"

// create options for the main menu
void load_main_menu(Menu::Menu& menu){
    Menu::addOption(menu, Key::N, "nouvel agenda", "create_agenda");
    Menu::addOption(menu, Key::c, "charger un agenda", "load_agenda");
    Menu::addOption(menu, Key::s, "supprimer un agenda", "delete_agenda");
    Menu::addOption(menu, Key::q, "quitter", "quit");
}

// create options for the agenda menu
void load_agenda_menu(Menu::Menu& menu){
    Menu::addOption(menu, Key::a, "afficher l'agenda", "show_agenda");
    Menu::addOption(menu, Key::e, "exporter l'agenda au format HTML", "export_agenda_html");
    Menu::addOption(menu, Key::h, "ajouter un évènement", "add_event");
    Menu::addOption(menu, Key::d, "supprimer un évènement", "remove_event");
    Menu::addOption(menu, Key::q, "fermer l'agenda", "close_agenda");
}

// loop for the agenda menu
void loop_agenda(Agenda::Agenda& agenda){
    Menu::Menu agenda_menu = Menu::menu("options pour l'agenda '" + agenda.name + "'");
    load_agenda_menu(agenda_menu);
    bool running = true;
    while(running){
        std::string am_res = Menu::show(agenda_menu); // "am_res" for "agenda_menu_result"
        if(am_res == "close_agenda"){
            running = false;
        }
        else if(am_res == "show_agenda"){
            Agenda_window::Display_Agenda::Display_Agenda d = Agenda_window::Display_Agenda::display_agenda(agenda);
            Agenda_window::Display_Agenda::show(d);
            Menu::reset(agenda_menu);
        }
        else if(am_res == "export_agenda_html"){
            Agenda_window::exportHTML(agenda);
            Menu::reset(agenda_menu);
        }
        else if(am_res == "add_event"){
            Agenda_window::Display_Agenda::addEvent(agenda);
            Menu::reset(agenda_menu);
        }
        else if(am_res == "remove_event"){
            Agenda_window::Display_Agenda::removeEvent(agenda);
            Menu::reset(agenda_menu);
        }
        else if(am_res == ""){
            running = false;
        }
    }
}


int main(int argc, char** argv){
    enableUTF8();
    enableANSI();
    enable_raw_mode();
    Getkey::is_input_from_file(argc, argv);
    

    // load the main menu
    Menu::Menu main_menu = Menu::menu("main_menu");
    load_main_menu(main_menu);

    // main loop
    bool running = true;
    do{
        Menu::reset(main_menu);
        std::string mm_res = Menu::show(main_menu); // "mm_res" for "main_menu_result"
        if(mm_res == "quit"){
            running = false;
        }
        else if(mm_res == "create_agenda"){
            std::string UID = Agenda_window::create_agenda();
            if (UID == "q") {
                Menu::reset(main_menu);
                continue;
            }
            Agenda::Agenda agenda = Agenda::load(UID);
            loop_agenda(agenda);
            Agenda_window::save_agenda(agenda);
            Menu::reset(main_menu);
        }
        else if(mm_res == "load_agenda"){
            std::string UID = Agenda_window::load_agenda();
            if (UID == "q"){
                Menu::reset(main_menu);
                continue;
            }
            Agenda::Agenda agenda = Agenda::load(UID);
            loop_agenda(agenda);
            Agenda_window::save_agenda(agenda);
            Menu::reset(main_menu);
        }
        else if(mm_res == "delete_agenda"){
            std::string UID = Agenda_window::delete_agenda();
            if (UID == "q"){
                Menu::reset(main_menu);
                continue;
            }
            Information::Information info;
            if (!Agenda::deleteAgenda(UID)){
                info = Information::information("Agenda supprimé");
            }
            else{
                info = Information::information("Agenda non supprimé");
            }
            Information::show(info);
        }
        else if(mm_res == ""){
            running = false;
        }
    }while(running);

    disableUTF8();
    disable_raw_mode();
}