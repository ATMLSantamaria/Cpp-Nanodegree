#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

static bool Compare(const Process & a, const Process & b){
    return b < a;
}

Processor& System::Cpu() { 
    return cpu_; }

vector<Process>& System::Processes() { 
    //This function is call in every iteration of ncursesdisplay
    //This imply that in each iteration processes will be again created and thus, updated
    std::vector<int> n_processes = LinuxParser::Pids();
    processes_.clear();
    for (int i : n_processes){
        Process a;
        a.Pid(i);
        processes_.push_back(a);
    }
    //bool prueba = (processes_[0] < processes_[1]);
    std::sort (processes_.begin(),processes_.end(),Compare);
    return processes_; }

std::string System::Kernel() { 
    string kernel_id = LinuxParser::Kernel();
    return kernel_id; }

float System::MemoryUtilization() { 
    float tmp = LinuxParser::MemoryUtilization();
    return tmp; }

std::string System::OperatingSystem() { 
    string os_name = LinuxParser::OperatingSystem();
    return os_name; }

int System::RunningProcesses() { 
    int running_processes = LinuxParser::RunningProcesses();
    return running_processes; }

int System::TotalProcesses() { 
    int total_processes = LinuxParser::TotalProcesses();
    return total_processes; }

long int System::UpTime() { 
    long up_time = LinuxParser::UpTime();
    return up_time;}