//  MovieBookingSystem.cpp
//  CS201 Homework 3: MovieBookingSystemLinkedList
//  May 2021
//  Can Avşar
//  21902111

#include <stdio.h>
#include <iostream>
#include "MovieBookingSystem.h"
#include "Movie.h"
#include <ctime>

using namespace std;


MovieBookingSystem::MovieBookingSystem()
{
    uniqueResCode = 1;
}

MovieBookingSystem::~MovieBookingSystem()
{
}

void MovieBookingSystem::addMovie(const long movieID, const int audienceRadius)
{
    string movieTime;
    movieTime = ctime(&movieID);
    movieTime[movieTime.length()-1] = ' '; // to eliminate \n
    
    int movieIndex = movies.getIndex(movieID);
   
    if(audienceRadius < 0 || audienceRadius > 7)
    {
        cout << "Radius is invalid, it should be in range [0,7]" << endl;
        return;
    }
    
    if(movieIndex > 0)
    {
        cout << "Movie at " << movieTime << "already exists" << endl;
        return;
    }
    
    Movie movie(movieID, audienceRadius);
    movies.insert(movies.getLength()+1, movie);
    
    
    cout << "Movie at " << movieTime << "has been added" << endl;
}

void MovieBookingSystem::cancelMovie(const long movieID)
{
    int index = movies.getIndex(movieID);
    
    string movieTime;
    movieTime = ctime(&movieID);
    movieTime[movieTime.length()-1] = ' ';
    
    
    if(!index)
    {
        cout << "Movie at " << movieTime << "does not exist" << endl;
        return;
    }
    
    movies.remove(index);
    
    cout << "Movie at " << movieTime << "has been canceled" << endl;

    
}

void MovieBookingSystem::showAllMovies() const
{
    if( movies.getLength() == 0)
    {
        cout << "No movie on show" << endl;
        return;
    }
    
    cout << "Movies on show:" << endl;
    
    Movie movie;
    long movieID;
    string movieTime;
    
    for(int i = 1; i <= movies.getLength(); i++)
    {
        movies.retrieve(i, movie);
        movieID = movie.getMovieID();
        movieTime = ctime(&movieID);
        movieTime[movieTime.length()-1] = ' ';
        cout << "Movie at " << movieTime << "(" << movie.getNumOfAvailableSeats() << " available seats)" << endl;
    }
    
}

void MovieBookingSystem::showMovie(const long movieID) const
{
    
    int index = movies.getIndex(movieID);

    string movieTime;
    movieTime = ctime(&movieID);
    movieTime[movieTime.length()-1] = ' ';
    

    if(!index)
    {
        cout << "No such movie exists." << endl;
        return;
    }

    
    Movie movie;
    movies.retrieve(index, movie);

    cout << "Movie at " << movieTime << " has " << movie.getNumOfAvailableSeats() << " available seats " << endl;
    
    movie.printSeatingPlan();
}

int MovieBookingSystem::makeReservation(const long movieID, const int row, const char col)
{
    int index = movies.getIndex(movieID);
    
    Movie movie;
    movies.retrieve(index, movie);
    
    string movieTime;
    movieTime = ctime(&movieID);
    movieTime[movieTime.length()-1] = ' ';
    
    int returnCode;
    
    returnCode = movie.reserveSeat(row, col);
    
    if(returnCode == -1)
    {
        cout << "Seat " << col << row << " is not occupiable in Movie " << movieTime << endl;
        return 0;
    }
    if(returnCode == 0)
    {
        cout << "Seat " << col << row << " is not available in Movie " << movieTime << endl;
        return 0;
    }
    else
    {
        movies.remove(index);
        movies.insert(index, movie);
        
        reservationCodes.insert(reservationCodes.getLength()+1, uniqueResCode);
        
        reservationCodes.setResDetails(reservationCodes.getLength(), movieID, row, col);
                
        cout << "Reservation done for " << col << row << " in Movie at " << movieTime << endl;
        
        uniqueResCode++;
        return uniqueResCode-1;
    }
}
void MovieBookingSystem::cancelReservations(ReservationList resCode)
{
    int reservationCode;
    int resIndex;
    int code, row, col;
    long movieID;
    string movieTime;
    int size = resCode.getLength();
    Movie movie;
    
    for (int i = 1; i <= size; i++)
    {
        
        resCode.retrieve(i, reservationCode);
        resIndex = reservationCodes.getIndex(reservationCode);
        
        if(resIndex < 1)
        {
            cout << "Some reservation codes do not exist. Cancelation is failed" << endl;
            return;
        }
    }
    
    for (int i = size; i >= 1; i--)
    {
        resCode.retrieve(i, reservationCode);
        
        resIndex = reservationCodes.getIndex(reservationCode);
        
        reservationCodes.getResDetails(resIndex, code, movieID, row, col);
        
        int movieIndex = movies.getIndex(movieID);
        
        movies.retrieve(movieIndex, movie);
        
        movie.freeSeat(row, col);

        reservationCodes.remove(resIndex);
        
        movieTime = ctime(&movieID);
        movieTime[movieTime.length()-1] = ' ';
        
        cout << "Reservation on Code " << reservationCode << " is canceled: Seat " << char(col)  << row << " in Movie at " << movieTime << endl;
    }
}

void MovieBookingSystem::showReservation(const int resCode) const
{
    
    int resIndex = reservationCodes.getIndex(resCode);

    long movieID;
    int code, row, col;
    string movieTime;
        
    if(resIndex < 1)
    {
        cout << "No reservations with Code " << resCode << endl;
    }
    else
    {
        
        reservationCodes.getResDetails(resIndex, code, movieID, row, col);
        

        movieTime = ctime(&movieID);
        movieTime[movieTime.length()-1] = ' ';
        
        cout << "Reservation with Code " << code << ": Seat " << char(col) << row << " in Movie at " << movieTime;
    }
    
}

