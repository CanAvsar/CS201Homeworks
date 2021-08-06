//  MovieList.h
//  CS201 Homework 3: MovieBookingSystemLinkedList
//  May 2021
//  Can Avşar
//  21902111

#ifndef MovieList_h
#define MovieList_h

#include "Movie.h"

class MovieList{
public:
    MovieList();
    MovieList( const MovieList& aList );
    ~MovieList();
    
    bool isEmpty() const;
    int getLength() const ;
    bool retrieve(int index, Movie& movie) const;
    bool insert(int index, Movie& movie);
    bool remove(int index);
    int getIndex(long MovieID) const;
    
    

private:
    struct MovieNode
    {
        Movie movie;
        MovieNode* next;

    };
    
    int size;
    MovieNode *head;
    MovieNode *find(int index) const;
    
};



#endif 
