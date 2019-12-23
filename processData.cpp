/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : processData.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : Implementation of main features in the assignment
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

//g++ -g main.cpp dbLib.cpp processData.cpp

#include "processData.h"
#include "dbLib.h"

#define arrMAX 10000

/* TODO: You can implement methods, functions that support your data structures here.
 * */
using namespace std;

void Initialization()
{
    // If you use global variables, please initialize them explicitly in this function.
}

void Finalization()
{
    // Release your data before exiting
}

void ProcessRequest(const char *pRequest, void *pData, void *&pOutput, int &N)
{
    // TODO: Implement this function for processing a request
    // NOTE: You can add other functions to support this main process.
    //       pData is a pointer to a data structure that manages the dataset
    //       pOutput is a pointer reference. It is set to nullptr and student must allocate data for it in order to save the required output
    //       N is the size of output, must be a non-negative number
    string tmpRequest = pRequest;
    removeExtraSpaces(tmpRequest);
    TDataset *_pData = (TDataset *)pData;

    /// CL
    /// Count the number of lines in the dataset.
    if (tmpRequest == "CL")
    {
        int *rs = new int;
        *rs = getNumOfLines(_pData);
        pOutput = (void *)rs;
        N = 1;
    }

    /// CL <city_name>
    /// Count the number of lines in the given city
    if (tmpRequest.substr(0, 3) == "CL ")
    {
        string cityName = tmpRequest.substr(3);
        int *rs = new int(getNumOfLinesInCity(_pData, cityName));
        pOutput = (void *)rs;
        N = 1;
    }

    /// LSC <city_name>
    /// List stations (station_id) of a city (given <city_name>).
    if (tmpRequest.substr(0, 4) == "LSC ")
    {
        string cityName = tmpRequest.substr(4);
        int *rs = new int[arrMAX], numOfStations;
        listStationsInCity(_pData, cityName, rs, numOfStations);
        pOutput = (void *)rs;
        N = numOfStations;
    }

    /// LLC <city_name>
    /// List lines (line_id) of a city (given <city_name>).
    if (tmpRequest.substr(0, 4) == "LLC ")
    {
        string cityName = tmpRequest.substr(4);
        int *rs = new int[arrMAX], numOfLines;
        listLinesInCity(_pData, cityName, rs, numOfLines);
        pOutput = (void *)rs;
        N = numOfLines;
    }

    /// LSL <line_id>
    /// List stations (station_id) of a line with <line_id>.
    if (tmpRequest.substr(0, 4) == "LSL ")
    {
        string strLineId = tmpRequest.substr(4);
        int lineId = string2int(strLineId), numOfLines,
            *rs = new int[arrMAX];
        listStationsInLine(_pData, lineId, rs, numOfLines);
        pOutput = (void *)rs;
        N = numOfLines;
    }

    /// FC <city_name>
    /// Find a city with the given name
    /// Return the first city_id if found, -1 otherwise.
    if (tmpRequest.substr(0, 3) == "FC ")
    {
        string cityName = tmpRequest.substr(3);
        int *rs = new int(getCityIdByName(_pData, cityName));
        pOutput = (void *)rs;
        N = 1;
    }

    ///FS <station_name>
    /// Find a station with the given name
    /// Return the first station_id if found, -1 otherwise
    if (tmpRequest.substr(0, 3) == "FS ")
    {
        string stationName = tmpRequest.substr(3);
        int *rs = new int(getStationIdByName(_pData, stationName));
        pOutput = (void *)rs;
        N = 1;
    }

    /// SLP <station_id> <track_id>
    /// Find the position of a station in a track.
    /// Return the index of that station if found, -1 otherwise.
    if (tmpRequest.substr(0, 43) == "SLP ")
    {
        int i = tmpRequest.find(' '), stationId, trackId;
        string tmp = extract(tmpRequest, ' ', ' ');
        stationId = string2int(tmp);
        tmp = tmpRequest.substr(tmpRequest.find(' ') + 1);
        trackId = string2int(tmp);

        int *rs = new int(getPosOfStationInTrack(_pData, stationId, trackId));
        pOutput = (void *)rs;
        N = 1;
    }

    /// IS <csv_description>
    /// Insert a station into the dataset.
    /// If this operation success, we have to receive station id as the return value.
    if (tmpRequest.substr(0, 3) == "IS ")
    {
        string csvDescription = tmpRequest.substr(3);
        int *rs = new int(insertStation(_pData, csvDescription));
        pOutput = (void *)rs;
        N = 1;
    }

    /// RS <station_id>
    /// Remove a station from the dataset.
    /// Return 0 if success, return -1 if the station does not exist or can not be removed.
    if (tmpRequest.substr(0, 3) == "RS ")
    {
        int stationId = string2int(tmpRequest.substr(3));
        int *rs = new int(removeStation(_pData, stationId));
        pOutput = (void *)rs;
        N = 1;
    }

    /// US <station_id> <csv_description>
    /// Update the information of a station with id <station_id>
    /// Return 0 if success, and -1 otherwise.
    if (tmpRequest.substr(0, 3) == "US ")
    {
        int stationId = string2int(extract(tmpRequest, ' ', ' '));
        string csvDescription = tmpRequest.substr(tmpRequest.find(' ') + 1);
        int *rs = new int(updateStation(_pData, stationId, csvDescription));
        pOutput = (void *)rs;
        N = 1;
    }

    /// ISL <station_id> <line_id> <p_i>
    /// Insert a station <station_id> to a line <line_id> at index <p_i>
    /// Return 0 if success, and -1 otherwise.
    if (tmpRequest.substr(0, 4) == "ISL ")
    {
        int stationId, lineId, pos;
        string tmp = extract(tmpRequest, ' ', ' ');
        stationId = string2int(tmp);
        tmp = extract(tmpRequest, ' ', ' ');
        lineId = string2int(tmp);
        tmp = tmpRequest.substr(tmpRequest.find(' ') + 1);
        pos = string2int(tmp);
        int *rs = new int(insertStationToLine(_pData, stationId, lineId, pos));
        pOutput = (void *)rs;
        N = 1;
    }

    /// RSL <station_id> <line_id>
    /// Remove a station <station_id> from a line <line_id>.
    /// Return 0 if success, and -1 otherwise.
    if (tmpRequest.substr(0, 4) == "RSL ")
    {
        int stationId = string2int(extract(tmpRequest, ' ', ' ')),
            lineId = string2int(tmpRequest.substr(tmpRequest.find(' ') + 1));
        int *rs = new int(removeStationFromLine(_pData, stationId, lineId));
        pOutput = (void *)rs;
        N = 1;
    }
}
