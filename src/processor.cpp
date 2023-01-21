#include "processor.h"
#include "linux_parser.h"

#include <string>
#include <vector>

using std::vector;
using std::string;
using std::stol;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {     // get parsed string values
    vector<string> cpu_vector = LinuxParser::CpuUtilization();

    // define private members, see processor.h
    long user = stol(cpu_vector[0]);
    long nice = stol(cpu_vector[1]);
    long system = stol(cpu_vector[2]);
    long idle = stol(cpu_vector[3]);
    long iowait = stol(cpu_vector[4]);
    long irq = stol(cpu_vector[5]);
    long softirq = stol(cpu_vector[6]);
    long steal = stol(cpu_vector[7]);
    long guest = stol(cpu_vector[8]);
    long guest_nice = stol(cpu_vector[9]);

    // CPU utilization = Active_Jiffies / Total_jiffies
    // https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux

    long Total_Idle = idle + iowait;
    long Total_NonIdle = user + nice + system + irq + softirq + steal;
    long Total = Total_Idle + Total_NonIdle;

    long Total_diff = Total - Total_prev;
    long Total_Idle_diff = Total_Idle - Total_Idle_prev;

    // type cast operands to floats, otherwise int division rounded to 0 or 1
    float cpu_usage = (float)(Total_diff - Total_Idle_diff) / (float)Total_diff;

    // store previous values for next function call
    Total_prev = Total;
    Total_Idle_prev = Total_Idle;
    user_prev = user;
    nice_prev = nice;
    system_prev = system;
    idle_prev = idle;
    iowait_prev = iowait;
    irq_prev = irq;
    softirq_prev = softirq;
    steal_prev = steal;
    guest_prev = guest;
    guest_nice_prev = guest_nice;

    return cpu_usage;  }