//  Reservation.h
//  CS201 Homework 1: MovieBookingSystem
//  March 2021
//  Can Avşar
//  21902111

#ifndef Reservation_h
#define Reservation_h

class Reservation
{
public:
    Reservation();
    Reservation(long movieID, int row, char col);
    ~Reservation();
    
    void    setResCode(int resCode);
    int     getResCode();
    int     getRowNo();
    char    getColNo();
    long    getResMovieID();




    
private:
    long    _movieID;
    int     _row;
    char    _col;
    int     _resCode;

};

#endif /* Reservation_h */
