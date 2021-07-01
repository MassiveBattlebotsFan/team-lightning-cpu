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

int menu(){
  CPU cpu; //starts the vCPU
  char* input;
  input = new char[2048];
  while(true){
    cout << "PL2> ";
    cin.getline(input, 2048, '\n');
    //cout << input << endl;
    if(strcmp(input, "status")==0){
      cout << "Accumulator: 0x" << std::setfill('0') << std::setw(2) << cpu.getAccum() << endl;
    }
    if(strcmp(input, "exit")==0){
      break;
    }
    if(strcmp(input, "run")==0){
      cout << "opcode> ";
      uint16_t opcode = 0x0;
      cin.getline(input, 2048, '\n');
      opcode = (uint16_t)strtol(input, NULL, 16);
      cout << "Starting operation..." << endl;
      uint16_t status = cpu.run(opcode);
      cout << "Operation exited, returning: " << std::setfill('0') << std::setw(2) << status << endl;
    }
    /*
    if(strcmp(input, "reset")==0){

    }
    */
    if(strcmp(input, "load")==0){
      cout << "ROM> ";
      char rom[1024] = "";
      cin.getline(rom, 1024, '\n');
      bool ldStatus = cpu.load(rom);
      if(ldStatus){
        cout << "ROM load successful!" << endl;
      }else{
        cerr << "ROM load failed!" << endl;
      }
    }
    if(strcmp(input, "runrom")==0){
      cout << "Running ROM..." << endl;
      cpu.exec();
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
