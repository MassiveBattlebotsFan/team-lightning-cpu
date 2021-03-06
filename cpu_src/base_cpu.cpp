#include <cstdint>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <bitset>
#include <map>
#include <functional>
#include <chrono>
#include "headers/base_cpu.hpp"

BaseCPU::BaseCPU(){
  this->opCode = 0x0;
  this->accumulator = 0x0;
  this->instrArg = 0x0;
  for(uint16_t i = 0; i < 0x1FFF; i++){
    this->datMem[i] = 0x0;
  }
  this->execAddr = 0x0;
  this->datAddr = 0x0;
  this->datReg = 0x0;
}

uint16_t BaseCPU::run(uint32_t instruction){
  std::stringstream formattedInstr;
  formattedInstr << std::hex << std::setfill('0') << std::setw(6) << instruction;
  //std::cerr << formattedInstr.str() << std::endl;
  char fOpcode1[16];
  strncpy(fOpcode1, formattedInstr.str().c_str(), 2);
  char fArg1[16];
  strncpy(fArg1, formattedInstr.str().c_str() + 2, 4);
  std::uint8_t formattedOpcode = (uint8_t)strtol(fOpcode1, NULL, 16);
  std::uint16_t formattedArg = (uint16_t)strtol(fArg1, NULL, 16);
  return this->interpretInstr(formattedOpcode, formattedArg);
}

std::uint32_t BaseCPU::interpretInstr(uint8_t opCode, uint16_t arg){
  this->opCode = opCode;
  this->instrArg = arg;
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
  switch(this->opCode){
    case 0xC:
      this->execAddr = this->instrArg;
      return 0x0;
      break;
    case 0xB: {
      if(this->accumulator != 0x0){
        this->execAddr = this->datMem[this->datAddr];
      }
      return 0x0;
      break;
    }
    case 0xA: {
      this->datMem[this->datAddr] = this->execAddr;
      return 0x0;
      break;
    }
    case 0x9:{
      uint16_t temp = this->accumulator;
      this->accumulator = this->datReg;
      this->datReg = temp;
      return 0x0;
      break;
    }
    case 0x8:
      this->accumulator -= this->instrArg;
      return this->accumulator;
      break;
    case 0x7:
      this->accumulator += this->instrArg;
      return this->accumulator;
      break;
    case 0x6:
      this->datReg = this->datAddr;
      return this->datReg;
      break;
    case 0x5:
      if(this->datReg <= 0x1FFF){
        this->datAddr = this->datReg;
        return 0xFF;
        break;
      }else{
        return 0x0;
        break;
      }
    case 0x4:
      return this->accumulator;
      break;
    case 0x3:
      this->accumulator = this->instrArg;
      return this->instrArg;
      break;
    case 0x2:
      this->datReg = this->datMem[this->datAddr];
      return 0x0;
      break;
    case 0x1:
      this->datMem[this->datAddr] = this->datReg;
      return 0x0;
      break;
    case 0x0:
      return 0x99999999;
      break;
    default:
      for(auto pair : this->opCodes){
        if(this->opCode == pair.first){
          pair.second();
        }
      }
      break;
  }
  return this->opCode;
}

void BaseCPU::exec(){
  uint32_t ret;
  std::chrono::steady_clock::time_point beginExec = std::chrono::steady_clock::now();
  long double avgClock = 0.0;
  int cycles = 0;
  for(this->execAddr; this->execAddr < 0x1FFF; this->execAddr+=2){
    std::chrono::steady_clock::time_point beginInstr = std::chrono::steady_clock::now();
    //std::cerr << std::hex << std::setfill('0') << std::setw(2) << (uint16_t)this->datMem[this->execAddr] << std::setw(4) << (uint16_t)this->datMem[this->execAddr+1] << std::endl; //error checking data load
    ret = this->interpretInstr((this->datMem[this->execAddr]&0b0000000011111111), this->datMem[this->execAddr+1]);
    std::chrono::steady_clock::time_point endInstr = std::chrono::steady_clock::now();
    std::chrono::nanoseconds instrTimeSpan = std::chrono::duration_cast<std::chrono::nanoseconds>(endInstr - beginInstr);
    while(true){
      endInstr = std::chrono::steady_clock::now();
      instrTimeSpan = std::chrono::duration_cast<std::chrono::nanoseconds>(endInstr - beginInstr);
      if(instrTimeSpan.count()/1000000 >= 0.9){
        break;
      }
    }
    //std::clog << "\ninstr time: " << instrTimeSpan.count() << " nanoseconds" << std::endl;
    avgClock += instrTimeSpan.count();
    cycles++;
    if(ret == 0x99999999){
      break;
    }
  }
  std::chrono::steady_clock::time_point endExec = std::chrono::steady_clock::now();
  std::chrono::microseconds instrTimeSpan = std::chrono::duration_cast<std::chrono::microseconds>(endExec - beginExec);
  std::clog << "\nexec time: " << instrTimeSpan.count() << " microseconds" << std::endl;
  std::clog << "average instr time: " << (avgClock/cycles)/1000 << " microseconds" << std::endl;
  std::clog << "average clock speed: " << (1/(avgClock/cycles))*1000000 << " kHz" << std::endl;
}
