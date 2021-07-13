# Extending the BaseCPU:
Extension modules have access to BaseCPU::datReg, BaseCPU::datMem, and BaseCPU::datAddr.    
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
# Current opcodes [TEMP]:  
0x00: returns 0x9999, used for prog termination   
0x01: sets romAddr to instrArg  
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
