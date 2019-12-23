/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DBLIB_H
#define DSA191_A1_DBLIB_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>

#include "dsaLib.h"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */
struct TCity
{
    // The structure to store city information
public:
    int id;
    string name;
};

struct TStation
{
public:
    int id;
    string name;
    string geometry;
    int buildstart;
    int opening;
    int closure;
    int cityId;
};

struct TStationLine
{
public:
    int id;
    int stationId;
    int lineId;
    int cityId;
};

struct TLine
{
    // The structure to store line information
public:
    int id;
    int cityId;
    string name;
};

struct TTrack
{
    // The structure to store track information
public:
    int id;
    string geometry;
    int cityId;
};

class TDataset
{
    // This class can be a container that help you manage your tables
public:
    L1List<TCity> *cityList = new L1List<TCity>();
    L1List<TLine> *lineList = new L1List<TLine>();
    L1List<TStation> *stationList = new L1List<TStation>();
    L1List<TStationLine> *stationLineList = new L1List<TStationLine>();
    L1List<TTrack> *trackList = new L1List<TTrack>();
};

// Please add more or modify as needed
string extract(string &str, char beg, char end);
void removeExtraSpaces(string &str);
int string2int(string str);

void LoadData(void *&);
void ReleaseData(void *&);
void LoadCities(TDataset *&);
void LoadLines(TDataset *&);
void LoadStations(TDataset *&);
void LoadStationLines(TDataset *&);
void LoadTracks(TDataset *&);

L1Item<TCity> *findCityByName(TDataset *pData, string name);
L1Item<TStation> *findStationById(TDataset *pData, int id);

int getCityIdByName(TDataset *pData, string name);
int getStationIdByName(TDataset *pData, string name);
int getPosOfStationInTrack(TDataset *pData, int stationId, int trackId);

int insertStation(TDataset *&pData, string csvDescription);
int removeStation(TDataset *&pData, int stationId);
int updateStation(TDataset *&pData, int stationId, string csvDescription);

int insertStationToLine(TDataset *&pData, int stationId, int lineId, int pos);
int removeStationFromLine(TDataset *&pData, int stationId, int lineId);

int getNumOfLines(TDataset *pData);
int getNumOfLinesInCity(TDataset *pData, string cityName);
void *listStationsInCity(TDataset *pData, string cityName, int *&rs, int &numOfStation);
void *listLinesInCity(TDataset *pData, string cityName, int *&rs, int &numOfLines);
void *listStationsInLine(TDataset *pData, int lineId, int *&rs, int &numOfStation);

#endif //DSA191_A1_DBLIB_H
