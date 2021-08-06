//  Seat.h
//  CS201 Homework 3: MovieBookingSystemLinkedList
//  May 2021
//  Can Avşar
//  21902111

#ifndef Seat_h
#define Seat_h

#include <iostream>

using namespace std;

class Seat
{
public:
    
    
    Seat();
    Seat(int row, int col);
    ~Seat();
    
    bool getIfOccupied();
    void setOccupied(bool occupied);

    int getRowCol();

    
private:
    
    int _row;
    int _col;
    bool _occupied;
    
};


#endif

