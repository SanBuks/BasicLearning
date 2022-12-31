#include <cmath>
#include <cstdio>

#define POS_INFINITY 0X7FF0000000000000
#define NEG_INFINITY 0XFFF0000000000000
#define NEG_ZERO     0X8000000000000000

#define POS_INFINITY2 1e400
#define NEG_INFINITY2 -POS_INFINITY2
#define NEG_ZERO2     1.0/POS_INFINITY2

int main() {

  printf("%f\n", INFINITY);
  printf("%f\n", NAN);

  // 通过编码方式
  printf("%f\n", POS_INFINITY);
  printf("%f\n", NEG_INFINITY);
  printf("%f\n", NEG_ZERO);

  // 通过转化方式
  printf("%f\n", POS_INFINITY2);
  printf("%f\n", NEG_INFINITY2);
  printf("%f\n", NEG_ZERO2);
  return 0;
}