//  Movie.cpp
//  CS201 Homework 3: MovieBookingSystemLinkedList
//  May 2021
//  Can Avşar
//  21902111

#include <stdio.h>
#include <iostream>
#include "Movie.h"
#include "MovieBookingSystem.h"
#include "Seat.h"

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
    
    
    for (int i = 0; i < _numOfOccupiableRows; i++)
    {
        for (int j = 0; j < _numOfOccupiableCols; j++)
        {
            Seat seat(i, j);
            _seats.insert((_seats.getLength())+1, seat);
        }
    }
    
}

int Movie::getNumOfAvailableSeats()
{
    
    for (int i = 1; i <= _seats.getLength(); i++)
    {
        Seat seat;
        
        _seats.retrieve(i, seat);
        
        if(!(seat.getIfOccupied()))
        {
            _numOfAvailableSeats++;
        }
        
    }
    return _numOfAvailableSeats;
}

long Movie::getMovieID()
{
    return _movieID;
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
            Seat seat;
            
            _seats.retrieve(i*_numOfOccupiableCols+j+1, seat);
            
            if(seat.getIfOccupied())
                cout << "x ";
            else
                cout << "o ";
        }
        cout << endl;

    }
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
        
        int seatIndex = rowNo*_numOfOccupiableCols+colNo+1;
        
        Seat seat;
        
        _seats.retrieve(seatIndex, seat);
        
        
        if(seat.getIfOccupied())
        {
            return 0; //Not available
        }
        else
        {
            _seats.remove(seatIndex);
            seat.setOccupied(true);
            _seats.insert(seatIndex, seat);
            return 1; //Ocupiable, available and reserved
        }
        
    }
}

void Movie::freeSeat(int row, char col)
{
    
    int colNo;
    int rowNo;
    int colNoToCheck;
    
    colNoToCheck = (((int)(col))-64);
    
    rowNo = (row-1)/(_audienceRadius+1);
    colNo = ((((int)(col))-65)/(_audienceRadius+1));
    
    int seatIndex = rowNo*_numOfOccupiableCols+colNo+1;
    
    Seat seat;
    
    _seats.retrieve(seatIndex, seat);
    
    _seats.remove(seatIndex);
    seat.setOccupied(false);
    _seats.insert(seatIndex, seat);

}

