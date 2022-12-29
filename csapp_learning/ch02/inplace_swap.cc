#include <iostream>

void inplace_swap(int &a, int &b) {
  a = a ^ b;
  b = a ^ b;
  a = a ^ b;
}

int main() {
  int a = 1, b = 2;
  inplace_swap(a, b);
  std::cout << a << " " << b << "\n";
  return 0;
}