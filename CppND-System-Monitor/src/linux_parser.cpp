#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
//#include <string.h>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

string LinuxParser::OperatingSystem() {
  string line;
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
  return value;
}

string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
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
  return pids;
}

float LinuxParser::MemoryUtilization() { 
  string memTotal, memFree;
  string line;
  string name, num_value;
  std::ifstream stream(kProcDirectory+kMeminfoFilename);
  if (stream.is_open()){
    std::getline(stream,line);
    std::istringstream linestream(line);
    linestream >> name >> memTotal;
    line.clear();
    std::getline(stream,line);
    std::istringstream linestream2(line);
    linestream2 >> name >> memFree;
  }
  //TOTAL_USED_MEMORY
  return (float)(stoi(memTotal) - stoi(memFree))/(float)stoi(memTotal);
  }

long LinuxParser::UpTime() { 
    string upTime;
    string line;
    std::ifstream filestream(kProcDirectory+kUptimeFilename);
    if(filestream.is_open()){
      std::getline(filestream,line);
      std::istringstream line_stream(line);
      line_stream >> upTime;

      int coma = upTime.find('.');
      string n1 = upTime.substr(0,coma);
      string n2 = upTime.substr(coma+1);
      float num =(float)stoi(n1)+(float)stoi(n2)/100; //this was a way to take decimal part of second, innecesary
      return stoi(n1);
    }
  return 0; }

//I di not need to use this functions, I think their purpose is fulfill
//by the Cpu Utilization in system and process

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

vector<string> LinuxParser::CpuUtilization() { 
  vector<string> contenido;
  string line;
  std::ifstream file_stream(kProcDirectory+kStatFilename);
  if(file_stream.is_open()){
    std::getline(file_stream,line);
    std::istringstream s_stream(line);
    string each_number;
    while(std::getline(s_stream,each_number,' ')){
      if (each_number != ""){
        contenido.push_back(each_number);}
    }
  }
  return contenido; }

vector<string> LinuxParser::Process_CpuUtilization(int pid) { 
  vector<string> contenido;
  string line;
  std::ifstream file_stream(kProcDirectory+std::to_string(pid)+kStatFilename);
  if(file_stream.is_open()){
    std::getline(file_stream,line);
    std::istringstream s_stream(line);
    string each_number;
    while(std::getline(s_stream,each_number,' ')){
      if (each_number != ""){
        contenido.push_back(each_number);}
    }
  }
  return contenido; }

int LinuxParser::TotalProcesses() { 
  string total_processes,name;
  string line;
  std::ifstream stream_to_stat(kProcDirectory+kStatFilename);
  if(stream_to_stat.is_open()){
    
    while(std::getline(stream_to_stat,line)){
      std::istringstream line_stream(line);
      while(line_stream >> name >> total_processes){
        if(name =="processes"){
          return stoi(total_processes);
        }
      }
    }
  }
  return 0; }

int LinuxParser::RunningProcesses() {
  string running_processes,name;
  string line;
  std::ifstream stream_to_stat(kProcDirectory+kStatFilename);
  if(stream_to_stat.is_open()){
    
    while(std::getline(stream_to_stat,line)){
      std::istringstream line_stream(line);
      while(line_stream >> name >> running_processes){
        if(name =="procs_running"){
          return stoi(running_processes);
        }
      }
    }
  }
  return 0;
}

string LinuxParser::Command(int pid) { 
  std::ifstream f_stream_to_cmd(kProcDirectory+std::to_string(pid)+kCmdlineFilename);
  string line;
  if (f_stream_to_cmd.is_open()){
    std::getline(f_stream_to_cmd,line);
  }
  return line; }

string LinuxParser::Ram(int pid) {
  std::ifstream f_stream(kProcDirectory+std::to_string(pid)+kStatusFilename);
  string field, RAM;
  string line;
  if (f_stream.is_open()){
    while(std::getline(f_stream,line)){
      std::istringstream s_stream(line);
      s_stream >> field >> RAM;
      if (field == "VmSize:"){
        break;
      }
    }
  }
  //RAM.insert(RAM.end()-3,'.');
  return RAM; }

string LinuxParser::Uid(int pid) { 
  std::ifstream f_stream(kProcDirectory+std::to_string(pid)+kStatusFilename);
  string field, UID;
  string line;
  if (f_stream.is_open()){
    while(std::getline(f_stream,line)){
      std::istringstream s_stream(line);
      s_stream >> field >> UID;
      if (field == "Uid:"){
        return UID;
      }
    }
  }
  return string(); }

string LinuxParser::User(int pid) { 
  return LinuxParser::UID_TO_USER(LinuxParser::Uid(pid));
  }

string LinuxParser::UID_TO_USER(string UID){
  std::ifstream f_stream_to_passwd("/etc/passwd");
  string usr_name,uid,something,line;
  if (f_stream_to_passwd.is_open()){
    while(std::getline(f_stream_to_passwd,line)){
      std::replace(line.begin(),line.end(),':',' ');
      std::istringstream s_stream(line);
      s_stream >> usr_name >> something >>uid;
      if(uid == UID){
        return usr_name;
      }
    }
  }
  return string();
}

long LinuxParser::UpTime(int pid) { 
  std::ifstream f_stream(kProcDirectory+std::to_string(pid)+kStatFilename);
  string field, UP_TIME;
  string line;
  if (f_stream.is_open()){
    std::getline(f_stream,line);
    std::istringstream s_stream(line);
    int i = 0;
    while(s_stream >> UP_TIME){
      i++;
      if (i == 22){
        break;
      } 
    }
  }
  long up_time = stoi(UP_TIME)/sysconf(_SC_CLK_TCK);
  return up_time; }
