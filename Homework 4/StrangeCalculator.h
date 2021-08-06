//  StrangeCalculator.h
//  CS201 Homework 4: StrangeCalculator
//  May 2021
//  Can Avşar
//  21902111

#ifndef StrangeCalculator_h
#define StrangeCalculator_h
#include <iostream>
using namespace std;

class StrangeCalculator
{
public:
    
    StrangeCalculator();
    ~StrangeCalculator();
    
    

};

string infix2prefix(const string exp);

double evaluatePrefix(const string exp);

bool isBalancedInfix(const string exp);

void evaluateInputPrefixExpression();

string reverseExp(const string exp);

int precedence(char op);

string removeSpace(const string exp);




#endif /* StrangeCalculator_h */
