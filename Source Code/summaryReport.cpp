#include <iostream>
#include <map>
#include <iomanip>
#include <sstream>
#include <vector>
#include <cmath>

#include "summaryReport.h"
#include "structs.h"
#include "map.h"

using namespace std;

string SummaryReport::CityInformation::toString()
{
    ostringstream os;
    os << "City Name : " << cityName << endl;
    os << "City Id   : " << cityId << endl;

    os << fixed << setprecision(2);
    os << "Ave. Cloud Cover (ACC)    : " << averageCloudCover << "  (" << Map::getLMH_Symbol(averageCloudCover) << ")" << endl;
    os << "Ave. Pressure    (AP)     : " << averageAtmosphericPressure << "  (" << Map::getLMH_Symbol(averageAtmosphericPressure) << ")" << endl;
    os << "Probability of Rain   (%) : " << rainProbability << endl;
    os << graphics << endl;

    return os.str();
};

SummaryReport::CityInformation cityInformation;
vector<SummaryReport::CityInformation> cityInformations_Vector;

void SummaryReport::displayWeatherForecastSummaryReport()
{
    collateSummaryReportDetailsForEachCity();
    printCityInformation_Vector();
}

void SummaryReport::collateSummaryReportDetailsForEachCity()
{
    map<int, int> occurenceOfEachCityId;
    countTotalOccurenceOfEachCityId(occurenceOfEachCityId);
    storeTotalOccurenceOfEachCityId(occurenceOfEachCityId);
    storeCityInformation();
}

map<int, int> SummaryReport::countTotalOccurenceOfEachCityId(map<int, int> &occurenceOfEachCityId)
{
    for (int i = 0; i < cityLocations_Vector.size(); i++)
    {
        int cityId = cityLocations_Vector[i].cityId;
        occurenceOfEachCityId[cityId]++;
    }
    return occurenceOfEachCityId;
}

void SummaryReport::storeTotalOccurenceOfEachCityId(map<int, int> &occurenceOfEachCityId)
{
    map<int, int>::iterator it;
    for (it = occurenceOfEachCityId.begin(); it != occurenceOfEachCityId.end(); it++)
    {
        int key = it->first, value = it->second;
        cityInformation.cityId = key;
        cityInformation.otherInformation.totalOccurrence = value;
        cityInformations_Vector.push_back(cityInformation);
    }
}

void SummaryReport::storeCityInformation()
{
    for (int i = 0; i < cityInformations_Vector.size(); i++)
    {
        SummaryReport::CityInformation &city = cityInformations_Vector[i];
        store_Original_XYrange(city, i);
        store_Final_XYrange(city);
        storeSumAndAverage(city);
        storeRainProbabilityAndGraphics(city);
    }
}

void SummaryReport::store_Original_XYrange(CityInformation &city, const int index)
{
    int minX, maxX, minY, maxY, count = 0;
    string cityName;
    findRespectiveData(minX, maxX, minY, maxY, count, cityName, index);

    if (count == city.otherInformation.totalOccurrence)
    {
        city.otherInformation.originalRange.minX = minX;
        city.otherInformation.originalRange.maxX = maxX;
        city.otherInformation.originalRange.minY = minY;
        city.otherInformation.originalRange.maxY = maxY;
        city.cityName = cityName;
    }
}

void SummaryReport::findRespectiveData(int &minX, int &maxX, int &minY, int &maxY, int &count, string &cityName, const int index)
{
    for (int j = 0; j < cityLocations_Vector.size(); j++)
    {
        if (isTheSameCityId(cityInformations_Vector[index].cityId, cityLocations_Vector[j].cityId))
        {
            int Xcoordinate = cityLocations_Vector[j].Xcoordinate, Ycoordinate = cityLocations_Vector[j].Ycoordinate;

            cityName = cityLocations_Vector[j].cityName;

            if (count == 0) // For structs members that have not been initialise yet
            {
                minX = maxX = Xcoordinate;
                minY = maxY = Ycoordinate;
            }
            else
            {
                minX = minValue(Xcoordinate, minX);
                maxX = maxValue(Xcoordinate, maxX);

                minY = minValue(Ycoordinate, minY);
                maxY = maxValue(Ycoordinate, maxY);
            }
            count++;
        }
    }
}

bool SummaryReport::isTheSameCityId(int a, int b) { return (a == b); }

int SummaryReport::minValue(int a, int b) { return ((a < b) ? a : b); }

int SummaryReport::maxValue(int a, int b) { return ((a > b) ? a : b); }

void SummaryReport::store_Final_XYrange(CityInformation &city)
{
    SummaryReport::CityInformation::OtherInformation &cityOtherInformation = city.otherInformation;

    cityOtherInformation.finalRange.minX = getMin((cityOtherInformation.originalRange.minX - 1), mapSize.minX);
    cityOtherInformation.finalRange.minY = getMin((cityOtherInformation.originalRange.minY - 1), mapSize.minY);

    cityOtherInformation.finalRange.maxX = getMax((cityOtherInformation.originalRange.maxX + 1), mapSize.maxX);
    cityOtherInformation.finalRange.maxY = getMax((cityOtherInformation.originalRange.maxY + 1), mapSize.maxY);
}

int SummaryReport::getMin(int a, int b) { return ((a < b) ? b : a); }

int SummaryReport::getMax(int a, int b) { return ((a > b) ? b : a); }

void SummaryReport::printCityInformation_Vector()
{
    for (int i = 0; i < cityInformations_Vector.size(); i++)
    {
        cout << cityInformations_Vector[i].toString() << "\n"
             << endl;
    }
}

void SummaryReport::storeSumAndAverage(CityInformation &city)
{
    SummaryReport::CityInformation::OtherInformation &cityOtherInformation = city.otherInformation;

    int minX = cityOtherInformation.finalRange.minX;
    int minY = cityOtherInformation.finalRange.minY;
    int maxX = cityOtherInformation.finalRange.maxX;
    int maxY = cityOtherInformation.finalRange.maxY;

    int count = 0, cloudCoverSum = 0, atmosphericPressureSum = 0;

    calculateSum(cloudCoverSum, atmosphericPressureSum, count, minX, maxX, minY, maxY);
    cityOtherInformation.sumCloudCover = cloudCoverSum;
    cityOtherInformation.sumAtmosphericPressure = atmosphericPressureSum;
    cityOtherInformation.citySize = count;

    double cloudAverageValue = getTwoSigFigValue((double)cloudCoverSum / count);
    double pressureAverageValue = getTwoSigFigValue((double)atmosphericPressureSum / count);

    city.averageCloudCover = cloudAverageValue;
    city.averageAtmosphericPressure = pressureAverageValue;
}

void SummaryReport::calculateSum(int &cloudCoverSum, int &atmosphericPressureSum, int &count, int minX, int maxX, int minY, int maxY)
{
    for (int minRow = minY; minRow <= maxY; minRow++)
    {
        for (int minCol = minX; minCol <= maxX; minCol++)
        {
            cloudCoverSum += getCloudCoverValue(minRow, minCol);
            atmosphericPressureSum += getAtmosphericPressureValue(minRow, minCol);
            count++;
        }
    }
}

int SummaryReport::getCloudCoverValue(int rowIndex, int colIndex)
{
    int i = 0;
    bool found = false;
    int value;
    while (i < cloudCovers_Vector.size() && !found)
    {
        int Xcoordinate = cloudCovers_Vector[i].Xcoordinate;
        int Ycoordinate = cloudCovers_Vector[i].Ycoordinate;
        if (Xcoordinate == colIndex && Ycoordinate == rowIndex)
        {
            value = cloudCovers_Vector[i].cloudCoverValue;
            found = true;
        }
        else
        {
            i++;
        }
    }
    return value;
}

int SummaryReport::getAtmosphericPressureValue(int rowIndex, int colIndex)
{
    int i = 0;
    bool found = false;
    int value;
    while (i < atmosphericPressures_Vector.size() && !found)
    {
        int Xcoordinate = atmosphericPressures_Vector[i].Xcoordinate;
        int Ycoordinate = atmosphericPressures_Vector[i].Ycoordinate;
        if (Xcoordinate == colIndex && Ycoordinate == rowIndex)
        {
            value = atmosphericPressures_Vector[i].atmosphericPressureValue;
            found = true;
        }
        else
        {
            i++;
        }
    }
    return value;
}

double SummaryReport::getTwoSigFigValue(double value)
{
    return (round(value * 100.0) / 100.0);
}

void SummaryReport::storeRainProbabilityAndGraphics(CityInformation &city)
{
    char ACC = Map::getLMH_Symbol(city.averageCloudCover);
    char AP = Map::getLMH_Symbol(city.averageAtmosphericPressure);
    double rainProbability;
    string graphics;

    if (AP == 'L' && ACC == 'H')
    {
        rainProbability = 90.00;
        graphics = createGraphics(4, 5, 5);
    }
    else if (AP == 'L' && ACC == 'M')
    {
        rainProbability = 80.00;
        graphics = createGraphics(4, 5, 4);
    }
    else if (AP == 'L' && ACC == 'L')
    {
        rainProbability = 70.00;
        graphics = createGraphics(4, 5, 3);
    }
    else if (AP == 'M' && ACC == 'H')
    {
        rainProbability = 60.00;
        graphics = createGraphics(4, 5, 2);
    }
    else if (AP == 'M' && ACC == 'M')
    {
        rainProbability = 50.00;
        graphics = createGraphics(4, 5, 1);
    }
    else if (AP == 'M' && ACC == 'L')
    {
        rainProbability = 40.00;
        graphics = createGraphics(4, 5, 0);
    }
    else if (AP == 'H' && ACC == 'H')
    {
        rainProbability = 30.00;
        graphics = createGraphics(3, 4, 0);
    }
    else if (AP == 'H' && ACC == 'M')
    {
        rainProbability = 20.00;
        graphics = createGraphics(2, 3, 0);
    }
    else if (AP == 'H' && ACC == 'L')
    {
        rainProbability = 10.00;
        graphics = createGraphics(1, 2, 0);
    }
    else
    {
        rainProbability = 0.00;
        graphics = "";
    }

    if (rainProbability != 0.00 || graphics != "")
    {
        city.rainProbability = rainProbability;
        city.graphics = graphics;
    }
}

string SummaryReport::createGraphics(int firstLine, int secondLine, int thirdLine)
{
    string str;
    appendCharacters(str, firstLine, '~');
    appendCharacters(str, secondLine, '~');
    appendCharacters(str, (5 - thirdLine), ' ', false);
    appendCharacters(str, thirdLine, '\\', false);
    return str;
}

void SummaryReport::appendCharacters(string &str, int noOfTimes, char character, bool isAddnewline)
{
    for (int i = 0; i < noOfTimes; i++)
    {
        str.push_back(character);
    }
    if (isAddnewline)
    {
        str.push_back('\n');
    }
}