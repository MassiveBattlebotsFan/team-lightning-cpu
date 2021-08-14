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
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "headers/menu.hpp"
using namespace std;

int main(int numArgs, char* args[]){
  //init cout to run in hex mode
  cout << "PL2 vCPU control\nStarting..." << std::hex << endl;
  ofstream log("pl2.log");
  auto rdbuf_bak = clog.rdbuf();
  clog.rdbuf(log.rdbuf());
  for(int i = 1; i < numArgs; i++){
    if(strcmp(args[i], "-v")==0){
      clog.rdbuf(rdbuf_bak);
      log.close();
    }
  }
  int errors = menu(); //starts the control menu
  cout << "PL2 vCPU shutting down with code " << errors << "..." << endl;
  log.close();
  clog.rdbuf(rdbuf_bak);
  return 0;
}
