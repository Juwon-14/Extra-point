//
//  DateTime.h
//  Extra point
//
//  Created by Juwon Hong on 12/12/24.
//

// DateTime.h
#ifndef DATETIME_H
#define DATETIME_H

#include <string>
#include <sstream>
#include <iomanip>

class DateTime {
private:
    int year, month, day;
    int hour, minute, second;
    int timeZoneOffset; 

public:
    DateTime(int y = 1970, int m = 1, int d = 1, int h = 0, int min = 0, int sec = 0, int tz = 0);

    void addSeconds(int sec);
    void addMinutes(int min);
    void addHours(int hrs);
    void addDays(int days);

    void adjustTimeZone(int newOffset);
    void applyDaylightSaving(int startMonth, int startDay, int endMonth, int endDay);

    bool isLeapYear() const;
    int daysInMonth() const;
    std::string dayOfWeek() const;

    std::string format(const std::string& formatString) const;
    std::string serialize() const;
    static DateTime deserialize(const std::string& serializedString);
};

#endif
