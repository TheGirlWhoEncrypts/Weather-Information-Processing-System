#ifndef MAP_H
#define MAP_H

#include <string>

namespace Map
{
void displayMap(int userChoiceNumber);
int calculateMapSize(int min, int max);

void mapFormatter(int **p2DArray, int noOfRows, int noOfCols, int userChoiceNumber);
void printYAxis(int i);
bool isXAxis(int i);
void printXAxis(int j);
bool isBorder(int i, int j);
void print2DArrayValue(int value, int userChoiceNumber);
void printData(std::string data);
int calculateCoordinate(int index, int minIdxrange);
void printYAxis(int i);
char getLMH_Symbol(int value);
bool isWithinRange(int min, int max, int value);
}

#endif
