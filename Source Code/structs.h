#ifndef STRUCTS_H
#define STRUCTS_H

#include <vector>
#include <string>

struct XYrange
{
    int minX, maxX;
    int minY, maxY;
};

struct CityLocation
{
    int Xcoordinate, Ycoordinate;
    int cityId;
    std::string cityName;
};

struct CloudCover
{
    int Xcoordinate, Ycoordinate;
    int cloudCoverValue;
};

struct AtmosphericPressure
{
    int Xcoordinate, Ycoordinate;
    int atmosphericPressureValue;
};

extern XYrange mapSize;
extern CityLocation cityLocation;
extern CloudCover cloudCover;
extern AtmosphericPressure atmosphericPressure;

extern std::vector<CityLocation> cityLocations_Vector;
extern std::vector<CloudCover> cloudCovers_Vector;
extern std::vector<AtmosphericPressure> atmosphericPressures_Vector;
#endif