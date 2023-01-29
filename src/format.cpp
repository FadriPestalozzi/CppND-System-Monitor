#include <sstream>
#include <string>

#include "format.h"
#include <iomanip> // pad zeros

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long secondsTotal) { 
    
long secondsRemaining, minutesTotal, minutesRemaining, hoursTotal;

    minutesTotal = secondsTotal / 60;
    secondsRemaining = secondsTotal % 60; // [SS]
    
    hoursTotal = minutesTotal / 60; // [HH]
    minutesRemaining = minutesTotal % 60; // [MM]

    // use stringstream to convert long to string
    std::stringstream stream_HH;
    std::stringstream stream_MM;
    std::stringstream stream_SS;

    // add long number to variable of type stringstream
    stream_HH << std::setw(2) << std::setfill('0') << hoursTotal; // pad zeros if value below 10
    stream_MM << std::setw(2) << std::setfill('0') << minutesRemaining; // pad zeros if value below 10
    stream_SS << std::setw(2) << std::setfill('0') << secondsRemaining; // pad zeros if value below 10

    // initialize output strings
    string HH, MM, SS, output;
    
    // get string from stringstream using method .str()
    HH = stream_HH.str();
    MM = stream_MM.str();
    SS = stream_SS.str();

    output = HH + ":" + MM + ":" + SS;
    return output; }