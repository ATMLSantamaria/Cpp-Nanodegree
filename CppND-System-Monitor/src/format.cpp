#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds/*[[maybe_unused]]*/) { 
    string hh, mm,ss;
    int h, m, s;
    h = seconds/3600;
    m = (seconds%3600)/60;
    s = (seconds%3600)%60;
    hh = std::to_string(h);
    mm = std::to_string(m);
    ss = std::to_string(s);
    return hh+':'+mm+':'+ss; }