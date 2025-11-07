// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>  // srand, rand
#include <ctime>    // time

#include "sensor.h"
#include "measurement.h"
#include "storage.h"
#include "utils.h"

// ====== Enkla inläsningshjälpare ======
int readInt(const std::string& prompt, int lo, int hi) {
    while (true) {
        std::cout << prompt;
        int x;
        if (std::cin >> x && x >= lo && x <= hi) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return x;
        }
        std::cout << "Ogiltigt val. Försök igen.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double readDouble(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        double x;
        if (std::cin >> x) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return x;
        }
        std::cout << "Felaktig siffra. Försök igen.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

// ====== Del A: läs ett mätvärde från varje sensor och spara ======
void takeOneReadingForAll(const std::vector<Sensor>& sensors, MeasurementStorage& storage) {
    std::string ts = nowTimestamp();
    for (const auto& s : sensors) {
        Measurement m;
        m.timestamp = ts;
        m.sensorName = s.name;
        m.unit = s.unit;
        m.value = readSensorValue(s);
        storage.add(m);   // Del B: lägg i lagring
    }
    std::cout << "Mätningar sparade (" << ts << ").\n";
}

// ====== Del C: visa statistik för vald sensor ======
void showStatsMenu(const MeasurementStorage& storage, const std::vector<Sensor>& sensors) {
    if (sensors.empty()) { std::cout << "Inga sensorer.\n"; return; }

    std::cout << "Välj sensor:\n";
    for (size_t i = 0; i < sensors.size(); ++i) {
        std::cout << "  " << (i + 1) << ") " << sensors[i].name << "\n";
    }
    int idx = readInt("Val: ", 1, (int)sensors.size()) - 1;

    size_t count = 0;
    double mean = 0.0, mn = 0.0, mx = 0.0;
    if (storage.statsForSensor(sensors[idx].name, count, mean, mn, mx)) {
        std::cout << "Statistik för " << sensors[idx].name << ":\n";
        std::cout << "  Antal: " << count << "\n";
        std::cout << "  Medel: " << mean << "\n";
        std::cout << "  Min  : " << mn << "\n";
        std::cout << "  Max  : " << mx << "\n";
    }
    else {
        std::cout << "Inga värden ännu för den sensorn.\n";
    }
}

int main() {
    // Fröa enkel slumpgenerator en gång
    std::srand((unsigned)std::time(nullptr));

    // Några exempel-sensorer (kan läggas till fler via menyn)
    std::vector<Sensor> sensors;
    sensors.push_back({ "Temperatur",    "°C", 18.0, 26.0 });
    sensors.push_back({ "Luftfuktighet", "%",  30.0, 70.0 });

    // Här sparas alla mätningar
    MeasurementStorage storage;

    // Enkel meny som täcker Del A–D
    while (true) {
        std::cout << "\n=== Flersensorsystem (nybörjarvänlig) ===\n"
            << "1) Läs nya mätvärden (alla sensorer)\n"   // Del A + Del B
            << "2) Visa statistik för en sensor\n"        // Del C
            << "3) Visa alla mätvärden\n"                 // Del B (utskrift)
            << "4) Spara till CSV\n"                      // Del D (spara)
            << "5) Läs in från CSV\n"                     // Del D (läsa)
            << "6) Lägg till sensor\n"                    // Extra: enkel sensorhantering
            << "0) Avsluta\n";

        int choice = readInt("Val: ", 0, 6);
        if (choice == 0) break;

        if (choice == 1) {
            takeOneReadingForAll(sensors, storage);
        }
        else if (choice == 2) {
            showStatsMenu(storage, sensors);
        }
        else if (choice == 3) {
            storage.printAll();
        }
        else if (choice == 4) {
            std::string path = readLine("Filnamn att spara (t.ex. data.csv): ");
            if (storage.saveCsv(path)) std::cout << "Sparat.\n";
            else std::cout << "Kunde inte spara.\n";
        }
        else if (choice == 5) {
            std::string path = readLine("Filnamn att läsa (t.ex. data.csv): ");
            if (storage.loadCsv(path)) std::cout << "Klart.\n";
            else std::cout << "Kunde inte läsa filen.\n";
        }
        else if (choice == 6) {
            // Enkel dialog för att lägga till en ny sensor
            std::string n = readLine("Sensorns namn: ");
            std::string u = readLine("Enhet (t.ex. °C eller %): ");
            double mn = readDouble("Minvärde: ");
            double mx = readDouble("Maxvärde: ");
            if (mx < mn) std::swap(mx, mn); // säkerställ rätt ordning
            sensors.push_back({ n, u, mn, mx });
            std::cout << "Sensor tillagd.\n";
        }
    }

    std::cout << "Hejdå!\n";
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file