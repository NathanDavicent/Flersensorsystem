#pragma once
#include <string>

// Mycket enkel beskrivning av en sensor
struct Sensor {
    std::string name;     // t.ex. "Temperatur"
    std::string unit;     // t.ex. "°C"
    double minValue;      // lägsta simulerade värde
    double maxValue;      // högsta simulerade värde
};

// Returnerar ett simulerat mätvärde inom [minValue, maxValue]
// (Nybörjarvänlig: använder rand() istället för <random>.)
double readSensorValue(const Sensor& s);
