#include <iostream>

bool IsLittleEndian() {
  constexpr int a = 1;
  return *(reinterpret_cast<const char *>(&a));
}

int main() {
  std::cout << IsLittleEndian();
  return 0;
}
