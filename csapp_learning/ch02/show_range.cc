#include <cstdlib>
#include <limits>
#include <iostream>

template <typename T>
void ShowRange() {
  std::cout << std::numeric_limits<T>::min() << " ~ "
            << std::numeric_limits<T>::max() << "\n";
}

template <typename T>
void ShowFloatRange() {
  std::cout << std::numeric_limits<T>::lowest() << " ~ "
            << std::numeric_limits<T>::max() << "\n";
}

int main() {
  std::cout << "machine words size: " << sizeof(int *) << "\n";

  std::cout << "unsigned short: "; ShowRange<unsigned short>();
  std::cout << "short: "; ShowRange<short>();

  std::cout << "unsigned int: "; ShowRange<unsigned int>();
  std::cout << "int: "; ShowRange<int>();

  std::cout << "unsigned long: "; ShowRange<unsigned long>();
  std::cout << "long: "; ShowRange<long>();

  std::cout << "float: "; ShowFloatRange<float>();
  std::cout << "double: "; ShowFloatRange<double>();
  std::cout << "long double: "; ShowFloatRange<long double>();

  return EXIT_SUCCESS;
}