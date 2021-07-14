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
    std::uint16_t datReg;
    std::uint16_t datMem[0x2000]; //8k 2 byte words
    std::uint16_t datAddr;
    std::uint16_t instrArg;
    std::map<uint8_t, std::function<void(void)>> opCodes;
  private:
    //opcode reg, instr reg, and ROM buffer for loaded files
    std::uint8_t opCode;
    std::uint16_t romBuffer[0x10000]; //this is 16 bits wide
    std::uint16_t romAddr;
    std::uint16_t execAddr;
    //accumulator private b/c datAddr
    std::uint16_t accumulator;
    //interpreter doesn't need to be accessed by addons
    std::uint32_t interpretInstr(uint8_t opCode, uint16_t arg);
  public:
    BaseCPU();
    std::uint16_t* romdump();
    std::uint16_t run(uint32_t instruction);
    void exec(); //this runs ROMcode, not the same as CPU::run()
    bool attach(char fname[1024]);
    void detach();
    void load(uint16_t offset);
};

#endif
