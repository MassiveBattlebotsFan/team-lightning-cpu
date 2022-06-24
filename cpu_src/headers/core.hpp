#ifndef PL2_CORE_H
#define PL2_CORE_H

#include <vector>

#include "module.hpp"
#include "clock.hpp"
#include "cpu.hpp"

class PL2_Core{
private:
  PL2_Clock* clock;
  PL2_CPU* cpu;
  std::vector<PL2_Module*> modules;
  bool isReady;
  
public:
  PL2_Core(PL2_CPU& cpu, PL2_Clock& clock);
  void addModule(PL2_Module& module);
  void start();
  void stop();
  void ready();
};

#endif
