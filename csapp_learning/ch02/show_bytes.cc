#include <cstdio>
#include <cstdlib>
#include <cstring>

template <typename T>
void ShowBytes(const T *p, size_t len = sizeof(T)) {
  // 一定是 unsigned char *, 而非 char *
  const auto *s = reinterpret_cast<const unsigned char *>(p);
  for (size_t i = 0; i != len; ++i) {
    printf("%.2x ", s[i]);  // x 表示整数, .2 表示最少两位数
  }
  printf("\n");
}

int main() {
  int int_n = 12345;
  long long long_long_n = 12345;
  float float_n = 12345.0;
  double double_n = 12345.0;
  const char *p = "aA0";

  ShowBytes(&int_n);
  ShowBytes(&long_long_n);
  ShowBytes(&float_n);
  ShowBytes(&double_n);
  ShowBytes(p, strlen(p) + 1);

  return EXIT_SUCCESS;
}