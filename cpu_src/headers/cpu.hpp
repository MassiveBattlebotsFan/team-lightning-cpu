#ifndef PL2_CPU_H
#define PL2_CPU_H

#include <cstdint>

class PL2_CPU{
private:
  //registers
  std::uint16_t acc;
  //error var, if set CPU doesn't run
  bool isErr;

public:
  //io bus
  //2x rom and mem 32 bit bus (split 16 bit input, 16 bit output)
  //12x general purpose 16 bit bus
  //total: 16x 16 bit bus
  std::uint16_t memAddr; //output, moved by cmd
  std::uint16_t mem; //input/output
  std::uint16_t romAddr; //output, moved by clock 2 positions per pulse
  std::uint16_t rom; //input, split into upper byte = instruction, lower byte = arg
  std::uint16_t bus_5;
  std::uint16_t bus_6;
  std::uint16_t bus_7;
  std::uint16_t bus_8;
  std::uint16_t bus_9;
  std::uint16_t bus_10;
  std::uint16_t bus_11;
  std::uint16_t bus_12;
  std::uint16_t bus_13;
  std::uint16_t bus_14;
  std::uint16_t bus_15;
  std::uint16_t bus_16;

  PL2_CPU();
  void run();
  void reset();
};

#endif
