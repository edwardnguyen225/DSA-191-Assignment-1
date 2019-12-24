/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "dbLib.h"

#define arrMAX 10000

/* TODO: You can implement methods, functions that support your data structures here.
 * */
string extract(string &str, char beg, char end)
{
    size_t begPos;
    if ((begPos = str.find(beg)) != string::npos)
    {
        size_t endPos;
        if ((endPos = str.find(end, begPos)) != string::npos)
        {
            string result = str.substr(begPos + 1, endPos - begPos - 1);
            str.erase(begPos, endPos - begPos + 1);
            return result;
        }
    }

    return string();
}

void RemoveChar(string &str, char c)
{
    string result;
    for (size_t i = 0; i < str.size(); i++)
    {
        char currentChar = str[i];
        if (currentChar != c)
            result += currentChar;
    }
    str = result;
}

void removeExtraSpaces(string &str)
{
    int len = str.length();
    while (str[0] == ' ')
    {
        str.erase(0, 1);
        len--;
    }

    while (str[len - 1] == ' ')
    {
        str.pop_back();
        len--;
    }

    for (int i = 1; i < len - 1; i++)
    {
        if (str[i] == ' ' && str[i + 1] == ' ')
        {
            str.erase(i, 1);
            len--;
            i--;
        }
    }
}

int string2int(string str)
{
    if (str == "")
        return -1;
    return stoi(str);
}

void LoadData(void *&pData)
{
    TDataset *_pData = new TDataset();
    LoadLines(_pData);
    LoadCities(_pData);
    LoadStations(_pData);
    LoadStationLines(_pData);
    LoadTracks(_pData);
    pData = _pData;
}

void ReleaseData(void *&pData)
{
}

void LoadLines(TDataset *&pData)
{
    ifstream fileIn("lines.csv");

    if (!fileIn.is_open())
        cout << "ERROR: could not open file" << endl;

    int commaCount = 0;
    const int numOfCommas = 6;
    string tmp;

    TLine pLine;

    getline(fileIn, tmp);

    while (!fileIn.eof())
    {
        switch (commaCount)
        {
        case 0:
            getline(fileIn, tmp, ',');
            if (tmp == "")
                break;
            pLine.id = string2int(tmp);
            pData->lineList->setIdMax(pLine.id);
            break;

        case 1:
            getline(fileIn, tmp, ',');
            pLine.cityId = string2int(tmp);
            break;

        case 2:
            getline(fileIn, pLine.name, ',');
            break;

        default:
            if (commaCount < numOfCommas)
                getline(fileIn, tmp, ',');
            else
                getline(fileIn, tmp, '\n');
            break;
        }
        commaCount++;
        if (commaCount == numOfCommas + 1)
        {
            pData->lineList->push_back(pLine);
            commaCount = 0;
        }
    }
}

void LoadCities(TDataset *&pData)
{
    ifstream fileIn("cities.csv");

    if (!fileIn.is_open())
        cout << "ERROR: could not open file" << endl;

    int commaCount = 0;
    const int numOfCommas = 6;
    string tmp;

    TCity pCity;

    getline(fileIn, tmp);

    while (!fileIn.eof())
    {
        switch (commaCount)
        {
        case 0:
            getline(fileIn, tmp, ',');
            if (tmp == "")
                break;
            pCity.id = string2int(tmp);
            pData->cityList->setIdMax(pCity.id);
            break;

        case 2:
            getline(fileIn, pCity.name, ',');
            break;

            // default:
            //     if (commaCount < numOfCommas)
            //         getline(fileIn, tmp, ',');
            //     else
            //         getline(fileIn, tmp, '\n');
            //     break;
        }
        commaCount++;
        if (commaCount == 3)
        {
            pData->cityList->push_back(pCity);
            getline(fileIn, tmp);
            commaCount = 0;
        }
    }
}

void LoadStations(TDataset *&pData)
{
    ifstream fileIn("stations.csv");

    if (!fileIn.is_open())
        cout << "ERROR: could not open file" << endl;

    string tmp;

    TStation pStation;

    getline(fileIn, tmp);

    while (!fileIn.eof())
    {
        //id,name,geometry,buildstart,opening,closure,city_id
        getline(fileIn, tmp, ',');
        pStation.id = string2int(tmp);
        pData->stationList->setIdMax(pStation.id);
        if (pStation.id != -1)
        {
            getline(fileIn, pStation.name, ',');
            if (pStation.name.substr(0, 1) == "\"" && pStation.name.back() != '\"')
            {
                getline(fileIn, tmp, ',');
                pStation.name += "," + tmp;
            }
            RemoveChar(pStation.name, '"');

            getline(fileIn, pStation.geometry, ',');

            getline(fileIn, tmp, ',');
            pStation.buildstart = string2int(tmp);

            getline(fileIn, tmp, ',');
            pStation.opening = string2int(tmp);

            getline(fileIn, tmp, ',');
            pStation.closure = string2int(tmp);

            getline(fileIn, tmp);
            pStation.cityId = string2int(tmp);

            pData->stationList->push_back(pStation);
        }
    }
}

void LoadStationLines(TDataset *&pData)
{
    ifstream fileIn("station_lines.csv");

    if (!fileIn.is_open())
        cout << "ERROR: could not open file" << endl;

    string tmp;

    TStationLine pStationLine;

    getline(fileIn, tmp);

    while (!fileIn.eof())
    {
        // id,station_id,line_id,city_id,created_at,updated_at
        getline(fileIn, tmp, ',');
        pStationLine.id = string2int(tmp);
        pData->stationLineList->setIdMax(pStationLine.id);
        if (pStationLine.id != -1)
        {
            getline(fileIn, tmp, ',');
            pStationLine.stationId = string2int(tmp);

            getline(fileIn, tmp, ',');
            pStationLine.lineId = string2int(tmp);

            getline(fileIn, tmp, ',');
            pStationLine.cityId = string2int(tmp);

            getline(fileIn, tmp);

            pData->stationLineList->push_back(pStationLine);
        }
    }
}

void LoadTracks(TDataset *&pData)
{
    ifstream fileIn("tracks.csv");

    if (!fileIn.is_open())
        cout << "ERROR: could not open file" << endl;

    int commaCount = 0;
    const int numOfCommas = 6;
    string tmp;

    TTrack pTrack;

    getline(fileIn, tmp);

    while (!fileIn.eof())
    {
        // id,geometry,buildstart,opening,closure,length,city_id
        switch (commaCount)
        {
        case 0:
            getline(fileIn, tmp, ',');
            if (tmp == "")
                break;
            pTrack.id = string2int(tmp);
            pData->trackList->setIdMax(pTrack.id);
            break;

        case 1:
            getline(fileIn, tmp, '\"');
            getline(fileIn, tmp, '\"'); // vì dữ liệu đầu vào là ,"Line(...)", ...
            pTrack.geometry = tmp;
            getline(fileIn, tmp, ',');
            break;

        case 6:
            getline(fileIn, tmp, '\n');
            pTrack.cityId = string2int(tmp);
            break;

        default:
            getline(fileIn, tmp, ',');
            break;
        }
        commaCount++;
        if (commaCount == numOfCommas + 1)
        {
            pData->trackList->push_back(pTrack);
            commaCount = 0;
        }
    }
}

L1Item<TCity> *findCityById(TDataset *pData, int id)
{
    L1Item<TCity> *pCity;
    bool isFound = false;
    pCity = pData->cityList->getItem(0);
    while (pCity != NULL)
    {
        if (pCity->data.id == id)
            return pCity;
        pCity = pCity->pNext;
    }
    return NULL;
}

L1Item<TCity> *findCityByName(TDataset *pData, string name)
{
    L1Item<TCity> *pCity;
    bool isFound = false;
    pCity = pData->cityList->getItem(0);
    while (pCity != NULL)
    {
        if (pCity->data.name == name)
            return pCity;
        pCity = pCity->pNext;
    }
    return NULL;
}

L1Item<TStation> *findStationById(TDataset *pData, int id)
{
    L1Item<TStation> *pStation;
    bool isFound = false;
    pStation = pData->stationList->getItem(0);
    while (pStation != NULL)
    {
        if (pStation->data.id == id)
            return pStation;
        pStation = pStation->pNext;
    }
    return NULL;
}

L1Item<TStation> *findStationByName(TDataset *pData, string name)
{
    L1Item<TStation> *pStation;
    bool isFound = false;
    pStation = pData->stationList->getItem(0);
    while (pStation != NULL)
    {
        if (pStation->data.name == name)
            return pStation;
        pStation = pStation->pNext;
    }
    return NULL;
}

L1Item<TTrack> *findTrackById(TDataset *pData, int id)
{
    L1Item<TTrack> *pTrack;
    bool isFound = false;
    pTrack = pData->trackList->getItem(0);
    while (pTrack != NULL)
    {
        if (pTrack->data.id == id)
            return pTrack;
        pTrack = pTrack->pNext;
    }
    return NULL;
}

L1Item<TLine> *findLineById(TDataset *pData, int id)
{
    L1Item<TLine> *pLine;
    bool isFound = false;
    pLine = pData->lineList->getItem(0);
    while (pLine != NULL)
    {
        if (pLine->data.id == id)
            return pLine;
        pLine = pLine->pNext;
    }
    return NULL;
}

int getCityIdByName(TDataset *pData, string name)
{
    L1Item<TCity> *pCity = findCityByName(pData, name);
    if (pCity != NULL)
        return pCity->data.id;

    return -1;
}

int getStationIdByName(TDataset *pData, string name)
{
    L1Item<TStation> *pStation = findStationByName(pData, name);
    if (pStation != NULL)
        return pStation->data.id;

    return -1;
}

int getPosOfStationInTrack(TDataset *pData, int stationId, int trackId)
{
    string tmp;
    L1Item<TTrack> *pTrack = findTrackById(pData, trackId);
    if (pTrack == NULL)
        return -1;
    L1Item<TStation> *pStation = findStationById(pData, stationId);
    if (pStation == NULL)
        return -1;
    string line = extract(pTrack->data.geometry, '(', ')'),
           point = extract(pStation->data.geometry, '(', ')');
    cout << point << endl;
    int index = 0, indexOfComma;
    bool endOfLine = false, isFound = false;
    while (!endOfLine)
    {
        indexOfComma = line.find(",");
        if (indexOfComma <= line.length())
        {
            tmp = line.substr(0, indexOfComma);
            line.erase(0, indexOfComma + 1);
        }
        else
        {
            tmp = line;
            endOfLine = true;
        }
        if (tmp == point)
            return index;
        index++;
    }
    return -1;
}

int getNumOfLines(TDataset *pData)
{
    return pData->lineList->getSize();
}

int getNumOfLinesInCity(TDataset *pData, string cityName)
{
    L1Item<TLine> *pLine;

    int count = 0,
        cityId = getCityIdByName(pData, cityName);
    if (cityId == -1)
        return -1;
    pLine = pData->lineList->getItem(0);
    while (pLine != NULL)
    {
        if (pLine->data.cityId == cityId)
            ++count;
        pLine = pLine->pNext;
    }
    return count;
}

// csvDiscription = "name,geometry,buildstart,opening,closure"
int insertStation(TDataset *&pData, string csvDescription)
{
    TStation pStation;
    int indexOfComma, i = 0;
    string tmp;
    do
    {
        indexOfComma = csvDescription.find(',');
        tmp = csvDescription.substr(0, indexOfComma);
        RemoveChar(tmp, '"');
        switch (i)
        {
        case 0:
            pStation.name = tmp;
            break;

        case 1:
            pStation.geometry = tmp;
            break;

        case 2:
            pStation.buildstart = string2int(tmp);
            break;

        case 3:
            pStation.opening = string2int(tmp);
            break;

        case 4:
            pStation.closure = string2int(tmp);
            break;

        default:
            break;
        }
        i++;
        csvDescription.erase(0, indexOfComma + 1);
    } while (i <= 4);

    pStation.id = pData->stationList->getIdMax() + 1;
    pData->stationList->push_back(pStation);
    pData->stationList->setIdMax(pStation.id);

    return pStation.id;
}

int removeStation(TDataset *&pData, int stationId)
{
    L1Item<TStation> *pStation = findStationById(pData, stationId),
                     *tmpPStation = pData->stationList->getItem(0);
    if (pStation == NULL)
        return -1;

    // delete station_id in line
    L1Item<TStationLine> *pStationLine = pData->stationLineList->getItem(0);
    for (int i = 0; i < pData->stationLineList->getSize(); i++)
    {
        if (pStationLine->data.stationId == stationId)
        {
            pData->stationLineList->remove(i);
            i--;
        }
        pStationLine = pStationLine->pNext;
    }

    // delete station in track
    string stationPoint = extract(pStation->data.geometry, '(', ')');
    L1Item<TTrack> *pTrack = pData->trackList->getItem(0);
    int begPos, pointLength = stationPoint.length();
    for (int i = 0; i < pData->trackList->getSize(); i++)
    {
        if ((begPos = pTrack->data.geometry.find(stationPoint)) != string::npos)
        {
            string str = pTrack->data.geometry;
            if (str[begPos + pointLength] == ')')
                str.erase(begPos - 1, pointLength);
            else
                str.erase(begPos, pointLength + 1);
            pTrack->data.geometry = str;
        }
        pTrack = pTrack->pNext;
    }

    // delete station form station_list
    for (int i = 0; i < pData->stationList->getSize(); i++)
    {
        if (tmpPStation == pStation)
        {
            pData->stationList->remove(i);
            return 0;
        }

        tmpPStation = tmpPStation->pNext;
    }

    return -1;
}

int updateStation(TDataset *&pData, int stationId, string csvDescription)
{
    L1Item<TStation> *pStation = findStationById(pData, stationId);
    if (pStation == NULL)
        return -1;

    // get for later update in track
    string oldStationPoint = extract(pStation->data.geometry, '(', ')');

    // update station
    int indexOfComma, i = 0;
    string tmp;
    do
    {
        indexOfComma = csvDescription.find(',');
        tmp = csvDescription.substr(0, indexOfComma);
        RemoveChar(tmp, '"');
        switch (i)
        {
        case 0:
            pStation->data.name = tmp;
            break;

        case 1:
            pStation->data.geometry = tmp;
            break;

        case 2:
            pStation->data.buildstart = string2int(tmp);
            break;

        case 3:
            pStation->data.opening = string2int(tmp);
            break;

        case 4:
            pStation->data.closure = string2int(tmp);
            break;

        default:
            break;
        }
        i++;
        csvDescription.erase(0, indexOfComma + 1);
    } while (i <= 4);

    // update station in track
    string newStationPoint = extract(pStation->data.geometry, '(', ')');
    L1Item<TTrack> *pTrack = pData->trackList->getItem(0);
    int begPos, oldPointLength = oldStationPoint.length();
    for (int i = 0; i < pData->trackList->getSize(); i++)
    {
        if ((begPos = pTrack->data.geometry.find(oldStationPoint)) != string::npos)
        {
            if (pTrack->data.id == 3816)
                cout << "OLD\n" << pTrack->data.geometry << endl;
            pTrack->data.geometry.replace(begPos, oldPointLength, newStationPoint);
            if (pTrack->data.id == 3816)
                cout << "NEW\n" << pTrack->data.geometry << endl;
        }
        pTrack = pTrack->pNext;
    }

    return 0;
}

int insertStationToLine(TDataset *&pData, int stationId, int lineId, int pos)
{
    L1Item<TStation> *pStation = findStationById(pData, stationId);
    if (pStation == NULL)
        return -1;

    TStationLine stationLine;
    stationLine.id = pData->stationLineList->getIdMax() + 1;
    stationLine.stationId = stationId;
    stationLine.lineId = lineId;
    stationLine.cityId = pStation->data.cityId;

    L1Item<TStationLine> *pStationLine = pData->stationLineList->getItem(0);
    int currIndexStation = 0,
        *arrStationLine = new int[arrMAX]; // Save the position of station in stationLine List
    for (int i = 0; i < pData->stationLineList->getSize(); i++)
    {
        if (pStationLine->data.lineId == lineId)
        {
            if (pStationLine->data.stationId == stationLine.stationId)
                return -1;
            arrStationLine[currIndexStation] = i;
            currIndexStation++;
        }

        pStationLine = pStationLine->pNext;
    }

    if (pos < currIndexStation)
    {
        pData->stationLineList->insert(arrStationLine[pos], stationLine);
        return 0;
    }
    else if (pos == currIndexStation)
    {
        pData->stationLineList->push_back(stationLine);
        return 0;
    }

    return -1;
}

int removeStationFromLine(TDataset *&pData, int stationId, int lineId)
{
    L1Item<TStationLine> *pStationLine = pData->stationLineList->getItem(0);
    for (int i = 0; i < pData->stationLineList->getSize(); i++)
    {
        if (pStationLine->data.lineId == lineId && pStationLine->data.stationId == stationId)
        {
            pData->stationLineList->remove(i);
            return 0;
        }
        pStationLine = pStationLine->pNext;
    }

    return -1;
}

void *listStationsInCity(TDataset *pData, string cityName, int *&rs, int &numOfStation)
{
    L1Item<TStation> *pStation;
    int cityId = getCityIdByName(pData, cityName);
    numOfStation = 0;
    pStation = pData->stationList->getItem(0);
    for (int i = 0; i < pData->stationList->getSize(); i++)
    {
        if (pStation->data.cityId == cityId)
        {
            rs[numOfStation] = pStation->data.id;
            numOfStation++;
        }
        pStation = pStation->pNext;
    }

    // if (numOfStation == 0)
    // {
    //     rs[0] = -1;
    //     numOfStation = 1;
    // }
}

void *listLinesInCity(TDataset *pData, string cityName, int *&rs, int &numOfLines)
{
    L1Item<TLine> *pLine;
    int cityId = getCityIdByName(pData, cityName);
    numOfLines = 0;
    pLine = pData->lineList->getItem(0);
    for (int i = 0; i < pData->lineList->getSize(); i++)
    {
        if (pLine->data.cityId == cityId)
        {
            rs[numOfLines] = pLine->data.id;
            numOfLines++;
        }
        pLine = pLine->pNext;
    }

    // if (numOfLines == 0)
    // {
    //     rs[0] = -1;
    //     numOfLines = 1;
    // }
}

void *listStationsInLine(TDataset *pData, int lineId, int *&rs, int &numOfStation)
{
    L1Item<TStationLine> *pStationLine;
    numOfStation = 0;
    pStationLine = pData->stationLineList->getItem(0);
    for (int i = 0; i < pData->stationLineList->getSize(); i++)
    {
        if (pStationLine->data.lineId == lineId)
        {
            rs[numOfStation] = pStationLine->data.stationId;
            numOfStation++;
        }
        pStationLine = pStationLine->pNext;
    }

    // if (numOfStation == 0)
    // {
    //     rs[0] = -1;
    //     numOfStation = 1;
    // }
}
