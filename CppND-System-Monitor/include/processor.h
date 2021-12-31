#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"
#include <thread>
#include <chrono>
using std::string;
using std::vector;

class Processor {
  public:
    Processor();
    float Utilization();
    
  private:
    float idle{0},prev_idle;
    float total{0}, prev_total;
};

#endif