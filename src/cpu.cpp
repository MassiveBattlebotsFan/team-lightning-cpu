#include <cstdint>
#include <strstream>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <bitset>

#include "headers/cpu.hpp"

CPU::CPU(){
  this->opCode = 0x0;
  this->accumulator = 0x0;
  this->instrArg = 0x0;
  for(uint8_t i = 0; i < 255; i++){
    this->datMem[i] = 0x0;
  }

  for(uint16_t i = 0; i < 0xFFF; i++){
    this->progMem[i] = 0x0;
  }
  this->progAddr = 0x0;
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

std::uint16_t CPU::interpretInstr(uint8_t opCode, uint8_t arg){
  this->opCode = opCode;
  this->instrArg = arg;
  /*
  opcodes [TEMP]:
  0x00/invalid: returns the opcode, basically no operation
  0x01: sets progAddr to arg
  0x02: gets progAddr to accumulator
  0x03: sets datMem at arg to accumulator
  0x04: gets datMem at arg to accumulator
  0x05: sets accumulator
  0x06: gets accumulator
  0x07: if arg is 0 reads one input byte into accumulator, else prints accumulator
  */
  switch(this->opCode){
/*
    case 0x7:
      if(this->instrArg == 0x0){
        char buffer[8];
        cin.get(buffer, 1);
        this->accumulator = buffer;
        return this->accumulator;
        break;
      }else{

      }*/
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
      return this->progAddr;
      break;
    case 0x1:
      this->progAddr = this->instrArg;
      return this->progAddr;
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

bool CPU::load(char fname[1024]){
  std::ifstream ifile;
  char buffer[0x10000];
  ifile.open(fname);
  if(ifile.good()){
    for(uint16_t i = 0; i < 0x10000; i++){
      ifile.getline(buffer, 0xFFF, ';');
      std::cerr << buffer << std::endl;
      if(ifile.eof()){
        break;
      }
      progMem[i] = (uint16_t)strtol(buffer, NULL, 16);
    }
    return true;
  }
  else{
    return false;
  }
}

void CPU::exec(){
  uint16_t ret;
  for(this->progAddr; this->progAddr < 0xFF; this->progAddr++){
    //std::cerr << std::hex << std::setfill('0') << std::setw(4) << (uint16_t)this->progMem[this->progAddr] << std::endl; //error checking data laod
    ret = this->run(this->progMem[this->progAddr]);
    if(ret == 0x9999){
      break;
    }
  }
}
