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
    //auto old_rdbuf = clog.rdbuf(); // not implemented
    clog.rdbuf(logging.rdbuf());

    std::map<uint8_t, string> opcodes = {};

    if(argc == 1){
      cerr << "Usage: " << argv[0] << " <source.pl2> [output.pl2c]" << endl;
      return -1;
    }
    string outfile, infile = argv[1];
    if(argc >= 3){
      outfile = argv[2];
    }else{
      outfile = infile + 'c';
    }
    ifstream opcodesIn;
    opcodesIn.open("opcodes.db");
    if(!opcodesIn.is_open()){
      throw("opcodes.db open failed");
    }
    char buffer1[4096] = "", buffer2[4096] = "", buffer3[4096] = "";
    stringstream parser;
    while(!opcodesIn.eof()){
      parser.str("");
      opcodesIn.getline(buffer1, 4096, '\n');
      if(opcodesIn.fail()){
        if(opcodesIn.bad()){
          throw("opcodes.db read stream bad");
        }
        if(opcodesIn.eof()){
          break;
        }
        throw("opcodes.db read loop failed");
      }
      parser << buffer1 << '\0';
      parser.getline(buffer2, 4096, '=');
      parser.getline(buffer3, 4096, '\0');
      clog << buffer2 << ", " << buffer3 << endl;
      opcodes.insert(std::pair<uint8_t, string>((uint8_t)strtol(buffer2, NULL, 16), (string)buffer3));
    }
    opcodesIn.close();
    
    return 0;
  }catch(const char* error){
    cerr << "Error: " << error << ", errno = " << strerror(errno) << endl;
    return -1;
  }catch(...){
    cerr << "Unknown error. Program aborting." << endl;
    return -1;
  }
}
