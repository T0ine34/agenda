
#include "deltatime.hpp"
#include "data.hpp"

#include <iostream>

namespace Deltatime{

// ------------------------------------------------------------------
// ----------------------- Constructors -----------------------------
    Deltatime deltatime(int years, int months, int days, int hours, int minutes, int seconds){
        Deltatime deltatime;
        deltatime.years = years;
        deltatime.months = months;
        deltatime.days = days;
        deltatime.hours = hours;
        deltatime.minutes = minutes;
        deltatime.seconds = seconds;
        return deltatime;
    }

    Deltatime deltatime(int hours, int minutes, int seconds){
        Deltatime deltatime;
        deltatime.years = 0;
        deltatime.months = 0;
        deltatime.days = 0;
        deltatime.hours = hours;
        deltatime.minutes = minutes;
        deltatime.seconds = seconds;
        return deltatime;
    }

    Deltatime deltatime(int minutes, int seconds){
        Deltatime deltatime;
        deltatime.years = 0;
        deltatime.months = 0;
        deltatime.days = 0;
        deltatime.hours = 0;
        deltatime.minutes = minutes;
        deltatime.seconds = seconds;
        return deltatime;
    }

    Deltatime deltatime(int seconds){
        Deltatime deltatime;
        deltatime.years = 0;
        deltatime.months = 0;
        deltatime.days = 0;
        deltatime.hours = 0;
        deltatime.minutes = 0;
        deltatime.seconds = seconds;
        return deltatime;
    }

    Deltatime deltatime(){
        Deltatime deltatime;
        deltatime.years = 0;
        deltatime.months = 0;
        deltatime.days = 0;
        deltatime.hours = 0;
        deltatime.minutes = 0;
        deltatime.seconds = 0;
        return deltatime;
    }

    Deltatime years(int years){
        Deltatime deltatime;
        deltatime.years = years;
        deltatime.months = 0;
        deltatime.days = 0;
        deltatime.hours = 0;
        deltatime.minutes = 0;
        deltatime.seconds = 0;
        return deltatime;
    }
    Deltatime months(int months){
        Deltatime deltatime;
        deltatime.years = 0;
        deltatime.months = months;
        deltatime.days = 0;
        deltatime.hours = 0;
        deltatime.minutes = 0;
        deltatime.seconds = 0;
        return deltatime;
    }
    Deltatime days(int days){
        Deltatime deltatime;
        deltatime.years = 0;
        deltatime.months = 0;
        deltatime.days = days;
        deltatime.hours = 0;
        deltatime.minutes = 0;
        deltatime.seconds = 0;
        return deltatime;
    }
    Deltatime hours(int hours){
        Deltatime deltatime;
        deltatime.years = 0;
        deltatime.months = 0;
        deltatime.days = 0;
        deltatime.hours = hours;
        deltatime.minutes = 0;
        deltatime.seconds = 0;
        return deltatime;
    }
    Deltatime minutes(int minutes){
        Deltatime deltatime;
        deltatime.years = 0;
        deltatime.months = 0;
        deltatime.days = 0;
        deltatime.hours = 0;
        deltatime.minutes = minutes;
        deltatime.seconds = 0;
        return deltatime;
    }
    Deltatime seconds(int seconds){
        Deltatime deltatime;
        deltatime.years = 0;
        deltatime.months = 0;
        deltatime.days = 0;
        deltatime.hours = 0;
        deltatime.minutes = 0;
        deltatime.seconds = seconds;
        return deltatime;
    }


// ------------------------------------------------------------------
// ----------------------- Operators --------------------------------
    bool operator==(const Deltatime& deltatime1, const Deltatime& deltatime2){
        return (deltatime1.years == deltatime2.years) && (deltatime1.months == deltatime2.months) && (deltatime1.days == deltatime2.days) && (deltatime1.hours == deltatime2.hours) && (deltatime1.minutes == deltatime2.minutes) && (deltatime1.seconds == deltatime2.seconds);
    }

    bool operator!=(const Deltatime& deltatime1, const Deltatime& deltatime2){
        return !(deltatime1 == deltatime2);
    }

    bool operator<(const Deltatime& deltatime1, const Deltatime& deltatime2){
        if(deltatime1.years < deltatime2.years){
            return true;
        }else if(deltatime1.years > deltatime2.years){
            return false;
        }else{
            if(deltatime1.months < deltatime2.months){
                return true;
            }else if(deltatime1.months > deltatime2.months){
                return false;
            }else{
                if(deltatime1.days < deltatime2.days){
                    return true;
                }else if(deltatime1.days > deltatime2.days){
                    return false;
                }else{
                    if(deltatime1.hours < deltatime2.hours){
                        return true;
                    }else if(deltatime1.hours > deltatime2.hours){
                        return false;
                    }else{
                        if(deltatime1.minutes < deltatime2.minutes){
                            return true;
                        }else if(deltatime1.minutes > deltatime2.minutes){
                            return false;
                        }else{
                            if(deltatime1.seconds < deltatime2.seconds){
                                return true;
                            }else{
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }

    bool operator>(const Deltatime& deltatime1, const Deltatime& deltatime2){
        return deltatime2 < deltatime1;
    }

    bool operator<=(const Deltatime& deltatime1, const Deltatime& deltatime2){
        return !(deltatime1 > deltatime2);
    }

    bool operator>=(const Deltatime& deltatime1, const Deltatime& deltatime2){
        return !(deltatime1 < deltatime2);
    }

    Deltatime operator+(const Deltatime& deltatime1, const Deltatime& deltatime2){
        Deltatime deltatime;
        deltatime.years = deltatime1.years + deltatime2.years;
        deltatime.months = deltatime1.months + deltatime2.months;
        deltatime.days = deltatime1.days + deltatime2.days;
        deltatime.hours = deltatime1.hours + deltatime2.hours;
        deltatime.minutes = deltatime1.minutes + deltatime2.minutes;
        deltatime.seconds = deltatime1.seconds + deltatime2.seconds;
        return deltatime;
    }

    Deltatime operator-(const Deltatime& deltatime1, const Deltatime& deltatime2){
        Deltatime deltatime;
        deltatime.years = deltatime1.years - deltatime2.years;
        deltatime.months = deltatime1.months - deltatime2.months;
        deltatime.days = deltatime1.days - deltatime2.days;
        deltatime.hours = deltatime1.hours - deltatime2.hours;
        deltatime.minutes = deltatime1.minutes - deltatime2.minutes;
        deltatime.seconds = deltatime1.seconds - deltatime2.seconds;
        return deltatime;
    }


    void operator+=(Deltatime& deltatime1, const Deltatime& deltatime2){
        deltatime1 = deltatime1 + deltatime2;
    }

    void operator-=(Deltatime& deltatime1, const Deltatime& deltatime2){
        deltatime1 = deltatime1 - deltatime2;
    }

    Deltatime operator+(const Deltatime& deltatime, int seconds){
        Deltatime deltatime2;
        deltatime2.years = 0;
        deltatime2.months = 0;
        deltatime2.days = 0;
        deltatime2.hours = 0;
        deltatime2.minutes = 0;
        deltatime2.seconds = seconds;
        return deltatime + deltatime2;
    }

    Deltatime operator-(const Deltatime& deltatime, int seconds){
        Deltatime deltatime2;
        deltatime2.years = 0;
        deltatime2.months = 0;
        deltatime2.days = 0;
        deltatime2.hours = 0;
        deltatime2.minutes = 0;
        deltatime2.seconds = seconds;
        return deltatime - deltatime2;
    }

    void operator+=(Deltatime& deltatime, int seconds){
        deltatime = deltatime + seconds;
    }

    void operator-=(Deltatime& deltatime, int seconds){
        deltatime = deltatime - seconds;
    }

    Deltatime operator*(const Deltatime& deltatime, int factor){
        int years = deltatime.years * factor;
        int months = deltatime.months * factor;
        int days = deltatime.days * factor;
        int hours = deltatime.hours * factor;
        int minutes = deltatime.minutes * factor;
        int seconds = deltatime.seconds * factor;
        if (seconds >= 60){
            minutes += seconds / 60;
            seconds = seconds % 60;
        }
        if (minutes >= 60){
            hours += minutes / 60;
            minutes = minutes % 60;
        }
        if (hours >= 24){
            days += hours / 24;
            hours = hours % 24;
        }
        if (days >= 30){
            months += days / 30;
            days = days % 30;
        }
        if (months >= 12){
            years += months / 12;
            months = months % 12;
        }
        Deltatime deltatime2 = ::Deltatime::deltatime(years, months, days, hours, minutes, seconds);

        return deltatime2;


    }

    Deltatime operator/(const Deltatime& deltatime, int factor){
        int years = deltatime.years / factor;
        int months = deltatime.months / factor;
        int days = deltatime.days / factor;
        int hours = deltatime.hours / factor;
        int minutes = deltatime.minutes / factor;
        int seconds = deltatime.seconds / factor;
        Deltatime deltatime2 = ::Deltatime::deltatime(years, months, days, hours, minutes, seconds);
        return deltatime2;
    }

    void operator*=(Deltatime& deltatime, int factor){
        deltatime = deltatime * factor;
    }

    void operator/=(Deltatime& deltatime, int factor){
        deltatime = deltatime / factor;
    }

    std::string to_string(const Deltatime& deltatime, std::string locale){
        std::string deltatime_string;
        if (deltatime.years > 0){
            deltatime_string += std::to_string(deltatime.years);
            deltatime_string += " ";
            deltatime_string += Date_Data::year.at(locale);
            deltatime_string += ", ";
        }
        if (deltatime.months > 0){
            deltatime_string += std::to_string(deltatime.months);
            deltatime_string += " ";
            deltatime_string += Date_Data::month.at(locale);
            deltatime_string += ", ";
        }
        if (deltatime.days > 0){
            deltatime_string += std::to_string(deltatime.days);
            deltatime_string += " ";
            deltatime_string += Date_Data::day.at(locale);
            deltatime_string += ", ";
        }
        if (deltatime.hours > 0){
            deltatime_string += std::to_string(deltatime.hours);
            deltatime_string += " ";
            deltatime_string += Date_Data::hour.at(locale);
            deltatime_string += ", ";
        }
        if (deltatime.minutes > 0){
            deltatime_string += std::to_string(deltatime.minutes);
            deltatime_string += " ";
            deltatime_string += Date_Data::minute.at(locale);
            deltatime_string += ", ";
        }
        deltatime_string += std::to_string(deltatime.seconds);
        deltatime_string += " ";
        deltatime_string += Date_Data::second.at(locale);
        return deltatime_string;
    }
}