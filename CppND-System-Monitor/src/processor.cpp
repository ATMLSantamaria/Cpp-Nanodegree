#include "processor.h"

//alias for namespace
namespace LP = LinuxParser;

Processor::Processor(){
    //Start utilization data vector
    vector<string> s_utilization 
        = LinuxParser::CpuUtilization();
    float prev_nonidle = (float)(stoi(s_utilization[LP::kUser_])+stoi(s_utilization[LP::kNice_])+stoi(s_utilization[LP::kSystem_])+
      stoi(s_utilization[LP::kIRQ_])+stoi(s_utilization[LP::kSoftIRQ_])+stoi(s_utilization[LP::kSteal_]));
    prev_idle = (float)(stoi(s_utilization[LP::kIdle_])+stoi(s_utilization[LP::kIOwait_]));
    prev_total = prev_idle + prev_nonidle;
    
    //Create a difference between prev and current for initial computation
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}
float Processor::Utilization() { 

    //Current utilization data vector
    vector<string> c_utilization
     = LinuxParser::CpuUtilization();


    //Current total & idle
    float nonidle = (float)(stoi(c_utilization[LP::kUser_])+stoi(c_utilization[LP::kNice_])+stoi(c_utilization[LP::kSystem_])+
      stoi(c_utilization[LP::kIRQ_])+stoi(c_utilization[LP::kSoftIRQ_])+stoi(c_utilization[LP::kSteal_]));
    idle = (float)(stoi(c_utilization[LP::kIdle_])+stoi(c_utilization[LP::kIOwait_]));
    total = idle + nonidle;
    //dif computation
    float total_dif = total - prev_total;
    float idle_dif = idle - prev_idle;
  
    //Percentage cpu computation
    float cpu_percentage{0};
    //Avoid ugly 0 division consequences
    if (total_dif != 0){
        cpu_percentage = (total_dif-idle_dif)/total_dif;
    }

    //Update prev values
    prev_idle = idle;
    prev_total = total;
    return cpu_percentage; }