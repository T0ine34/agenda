#ifndef __DATETIME_HPP__
#define __DATETIME_HPP__

#include <string>
#include "deltatime.hpp"

namespace Datetime{

// ------------------------------------------------------------------
// --------------------------- Structure ----------------------------
    struct Datetime{
        unsigned short year;
        unsigned char month;
        unsigned char day;
        unsigned char hour;
        unsigned char minute;
        unsigned char second;
    };

    const Datetime empty_datetime = Datetime{65535, 255, 255, 255, 255, 255};

// ------------------------------------------------------------------
// ---------------------------Constructors---------------------------
    Datetime datetime(int year, int month, int day, int hour, int minute, int second);
    Datetime datetime(int year, int month, int day);
    Datetime datetime();

    Datetime now();

// ------------------------------------------------------------------
// ----------------------- String Functions -------------------------
    std::string format(const Datetime& datetime, std::string format, std::string locale = "en");
    std::string to_string(const Datetime& datetime, std::string locale = "en");

    Datetime from_string(std::string datetime, std::string format = "%d/%m/%Y %H:%M:%S", std::string locale = "en");

// ------------------------------------------------------------------
// ------------------------ Date Getters ----------------------------
    bool is_leap_year(const Datetime& datetime);
    unsigned short days_in_month(const Datetime& datetime);
    unsigned short days_in_year(const Datetime& datetime);
    unsigned short day_of_year(const Datetime& datetime);
    // 0 = Sunday, 1 = Monday, 2 = Tuesday, 3 = Wednesday, 4 = Thursday, 5 = Friday, 6 = Saturday
    unsigned short day_of_week(const Datetime& datetime);
    unsigned short day_of_week(unsigned short year, unsigned char month, unsigned char day);

    unsigned short days_in_month(unsigned short year, unsigned char month);
    unsigned short days_in_year(unsigned short year);


// ------------------------------------------------------------------
// ------------------------ Date Setters ----------------------------

    void set_year(Datetime& datetime, unsigned short year);
    void set_month(Datetime& datetime, unsigned char month);
    void set_day(Datetime& datetime, unsigned char day);
    void set_hour(Datetime& datetime, unsigned char hour);
    void set_minute(Datetime& datetime, unsigned char minute);
    void set_second(Datetime& datetime, unsigned char second);


// ------------------------------------------------------------------
// ------------------------ Date Operators --------------------------
    bool operator==(const Datetime& datetime1, const Datetime& datetime2);
    bool operator!=(const Datetime& datetime1, const Datetime& datetime2);
    bool operator<(const Datetime& datetime1, const Datetime& datetime2);
    bool operator>(const Datetime& datetime1, const Datetime& datetime2);
    bool operator<=(const Datetime& datetime1, const Datetime& datetime2);
    bool operator>=(const Datetime& datetime1, const Datetime& datetime2);

    Datetime operator+(const Datetime& datetime, int seconds);
    Datetime operator-(const Datetime& datetime, int seconds);

    Datetime operator+=(Datetime& datetime, int seconds);
    Datetime operator-=(Datetime& datetime, int seconds);

    Datetime operator+(const Datetime& datetime, const Deltatime::Deltatime& deltatime);

    Datetime operator-(const Datetime& datetime, const Deltatime::Deltatime& deltatime);

    Deltatime::Deltatime operator-(const Datetime& datetime1, const Datetime& datetime2);

    Datetime operator+=(Datetime& datetime, const Deltatime::Deltatime& deltatime);

    Datetime operator-=(Datetime& datetime, const Deltatime::Deltatime& deltatime);
}
#endif