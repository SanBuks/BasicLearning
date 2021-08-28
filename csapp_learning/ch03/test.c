#include "stdio.h"
int main() {
  char c = 0xAA;
  unsigned a = (unsigned)(unsigned char) c;
  printf("%u", a);
}
