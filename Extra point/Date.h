//
//  Date.h
//  Extra point
//
//  Created by Juwon Hong on 12/13/24.
//

// Date.h
#ifndef DATE_H
#define DATE_H

#include "Time.h"

class Date : public Time {
protected:
    int year, month, day;

public:
    Date(int y = 0, int m = 1, int d = 1, int h = 0, int min = 0, int s = 0);

    bool isLeapYear(int y) const;
    int daysInMonth(int y, int m) const;

    void addDays(int d);
    void addMonths(int m);
    void addYears(int y);

    int getYear() const;
    int getMonth() const;
    int getDay() const;

    int dayOfWeek() const; // Added method for calendar operations
};

#endif
