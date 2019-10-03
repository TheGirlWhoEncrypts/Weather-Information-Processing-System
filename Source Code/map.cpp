#include <iostream>
#include <iomanip>
#include <string>

#include "map.h"
#include "structs.h"
#include "twoDimensionalArray.h"

using namespace std;

void Map::displayMap(int userChoiceNumber)
{
    int noOfCols = calculateMapSize(mapSize.minX, mapSize.maxX);
    int noOfRows = calculateMapSize(mapSize.minY, mapSize.maxY);

    int **p2DArray = Two_D_Array::allocate2DArray(noOfRows, noOfCols);
    Two_D_Array::initialize2DArray(p2DArray, noOfRows, noOfCols);
    Two_D_Array::assignValuesTo2DArray(p2DArray, userChoiceNumber);

    mapFormatter(p2DArray, noOfRows, noOfCols, userChoiceNumber);

    Two_D_Array::delete2DArray(p2DArray, noOfRows, noOfCols);
}

int Map::calculateMapSize(int min, int max)
{
    return ((max - min) + 1);
}

void Map::mapFormatter(int **p2DArray, int noOfRows, int noOfCols, int userChoiceNumber)
{
    for (int i = (mapSize.maxY + 1); i >= (mapSize.minY - 2); i--)
    {
        printYAxis(i);
        for (int j = (mapSize.minX - 1); j <= (mapSize.maxX + 1); j++)
        {
            // If  minimum IdxRange != 0, make adjustment when accessing the current coordinates
            int xCoordinate = calculateCoordinate(j, mapSize.minX);
            int yCoordinate = calculateCoordinate(i, mapSize.minY);
            if (isXAxis(i))
            {
                printXAxis(j);
            }
            else if (isBorder(i, j))
            {
                printData("#");
            }
            else if (p2DArray[yCoordinate][xCoordinate] != -1)
            {
                int value = p2DArray[yCoordinate][xCoordinate];
                print2DArrayValue(value, userChoiceNumber);
            }
            else
            {
                printData(" ");
            }
        }
        cout << endl;
    }
}

void Map::printYAxis(int i)
{
    ((i >= mapSize.minY) && (i <= mapSize.maxY)) ? printData(to_string(i)) : printData(" ");
}

void Map::printData(string data)
{
    cout << right << setw(4) << data;
}

int Map::calculateCoordinate(int index, int minIdxrange)
{
    return (minIdxrange == 0) ? index : index + (0 - minIdxrange);
}

bool Map::isXAxis(int i)
{
    return (i == (mapSize.minY - 2));
}

void Map::printXAxis(int j)
{
    ((j == (mapSize.minX - 1)) || (j == mapSize.maxX + 1)) ? printData(" ") : printData(to_string(j));
}

bool Map::isBorder(int i, int j)
{
    return ((j == mapSize.minX - 1) || (j == mapSize.maxX + 1) || (i == mapSize.minY - 1) || (i == mapSize.maxY + 1));
}

void Map::print2DArrayValue(int value, int userChoiceNumber)
{
    if (userChoiceNumber == 4 || userChoiceNumber == 6)
    {
        string LMH_symbol(1, getLMH_Symbol(value));
        printData(LMH_symbol);
    }
    else if (userChoiceNumber == 3 || userChoiceNumber == 5)
    {
        printData(to_string(value / 10));
    }
    else
    {
        printData(to_string(value));
    }
}

char Map::getLMH_Symbol(int value)
{
    if (isWithinRange(0, 35, value))
    {
        return 'L';
    }
    else if (isWithinRange(35, 65, value))
    {
        return 'M';
    }
    else
    {
        return 'H';
    }
}

bool Map::isWithinRange(int min, int max, int value)
{
    return ((min <= value) && (value < max));
}