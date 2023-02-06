#ifndef PROCESS_H
#define PROCESS_H

#include <string>
// different overloading of operator< to adjust column sorting
// used in process.cpp and ncurses_display.cpp
// enumerate different column sorting options 
enum colSortOptions { by_cpu, by_cpu_inv, by_ram, by_ram_inv, by_time, by_time_inv, by_cmd, by_cmd_inv}; 

// global variable declared as "extern" in header .h file, included in all source .cpp files
extern colSortOptions colSort; 

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid_new){pid = pid_new;}   // constructor to generate new process with PID
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process a);  // TODO: See src/process.cpp
    
  // TODO: Declare any necessary private members
 private:
    int pid;
};

#endif