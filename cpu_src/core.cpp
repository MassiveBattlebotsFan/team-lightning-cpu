#include <vector>

#include "headers/core.hpp"

PL2_Core::PL2_Core(PL2_CPU& cpu, PL2_Clock& clock){
  this->cpu = cpu;
  this->clock = clock;
}

void PL2_Core::addModule(PL2_Module& module){
  module->setCPU(this->cpu);
  module->setClock(this->clock);
  this->modules.push_back(module);
}

void PL2_Core::start(){
  this->clock->start();
}
