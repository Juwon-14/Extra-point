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

class Time {
public:
    int hour, minute, second;
    int timeZoneOffset;

    Time(int h = 0, int m = 0, int s = 0, int tz = 0);
    void addSeconds(int sec);
    void adjustTimeZone(int newOffset);
};

class Date {
public:
    int year, month, day;

    Date(int y = 1970, int m = 1, int d = 1);
    bool isLeapYear() const;
    int daysInMonth() const;
    void addDays(int days);
    std::string dayOfWeek() const;
};

class DateTime {
public:
    Date date;
    Time time;
    
    DateTime(int y = 1970, int m = 1, int d = 1, int h = 0, int min = 0, int sec = 0, int tz = 0);
        void addSeconds(int sec);
        void addMinutes(int min);
        void addHours(int hrs);
        void addDays(int days);
        void adjustTimeZone(int newOffset);
        void applyDaylightSaving(int startMonth, int startDay, int endMonth, int endDay);
        std::string format(const std::string& formatString) const;
        std::string serialize() const; // Serialize DateTime to string
        static DateTime deserialize(const std::string& serializedString); // Deserialize from string
    };

    #endif
