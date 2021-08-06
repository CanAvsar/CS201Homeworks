//  Reservation.cpp
//  CS201 Homework 1: MovieBookingSystem
//  March 2021
//  Can Avşar
//  21902111

#include <stdio.h>
#include "Reservation.h"


Reservation::Reservation()
{
    _movieID = 0;
    _row = 0;
    _col = 0;
    _resCode = 0;
}

Reservation::Reservation(long movieID, int row, char col)
{
    _movieID = movieID;
    _row = row;
    _col = col;
    
    _resCode = 0;
}

Reservation::~Reservation()
{
}

void Reservation::setResCode(int resCode)
{
    _resCode = resCode;
}

int Reservation::getResCode()
{
    return _resCode;
}

int Reservation::getRowNo()
{
    return _row;
}

char Reservation::getColNo()
{
    return _col;
}

long Reservation::getResMovieID()
{
    return _movieID;
}





