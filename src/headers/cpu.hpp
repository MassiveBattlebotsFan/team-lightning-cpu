#ifndef CPU_H
#define CPU_H
#include <cstdint>

class CPU{
  /*
  CPU class, contains interpreter for the hex machine code, main bus, and any other parts.
  */
  protected:
    //main bus, 32/40 bits implemented
    std::uint8_t opCode;
    std::uint8_t instrArg;
    std::uint8_t accumulator;
    std::uint8_t datMem[256];
    std::uint8_t memAddr;
    std::uint8_t interpretInstr(uint8_t opCode, uint8_t arg);
  public:
    CPU();
    std::uint16_t getAccum();
    std::uint16_t run(uint16_t instruction);
};

#endif
