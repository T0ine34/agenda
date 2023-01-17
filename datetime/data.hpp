#ifndef __DATETIME_DATA_HPP__
#define __DATETIME_DATA_HPP__

#include <string>
#include <vector>
#include <map>


namespace Date_Data{
    // ------------------------------------------------------------------
    // ----------------------------- Lists ------------------------------

    const std::map<std::string, std::vector<std::string>> months = {
        {"en", {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"}},
        {"fr", {"Janvier", "Février", "Mars", "Avril", "Mai", "Juin", "Juillet", "Août", "Septembre", "Octobre", "Novembre", "Décembre"}},
        {"es", {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"}},
        {"de", {"Januar", "Februar", "März", "April", "Mai", "Juni", "Juli", "August", "September", "Oktober", "November", "Dezember"}},
        {"it", {"Gennaio", "Febbraio", "Marzo", "Aprile", "Maggio", "Giugno", "Luglio", "Agosto", "Settembre", "Ottobre", "Novembre", "Dicembre"}},
        {"pt", {"Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"}}
    };

    const std::map<std::string, std::vector<std::string>> days = {
        {"en", {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"}},
        {"fr", {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"}},
        {"es", {"Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado", "Domingo"}},
        {"de", {"Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag", "Sonntag"}},
        {"it", {"Lunedì", "Martedì", "Mercoledì", "Giovedì", "Venerdì", "Sabato", "Domenica"}},
        {"pt", {"Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sábado", "Domingo"}}
    };

    const std::map<std::string, std::string> local_format = {
        {"en", "%a %b %d %H:%M:%S %Y"},
        {"fr", "%a %d %b %Y %H:%M:%S"}
    };

    const std::map<std::string, std::string> year{
        {"en", "year(s)"},
        {"fr", "année(s)"},
        {"es", "año(s)"},
        {"de", "Jahr(e)"},
        {"it", "anno(i)"},
        {"pt", "ano(s)"}
    };

    const std::map<std::string, std::string> month{
        {"en", "month(s)"},
        {"fr", "mois"},
        {"es", "mes(es)"},
        {"de", "Monat(e)"},
        {"it", "mese(i)"},
        {"pt", "mês(es)"}
    };

    const std::map<std::string, std::string> day{
        {"en", "day(s)"},
        {"fr", "jour(s)"},
        {"es", "día(s)"},
        {"de", "Tag(e)"},
        {"it", "giorno(i)"},
        {"pt", "dia(s)"}
    };

    const std::map<std::string, std::string> hour{
        {"en", "hour(s)"},
        {"fr", "heure(s)"},
        {"es", "hora(s)"},
        {"de", "Stunde(n)"},
        {"it", "ora(e)"},
        {"pt", "hora(s)"}
    };

    const std::map<std::string, std::string> minute{
        {"en", "minute(s)"},
        {"fr", "minute(s)"},
        {"es", "minuto(s)"},
        {"de", "Minute(n)"},
        {"it", "minuto(i)"},
        {"pt", "minuto(s)"}
    };

    const std::map<std::string, std::string> second{
        {"en", "second(s)"},
        {"fr", "seconde(s)"},
        {"es", "segundo(s)"},
        {"de", "Sekunde(n)"},
        {"it", "secondo(i)"},
        {"pt", "segundo(s)"}
    };
}


#endif