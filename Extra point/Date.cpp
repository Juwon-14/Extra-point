//
//  Date.cpp
//  Extra point
//
//  Created by Juwon Hong on 12/13/24.
//

// Date.cpp
#include "Date.h"

Date::Date(int y, int m, int d, int h, int min, int s) : Time(h, min, s), year(y), month(m), day(d) {}

bool Date::isLeapYear(int y) const {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int Date::daysInMonth(int y, int m) const {
    static const int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (m == 2 && isLeapYear(y)) return 29;
    return days[m - 1];
}

void Date::addDays(int d) {
    day += d;
    while (day > daysInMonth(year, month)) {
        day -= daysInMonth(year, month);
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
}

void Date::addMonths(int m) {
    month += m;
    while (month > 12) {
        month -= 12;
        year++;
    }
}

void Date::addYears(int y) {
    year += y;
}

int Date::getYear() const {
    return year;
}

int Date::getMonth() const {
    return month;
}

int Date::getDay() const {
    return day;
}

int Date::dayOfWeek() const {
    // Zeller's Congruence
    int m = month, y = year;
    if (m < 3) {
        m += 12;
        y--;
    }
    int K = y % 100;
    int J = y / 100;
    int f = day + (13 * (m + 1)) / 5 + K + (K / 4) + (J / 4) - 2 * J;
    return ((f % 7) + 7) % 7; 
}
