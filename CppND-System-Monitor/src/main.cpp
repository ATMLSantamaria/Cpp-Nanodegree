#include "ncurses_display.h"
#include "system.h"
#include "stdlib.h"

int main() {

  System system;
  NCursesDisplay::Display(system);
}

void alternative_PID1(){
  system("ls -l /proc/ > /home/workspace/CppND-System-Monitor/PID.txt"); //then read from there
  }
  
void alternative_PID2(){
  FILE *proc = popen("/bin/ls -al /proc/","r");
  char buf[1024];
  while ( !feof(proc) && fgets(buf,sizeof(buf),proc) ){
    //printf("Line read: %s",buf[1020].);
    printf("Line read: %c%c%c%c%c",buf[0],buf[1],buf[2],buf[3],'\n');
    }
}
