//
//  main.cpp
//  Extra point
//
//  Created by Juwon Hong on 12/12/24.
//

// main.cpp
#include <iostream>
#include "DateTime.h"

int main() {
    DateTime dt(2024, 12, 11, 14, 30, 45, 0);
    dt.addDays(1);
    dt.addSeconds(3600);
    dt.adjustTimeZone(-5);
    dt.applyDaylightSaving(3, 10, 11, 5);

    std::cout << dt.format("Today is Y-MM-DD, and the time is HH:mm:ss") << std::endl;
    std::cout << "Serialized: " << dt.serialize() << std::endl;

    DateTime deserialized = DateTime::deserialize("2024-12-12T15:30:45Z");
    std::cout << "Deserialized: " << deserialized.format("Y-MM-DD HH:mm:ss") << std::endl;

    std::cout << "Day of the Week: " << dt.dayOfWeek() << std::endl;

    return 0;
}

