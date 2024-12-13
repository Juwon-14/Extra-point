//
//  Time.h
//  Extra point
//
//  Created by Juwon Hong on 12/13/24.
//

// Time.h
#ifndef TIME_H
#define TIME_H

class Time {
protected:
    int hour, minute, second;

public:
    Time(int h = 0, int m = 0, int s = 0);

    void addSeconds(int sec);
    void addMinutes(int min);
    void addHours(int hrs);

    int getHour() const;
    int getMinute() const;
    int getSecond() const;

    void normalize();
};

#endif
