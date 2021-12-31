#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

int Process::Pid() { return pid_; }
void Process::Pid(int pid){
    pid_ = pid;
}
float Process::CpuUtilization() { 
    float up_time = LinuxParser::UpTime();
    vector<string> stat = LinuxParser::Process_CpuUtilization(this->pid_);
    float total_time = (float)(stoi(stat[13])+stoi(stat[14])+stoi(stat[15])+stoi(stat[16]));

    float seconds = up_time - (float)stoi(stat[21])/sysconf(_SC_CLK_TCK);
    float cpu_usage = (total_time/sysconf(_SC_CLK_TCK))/seconds;
    return cpu_usage; }

string Process::Command() { 
    return LinuxParser::Command(this->pid_); }

string Process::Ram() const {
     return LinuxParser::Ram(this->pid_);
      }

string Process::User() { 
    return LinuxParser::User(this->pid_);
    }

long int Process::UpTime() { 
    return LinuxParser::UpTime(this->pid_); }


bool Process::operator<(Process const& other) const {
    int n1 = stoi(this->Ram());
    int n2 = stoi(other.Ram());
    bool a = (n1 < n2);
    return a;}
 