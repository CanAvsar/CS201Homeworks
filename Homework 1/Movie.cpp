//  Movie.cpp
//  CS201 Homework 1: MovieBookingSystem
//  March 2021
//  Can Avşar
//  21902111

#include <iostream>
#include "Movie.h"
#include "MovieBookingSystem.h"

using namespace std;


Movie::Movie()
{
    _movieID = 0;
    _audienceRadius = 0;
    _numOfOccupiableRows = 0;
    _numOfOccupiableCols = 0;
    _numOfAvailableSeats = 0;
}

Movie::Movie(long movieID, int audienceRadius)
{
    _movieID = movieID;
    _audienceRadius = audienceRadius;
    _numOfOccupiableRows = 0;
    _numOfOccupiableCols = 0;
    _numOfAvailableSeats = 0;

    createSeats();
}

Movie::~Movie()
{
    
}

void Movie::createSeats()
{
    int maxNumOfRow = MovieBookingSystem::numOfRow;
    int maxNumOfCol = MovieBookingSystem::numOfColumn;
    
    if(_audienceRadius)
    {
        _numOfOccupiableRows = ((int)((maxNumOfRow-1)/(_audienceRadius+1)))+1;
        _numOfOccupiableCols = ((int)((maxNumOfCol-1)/(_audienceRadius+1)))+1;
    }
    else
    {
        _numOfOccupiableRows = maxNumOfRow;
        _numOfOccupiableCols = maxNumOfCol;
    }
    
    _seats = new int*[_numOfOccupiableRows];
    
    for ( int i = 0; i < _numOfOccupiableRows; i++ )
    {
        _seats[i] = new int[_numOfOccupiableCols];
    }
    
    for (int i = 0; i < _numOfOccupiableRows; i++)
    {
        for (int j = 0; j < _numOfOccupiableCols; j++)
        {
            _seats[i][j] = 0;
        }
    }
    
    //_numOfAvailableSeats = (_numOfOccupiableRows * _numOfOccupiableCols);
}

long Movie::getMovieID()
{
    return _movieID;
}

int Movie::getNumOfAvailableSeats()
{
    for (int i = 0; i < _numOfOccupiableRows; i++)
    {
        for (int j = 0; j < _numOfOccupiableCols; j++)
        {
            if(_seats[i][j] == 0)
                _numOfAvailableSeats++;
        }
    }

    return _numOfAvailableSeats;
}

int Movie::getAudienceRadius()
{
    return _audienceRadius;
}

int Movie::reserveSeat(int row, char col)
{
    
    int colNo;
    int rowNo;
    int colNoToCheck;
    
    colNoToCheck = (((int)(col))-64);
    
    if(((row-1) % (_audienceRadius+1) != 0) || ((colNoToCheck-1) % (_audienceRadius+1) != 0))
    {
        return -1; // Not occupiable
    }
    else
    {
        rowNo = (row-1)/(_audienceRadius+1);
        colNo = ((((int)(col))-65)/(_audienceRadius+1));
        
        if(_seats[rowNo][colNo] == 1)
        {
            return 0; //Not available
        }
        else
        {
            _seats[rowNo][colNo] = 1;
            return 1; //Ocupiable, available and reserved
        }
    }
}


int Movie::freeSeat(int row, char col)
{
    
    int colNo;
    int rowNo;
    int colNoToCheck;
    
    colNoToCheck = (((int)(col))-64);
    
    if(((row-1) % (_audienceRadius+1) != 0) || ((colNoToCheck-1) % (_audienceRadius+1) != 0))
    {
        return -1; // Not occupiable
    }
    else
    {
        rowNo = (row-1)/(_audienceRadius+1);
        colNo = ((((int)(col))-65)/(_audienceRadius+1));
        
        if(_seats[rowNo][colNo] == 0)
        {
            return 0; //Is already free
        }
        else
        {
            _seats[rowNo][colNo] = 0;
            return 1; //Freed
        }
    }
}

void Movie::printSeatingPlan()
{
    int count;
    int printNo;
    cout << "   ";
    
    for (int i = 0; i < _numOfOccupiableCols; i++)
    {
        count = (_audienceRadius+1)*i + 65;
        cout << char(count) << " ";
    }
    
    cout << endl;
    
    for (int i = 0; i < _numOfOccupiableRows; i++ )
    {
        printNo = (_audienceRadius+1)*i + 1;
        
        if(printNo < 10)
        {
            cout << " " << printNo << " " ;
        }
        else
        {
            cout << printNo << " ";
        }
        
        for(int j = 0; j < _numOfOccupiableCols; j++ )
        {
            if(_seats[i][j])
                cout << "o ";
            else
                cout << "x ";
        }
        cout << endl;

    }
}

