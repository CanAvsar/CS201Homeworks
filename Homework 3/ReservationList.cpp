//  ReservationList.cpp
//  CS201 Homework 3: MovieBookingSystemLinkedList
//  May 2021
//  Can Avşar
//  21902111

#include <stdio.h>
#include "ReservationList.h"

ReservationList::ReservationList(): size(0), head(NULL)
{
}

ReservationList::ReservationList(const ReservationList& aList): size(aList.size)
{
    if (aList.head == NULL)
        head = NULL;  // original list is empty
    else {
        // copy first node
        head = new ReservationNode;
        head->Code = aList.head->Code;
        // copy rest of list
        ReservationNode *newPtr = head;  // new list ptr
        
        for (ReservationNode *origPtr = aList.head->next;
             origPtr != NULL;
             origPtr = origPtr->next){
            newPtr->next = new ReservationNode;
            newPtr = newPtr->next;
            newPtr->Code = origPtr->Code;
        }
        newPtr->next = NULL;
    }
}

ReservationList::~ReservationList()
{
}

bool ReservationList::isEmpty() const
{
    return size == 0;
}

int ReservationList::getLength() const
{
    return size;
}

bool ReservationList::retrieve(int index, int& resCode) const
{
    if ((index < 1) || (index > getLength()))
        return false;
    
    // get pointer to node, then data in node
    ReservationNode *cur = find(index);
    resCode = cur->Code;
    
    return true;
}

bool ReservationList::insert(int index, int resCode)
{
    int newLength = getLength() + 1;
    
    if ((index < 1) || (index > newLength))
        return false;
    
    ReservationNode *newPtr = new ReservationNode;
    size = newLength;
    newPtr->Code = resCode;
    
    if (index == 1)
    {
        newPtr->next = head;
        head = newPtr;
    }
    else
    {
        ReservationNode *prev = find(index-1);
        newPtr->next = prev->next;
        prev->next = newPtr;
    }
    
    return true;
}

bool ReservationList::remove(int index)
{
    
    ReservationNode *cur;
    
    if ((index < 1) || (index > getLength()))
        return false;
    
    --size;
    if (index == 1){
        cur = head;
        head = head->next;
    }
    else
    {
        ReservationNode *prev = find(index-1);
        cur = prev->next;
        prev->next = cur->next;
    }
    cur->next = NULL;
    delete cur;
    cur = NULL;
    
    return true;
}

bool ReservationList::getResDetails(int index, int& resCode, long& movieID, int& row, int& col) const
{
    if ((index < 1) || (index > getLength()))
        return false;
    
    // get pointer to node, then data in node
    ReservationNode *cur = find(index);
    resCode = cur->Code;
    movieID = cur->movieID;
    row = cur->row;
    col = cur->col;
    
    return true;
}

bool ReservationList::setResDetails(int index, long movieID, int row, int col)
{
    if ((index < 1) || (index > getLength()))
        return false;
    
    // get pointer to node, then data in node
    ReservationNode *cur = find(index);
    cur->movieID = movieID;
    cur->row = row;
    cur->col = col;
    
    return true;
}


int ReservationList::getIndex(int resCode) const
{
    ReservationNode *cur = head;

    for (int i = 1; i <= getLength(); i++)
    {
        if(cur->Code == resCode)
        {
            return i;
        }
        
        cur = cur->next;

    }

    return 0;
}


ReservationList::ReservationNode *ReservationList::find(int index) const
{
    if ( (index < 1) || (index > getLength()) )
        return NULL;
    
    else{ // count from the beginning of the list
        ReservationNode *cur = head;
        for (int skip = 1; skip < index; ++skip)
        cur = cur->next;
        return cur;
    }
}

