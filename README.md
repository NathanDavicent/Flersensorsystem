# Flersensorsystem

Ett skolprojekt skrivet i **C++17** där flera sensorer simulerar mätvärden som sparas, visas, analyseras och kan exporteras till CSV-filer.

# Funktioner
- Läs in simulerade mätvärden från flera sensorer  
- Visa alla mätningar i tabellformat  
- Beräkna enkel statistik (antal, medel, min, max) per sensor  
- Spara och läsa mätdata till/från CSV-fil  
- Lägg till egna sensorer under körning  

# Teknisk information
- Språk: **C++17**  
- Inga new eller delete används  
- Uppdelat i .cpp och .h - filer enligt god praxis  
- All logik ligger i klasser (t.ex. Sensor, MeasurementStorage, Utils)  
- main.cpp hanterar endast programflödet  

## Projektstruktur
project/
- main.cpp
- sensor.h
- sensor.cpp
- measurement.h
- storage.h
- storage.cpp
- utils.h
- utils.cpp
