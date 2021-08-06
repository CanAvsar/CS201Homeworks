//  MovieBookingSystem.h
//  CS201 Homework 3: MovieBookingSystemLinkedList
//  May 2021
//  Can Avşar
//  21902111

#ifndef MovieBookingSystem_h
#define MovieBookingSystem_h

#include "ReservationList.h"
#include "MovieList.h"


class MovieBookingSystem
{
public:
    const static int numOfRow = 30;
    const static int numOfColumn = 26;
    MovieBookingSystem();
    ~MovieBookingSystem();
    
    
    void addMovie( const long movieID, const int audienceRadius );
    void cancelMovie( const long movieID);
    void showAllMovies() const;
    void showMovie( const long movieID) const;
    int makeReservation( const long movieID, const int row, const char col);
    void cancelReservations(ReservationList resCode);
    void showReservation( const int resCode) const;

private:
    MovieList movies;
    ReservationList reservationCodes;
    int uniqueResCode;


};

#endif
