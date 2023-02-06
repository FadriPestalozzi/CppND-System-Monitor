#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return LinuxParser::CpuUtilization(pid); }

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid); }

// TODO: Return the age of this process (in seconds)
// process starting after system
long int Process::UpTime() { return LinuxParser::UpTime(pid); }

// mystoi and not stoi since string not always containing a number -> catch error
int mystoi(std::string a){
    try
    {
        return stoi(a);
    }
    catch(const std::invalid_argument &e) // e = exception
    {
        return 0;
    }
}

// TODO: Overload the "less than" comparison operator for Process objects to sort in system.cpp
    // to sort for different columns, change overload function operator< using keyboard input
bool Process::operator<(Process a) { 
    switch(colSort){
        case by_cpu : return CpuUtilization() > a.CpuUtilization();
            break;
        case by_cpu_inv : return CpuUtilization() < a.CpuUtilization();
            break;
        case by_ram : return mystoi(Ram()) > mystoi(a.Ram());
            break;
        case by_ram_inv : return mystoi(Ram()) < mystoi(a.Ram());
            break;    
        case by_time : return UpTime() > a.UpTime(); 
            break;
        case by_time_inv : return UpTime() < a.UpTime();
            break;    
        case by_cmd : return mystoi(Command()) > mystoi(a.Command());
            break;
        case by_cmd_inv : return mystoi(Command()) < mystoi(a.Command());
            break;    
        default : return CpuUtilization() > a.CpuUtilization();
    }
}
