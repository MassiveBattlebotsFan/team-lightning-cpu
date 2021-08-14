#ifndef ROM_CPU_H
#define ROM_CPU_H
#include "base_cpu.hpp"
#include <cstdint>
class RomCPU : public BaseCPU{
  protected:
    std::uint16_t romBuffer[0x10000]; //this is 16 bits wide
    std::uint16_t romAddr;
    void getRomBuffer();
    void setRomAddr();
    void getRomAddr();
  public:
    std::uint16_t* romdump();
    bool attach(char fname[1024]);
    void detach();
    void load(uint16_t offset);
    RomCPU();
};
#endif
