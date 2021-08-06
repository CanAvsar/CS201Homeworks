//  Movie.h
//  CS201 Homework 3: MovieBookingSystemLinkedList
//  May 2021
//  Can Avşar
//  21902111

#ifndef Movie_h
#define Movie_h
#include "SeatList.h"


class Movie
{
public:
    
    
    Movie();
    Movie(long movieID, int audienceRadius);
    ~Movie();
    
    void    createSeats();
    long    getMovieID();
    int     getNumOfAvailableSeats();
    int     getAudienceRadius();
    void    printSeatingPlan();
    int     reserveSeat(int row, char col);
    void     freeSeat(int row, char col);
    void    printSeats();

    
private:
    
    long    _movieID;
    int     _audienceRadius;
    //int**   _seats;
    SeatList _seats;
    int     _numOfOccupiableRows;
    int     _numOfOccupiableCols;
    int     _numOfAvailableSeats;
    
};


#endif

