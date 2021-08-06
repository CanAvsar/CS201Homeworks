//  MovieList.cpp
//  CS201 Homework 3: MovieBookingSystemLinkedList
//  May 2021
//  Can Avşar
//  21902111

#include <stdio.h>
#include "MovieList.h"

MovieList::MovieList(): size(0), head(NULL)
{
}

MovieList::MovieList(const MovieList& aList): size(aList.size)
{
    if (aList.head == NULL)
        head = NULL;  // original list is empty
    else {
        // copy first node
        head = new MovieNode;
        head->movie = aList.head->movie;
        // copy rest of list
        MovieNode *newPtr = head;  // new list ptr
        
        for (MovieNode *origPtr = aList.head->next;
             origPtr != NULL;
             origPtr = origPtr->next){
            newPtr->next = new MovieNode;
            newPtr = newPtr->next;
            newPtr->movie = origPtr->movie;
        }
        newPtr->next = NULL;
    }
}

MovieList::~MovieList()
{
}

bool MovieList::isEmpty() const
{
    return size == 0;
}

int MovieList::getLength() const
{
    return size;
}

bool MovieList::retrieve(int index, Movie& movie) const
{
    if ((index < 1) || (index > getLength()))
        return false;
    
    // get pointer to node, then data in node
    MovieNode *cur = find(index);
    movie = cur->movie;
    
    return true;
}

bool MovieList::insert(int index, Movie& movie)
{
    int newLength = getLength() + 1;
    
    if ((index < 1) || (index > newLength))
        return false;
    
    MovieNode *newPtr = new MovieNode;
    size = newLength;
    newPtr->movie = movie;
    
    if (index == 1)
    {
        newPtr->next = head;
        head = newPtr;
    }
    else
    {
        MovieNode *prev = find(index-1);
        newPtr->next = prev->next;
        prev->next = newPtr;
    }
    return true;
}

bool MovieList::remove(int index)
{
    
    MovieNode *cur;
    
    if ((index < 1) || (index > getLength()))
        return false;
    
    --size;
    if (index == 1){
        cur = head;
        head = head->next;
    }
    else
    {
        MovieNode *prev = find(index-1);
        cur = prev->next;
        prev->next = cur->next;
    }
    cur->next = NULL;
    delete cur;
    cur = NULL;
    
    return true;
}

int MovieList::getIndex(long MovieID) const
{
    MovieNode *cur = head;

    for (int i = 1; i <= getLength(); i++)
    {
        if(cur->movie.getMovieID() == MovieID)
        {
            return i;
        }
        
        cur = cur->next;

    }

    return 0;
}

MovieList::MovieNode *MovieList::find(int index) const
{
    if ( (index < 1) || (index > getLength()) )
        return NULL;
    
    else{ // count from the beginning of the list
        MovieNode *cur = head;
        for (int skip = 1; skip < index; ++skip)
        cur = cur->next;
        return cur;
    }
}
