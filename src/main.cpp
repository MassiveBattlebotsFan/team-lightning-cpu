/*
Team Lightning's experimental esoteric VM
48 bit bus:
8 bit data memory
8 bit program ROM
16 bit instruction register (part that loads the instruction)
8 bit accumulator
8 bit I/O register
Instruction set:
Upper byte is instruction
Lower byte is arg
IE: 0x0E0F
*/
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include "headers/cpu.hpp"
using namespace std;

class IOCPU : public BaseCPU{
protected:
  void io_out(){
    cout << (uint8_t)this->datReg;
  }
  void io_in(){
    char* temp = new char[2];
    uint16_t i = 0;
    while(cin.getline(temp, 1, '\n')){
      this->datMem[this->datAddr+i] = (uint8_t)temp[0];
      i++;
    }
  }

public:
  IOCPU() : BaseCPU() {
    this->opCodes = {{(uint8_t)0x10, std::bind(&IOCPU::io_out, this)}, {(uint8_t)0x11, std::bind(&IOCPU::io_in, this)}};
  }
};
int menu(){
  IOCPU cpu; //starts the vCPU
  char* input;
  input = new char[2048];
  while(true){
    cout << "PL2> ";
    cin.getline(input, 2048, '\n');
    //cout << input << endl;
    /*if(strcmp(input, "status")==0){
      cout << "Accumulator: 0x" << std::setfill('0') << std::setw(2) << cpu.getAccum() << endl;
    }*/
    if(strcmp(input, "exit")==0){
      break;
    }
    if(strcmp(input, "run")==0){
      cout << "opcode> ";
      uint32_t opcode = 0x0;
      cin.getline(input, 2048, '\n');
      opcode = (uint32_t)strtol(input, NULL, 16);
      cout << "Starting operation..." << endl;
      uint16_t status = cpu.run(opcode);
      cout << "\nOperation exited, returning: 0x" << std::setfill('0') << std::setw(4) << status << endl;
    }
    /*
    if(strcmp(input, "reset")==0){

    }
    */
    if(strcmp(input, "attach")==0){
      cout << "ROM> ";
      char rom[1024] = "";
      cin.getline(rom, 1024, '\n');
      bool ldStatus = cpu.attach(rom);
      if(ldStatus){
        cout << "ROM attach successful!" << endl;
      }else{
        cerr << "ROM attach failed!" << endl;
      }
    }
    if(strcmp(input, "load")==0){
      cout << "Offset>";
      char offset[512] = "";
      cin.getline(offset, 512, '\n');
      cout << "Loading ROM..." << endl;
      cpu.load((uint16_t)strtol(offset, NULL, 16));
      cout << "ROM loaded." << endl;
    }
    if(strcmp(input, "runrom")==0){
      cout << "Running ROM..." << endl;
      cpu.exec();
      cout << "Finished execution of ROM." << endl;
    }
    if(strcmp(input, "rom")==0){
      uint16_t* pMem = cpu.romdump();
      for(uint16_t i = 0; i < 0x10000; i+=2){
        if(pMem[i]==0x0000){
          cout << "00,0000" << endl;
          break;
        }
        cout << std::setfill('0') << std::setw(2) << pMem[i] << ',' << std::setw(4) << pMem[i+1] << endl;
      }
    }
  }
  free(input);
  return 0;
}

int main(int numArgs, char* args[]){
  //init cout to run in hex mode
  cout << "PL2 vCPU control\nStarting..." << std::hex << endl;
  int errors = menu(); //starts the control menu
  cout << "PL2 vCPU shutting down with code " << errors << "..." << endl;
  return 0;
}
