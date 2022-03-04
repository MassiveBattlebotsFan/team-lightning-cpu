#ifndef IO_CPU_H
#define IO_CPU_H

#include "rom_cpu.hpp"

class CPU : public RomCPU{
protected:
  void io_out();
  void io_in();

public:
  CPU();
};
#endif
