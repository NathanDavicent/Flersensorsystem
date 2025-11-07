#include "sensor.h"
#include <cstdlib> // rand(), RAND_MAX

double readSensorValue(const Sensor& s) {
    // Enkel slump: tal i intervallet [0,1]
    double r = std::rand() / (double)RAND_MAX;
    // Skala till sensorns intervall
    return s.minValue + r * (s.maxValue - s.minValue);
}
