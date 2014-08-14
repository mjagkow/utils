/* 
 * File:   option_helper.cpp
 * Author: Igor Myagkov - myagkov@physics.msu.ru
 * 
 * Created on August 13, 2014, 7:56 PM
 */

#include "option_helper.h"

using namespace std;

ostream& operator<<(ostream& os, const OptionHelper& opt)
{
    os << opt._visible;
    return os;
}