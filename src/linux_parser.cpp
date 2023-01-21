#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "readFromFile.h"
#include "read_key_value.h"

using std::stof; // string to float
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
/*   string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value; */

    std::string path_OS = "/etc/os-release";
    std::string flag_OS = "PRETTY_NAME=";
    std::string string_OS = readFromFile(path_OS,flag_OS);
    return string_OS; 
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel; // pop tokens from stream
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
// Pid = process IDs = integer foldernames in /proc
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids; // return vector of process IDs
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 

    float memUse, memTot, memFree, memBuffer, memCache, value;
    std::ifstream fileStream(kProcDirectory + kMeminfoFilename);
    string line, key, unit;
    if (fileStream.is_open()) {
      while(std::getline(fileStream,line)){ // get each line from fileStream
        std::istringstream lineStream(line);
        lineStream >> key >> value >> unit; // key and value separated by spaces, unit not used
        if (key == "MemTotal:"){
          memTot = value;}
        if (key == "MemFree:"){
          memFree = value;}
        if (key == "Buffers:"){
          memBuffer = value;}
        if (key == "Cached:"){
          memCache = value;}
      }
    }
    memUse = (memTot - (memFree+memBuffer+memCache)) / memTot;
    return memUse;}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  float totProcesses, value;
    std::ifstream fileStream(kProcDirectory + kStatFilename);
    string line, key;
    if (fileStream.is_open()) {
      while(std::getline(fileStream,line)){ // get each line from fileStream
        std::istringstream lineStream(line);
        lineStream >> key >> value; // key and value separated by spaces
        if (key == "processes"){
          totProcesses = value;}
      }
    }
  return totProcesses; }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  float runProcesses, value;
    std::ifstream fileStream(kProcDirectory + kStatFilename);
    string line, key;
    if (fileStream.is_open()) {
      while(std::getline(fileStream,line)){ // get each line from fileStream
        std::istringstream lineStream(line);
        lineStream >> key >> value; // key and value separated by spaces
        if (key == "procs_running"){
          runProcesses = value;}
      }
    }
  return runProcesses; }

// TODO: Read and return the system uptime 
long LinuxParser::UpTime() { 
  long timeUpSeconds, timeIdleSeconds;
    std::ifstream fileStream(kProcDirectory + kUptimeFilename);
    string line, key;
    if (fileStream.is_open()) {
      std::getline(fileStream, line); // get line from fileStream
      std::istringstream lineStream(line);
      lineStream >> timeUpSeconds >> timeIdleSeconds; 
      }
  return timeUpSeconds; }

/* // TODO: Read and return the number of jiffies for the system
// tick rate = clock frequency in Hz = declared in include/asm-i386/param.h
// Jiffies = number of ticks since system booted = declared in <linux/jiffies.h>
// seconds = (jiffies / Hz)
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; } */

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  
  // initialize output
  vector<string> cpu_vector;
  string key, user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;

  // access file /proc/stat from namespace LinuxParser
  std::ifstream fileStream(kProcDirectory + kStatFilename); 
  std::string line;
  
  if(fileStream.is_open()){
    while(std::getline(fileStream,line)){ 
      std::istringstream lineStream(line);
      lineStream >> key >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
      if(key == "cpu"){
        cpu_vector.push_back(user);
        cpu_vector.push_back(nice);
        cpu_vector.push_back(system);
        cpu_vector.push_back(idle);
        cpu_vector.push_back(iowait);
        cpu_vector.push_back(irq);
        cpu_vector.push_back(softirq);
        cpu_vector.push_back(steal);
        cpu_vector.push_back(guest);
        cpu_vector.push_back(guest_nice);
      }
    } 
  }
  return cpu_vector; }

// Processor Utilization of individual PID, overloaded with overall CpuUtilization
// CPU utilization of a process stored in /proc/[PID]/stat
float LinuxParser::CpuUtilization(int pid) {
  string stat_int;
  string pid_str = to_string(pid);
  vector<string> PID_stat_vector;  
  int utime,stime,starttime,totaltime;
  long int uptime = LinuxParser::UpTime(); // [seconds]
  float time_seconds, cpu_percent{0.0};
  int freq = sysconf(_SC_CLK_TCK); // [Hz]
  std::ifstream filestream(kProcDirectory + pid_str + kStatFilename);
  if(filestream.is_open()){
      while (filestream >> stat_int){
          PID_stat_vector.push_back(stat_int);
      } // https://man7.org/linux/man-pages/man5/proc.5.html
    utime  = std::stoi(PID_stat_vector[13]); // time of process in user mode [clock ticks]
    stime  = std::stoi(PID_stat_vector[14]); // time of process in kernel mode [clock ticks]
    starttime = std::stoi(PID_stat_vector[21]); // time of process after boot [clock ticks]
    totaltime = (utime + stime)/freq; // [seconds]
    time_seconds = uptime - (starttime/freq); // [seconds]
    cpu_percent = totaltime / time_seconds;
  }
  return cpu_percent;}

// TODO: Read and return the command associated with a process
// command to launch a PID in /proc/[pid]/cmdline
string LinuxParser::Command(int pid) {  
  string pid_str = to_string(pid); // create filestream of PID path to get PID command
  std::ifstream filestream(kProcDirectory + pid_str + kCmdlineFilename);
  string line, command; // parse command from linestream
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> command; 
    }
  }
  return command; }

// TODO: Read and return the memory used by a process
string LinuxParser::Ram(int pid) {
  string pid_str = to_string(pid); // path to PID status
  string path = kProcDirectory + pid_str + kStatusFilename;
  string target_key = "VmRSS:"; // get value by key
  string memory = read_key_value(path, target_key);
  return memory;
  }

// TODO: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
  string pid_str = to_string(pid); // path to PID status
  string path = kProcDirectory + pid_str + kStatusFilename;
  string target_key = "Uid:"; // get value by key
  string uid = read_key_value(path, target_key);
  return uid;
}

// TODO: Read and return the user associated with a process
string LinuxParser::User(int pid) {
  string line, username, name_str, x, uid_str;
  // string pidNum = to_string(pid);
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      // to use linestream, ensure delimeter = space ' '
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> name_str >> x >> uid_str) {
        if (uid_str == LinuxParser::Uid(pid)) {
          username = name_str;
        }
      }
    }
  }
  return username;
}

// TODO: Read and return the uptime of a process
// UpTime = time since process started after system boot
// overloaded with overall Up Time
// starttime %llu
// before Linux 2.6, this value was expressed in jiffies
// since  Linux 2.6, this value is expressed in clock ticks
long LinuxParser::UpTime(int pid) { 
  long process_time_seconds{0}; 
  int freq = sysconf(_SC_CLK_TCK); // [Hz]
  string line, start_time;
  string pid_str = to_string(pid); 
  std::ifstream filestream(kProcDirectory + pid_str + kStatFilename);
    if (filestream.is_open()) {
      std::getline(filestream, line);
      std::istringstream linestream(line);
      for (int i = 0; i<22; ++i){ // get process start time on position 21
        linestream >> start_time;
      }
    }
  process_time_seconds = LinuxParser::UpTime() - std::stol(start_time)/freq;
  return process_time_seconds;
}
