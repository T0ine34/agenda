
#include <string>
#include <stdexcept>

#include "datetime.hpp"
#include "data.hpp" // List of months and days
#include "deltatime.hpp"


//returns a string with the number of digits specified or more
std::string format_number(int number, size_t digits){
    std::string result = std::to_string(number);
    while(result.size() < digits){
        result = "0" + result;
    }
    return result;
}

std::string format_number(std::string number, size_t digits){
    while(number.size() < digits){
        number = "0" + number;
    }
    return number;
}

namespace Datetime{



// ------------------------------------------------------------------
// ---------------------------Constructors---------------------------

    Datetime datetime(int year, int month, int day, int hour, int minute, int second){
        Datetime datetime;
        datetime.year = year;
        datetime.month = month;
        datetime.day = day;
        datetime.hour = hour;
        datetime.minute = minute;
        datetime.second = second;
        return datetime;
    }

    Datetime datetime(int year, int month, int day){
        Datetime datetime;
        datetime.year = year;
        datetime.month = month;
        datetime.day = day;
        datetime.hour = 0;
        datetime.minute = 0;
        datetime.second = 0;
        return datetime;
    }

    Datetime datetime(){
        Datetime datetime;
        datetime.year = 0;
        datetime.month = 0;
        datetime.day = 0;
        datetime.hour = 0;
        datetime.minute = 0;
        datetime.second = 0;
        return datetime;
    }

    Datetime now(){
        time_t now = time(0);
        tm* ltm = localtime(&now);
        Datetime datetime;
        datetime.year = 1900 + ltm->tm_year;
        datetime.month = 1 + ltm->tm_mon;
        datetime.day = ltm->tm_mday;
        datetime.hour = ltm->tm_hour;
        datetime.minute = ltm->tm_min;
        datetime.second = ltm->tm_sec;
        return datetime;
    }

// ------------------------------------------------------------------
// ----------------------- String Functions -------------------------

    /*
        Y for year in 4 digits
        y for year in 2 digits

        m for month in 2 digits
        b for short month name
        B for long month name

        d for day in 2 digits
        a for short day name
        A for long day name
        w for week day number
        j for day of the year

        H for hour in 2 digits
        I for hour in 12 hours format
        p for AM/PM

        M for minute in 2 digits

        S for second in 2 digits

        c for local datetime format
        

    */
    std::string format(const Datetime& datetime, std::string format, std::string locale){
        std::string result = "";
        for(std::size_t i = 0; i < format.size(); ++i){
            if (format[i] == '%'){
                switch(format[i+1]){
                    case 'Y':
                        result += std::to_string(datetime.year);
                        break;
                    case 'y':
                        result += format_number(datetime.year % 100, 2);
                        break;
                    case 'm':
                        result += format_number(datetime.month, 2);
                        break;
                    case 'b':
                        {
                            std::string t;
                            try{
                                t = ::Date_Data::months.at(locale)[datetime.month - 1].substr(0, 3);
                            }
                            catch(const std::out_of_range& e){
                                t = ::Date_Data::months.at("en")[datetime.month - 1].substr(0, 3); // Default locale
                            }
                            result += t;
                            break;
                        }
                    case 'B':
                        {
                            std::string t;
                            try{
                                t = ::Date_Data::months.at(locale)[datetime.month - 1];
                            }
                            catch(const std::out_of_range& e){
                                t = ::Date_Data::months.at("en")[datetime.month - 1]; // Default locale
                            }
                            result += t;
                            break;
                        }
                    case 'd':
                        result += format_number(datetime.day, 2);
                        break;
                    case 'a':
                        {
                            std::string t;
                            try{
                                t = ::Date_Data::days.at(locale)[day_of_week(datetime)].substr(0, 3);
                            }
                            catch(const std::out_of_range& e){
                                t = ::Date_Data::days.at("en")[day_of_week(datetime)].substr(0, 3); // Default locale
                            }
                            result += t;
                            break;
                        }
                    case 'A':
                        {
                            std::string t;
                            try{
                                t = ::Date_Data::days.at(locale)[day_of_week(datetime)];
                            }
                            catch(const std::out_of_range& e){
                                t = ::Date_Data::days.at("en")[day_of_week(datetime)]; // Default locale
                            }
                            result += t;
                            break;
                        }
                    case 'w':
                        result += std::to_string(datetime.day);
                        break;
                    case 'j':
                        result += std::to_string(datetime.day);
                        break;
                    case 'H':
                        result += format_number(datetime.hour, 2);
                        break;
                    case 'I':
                        result += format_number(datetime.hour % 12, 2);
                        break;
                    case 'p':
                        result += (datetime.hour < 12) ? "AM" : "PM";
                        break;
                    case 'M':
                        result += format_number(datetime.minute, 2);
                        break;
                    case 'S':
                        result += format_number(datetime.second, 2);
                        break;
                    case 'c':
                        {
                            std::string l;
                            try{
                                l = Date_Data::local_format.at(locale);
                            }
                            catch(const std::out_of_range& e){
                                l = Date_Data::local_format.at("en"); // Default locale
                            }
                            result += ::Datetime::format(datetime, l);
                            break;
                        }
                    default:
                        result += format[i+1];
                        break;
                }
                ++i;
            }
            else{
                result += format[i];
            }
        }
        return result;
    }

    std::string to_string(const Datetime& datetime, std::string locale){
        return ::Datetime::format(datetime, "%c", locale);
    }

    Datetime from_string(std::string datetime, std::string format, std::string locale){
        Datetime result = ::Datetime::datetime();
        for (std::size_t i = 0; i < format.size(); ++i){
            if (format[i] == '%'){
                switch(format[i+1]){
                    case 'Y':
                        result.year = std::stoi(datetime.substr(i, 4));
                        break;
                    case 'y':
                        result.year = std::stoi("20"+datetime.substr(i, 2));
                        break;
                    case 'm':
                        result.month = std::stoi(datetime.substr(i, 2));
                        break;
                    case 'd':
                        result.day = std::stoi(datetime.substr(i, 2));
                        break;
                    case 'H':
                        result.hour = std::stoi(datetime.substr(i, 2));
                        break;
                    case 'I':
                        result.hour = std::stoi(datetime.substr(i, 2));
                        break;
                    case 'p':
                        if (datetime.substr(i, 2) == "PM"){
                            result.hour += 12;
                        }
                        break;
                    case 'M':
                        result.minute = std::stoi(datetime.substr(i, 2));
                        break;
                    case 'S':
                        result.second = std::stoi(datetime.substr(i, 2));
                        break;
                    default:
                        break;
                }
                ++i;
            }
        }
        return result;
    }

// ------------------------------------------------------------------
// ------------------------ Date Getters ----------------------------

    bool is_leap_year(const Datetime& datetime){
        if (datetime.year % 4 == 0){
            if (datetime.year % 100 == 0){
                if (datetime.year % 400 == 0){
                    return true;
                }
                else{
                    return false;
                }
            }
            else{
                return true;
            }
        }
        else{
            return false;
        }
    }

    unsigned short days_in_month(const Datetime& datetime){
        if (datetime.month == 2){
            if (is_leap_year(datetime)){
                return 29;
            }
            else{
                return 28;
            }
        }
        else if (datetime.month == 4 || datetime.month == 6 || datetime.month == 9 || datetime.month == 11){
            return 30;
        }
        else{
            return 31;
        }
    }

    unsigned short days_in_year(const Datetime& datetime){
        if (is_leap_year(datetime)){
            return 366;
        }
        else{
            return 365;
        }
    }

    unsigned short day_of_year(const Datetime& datetime){
        unsigned short day = 0;
        for (unsigned short i = 1; i < datetime.month; ++i){
            day += days_in_month(datetime);
        }
        day += datetime.day;
        return day;
    }

    //return the day of the 
    unsigned short week_day(const Datetime& datetime){
        unsigned short day = 6;
        for (unsigned short i = 1; i < datetime.year; ++i){
            day += days_in_year(datetime);
        }
        day += day_of_year(datetime);
        return day % 7;
    }

    // return the day 
    unsigned short day_of_week(const Datetime& datetime){
        return (week_day(datetime) + 1) % 7;
    }
    
    unsigned short day_of_week(unsigned short year, unsigned char month, unsigned char day){
        Datetime datetime = ::Datetime::datetime(year, month, day);
        return day_of_week(datetime);
    }

    unsigned short days_in_month(unsigned short year, unsigned char month){
        Datetime datetime = ::Datetime::datetime(year, month, 1);
        return days_in_month(datetime);
    }

    unsigned short days_in_year(unsigned short year){
        Datetime datetime = ::Datetime::datetime(year, 1, 1);
        return days_in_year(datetime);
    }

// ------------------------------------------------------------------
// ------------------------ Date Setters ----------------------------

    void set_year(Datetime& datetime, unsigned short year){
        datetime.year = year;
    }

    void set_month(Datetime& datetime, unsigned char month){
        datetime.month = month;
    }

    void set_day(Datetime& datetime, unsigned char day){
        datetime.day = day;
    }

    void set_hour(Datetime& datetime, unsigned char hour){
        datetime.hour = hour;
    }

    void set_minute(Datetime& datetime, unsigned char minute){
        datetime.minute = minute;
    }

    void set_second(Datetime& datetime, unsigned char second){
        datetime.second = second;
    }

// ------------------------------------------------------------------
// ------------------------ Date Operators --------------------------

    bool operator==(const Datetime& datetime1, const Datetime& datetime2){
        return datetime1.year == datetime2.year && datetime1.month == datetime2.month && datetime1.day == datetime2.day && datetime1.hour == datetime2.hour && datetime1.minute == datetime2.minute && datetime1.second == datetime2.second;
    }

    bool operator!=(const Datetime& datetime1, const Datetime& datetime2){
        return !(datetime1 == datetime2);
    }

    bool operator<(const Datetime& datetime1, const Datetime& datetime2){
        if (datetime1.year < datetime2.year){
            return true;
        }
        else if (datetime1.year == datetime2.year){
            if (datetime1.month < datetime2.month){
                return true;
            }
            else if (datetime1.month == datetime2.month){
                if (datetime1.day < datetime2.day){
                    return true;
                }
                else if (datetime1.day == datetime2.day){
                    if (datetime1.hour < datetime2.hour){
                        return true;
                    }
                    else if (datetime1.hour == datetime2.hour){
                        if (datetime1.minute < datetime2.minute){
                            return true;
                        }
                        else if (datetime1.minute == datetime2.minute){
                            if (datetime1.second < datetime2.second){
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    bool operator>(const Datetime& datetime1, const Datetime& datetime2){
        return datetime2 < datetime1;
    }

    bool operator<=(const Datetime& datetime1, const Datetime& datetime2){
        return !(datetime1 > datetime2);
    }

    bool operator>=(const Datetime& datetime1, const Datetime& datetime2){
        return !(datetime1 < datetime2);
    }

    Datetime operator+(const Datetime& datetime, const Deltatime::Deltatime& deltatime){
        Datetime result = datetime;
        result.second += deltatime.seconds;
        if (result.second >= 60){
            result.second -= 60;
            ++result.minute;
        }
        result.minute += deltatime.minutes;
        if (result.minute >= 60){
            result.minute -= 60;
            ++result.hour;
        }
        result.hour += deltatime.hours;
        if (result.hour >= 24){
            result.hour -= 24;
            ++result.day;
        }
        result.day += deltatime.days;
        if (result.day > days_in_month(result)){
            result.day -= days_in_month(result);
            ++result.month;
        }
        result.month += deltatime.months;
        if (result.month > 12){
            result.month -= 12;
            ++result.year;
        }
        result.year += deltatime.years;
        return result;
    }

    Datetime operator-(const Datetime& datetime, const Deltatime::Deltatime& deltatime){
        Datetime result = datetime;
        result.second -= deltatime.seconds;
        if (result.second < 0){
            result.second += 60;
            --result.minute;
        }
        result.minute -= deltatime.minutes;
        if (result.minute < 0){
            result.minute += 60;
            --result.hour;
        }
        result.hour -= deltatime.hours;
        if (result.hour < 0){
            result.hour += 24;
            --result.day;
        }
        result.day -= deltatime.days;
        if (result.day < 1){
            result.day += days_in_month(result);
            --result.month;
        }
        result.month -= deltatime.months;
        if (result.month < 1){
            result.month += 12;
            --result.year;
        }
        result.year -= deltatime.years;
        return result;
    }

    Deltatime::Deltatime operator-(const Datetime& datetime1, const Datetime& datetime2){
        Deltatime::Deltatime result;
        result.years = datetime1.year - datetime2.year;
        result.months = datetime1.month - datetime2.month;
        result.days = datetime1.day - datetime2.day;
        result.hours = datetime1.hour - datetime2.hour;
        result.minutes = datetime1.minute - datetime2.minute;
        result.seconds = datetime1.second - datetime2.second;
        return result;
    }

    Datetime operator+=(Datetime& datetime, const Deltatime::Deltatime& deltatime){
        datetime = datetime + deltatime;
        return datetime;
    }

    Datetime operator-=(Datetime& datetime, const Deltatime::Deltatime& deltatime){
        datetime = datetime - deltatime;
        return datetime;
    }
}