#include <chrono>
#include <vector>

#include "headers/clock.hpp"
#include "headers/cpu.hpp"

PL2_Clock::PL2_Clock(PL2_CPU& cpu){
  this->cpu = cpu;
  this->cycleTime = 0.0;
  this->run=false;
}

void PL2_Clock::ready(){
  this->run=true;
}
void PL2_Clock::start(){
  do{
    this->cpu->run();
  }while(this->run);
}

void PL2_Clock::stop(){
  this->run=false;
}
