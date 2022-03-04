#include <iostream>
#include "headers/cpu.hpp"

PL2_CPU::PL2_CPU(){
  this->reset();
}
void PL2_CPU::reset(){
  this->memAddr = 0x0;
  this->mem = 0x0;
  this->romAddr = 0x0;
  this->rom = 0x0;
  this->bus_5 = 0x0;
  this->bus_6 = 0x0;
  this->bus_7 = 0x0;
  this->bus_8 = 0x0;
  this->bus_9 = 0x0;
  this->bus_10 = 0x0;
  this->bus_11 = 0x0;
  this->bus_12 = 0x0;
  this->bus_13 = 0x0;
  this->bus_14 = 0x0;
  this->bus_15 = 0x0;
  this->bus_16 = 0x0;
  this->acc = 0x0;
  this->isErr = false;
}
void PL2_CPU::run(){
  /*
  opcodes [TEMP]:
  0x00: returns 0x9999, used for prog termination
  0x01: sets datMem at datAddr to datReg
  0x02: gets datMem at datAddr to datReg
  0x03: sets accumulator to instrArg
  0x04: gets accumulator, does basically nothing
  0x05: sets datAddr to datReg
  0x06: gets datAddr to datReg
  0x07: add instrArg to accumulator
  0x08: sub instrArg from accumulator
  0x09: swap datReg and accumulator
  0x0A: store execAddr in datMem[datAddr] for loops (only in programs)
  0x0B: if accumulator != 0 jump execAddr to datMem[datAddr] (only in programs)
  0x0C: set execAddr to instrArg
  */
  /*
  opcode format:
    upper opcode is category
    lower opcode is command
  upper opcode:
    0x0: system
      lower opcode:
        0x0: HCF
        0x1: soft reset registers
        0x2: set acc upper
        0x3: set acc lower
        0x4-0xF: reserved
    0x1: math (reads mem bus)
      lower opcode:
        0x0: add
        0x1: sub
        0x2: mul
        0x3: div (div by 0 returns 0, all div is floored)
        0x4-0xF: reserved
    0x2: read from bus
      lower opcode: specifies bus
    0x3: write to bus
      lower opcode: specifies bus
    0x4-0xF: reserved
  */
  std::uint4_t upperOpcode = (std::uint4_t)((this->rom & 0xF000) >> 12);
  std::uint4_t lowerOpcode = (std::uint4_t)((this->rom & 0x0F00) >> 8);
  std::uint8_t arg = (std::uint8_t)(this->rom & 0x00FF);
  if(upperOpcode == 0x0){
    if(lowerOpcode == 0x0){
      this->isErr = true;
    }
    if(lowerOpcode == 0x1){
      this->acc = 0x0;
    }
    if(lowerOpcode == 0x2){
      this->acc = ((acc & 0x00FF) | ((uint16_t)arg << 8))
    }
    if(lowerOpcode == 0x3){
      this->acc = ((acc & 0xFF00) | arg)
    }
  }
  if(upperOpcode == 0x1){
    if(lowerOpcode == 0x0){

    }
  }
  if(upperOpcode == 0x2){

  }
  if(upperOpcode == 0x3){

  }
}
