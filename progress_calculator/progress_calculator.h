/*
 * File:   progress_calculator.h
 * Author: Igor Myagkov - myagkov@physics.msu.ru
 *
 * Created on November 27, 2013, 4:13 AM
 */

#ifndef PROGRESS_CALCULATOR_H
#define PROGRESS_CALCULATOR_H

#include <iostream>
#include <string>
#include <cmath>

class ProgressCalculator
{
protected:
    unsigned int _n;
    unsigned int _next;
    unsigned int _max;
    unsigned int _current;
    
    static std::string defaultPrefix;
    
    unsigned int getNext()
    {
        double part = ((double)_max) / ((double)_n);
        unsigned int step = floor( ((double)_current) / part) + 1;
        return (unsigned int)( ((double)step) * part );
    }
    
public:
    ProgressCalculator(unsigned long max)
    {
        _n = 100;
        _max = max;
        _current = 0;
        _next = 0;
    }
    
    void step()
    {
        step(defaultPrefix);
    }
    
    void step(const std::string &prefix)
    {
        _current ++;
        if(_current >= _next) 
        {
            std::cout << prefix << floor(((double)_current/(double)_max) * 100 + 0.5) << "%        \r";
            std::cout.flush();
            _next = getNext();
        }
        if( _current == _max ) 
        {
            std::cout << std::endl;
        }
    }
};


#endif /* PROGRESS_CALCULATOR_H */
