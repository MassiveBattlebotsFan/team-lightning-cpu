#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <cstring>
#include <map>

using namespace std;

int main(int argc, char const *argv[]) {
  try{
    //init logging to file
    ofstream logging("pl2asm.log");
    auto old_rdbuf = clog.rdbuf(); // not implemented
    clog.rdbuf(logging.rdbuf());

    std::map<string, uint16_t> opcodes = {};
    string opcodesDb = "opcodes.db";
    if(argc == 1){
      cerr << "Usage: " << argv[0] << " <source.pl2> [opcodes.db]" << endl;
      return -1;
    }
    string outfile, infile = argv[1];
    //if(argc >= 3){
    //  outfile = argv[2];
    //}else{
      outfile = infile + 'c';
    //}
    if(argc >= 2){
      opcodesDb = argv[2];
    }
    ifstream opcodesIn;
    opcodesIn.open(opcodesDb);
    if(!opcodesIn.is_open()){
      throw("opcodes db open failed");
    }
    char buffer1[4096] = "", buffer2[4096] = "", buffer3[4096] = "";
    stringstream parser;
    while(opcodesIn.getline(buffer1, 4096, '\n')){
      parser.str("");
      if(opcodesIn.fail()){
        if(opcodesIn.bad()){
          throw("opcodes db read stream bad");
        }
        if(opcodesIn.eof()){
          break;
        }
        throw("opcodes db read loop failed");
      }
      parser << buffer1 << '\0';
      parser.getline(buffer2, 4096, '=');
      parser.getline(buffer3, 4096, '\0');
      clog << buffer2 << ", " << buffer3 << endl;
      opcodes[buffer3] = (uint16_t)strtol(buffer2, NULL, 16);
    }
    opcodesIn.close();
    ifstream asmIn(infile.c_str());
    if(!asmIn.is_open()){
      throw("Assembly input file open failed");
    }
    ofstream asmOut(outfile.c_str());
    if(!asmOut.is_open()){
      throw("Assembled output file open failed");
    }
    uint16_t instrArgOut = 0x0;
    uint16_t opCodeOut = 0x0;

    while(asmIn.getline(buffer1, 4096, '\n')){
      parser.str("");
      if(asmIn.fail()){
        if(asmIn.bad()){
          throw("asm read stream bad");
        }
        throw("asm read loop failed");
      }
      parser << buffer1 << '\0';
      parser.getline(buffer2, 4096, ':');
      parser.getline(buffer3, 4096, '\0');
      instrArgOut = (uint16_t)strtol(buffer3, NULL, 16);
      opCodeOut = opcodes[buffer2];
      clog << std::hex << std::setfill('0') << std::setw(2) << opCodeOut;
      asmOut << std::hex << std::setfill('0') << std::setw(2) << opCodeOut;
      clog << std::hex << std::setfill('0') << ',' << std::setw(4) << instrArgOut << ';' << endl;
      asmOut << std::hex << std::setfill('0') << ',' << std::setw(4) << instrArgOut << ';';
    }
    asmIn.close();
    asmOut.close();
    return 0;
  }catch(const char* error){
    cerr << "Error: " << error << ", errno = " << strerror(errno) << endl;
    return -1;
  }catch(...){
    cerr << "Unknown error. Program aborting." << endl;
    return -1;
  }
}
