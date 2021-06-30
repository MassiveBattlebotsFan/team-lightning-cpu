#include <cstdint>
#include <strstream>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "headers/cpu.hpp"

CPU::CPU(){
  this->opCode = 0x0;
  this->accumulator = 0x0;
  this->instrArg = 0x0;
  for(uint8_t i = 0; i < 255; i++){
    this->datMem[i] = 0x0;
  }
  this->memAddr = 0x0;
}

std::uint16_t CPU::getAccum(){return this->accumulator;}

std::uint16_t CPU::run(uint16_t instruction){
  std::strstream formattedInstr;
  formattedInstr << std::hex << std::setfill('0') << std::setw(4) << instruction;
  //std::cerr << formattedInstr.str() << std::endl;
  char fOpcode1[16];
  strncpy(fOpcode1, formattedInstr.str(), 2);
  char fArg1[16];
  strncpy(fArg1, formattedInstr.str() + 2, 2);
  std::uint8_t formattedOpcode = (uint8_t)strtol(fOpcode1, NULL, 16);
  std::uint8_t formattedArg = (uint8_t)strtol(fArg1, NULL, 16);
  return this->interpretInstr(formattedOpcode, formattedArg);
}

std::uint8_t CPU::interpretInstr(uint8_t opCode, uint8_t arg){
  this->opCode = opCode;
  this->instrArg = arg;
  /*
  opcodes:
  0x00/invalid: returns the opcode, basically no operation
  0x01: sets memAddr to arg
  0x02: gets memAddr
  0x03: sets value at memAddr to arg
  0x04: gets value at memAddr
  */
  switch(this->opCode){
    case 0x4:
      return this->datMem[this->memAddr];
      break;
    case 0x3:
      this->datMem[this->memAddr] = this->instrArg;
      return this->instrArg;
      break;
    case 0x2:
      return this->memAddr;
      break;
    case 0x1:
      this->memAddr = this->instrArg;
      return this->memAddr;
      break;
    case 0x0:
    default:
      return this->opCode;
      break;
  }
  return this->opCode;
}
