#include <vector>

#include "headers/core.hpp"

PL2_Core::PL2_Core(PL2_CPU& cpu, PL2_Clock& clock){
  this->cpu = cpu;
  this->clock = clock;
  this->isReady = false;
}

void PL2_Core::addModule(PL2_Module& module){
  //module->setCPU(this->cpu);
  this->modules.push_back(module);
}

void PL2_Core::ready(){
  this->clock->setModules(this->modules&);
  this->clock->ready();
  this->isReady = true;
}

void PL2_Core::start(){
  if(this->isReady){
    this->clock->start();
    this->isReady = false;
  }
}
