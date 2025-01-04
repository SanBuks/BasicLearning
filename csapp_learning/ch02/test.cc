#include <iostream>

// *   Legal ops: ! ~ & ^ | + << >>

int allOddBits(int x) {
  int a = ((0xAA << 8) + 0xAA);
  a = (a << 16) + a;
  return !((x&a)^a);
}

int isAsciiDigit(int x) {
  // 0x30 - x - 1 < 0
  int a = (0x30 + ~x) >> 31;
  // x - 0x39 - 1 < 0
  int b = (x + ~0x39) >> 31;
  return a & b;
}

int main() {
  std::cout << isAsciiDigit(0x3a) << "\n";
  return 0;
}