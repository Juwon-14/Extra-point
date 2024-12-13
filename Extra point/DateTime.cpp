//
//  DateTime.cpp
//  Extra point
//
//  Created by Juwon Hong on 12/12/24.
//

// DateTime.cpp
#include "DateTime.h"

Time::Time(int h, int m, int s, int tz) : hour(h), minute(m), second(s), timeZoneOffset(tz) {}

void Time::addSeconds(int sec) {
    second += sec;
    minute += second / 60;
    second %= 60;
    hour += minute / 60;
    minute %= 60;
    hour %= 24;
}

void Time::adjustTimeZone(int newOffset) {
    int offsetDifference = newOffset - timeZoneOffset;
    addSeconds(offsetDifference * 3600);
    timeZoneOffset = newOffset;
}

Date::Date(int y, int m, int d) : year(y), month(m), day(d) {}

bool Date::isLeapYear() const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Date::daysInMonth() const {
    static const int daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return month == 2 && isLeapYear() ? 29 : daysPerMonth[month - 1];
}

void Date::addDays(int days) {
    while (days > 0) {
        int daysLeftInMonth = daysInMonth() - day;
        if (days <= daysLeftInMonth) {
                    day += days;
                    return;
                } else {
                    days -= (daysLeftInMonth + 1);
                    day = 1;
                    month++;
                    if (month > 12) {
                        month = 1;
                        year++;
                    }
                }
            }
        }

        std::string Date::dayOfWeek() const {
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

        DateTime::DateTime(int y, int m, int d, int h, int min, int sec, int tz) : date(y, m, d), time(h, min, sec, tz) {}

void DateTime::addSeconds(int sec) {
    time.addSeconds(sec);
    if (time.second < 0 || time.minute < 0) {
        date.addDays(-1);
    }
}

void DateTime::addMinutes(int min) {
    addSeconds(min * 60);
}

void DateTime::addHours(int hrs) {
    addMinutes(hrs * 60);
}

void DateTime::addDays(int days) {
    date.addDays(days);
}

void DateTime::adjustTimeZone(int newOffset) {
    time.adjustTimeZone(newOffset);
}

void DateTime::applyDaylightSaving(int startMonth, int startDay, int endMonth, int endDay) {
    if ((date.month > startMonth || (date.month == startMonth && date.day >= startDay)) &&
        (date.month < endMonth || (date.month == endMonth && date.day <= endDay))) {
        addHours(1);
    }
}

std::string DateTime::format(const std::string& formatString) const {
    std::ostringstream oss;
    for (size_t i = 0; i < formatString.size(); ++i) {
        if (formatString[i] == 'Y') {
            oss << date.year;
        } else if (formatString[i] == 'M' && formatString[i + 1] == 'M') {
            oss << std::setw(2) << std::setfill('0') << date.month;
            ++i;
        } else if (formatString[i] == 'D' && formatString[i + 1] == 'D') {
                   oss << std::setw(2) << std::setfill('0') << date.day;
                   ++i;
               } else if (formatString[i] == 'H' && formatString[i + 1] == 'H') {
                   oss << std::setw(2) << std::setfill('0') << time.hour;
                   ++i;
               } else if (formatString[i] == 'm' && formatString[i + 1] == 'm') {
                   oss << std::setw(2) << std::setfill('0') << time.minute;
                   ++i;
               } else if (formatString[i] == 's' && formatString[i + 1] == 's') {
                   oss << std::setw(2) << std::setfill('0') << time.second;
                   ++i;
               } else {
                   oss << formatString[i];
               }
           }
           return oss.str();
       }

       std::string DateTime::serialize() const {
           std::ostringstream oss;
           oss << date.year << "-" << std::setw(2) << std::setfill('0') << date.month << "-"
               << std::setw(2) << std::setfill('0') << date.day << "T"
               << std::setw(2) << std::setfill('0') << time.hour << ":"
               << std::setw(2) << std::setfill('0') << time.minute << ":"
               << std::setw(2) << std::setfill('0') << time.second << "Z";
           return oss.str();
       }

       DateTime DateTime::deserialize(const std::string& serializedString) {
           int y, m, d, h, min, s;
           sscanf(serializedString.c_str(), "%4d-%2d-%2dT%2d:%2d:%2dZ", &y, &m, &d, &h, &min, &s);
           return DateTime(y, m, d, h, min, s);
       }
