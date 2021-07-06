#ifndef BASE_CPU_H
#define BASE_CPU_H
#include <cstdint>
#include <map>
#include <functional>

class BaseCPU{
  /*
  CPU class, contains interpreter for the hex machine code, main bus, and any other parts.
  */
  protected:
    //these should be accessible by addon modules
    std::uint8_t accumulator;
    std::uint16_t datMem[0x1FFF]; //8k 2 byte words
    std::map<uint8_t, std::function<void()>> opCodes[0xff];
  private:
    //opcode reg, instr reg, and ROM buffer for loaded files
    std::uint8_t opCode;
    std::uint8_t instrArg;
    std::uint16_t romBuffer[0xFFFF]; //this is 16 bits wide
    std::uint16_t romAddr;
    //interpreter doesn't need to be accessed by addons
    std::uint16_t interpretInstr(uint8_t opCode, uint8_t arg);
  public:
    BaseCPU();
    std::uint16_t* romdump();
    std::uint16_t run(uint16_t instruction);
    void exec(); //this runs ROMcode, not the same as CPU::run()
    bool attach(char fname[1024]);
    void load(uint16_t offset);
};

#endif
