#include <cstdint>
#include <strstream>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <bitset>
#include <map>
#include <functional>

#include "headers/cpu.hpp"

#define UINT24_MAX (4095)
#define UINT_LEAST24_MAX (4095)

BaseCPU::BaseCPU(){
  this->opCode = 0x0;
  this->accumulator = 0x0;
  this->instrArg = 0x0;
  for(uint16_t i = 0; i < 0x1FFF; i++){
    this->datMem[i] = 0x0;
  }
  for(uint16_t i = 0; i < 0xFFFF; i++){
    this->romBuffer[i] = 0x0;
  }
  this->romAddr = 0x0;
  this->execAddr = 0x0;
  this->datAddr = 0x0;
}

std::uint16_t BaseCPU::run(uint16_t instruction){
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

std::uint16_t BaseCPU::interpretInstr(uint8_t opCode, uint8_t arg){
  this->opCode = opCode;
  this->instrArg = arg;
  /*
  opcodes [TEMP]:
  0x00/invalid: returns the opcode, basically no operation
  0x01: sets romAddr to arg
  0x02: gets romAddr to accumulator
  0x03: sets datMem at datAddr to accumulator
  0x04: gets datMem at datAddr to accumulator
  0x05: sets accumulator
  0x06: gets accumulator
  0x07: sets lower byte of datAddr to instrArg
  0x08: sets upper byte of datAddr to instrArg
  0x09: add arg to accumulator
  0x0A: sub arg from accumulator
  0x0B: store romAddr in datMem[arg] for loops (only in programs)
  0x0C: if accumulator != 0 jump to datMem[arg](upper nibble) and datMem[arg+1](lower nibble) (only in programs)
  */
  switch(this->opCode){
    case 0xC: {
      if(this->accumulator != 0x0){
        this->execAddr = this->datMem[this->datAddr];
      }
      return 0x0;
      break;
    }
    case 0xB: {
      this->datMem[this->datAddr] = this->execAddr;
      return 0x0;
      break;
    }
    case 0xA:
      this->accumulator -= this->instrArg;
      return this->accumulator;
      break;
    case 0x9:
      this->accumulator += this->instrArg;
      return this->accumulator;
      break;
    case 0x8: {
      if(this->instrArg <= 0x1F){
        uint8_t temp = (this->datAddr & 0b00001111);
        this->datAddr = (this->instrArg << 8) | temp;
        return this->instrArg;
      }else{
        return 0xFFFF;
      }
      break;
    }
    case 0x7: {
      uint8_t temp = (this->datAddr >> 8);
      this->datAddr = (temp << 8) | this->instrArg;
      return this->instrArg;
      break;
    }
    case 0x6:
      return this->accumulator;
      break;
    case 0x5:
      this->accumulator = this->instrArg;
      return this->instrArg;
      break;
    case 0x4:
      return this->datMem[this->instrArg];
      break;
    case 0x3:
      this->datMem[this->instrArg] = this->accumulator;
      return this->accumulator;
      break;
    case 0x2:
      return this->romAddr;
      break;
    case 0x1:
      this->romAddr = this->instrArg;
      return this->romAddr;
      break;
    case 0x0:
      return 0x9999;
      break;
    default:
      return this->opCode;
      break;
  }
  return this->opCode;
}

bool BaseCPU::attach(char fname[1024]){
  std::ifstream ifile;
  char buffer[0xFF];
  ifile.open(fname);
  if(ifile.good()){
    uint16_t i = this->romAddr;
    for(this->romAddr; this->romAddr < 0x10000; this->romAddr++){
      ifile.getline(buffer, 0xFF, ';');
      std::cerr << buffer << std::endl;
      if(ifile.eof()){
        break;
      }
      this->romBuffer[this->romAddr] = (uint16_t)strtol(buffer, NULL, 16);
    }
    this->romAddr = i;
    return true;
  }
  else{
    return false;
  }
}

void BaseCPU::load(uint16_t offset){
  for(uint16_t i = offset; i < 0x1FFF - offset; i++){
    this->datMem[i] = this->romBuffer[i];
    if(this->romBuffer[i] == 0x0000){
      break;
    }
  }
}
/*
void BaseCPU::exec(){
  uint16_t ret;
  for(this->progAddr; this->progAddr < 0xFF; this->progAddr++){
    //std::cerr << std::hex << std::setfill('0') << std::setw(4) << (uint16_t)this->progMem[this->progAddr] << std::endl; //error checking data load
    ret = this->run(this->progMem[this->progAddr]);
    if(ret == 0x9999){
      break;
    }
  }
}
*/
uint16_t* BaseCPU::romdump(){
  return this->romBuffer;
}
