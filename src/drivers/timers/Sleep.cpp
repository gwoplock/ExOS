#include "Sleep.h"
#include "Kernel.h"
#include "ProgrammableIntervalTimer.h"
unsigned int milisleep(unsigned int miliseconds){
    pit.setTimer(miliseconds);
}

unsigned int sleep(unsigned int seconds){
    pit.setTimer(1000*seconds);
}