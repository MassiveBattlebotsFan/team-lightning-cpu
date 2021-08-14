#include <iostream>
#include "headers/cpu.hpp"

void CPU::io_out(){
  std::cout << (uint8_t)this->datReg;
}
void CPU::io_in(){
  char* temp = new char[2];
  uint16_t i = 0;
  while(std::cin.getline(temp, 1, '\n')){
    this->datMem[this->datAddr+i] = (uint8_t)temp[0];
    i++;
  }
}

CPU::CPU() : RomCPU() {
  this->opCodes[(uint8_t)0x10] = std::bind(&CPU::io_out, this);
  this->opCodes[(uint8_t)0x11] = std::bind(&CPU::io_in, this);
}
