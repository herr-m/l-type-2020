#ifndef _DATABASESPAWNDS_
#define _DATABASESPAWNDS_

#include <string>

struct DataBaseSpawnDS final {
    const unsigned ennemyID;
    const double triggerPos, xOffSet;
    DataBaseSpawnDS(std::string eID, std::string sTime, std::string xOff) noexcept :
        ennemyID(std::stoi(eID)), triggerPos(std::stod(sTime)), xOffSet(std::stod(xOff)) {}
    constexpr DataBaseSpawnDS(unsigned eID, double sTime, double xOff) noexcept :
        ennemyID(eID), triggerPos(sTime), xOffSet(xOff) {}
    bool operator > (const DataBaseSpawnDS& other) const {return triggerPos > other.triggerPos;}
    bool operator == (const DataBaseSpawnDS& other) const {return triggerPos == other.triggerPos;}
};

#endif
