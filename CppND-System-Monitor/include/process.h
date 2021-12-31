#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include "linux_parser.h"
#include "processor.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram() const;                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& other) const;  // TODO: See src/process.cpp

  //Declare setters
  void Pid(int pid);
  // TODO: Declare any necessary private members
 private:
   int pid_;
   Processor cpu_proc;
};

#endif