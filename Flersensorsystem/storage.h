#pragma once
#include <vector>
#include <string>
#include "measurement.h"

// Enkel klass som håller ordning på alla mätningar
class MeasurementStorage {
public:
    // Del B: lägg till och visa
    void add(const Measurement& m);
    void printAll() const;

    // Del D: spara/läsa CSV
    bool saveCsv(const std::string& path) const;
    bool loadCsv(const std::string& path);

    // Del C: enkel statistik (antal/medel/min/max) för en sensor
    // Returnerar false om inga värden finns för sensorn.
    bool statsForSensor(const std::string& sensorName,
        size_t& outCount,
        double& outMean,
        double& outMin,
        double& outMax) const;

    // Hjälp: lista sensor-namn som finns i lagrade data (för menyval)
    std::vector<std::string> sensorNames() const;

private:
    std::vector<Measurement> data_;
};
