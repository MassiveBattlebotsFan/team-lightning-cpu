#ifndef CPU_H
#define CPU_H
#include <cstdint>

class CPU{
  /*
  CPU class, contains interpreter for the hex machine code, main bus, and any other parts.
  */
  protected:
    //main bus, 52/52 bits implemented
    std::uint8_t opCode;
    std::uint8_t instrArg;
    std::uint8_t accumulator;
    std::uint8_t datMem[256];
    std::uint16_t progMem[0x10000]; //this is 12 bits wide
    std::uint16_t progAddr;
    std::uint8_t out();
    std::uint8_t in();
    //interpreter is protected b/c easy to misformat
    std::uint16_t interpretInstr(uint8_t opCode, uint8_t arg);
  public:
    CPU();
    std::uint16_t getAccum();
    std::uint16_t run(uint16_t instruction);
    void exec(); //this runs ROMcode, not the same as CPU::run()

    bool load(char fname[1024]);
};

#endif
