#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>

#include "readFile.h"
#include "structs.h"

using namespace std;

vector<string> filenames_Vector; // To store the list of filenames when reading config.txt

void ReadFile::readAndProcessConfigurationFile()
{
    string validatedConfigFilename = validateConfigFilename();
    storeConfigFileInformation(validatedConfigFilename);
}

string ReadFile::validateConfigFilename()
{
    string configFilename;
    bool isConfigFileOpen = false;
    do
    {
        string userInput;
        cout << "Please enter config filename : ";
        cin >> userInput;

        fstream inputConfigFile(userInput.c_str(), fstream::in);

        if (!inputConfigFile)
        {
            cerr << "Error opening : " << userInput << "\n"
                 << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            configFilename = userInput;
            isConfigFileOpen = true;
        }
        inputConfigFile.close();

    } while (!isConfigFileOpen);

    cout << endl;
    return configFilename;
}

void ReadFile::storeConfigFileInformation(string filename)
{
    fstream inputConfigFile(filename.c_str(), fstream::in);
    string readConfigLine;
    int storing_gridX_and_gridY_IdxRange_Count = 0; // To count the no.of times it has read the IdxRange of either gridX or gridY

    while (getline(inputConfigFile, readConfigLine))
    {
        size_t found_IdxRange = readConfigLine.find("Grid");
        size_t found_txt = readConfigLine.find(".txt");

        if (found_IdxRange != string::npos)
        {
            readIdxRange(readConfigLine, found_IdxRange, storing_gridX_and_gridY_IdxRange_Count);
        }
        if (storing_gridX_and_gridY_IdxRange_Count == 2) // To ensure it has read both gridX AND gridY, before proceeding to cout
        {
            cout << "\nStoring data from input file :" << endl;
            storing_gridX_and_gridY_IdxRange_Count = 0; // Reset
        }
        if (found_txt != string::npos)
        {
            cout << readConfigLine;
            filenames_Vector.push_back(readConfigLine);
            readTextFile(readConfigLine);
        }
    }
    cout << "\nAll records successfully stored. Going back to main menu ...\n"
         << endl;
    inputConfigFile.close();
    filenames_Vector.clear();      
}

void ReadFile::readIdxRange(string readConfigLine, size_t found_IdxRange, int &count)
{
    vector<string> resultVector = tokenizeString(readConfigLine, "=");

    cout << "Reading in " << resultVector[0] << " : " << resultVector[1];

    // To accommodate for negative values
    regex regexPattern("(-?[0-9]+)(?:-)(-?[0-9]+)");
    smatch rangeVector;
    regex_search(resultVector[1], rangeVector, regexPattern);

    if (resultVector[0] == "GridX_IdxRange")
    {
        mapSize.minX = stoi(rangeVector[1]);
        mapSize.maxX = stoi(rangeVector[2]);
        count++;
    }
    else
    {
        mapSize.minY = stoi(rangeVector[1]);
        mapSize.maxY = stoi(rangeVector[2]);
        count++;
    }
    cout << " ... done!" << endl;
}

void ReadFile::readTextFile(string textFileName)
{
    fstream inputTextFile(textFileName.c_str(), fstream::in);
    string data;

    if (!inputTextFile)
    {
        cerr << " ... error opening! " << endl;
        return;
    }

    while (getline(inputTextFile, data))
    {
        size_t found_hyphen = data.find("-");
        size_t found_comma = data.find(",");

        if ((found_hyphen != string::npos) && (found_comma != string::npos))
        {
            vector<string> dataVector = tokenizeString(data, "-");
            vector<string> coordinatesVector = tokenizeString(dataVector[0], ",");

            initialiseVectorMembers(textFileName, dataVector, coordinatesVector);
        }
    }
    cout << " ... done!" << endl;
}

void ReadFile::initialiseVectorMembers(string textFileName, const vector<string> &dataVector, const vector<string> &coordinatesVector)
{
    int xCoordinate = stoi(coordinatesVector[0].substr(1));
    int yCoordinate = stoi(coordinatesVector[1].substr(0, coordinatesVector[1].length() - 1));
    int integerValue = stoi(dataVector[1]);

    if (textFileName.compare(filenames_Vector[0]) == 0)
    {
        string cityName = dataVector[2];
        cityLocation = {xCoordinate, yCoordinate, integerValue, cityName};
        cityLocations_Vector.push_back(cityLocation);
    }
    else if (textFileName.compare(filenames_Vector[1]) == 0)
    {
        cloudCover = {xCoordinate, yCoordinate, integerValue};
        cloudCovers_Vector.push_back(cloudCover);
    }
    else
    {
        atmosphericPressure = {xCoordinate, yCoordinate, integerValue};
        atmosphericPressures_Vector.push_back(atmosphericPressure);
    }
}

vector<string> ReadFile::tokenizeString(string str, string delimiter)
{
    size_t pos = 0;
    string token;
    vector<string> result;

    while ((pos = str.find(delimiter)) != string::npos)
    {
        token = str.substr(0, pos);
        result.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    result.push_back(str);
    return result;
}