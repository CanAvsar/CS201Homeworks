//  Seat.cpp
//  CS201 Homework 3: MovieBookingSystemLinkedList
//  May 2021
//  Can Avşar
//  21902111

#include <stdio.h>
#include "Seat.h"

#include <iostream>

using namespace std;

Seat::Seat()
{
    
}

Seat::Seat(int row, int col)
{
    _row = row;
    _col = col;
    _occupied = false;
}

Seat::~Seat()
{
}

bool Seat::getIfOccupied()
{
    return _occupied;
}

void Seat::setOccupied(bool occupied)
{
    _occupied = occupied;
}

int Seat::getRowCol()
{
    
    return _col;
}

