#ifndef TWO_D_ARRAY_H
#define TWO_D_ARRAY_H

namespace Two_D_Array
{
int **allocate2DArray(int rows, int cols);
void initialize2DArray(int **p2DArray, int rows, int cols);
void assignValuesTo2DArray(int **p2DArray, int userChoiceNumber);
void assign_CityLocation_Values(int **p2DArray);
void assign_CloudCover_Values(int **p2DArray);
void assign_AtmosphericPressure_Values(int **p2DArray);
int calculateCoordinate(int coordinate, int minIdxrange);
void delete2DArray(int **p2DArray, int rows, int cols);
}
#endif