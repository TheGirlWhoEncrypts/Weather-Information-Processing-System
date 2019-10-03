// g++ -std=c++11 main.cpp readFile.cpp structs.cpp map.cpp twoDimensionalArray.cpp summaryReport.cpp -o main.exe

#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>

#include "readFile.h"
#include "structs.h"
#include "map.h"
#include "summaryReport.h"

using namespace std;

/* ------------------------------------ Global Constant Variables ------------------------------------ */
const string DIVIDER = "-----------------------------------------------------------\n";
const string STUDENT_INFORMATION[4] = {
    "Student ID", ": 6278905", "Stduent Name", ": Yap Yuan Xin"};

const string OPTIONS[] = {
    "1)", "Read in and process a configuration file",
    "2)", "Display city map",
    "3)", "Display cloud coverage map (cloudiness index)",
    "4)", "Display cloud coverage map (LMH symbols)",
    "5)", "Display atmospheric pressure map (pressure index)",
    "6)", "Display atmospheric pressure map (LMH symbols)",
    "7)", "Show weather forecast summary report",
    "8)", "Quit"};

/* --------------------------------------- Function Definitions --------------------------------------- */
void executeWeatherInformationProcessingSystem();

void printMainMenu();
void printStringArray(const string arrayName[], int size, int width);
void setWidth(string str, int width);

int getUserChoiceInput();
bool integerValidation(int userInput);

void printOption(int userChoiceInput);

void processUserChoiceInput(int userChoiceInput, bool &isQuit);
void executeUserChoiceInput(int choiceNumber);
void promptUserToPressEnterToContinue();

/* ------------------------------------------------------------------------------------------------ */
int main()
{
    executeWeatherInformationProcessingSystem();
}

void executeWeatherInformationProcessingSystem()
{
    bool isQuit = false;
    do
    {
        printMainMenu();
        int userChoiceInput = getUserChoiceInput();
        printOption(userChoiceInput);
        processUserChoiceInput(userChoiceInput, isQuit);

    } while (!isQuit);
}

void printMainMenu()
{
    printStringArray(STUDENT_INFORMATION, 4, 15);
    cout << DIVIDER << "Welcome to Weather Information Processing System!\n"
         << endl;
    printStringArray(OPTIONS, sizeof(OPTIONS) / sizeof(string), 7);
}

void printStringArray(const string arrayName[], int size, int width)
{
    for (int i = 0; i < size; i++)
    {
        if (i % 2 == 0)
        {
            setWidth(arrayName[i], width);
        }
        else
        {
            cout << arrayName[i] << endl;
        }
    }
}

void setWidth(string str, int width)
{
    cout << left << setw(width) << str;
}

int getUserChoiceInput()
{
    int validatedInput = -1, userInput;
    bool isInteger = false;
    do
    {
        cout << "\nPlease enter your choice : ";
        cin >> userInput;
        isInteger = integerValidation(userInput);
    } while (!isInteger);

    validatedInput = userInput;
    return validatedInput;
}

bool integerValidation(int userInput)
{
    bool isInteger = false;
    if (!isdigit(userInput) && !(userInput >= 1 && userInput <= 8))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "ERROR : Invalid Input" << endl;
    }
    else
    {
        isInteger = true;
    }
    return isInteger;
}

void printOption(int userChoiceInput)
{
    cout << "\n[" << OPTIONS[(userChoiceInput * 2) - 1] << "]" << endl;
    if (userChoiceInput != 1)
    {
        cout << "\n";
    }
}

void processUserChoiceInput(int userChoiceInput, bool &isQuit)
{
    if (userChoiceInput == 8)
    {
        isQuit = true;
        cityLocations_Vector.clear();
        cloudCovers_Vector.clear();
        atmosphericPressures_Vector.clear();
    }
    else
    {
        executeUserChoiceInput(userChoiceInput);
        if (userChoiceInput >= 2 && userChoiceInput <= 7)
        {
            promptUserToPressEnterToContinue();
        }
    }
}

void executeUserChoiceInput(int choiceNumber)
{
    if (choiceNumber == 1)
    {
        ReadFile::readAndProcessConfigurationFile();
    }
    else if (choiceNumber >= 2 && choiceNumber <= 6)
    {
        Map::displayMap(choiceNumber);
    }
    else
    {
        cout << "Weather Forecast Summary Report\n"
             << DIVIDER << endl;

        SummaryReport::displayWeatherForecastSummaryReport();
    }
}

void promptUserToPressEnterToContinue()
{
    cin.ignore(1000, '\n');
    string userInput = "";
    do
    {
        cout << "\nPress <enter> to go back to main menu ...";
        getline(cin, userInput);
    } while (userInput.length() != 0);
    cout << endl;
}