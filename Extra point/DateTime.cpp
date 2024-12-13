//
//  DateTime.cpp
//  Extra point
//
//  Created by Juwon Hong on 12/12/24.
//

// DateTime.cpp
#include "DateTime.h"

DateTime::DateTime(int y, int m, int d, int h, int min, int sec, int tz) :
    year(y), month(m), day(d), hour(h), minute(min), second(sec), timeZoneOffset(tz) {}

void DateTime::addSeconds(int sec) {
    second += sec;
    minute += second / 60;
    second %= 60;
    hour += minute / 60;
    minute %= 60;
    day += hour / 24;
    hour %= 24;

    while (day > daysInMonth()) {
        day -= daysInMonth();
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
}

void DateTime::addMinutes(int min) {
    addSeconds(min * 60);
}

void DateTime::addHours(int hrs) {
    addMinutes(hrs * 60);
}

void DateTime::addDays(int days) {
    day += days;
    while (day > daysInMonth()) {
        day -= daysInMonth();
               month++;
               if (month > 12) {
                   month = 1;
                   year++;
               }
           }
       }

       void DateTime::adjustTimeZone(int newOffset) {
           int offsetDifference = newOffset - timeZoneOffset;
           addSeconds(offsetDifference * 3600);
           timeZoneOffset = newOffset;
       }

       void DateTime::applyDaylightSaving(int startMonth, int startDay, int endMonth, int endDay) {
           if ((month > startMonth || (month == startMonth && day >= startDay)) &&
               (month < endMonth || (month == endMonth && day <= endDay))) {
               addHours(1);
           }
       }

       bool DateTime::isLeapYear() const {
           return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
       }

       int DateTime::daysInMonth() const {
           static const int daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
           return month == 2 && isLeapYear() ? 29 : daysPerMonth[month - 1];
       }

       std::string DateTime::dayOfWeek() const {
           static const char* daysOfWeek[] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
           int y = year, m = month, d = day;
           if (m < 3) {
               m += 12;
                       y--;
                   }
                   int k = y % 100;
                   int j = y / 100;
                   int dayIndex = (d + 13 * (m + 1) / 5 + k + k / 4 + j / 4 - 2 * j) % 7;
                   return daysOfWeek[(dayIndex + 7) % 7];
               }

std::string DateTime::format(const std::string& formatString) const {
    std::ostringstream oss;
    for (size_t i = 0; i < formatString.size(); ++i) {
        if (formatString[i] == 'Y') {
            oss << year;
        } else if (formatString[i] == 'M' && formatString[i + 1] == 'M') {
            oss << std::setw(2) << std::setfill('0') << month;
            ++i;
        } else if (formatString[i] == 'D' && formatString[i + 1] == 'D') {
            oss << std::setw(2) << std::setfill('0') << day;
            ++i;
        } else if (formatString[i] == 'H' && formatString[i + 1] == 'H') {
            oss << std::setw(2) << std::setfill('0') << hour;
            ++i;
        } else if (formatString[i] == 'm' && formatString[i + 1] == 'm') {
            oss << std::setw(2) << std::setfill('0') << minute;
            ++i;
        } else if (formatString[i] == 's' && formatString[i + 1] == 's') {
            oss << std::setw(2) << std::setfill('0') << second;
            ++i;
        } else {
            oss << formatString[i];
        }
    }
    return oss.str();
    }

    std::string DateTime::serialize() const {
        std::ostringstream oss;
        oss << year << "-" << std::setw(2) << std::setfill('0') << month << "-"
            << std::setw(2) << std::setfill('0') << day << "T"
            << std::setw(2) << std::setfill('0') << hour << ":"
            << std::setw(2) << std::setfill('0') << minute << ":"
            << std::setw(2) << std::setfill('0') << second << "Z";
        return oss.str();
    }

    DateTime DateTime::deserialize(const std::string& serializedString) {
        int y, m, d, h, min, s;
        sscanf(serializedString.c_str(), "%4d-%2d-%2dT%2d:%2d:%2dZ", &y, &m, &d, &h, &min, &s);
        return DateTime(y, m, d, h, min, s);
    }
