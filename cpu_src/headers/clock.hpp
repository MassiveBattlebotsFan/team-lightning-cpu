#ifndef PL2_CLOCK_H
#define PL2_CLOCK_H

#include <cstdint>
#include <chrono>
#include <vector>

#include "cpu.hpp"
//#include "module.hpp"

class PL2_Clock{
private:
  double cycleTime;
  std::chrono::steady_clock::time_point cycleStartTimePoint;
  std::chrono::steady_clock::time_point cycleEndTimePoint;
  PL2_CPU* cpu;
  //std::vector<PL2_Module*> modules;
public:
  PL2_Clock();
  void start();
  //void setModules(std::vector<PL2_Module*>* modulesToSet);
  void stop();
};
