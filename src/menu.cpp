#include <iostream>
#include <iomanip>
#include <cstring>
#include "headers/menu.hpp"
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
      cout << "\nFinished execution of ROM." << endl;
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
    if(strcmp(input, "detach")==0){
      cout << "Detaching ROM..." << endl;
      cpu.detach();
      cout << "Detached ROM." << endl;
    }
  }
  free(input);
  return 0;
}
