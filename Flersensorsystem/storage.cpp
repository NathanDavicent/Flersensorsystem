#include "storage.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>      // för unika sensor-namn

void MeasurementStorage::add(const Measurement& m) {
    data_.push_back(m);
}

void MeasurementStorage::printAll() const {
    if (data_.empty()) {
        std::cout << "(Inga mätvärden ännu)\n";
        return;
    }
    std::cout << "Timestamp          | Sensor            | Värde        | Enhet\n";
    std::cout << "-------------------+-------------------+--------------+------\n";
    for (const auto& m : data_) {
        std::cout << std::left << std::setw(19) << m.timestamp << " | "
            << std::setw(17) << m.sensorName << " | "
            << std::right << std::setw(10) << std::fixed << std::setprecision(3) << m.value << " | "
            << std::left << std::setw(4) << m.unit << "\n";
    }
}

bool MeasurementStorage::saveCsv(const std::string& path) const {
    std::ofstream ofs(path.c_str());
    if (!ofs) return false;

    // Enkel CSV: "YYYY-MM-DD HH:MM, Namn, Värde, Enhet"
    for (const auto& m : data_) {
        ofs << m.timestamp << ", "
            << m.sensorName << ", "
            << std::fixed << std::setprecision(3) << m.value << ", "
            << m.unit << "\n";
    }
    return true;
}

bool MeasurementStorage::loadCsv(const std::string& path) {
    std::ifstream ifs(path.c_str());
    if (!ifs) return false;

    std::string line;
    size_t ok = 0, bad = 0;

    while (std::getline(ifs, line)) {
        // Förväntar 4 delar: timestamp, name, value, unit
        auto parts = splitCsvSimple(line);
        if (parts.size() != 4) { bad++; continue; }

        Measurement m;
        m.timestamp = parts[0];
        m.sensorName = parts[1];

        // försök tolka värdet
        try { m.value = std::stod(parts[2]); }
        catch (...) { bad++; continue; }

        m.unit = parts[3];

        data_.push_back(m);
        ok++;
    }

    std::cout << "Läste " << ok << " rader. Ignorerade " << bad << " felaktiga rader.\n";
    return true;
}

bool MeasurementStorage::statsForSensor(const std::string& sensorName,
    size_t& outCount,
    double& outMean,
    double& outMin,
    double& outMax) const {
    bool first = true;
    double sum = 0.0;
    size_t cnt = 0;
    double mn = 0.0;
    double mx = 0.0;

    // Gå igenom alla mätningar och samla de som tillhör sensorn
    for (const auto& m : data_) {
        if (m.sensorName == sensorName) {
            if (first) { mn = mx = m.value; first = false; }
            if (m.value < mn) mn = m.value;
            if (m.value > mx) mx = m.value;
            sum += m.value;
            cnt++;
        }
    }

    if (cnt == 0) return false;      // inga värden -> ingen statistik

    outCount = cnt;
    outMean = sum / cnt;
    outMin = mn;
    outMax = mx;
    return true;
}

std::vector<std::string> MeasurementStorage::sensorNames() const {
    std::set<std::string> s;         // set ger unika namn i sorterad ordning
    for (const auto& m : data_) s.insert(m.sensorName);
    return std::vector<std::string>(s.begin(), s.end());
}
