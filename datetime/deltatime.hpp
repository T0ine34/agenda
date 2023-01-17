#ifndef __DELTA_TIME_HPP__
#define __DELTA_TIME_HPP__

/*
The goal of this library is to provide a simple way to work with time differences.
It allow you to work with time differences like you would with a number.
You can add and subtract time differences, compare them, and convert them to strings.
*/

#include <string>

namespace Deltatime{
    
        struct Deltatime{
            unsigned short years;
            unsigned char months;
            unsigned char days;
            unsigned char hours;
            unsigned char minutes;
            unsigned char seconds;
        };

        const Deltatime empty_deltatime = Deltatime{65535, 255, 255, 255, 255, 255};
    
        Deltatime deltatime(int years, int months, int days, int hours, int minutes, int seconds);
        Deltatime deltatime(int hours, int minutes, int seconds);
        Deltatime deltatime(int minutes, int seconds);
        Deltatime deltatime(int seconds);
        Deltatime deltatime();

        Deltatime years(int years);
        Deltatime months(int months);
        Deltatime days(int days);
        Deltatime hours(int hours);
        Deltatime minutes(int minutes);
        Deltatime seconds(int seconds);
    
        bool operator==(const Deltatime& deltatime1, const Deltatime& deltatime2);
        bool operator!=(const Deltatime& deltatime1, const Deltatime& deltatime2);
        bool operator<(const Deltatime& deltatime1, const Deltatime& deltatime2);
        bool operator>(const Deltatime& deltatime1, const Deltatime& deltatime2);
        bool operator<=(const Deltatime& deltatime1, const Deltatime& deltatime2);
        bool operator>=(const Deltatime& deltatime1, const Deltatime& deltatime2);
    
        Deltatime operator+(const Deltatime& deltatime1, const Deltatime& deltatime2);
        Deltatime operator-(const Deltatime& deltatime1, const Deltatime& deltatime2);

        void operator+=(Deltatime& deltatime1, const Deltatime& deltatime2);
        void operator-=(Deltatime& deltatime1, const Deltatime& deltatime2);

        Deltatime operator+(const Deltatime& deltatime, int seconds);
        Deltatime operator-(const Deltatime& deltatime, int seconds);

        void operator+=(Deltatime& deltatime, int seconds);
        void operator-=(Deltatime& deltatime, int seconds);

        Deltatime operator*(const Deltatime& deltatime, int factor);
        Deltatime operator/(const Deltatime& deltatime, int factor);

        void operator*=(Deltatime& deltatime, int factor);
        void operator/=(Deltatime& deltatime, int factor);

        std::string to_string(const Deltatime& deltatime, std::string locale = "en");
}

#endif