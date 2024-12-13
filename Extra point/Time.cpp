//
//  Time.cpp
//  Extra point
//
//  Created by Juwon Hong on 12/13/24.
//

// Time.cpp
#include "Time.h"

Time::Time(int h, int m, int s) : hour(h), minute(m), second(s) {}

void Time::addSeconds(int sec) {
    second += sec;
    normalize();
}

void Time::addMinutes(int min) {
    minute += min;
    normalize();
}

void Time::addHours(int hrs) {
    hour += hrs;
    normalize();
}

int Time::getHour() const {
    return hour;
}

int Time::getMinute() const {
    return minute;
}

int Time::getSecond() const {
    return second;
}

void Time::normalize() {
    minute += second / 60;
    second %= 60;
    hour += minute / 60;
    minute %= 60;
    hour %= 24; 
}

