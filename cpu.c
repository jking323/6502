#include "cpu.h"
#include <unistd.h>

// createing redefinitions to prevent having to write unsigned short int over
// and over
typedef unsigned char byte;
typedef unsigned short int twoBytes;

// register declaration and memory pool allocation
byte a, x, y;
byte stackpointer;
byte flags;
twoBytes addr, pc;
byte memory[0x10000];

// basic functions to read and write bytes and read address values
byte read_byte(byte *addr) {
  sleep(CLOCK_TIME);
  return (*addr);
}

void write_byte(byte *addr, byte value) {
  sleep(CLOCK_TIME);
  *addr = value;
  return;
}

twoBytes read_address(byte offset) {
  twoBytes val = read_byte(memory + offset + 1);
  val <<= 8;
  val |= read_byte(memory + offset);
  return (val);
}

// reset the cpu
// I need to make sure this is accurate, right now it resets registers and
// erases ram Eventually ram will be segregated into the proper format

void reset_cpu() {
  a = 0;
  x = 0;
  y = 0;
  stackpointer = 0xFF;

  // erase all memory
  for (int i = 0; i < 0xFFFF; i++) {
    memory[i] = 0;
  }

  pc = (memory[0xFFFD] << 8) | memory[0xFFFC];
}

// opcode section

void ADC(byte *addr) {
  // maybe add decimel mode later

  twoBytes result = a + (*addr) + (flags & 1);
  byte truncresult = result & 0xFF;
  byte vflag = ((a ^ truncresult) & ((*addr) ^ truncresult) & 0x80) != 0;
  write_byte(&a, truncresult);
  flags = (flags & ~UNUSED) & ~BREAK_FLAG;

  if (a & 0x80) {
    flags |= NEGATIVE;
  }
  if (vflag << 6) {
    flags |= OVERFLOW;
  }
  if (a == 0) {
    flags |= ZERO_FLAG;
  }
  if ((res & 0x100) > 0) {
    flags |= CARRY;
  }
  return;
}

void AND(byte *addr) {
  twoBytes result = (a & *addr);
  flags = ()
}
