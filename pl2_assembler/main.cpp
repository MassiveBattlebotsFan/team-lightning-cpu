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
    std::map<unsigned int, string> opcodes;
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
    opcodesIn.open("./opcodes.db");
    if(opcodesIn.bad()){
      throw("opcodes.db not found.");
    }
    char buffer1[4096] = "", buffer2[4096] = "", buffer3[4096] = "";
    while(!opcodesIn.eof()){
      opcodesIn.getline(buffer1, 4096, '\n');
      if(opcodesIn.fail()){
        if(opcodesIn.bad()){
          throw("opcodes.db read stream broke");
        }
        char temp[] = "opcodes.db read loop breaking, ";
        throw(strcat(temp, strerror(errno)));
        cerr << buffer1 << endl;
        break;
      }
      stringstream parser;
      parser.str(buffer1);
      parser.getline(buffer2, 4096, '=');
      cerr << buffer2 << endl;
    }
    return 0;
  }catch(const char* error){
    cerr << "Error: " << error << endl;
    return -1;
  }catch(...){
    cerr << "Unknown error. Program aborting." << endl;
    return -1;
  }
}
