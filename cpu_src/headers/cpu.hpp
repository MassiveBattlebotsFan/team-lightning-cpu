#ifndef IO_CPU_H
#define IO_CPU_H
#include "base_cpu.hpp"
class CPU : public BaseCPU{
protected:
  void io_out();
  void io_in();

public:
  CPU();
};
#endif
