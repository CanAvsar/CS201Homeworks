//  MovieBookingSystem.cpp
//  CS201 Homework 1: MovieBookingSystem
//  March 2021
//  Can Avşar
//  21902111

#include <iostream>
#include <ctime>
#include "MovieBookingSystem.h"
#include "Movie.h"
#include "Reservation.h"

using namespace std;


MovieBookingSystem::MovieBookingSystem()
{
    _numOfMovies = 0;
    _numOfReservations = 0;
    _resCodeGenerator = 0;
    
    _movies = NULL;
    _reservations = NULL;
}

MovieBookingSystem::~MovieBookingSystem()
{
    if (_movies != NULL)
     delete[] _movies;
     
     if (_reservations != NULL)
     delete[] _reservations;
}

void MovieBookingSystem::addMovie(const long movieID, const int audienceRadius)
{
    string movieTime;
    movieTime = ctime(&movieID);
    movieTime[movieTime.length()-1] = ' '; // to eliminate \n
    
    if(audienceRadius < 0 || audienceRadius > 7)
    {
        cout << "Radius is invalid, it should be in range [0,7]" << endl;
        return;
    }
    
    if(findMovie(movieID) >= 0)
    {
        cout << "Movie at " << movieTime << "already exists" << endl;
        return;
    }
    
    Movie* tempMovies;
    Movie movie(movieID, audienceRadius);
    
    tempMovies = new Movie[_numOfMovies+1];
    
    for( int i = 0; i < _numOfMovies; i++)
    {
        tempMovies[i] = _movies[i];
    }
    
    tempMovies[_numOfMovies] = movie;
    
    delete[] _movies;
    
    _movies = tempMovies;
    
    _numOfMovies++;
    
    //delete[] tempMovies; //i tried to delete this but program didn't run well
    
    cout << "Movie at " << movieTime << "has been added" << endl;
}

void MovieBookingSystem::cancelMovie(const long movieID)
{
    string movieTime;
    movieTime = ctime(&movieID);
    movieTime[movieTime.length()-1] = ' ';
    
    int movieIndex = findMovie(movieID); // movieIndex which to be deleted
    
    if(movieIndex < 0)
    {
        cout << "Movie at " << movieTime << "does not exist" << endl;
        return;
    }
    
    // Cancel all reservations of a movie
    
    for(int i = 0; i < _numOfReservations; i++)
    {
        if(_reservations[i].getResMovieID() == movieID)
        {
            cancelReservation(_reservations[i].getResCode(), 0);
        }
    }
    
    
    Movie* tempMovies = new Movie[_numOfMovies-1];
    
    int j = 0;
    
    for (int i = 0; i < _numOfMovies; i++)
    {
        if(i != movieIndex)
        {
            tempMovies[j] = _movies[i];
            j++;
        }
    }
    
    
    delete[] _movies;
    
    _movies = tempMovies;
    
    _numOfMovies--;
    
    //delete[] tempMovies;
    
    
    cout << "Movie at " << movieTime << "has been canceled" << endl;
    
}

void MovieBookingSystem::showAllMovies()
{
    if( _numOfMovies == 0)
    {
        cout << "No movie on show" << endl;
        return;
    }
    
    cout << "Movies on show:" << endl;
    
    long movieID;
    string movieTime;
    
    Movie movie;
    
    for(int i = 0; i < _numOfMovies; i++)
    {
        movie = _movies[i];
        movieID = movie.getMovieID();
        movieTime = ctime(&movieID);
        movieTime[movieTime.length()-1] = ' ';
        cout << "Movie at " << movieTime << "(" << movie.getNumOfAvailableSeats() << " available seats)" << endl;
    }
    
}

void MovieBookingSystem::showMovie(const long movieID)
{
    string movieTime;
    movieTime = ctime(&movieID);
    movieTime[movieTime.length()-1] = ' ';
    
    if(findMovie(movieID) < 0)
    {
        cout << "No such movie exists." << endl;
        return;
    }
    
    Movie movie;
    movie = _movies[findMovie(movieID)];
    
    cout << "Movie at " << movieTime << " has " << movie.getNumOfAvailableSeats() << " available seats " << endl;
    
    movie.printSeatingPlan();
    
    
}

int MovieBookingSystem::makeReservation(const long movieID, const int row, const char col)
{
    Movie movie;
    movie = _movies[findMovie(movieID)];
    
    string movieTime;
    movieTime = ctime(&movieID);
    movieTime[movieTime.length()-1] = ' ';
    
    int returnCode;
    
    returnCode = movie.reserveSeat(row, col);
    
    if(returnCode == -1)
    {
        cout << "Seat " << col << row << " is not occupiable in Movie at " << movieTime << endl;
        return 0;
    }
    if(returnCode == 0)
    {
        cout << "Seat " << col << row << " is not available in Movie at " << movieTime << endl;
        return 0;
    }
    else
    {
        Reservation reservation(movieID, row, col);
        
        _resCodeGenerator++;
        
        reservation.setResCode(_resCodeGenerator);
        
        Reservation* tempReservations;
        
        tempReservations = new Reservation[_numOfReservations+1];
        
        for( int i = 0; i < _numOfReservations; i++)
        {
            tempReservations[i] = _reservations[i];
        }
        
        tempReservations[_numOfReservations] = reservation;
        
        delete[] _reservations;

        _reservations = tempReservations;
        
        _numOfReservations++;
            
        cout << "Reservation done for " << reservation.getColNo() << reservation.getRowNo() << " in Movie at " << movieTime << endl;
        
        return _resCodeGenerator;
    }
}

void MovieBookingSystem::cancelReservations(const int numRes, const int* resCode)
{
    int reservationCode;
    
    for (int i = 0; i < numRes; i++)
    {
        reservationCode = resCode[i];
        
        if(findReservation(reservationCode) < 0)
        {
            cout << "Some reservation codes do not exist. Cancelation is failed" << endl;
            return;
        }
    }
    
    for (int i = 0; i < numRes; i++)
    {
        reservationCode = resCode[i];
        cancelReservation(reservationCode, 1);
    }
    
}

void MovieBookingSystem::showReservation(const int resCode)
{
    int reservationIndex = findReservation(resCode);
    
    if(reservationIndex == -1)
    {
        cout << "No reservations with Code " << resCode << endl;
    }
    else
    {
        Movie movie;
        string movieTime;
        long movieID;
        
        movie = _movies[findMovie(_reservations[reservationIndex].getResMovieID())];
        movieID = movie.getMovieID();
        movieTime = ctime(&movieID);
        movieTime[movieTime.length()-1] = ' ';
        
        cout << "Reservation with Code " << resCode << ": Seat " << _reservations[reservationIndex].getColNo() <<
        _reservations[reservationIndex].getRowNo() << " in Movie at " << movieTime << endl;
    }
}

int MovieBookingSystem::findMovie(const long movieID)
{
    for(int i = 0; i < _numOfMovies; i++)
    {
        if(_movies[i].getMovieID() ==  movieID)
            return i;
    }
    return -1;
}

int MovieBookingSystem::findReservation(int resCode)
{
    for(int i = 0; i < _numOfReservations; i++)
    {
        if(_reservations[i].getResCode() ==  resCode)
            return i;
    }
    return -1;
}

void MovieBookingSystem::cancelReservation(int resCode, int callWithOutput)
{
    Movie movie;
    string movieTime;
    long movieID;
    
    int reservationIndex = findReservation(resCode); // reservationIndex which to be deleted
    
    movie = _movies[findMovie(_reservations[reservationIndex].getResMovieID())];
    movieID = movie.getMovieID();
    movieTime = ctime(&movieID);
    movieTime[movieTime.length()-1] = ' ';

    if(callWithOutput)
    {
    cout << "Reservation on Code " << resCode << " is canceled: Seat " << _reservations[reservationIndex].getColNo() << _reservations[reservationIndex].getRowNo() << " in Movie at " << movieTime << endl;
    }
    
    _movies[findMovie(_reservations[reservationIndex].getResMovieID())].freeSeat(_reservations[reservationIndex].getRowNo(), _reservations[reservationIndex].getColNo());
    
    Reservation* tempReservations = new Reservation[_numOfReservations-1];
    
    int newReservationCount = 0;
    
    for (int i = 0; i < _numOfReservations; i++)
    {
        if(i != reservationIndex)
        {
            tempReservations[newReservationCount] = _reservations[i];
            newReservationCount++;
        }
    }
    
    delete[] _reservations;
    
    _reservations = tempReservations;

    _numOfReservations--;
    
    //delete[] tempReservations;
    
    
    
    
    
}
