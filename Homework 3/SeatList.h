//  SeatList.h
//  CS201 Homework 3: MovieBookingSystemLinkedList
//  May 2021
//  Can Avşar
//  21902111

#ifndef SeatList_h
#define SeatList_h

#include "Seat.h"



class SeatList{
public:
    SeatList();
    SeatList( const SeatList& aList );
    ~SeatList();
    
    bool isEmpty() const;
    int getLength() const;
    bool retrieve(int index, Seat& seat) const;
    bool insert(int index, Seat& seat);
    bool remove(int index);
    
    

private:
    struct SeatNode
    {
        Seat seat;
        SeatNode* next;
    };
    
    int size;
    SeatNode *head;
    SeatNode *find(int index) const;
    
};



#endif

