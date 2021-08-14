#include <iostream>
#include <sstream>
#include <fstream>
#include "headers/rom_cpu.hpp"

void RomCPU::load(uint16_t offset){
  for(uint16_t i = 0; i < 0x1FFF - offset; i+=2){
    this->datMem[i+offset] = this->romBuffer[i];
    if(this->romBuffer[i] == 0x00){
      break;
    }
    this->datMem[i+offset+1] = this->romBuffer[i+1];
  }
}
bool RomCPU::attach(char fname[1024]){
  std::ifstream ifile;
  char buffer[0xFF];
  ifile.open(fname);
  if(ifile.good()){
    for(uint16_t i = 0; i < 0xFFFF; i++){
      this->romBuffer[i] = 0x0;
    }
    uint16_t i = this->romAddr;
    for(this->romAddr; this->romAddr < 0x10000; this->romAddr+=2){
      std::stringstream split;
      ifile.getline(buffer, 0xFF, ';');
      std::cerr << buffer << std::endl;
      if(ifile.eof()){
        break;
      }
      split << buffer;
      char split1[256], split2[256];
      split.getline(split1, 3, ',');
      split.getline(split2, 5);
      this->romBuffer[this->romAddr] = (uint16_t)strtol(split1, NULL, 16);
      this->romBuffer[this->romAddr + 1] = (uint16_t)strtol(split2, NULL, 16);
    }
    this->romAddr = i;
    return true;
  }
  else{
    return false;
  }
}
void RomCPU::getRomBuffer(){
  this->datReg = this->romBuffer[this->romAddr];
}
void RomCPU::setRomAddr(){
  this->romAddr = this->datReg;
}
void RomCPU::getRomAddr(){
  this->datReg = this->romAddr;
}
RomCPU::RomCPU() : BaseCPU() {
  for(uint16_t i = 0; i < 0xFFFF; i++){
    this->romBuffer[i] = 0x0;
  }
  this->romAddr = 0x0;
  this->opCodes[(uint8_t)0x0D] = std::bind(&RomCPU::setRomAddr, this);
  this->opCodes[(uint8_t)0x0E] = std::bind(&RomCPU::getRomAddr, this);
  this->opCodes[(uint8_t)0x0F] = std::bind(&RomCPU::getRomBuffer, this);
}
uint16_t* RomCPU::romdump(){
  return this->romBuffer;
}
void RomCPU::detach(){
  for(uint16_t i = 0; i < 0xFFFF; i++){
    this->romBuffer[i] = 0x0;
  }
}
