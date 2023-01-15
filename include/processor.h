#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
     long long Total, Total_Idle, user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    // initialize previous entries with 0, will be overwritten with measurement
    long long Total_prev{0}, Total_Idle_prev{0}, user_prev{0}, nice_prev{0}, system_prev{0}, idle_prev{0}, iowait_prev{0}, irq_prev{0}, softirq_prev{0}, steal_prev{0}, guest_prev{0}, guest_nice_prev{0};
    std::vector<std::string> cpu_vector,cpu_vector_prev;
};

#endif