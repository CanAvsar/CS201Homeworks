//  ReservationList.h
//  CS201 Homework 3: MovieBookingSystemLinkedList
//  May 2021
//  Can Avşar
//  21902111

#ifndef ReservationList_h
#define ReservationList_h



class ReservationList{
public:
    ReservationList();
    ReservationList( const ReservationList& aList );
    ~ReservationList();
    
    bool isEmpty() const;
    int getLength() const ;
    bool retrieve(int index, int& resCode) const;
    bool insert(int index, int resCode);
    bool remove(int index);
    bool getResDetails(int index, int& resCode, long& movieID, int& row, int& col) const;
    bool setResDetails(int index, long movieID, int row, int col);
    int getIndex(int resCode) const;


private:
    struct ReservationNode
    {
        int Code;
        int movieID;
        int row;
        int col;
        ReservationNode* next;
    };
    
    int size;
    ReservationNode *head;
    ReservationNode *find(int index) const;
    
};


#endif
