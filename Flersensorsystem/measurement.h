#pragma once
#include <string>

// En rad mätdata som vi sparar och visar
struct Measurement {
    std::string timestamp;   // "YYYY-MM-DD HH:MM" (lokal tid)
    std::string sensorName;  // vilket sensor-namn
    std::string unit;        // enhet, t.ex. "°C"
    double value;            // själva mätvärdet
};

