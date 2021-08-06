//  SeatList.cpp
//  CS201 Homework 3: MovieBookingSystemLinkedList
//  May 2021
//  Can Avşar
//  21902111

#include <stdio.h>
#include "SeatList.h"

SeatList::SeatList(): size(0), head(NULL)
{
}

SeatList::SeatList(const SeatList& aList): size(aList.size)
{
    if (aList.head == NULL)
        head = NULL;  // original list is empty
    else {
        // copy first node
        head = new SeatNode;
        head->seat = aList.head->seat;
        // copy rest of list
        SeatNode *newPtr = head;  // new list ptr
        
        for (SeatNode *origPtr = aList.head->next;
             origPtr != NULL;
             origPtr = origPtr->next){
            newPtr->next = new SeatNode;
            newPtr = newPtr->next;
            newPtr->seat = origPtr->seat;
        }
        newPtr->next = NULL;
    }
}

SeatList::~SeatList()
{
}

bool SeatList::isEmpty() const
{
    return size == 0;
}

int SeatList::getLength() const
{
    return size;
}

bool SeatList::retrieve(int index, Seat& seat) const
{
    if ((index < 1) || (index > getLength()))
        return false;
    
    // get pointer to node, then data in node
    SeatNode *cur = find(index);
    seat = cur->seat;
    
    return true;
}

bool SeatList::insert(int index, Seat& seat)
{
    int newLength = getLength() + 1;
    
    if ((index < 1) || (index > newLength))
        return false;
    
    SeatNode *newPtr = new SeatNode;
    size = newLength;
    newPtr->seat = seat;
    
    if (index == 1)
    {
        newPtr->next = head;
        head = newPtr;
    }
    else
    {
        SeatNode *prev = find(index-1);
        newPtr->next = prev->next;
        prev->next = newPtr;
    }
    return true;
}

bool SeatList::remove(int index)
{
    
    SeatNode *cur;
    
    if ((index < 1) || (index > getLength()))
        return false;
    
    --size;
    if (index == 1){
        cur = head;
        head = head->next;
    }
    else
    {
        SeatNode *prev = find(index-1);
        cur = prev->next;
        prev->next = cur->next;
    }
    cur->next = NULL;
    delete cur;
    cur = NULL;
    
    return true;
}

SeatList::SeatNode *SeatList::find(int index) const
{
    int size = getLength();
    if ( (index < 1) || (index > size ))
        return NULL;
    
    else
    { // count from the beginning of the list
        SeatNode *cur = head;
        for (int skip = 1; skip < index; ++skip)
        cur = cur->next;
        return cur;
    }
}
