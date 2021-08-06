//  Movie.h
//  CS201 Homework 1: MovieBookingSystem
//  March 2021
//  Can Avşar
//  21902111

#ifndef Movie_h
#define Movie_h

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
    int     freeSeat(int row, char col);
    
private:
    
    long    _movieID;
    int     _audienceRadius;
    int**   _seats;
    int     _numOfOccupiableRows;
    int     _numOfOccupiableCols;
    int     _numOfAvailableSeats;
    
};


#endif /* Movie_h */
