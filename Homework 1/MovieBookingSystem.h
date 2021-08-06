//  MovieBookingSystem.h
//  CS201 Homework 1: MovieBookingSystem
//  March 2021
//  Can Avşar
//  21902111

#ifndef MovieBookingSystem_h
#define MovieBookingSystem_h

#include "Movie.h"
#include "Reservation.h"




class MovieBookingSystem
{
public:
    const static int numOfRow = 30;
    const static int numOfColumn = 26;
    MovieBookingSystem();
    ~MovieBookingSystem();
    
    void    addMovie(const long movieID, const int audienceRadius);
    void    cancelMovie(const long movieID);
    void    showAllMovies();
    void    showMovie(const long movieID);
    int     makeReservation(const long movieID, const int row, const char col);
    void    cancelReservations(const int numRes, const int* resCode);
    void    showReservation(const int resCode);
    
    int     findMovie(const long movieID);
    int     findReservation(int resCode);
    void    cancelReservation(int resCode, int callWithOutput);



    
private:
    
    Movie*          _movies;
    Reservation*    _reservations;
    int             _numOfMovies;
    int             _numOfReservations;
    int             _resCodeGenerator;
};



#endif /* MovieBookingSystem_h */
