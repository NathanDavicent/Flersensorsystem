#pragma once
#include <string>
#include <vector>

// Ger nuvarande systemtid i format "YYYY-MM-DD HH:MM"
std::string nowTimestamp();

// Tar bort enkla blanksteg från början/slut
std::string trim(const std::string& s);

// Väldigt enkel CSV-split: delar på kommatecken och trimmar (inga citattecken hanteras)
std::vector<std::string> splitCsvSimple(const std::string& line);
