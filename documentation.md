# CPU specifications:  
For the purposes of these specifications, one word is equal to unsigned two bytes, one byte is equal to eight bits.    
Clock speed: 1kHz maximum  
Registers: 1 word datReg, 1 word accumulator, 1 word instrArg, 1 byte opCode  
Address pointers: 1 word datAddr, 1 word romAddr, 1 word execAddr  
Memory: 0x2000 word datMem  

# Assembly commands:  
Syntax: `CMD:[4 digit hex arg]`  
0x00=HLT  
0x01=SRA  
0x02=GRA  
0x03=SDM  
0x04=GDM  
0x05=SAI  
0x06=GEA  
0x07=SDA  
0x08=GDA  
0x09=ADD  
0x0A=SUB  
0x0B=SWP  
0x0C=SED  
0x0D=JNZ  
0x0E=JMP  
0x0F=GRD  

# Current BaseCPU opcodes:  
0x00: returns 0x99999999, used for prog termination   
0x01: sets romAddr to datReg
0x02: gets romAddr to datReg  
0x03: sets datMem at datAddr to datReg  
0x04: gets datMem at datAddr to datReg  
0x05: sets accumulator to instrArg  
0x06: gets accumulator, does basically nothing  
0x07: sets datAddr to datReg  
0x08: gets datAddr to datReg  
0x09: add instrArg to accumulator   
0x0A: sub instrArg from accumulator   
0x0B: swap datReg and accumulator   
0x0C: store execAddr in datMem[datAddr] for loops (only in programs)  
0x0D: if accumulator != 0 jump execAddr to datMem[datAddr] (only in programs)   
0x0E: set execAddr to instrArg  
0x0F: get romBuffer[romAddr] to datReg  

# Extending the BaseCPU:
Extension modules have access to BaseCPU::datReg, BaseCPU::datMem, BaseCPU::instrArg, and BaseCPU::datAddr.    
A typical extension looks like this, where `OPCODE` is the opcode used to run a module:    
<pre><code>class ExtendedCPU() : public BaseCPU(){    
  protected:    
    void ExampleModule(){ //this cannot take arguments, and must return void    
      //do stuff    
    }   
  ExtendedCPU() : BaseCPU(){    
    this->opCodes = {{(uint8_t)YOUR_OPCODE, std::bind(&ExtendedCPU::ExampleModule, this)}};
    //above binds opcode to function for execution by the CPU     
  }    
};</code></pre>

# Using extended CPUs with the PL2 control menu   
To use an extended CPU with the PL2 control menu ([menu.cpp](menu.cpp), [menu.hpp](headers\menu.hpp)), edit the [cpu.cpp](cpu.cpp) and [cpu.hpp](headers/cpu.hpp) files to add modules you need.
