#include <cstdio>
#include <limits>
#include <cstdint>

// 无符号溢出判断
bool UAddOk(unsigned x, unsigned y) {
  return x + y >= x;
}

void TestUAddOk() {
  unsigned int uia = 0XFFFFFFFEU;
  unsigned int uib = 0X00000001U;
  unsigned int uic = 0X00000002U;

  printf("------unsigned int add test------\n");
  std::printf("%.8x + %.8x %s overflow\n", uia, uib, UAddOk(uia, uib) ? "doesn't" : "");
  std::printf("%.8x + %.8x %s overflow\n", uia, uic, UAddOk(uia, uic) ? "doesn't" : "");
}

// 补数相加溢出判断
bool TAddOk(int x, int y) {
  // 2^(w-1) <= x + y <= 2^w-2
  // -2^(w-1)<= x + y - 2^w <= -2 < 0
  return !(x > 0 && y > 0 && x + y < 0) &&
         !(x < 0 && y < 0 && x + y >= 0);
  // -2^w <= x + y < -2^(w-1)
  // 0 <= x + y + 2^w < 2^(w-1)
}

void TestTAddOk() {
  int ia = 0X7FFFFFFF;
  int ib = 0X00000001;
  int ic = 0X80000000;
  int id = 0X80000000;

  printf("------signed int add test------\n");
  std::printf("%.8x + %.8x %s overflow\n", ia, ib, TAddOk(ia, ib) ? "doesn't" : "");
  std::printf("%.8x + %.8x %s overflow\n", ic, id, TAddOk(ic, id) ? "doesn't" : "");
  std::printf("%.8x + %.8x %s overflow\n", ib, ic, TAddOk(ib, ic) ? "doesn't" : "");

}

// 判断补码减法法是否溢出
bool TSubOk(int x, int y) {
  // -T_MIN = T_MIN
  if (y == std::numeric_limits<int>::lowest()) {
    return x < 0;
  } else {
    return TAddOk(x, -y);
  }
}

void TestTSubOk() {
  int ia = 0X7FFFFFFF;
  int ib = 0X00000001;
  int ic = 0X80000000;
  int id = 0X80000000;

  printf("------signed int sub test------\n");
  std::printf("%.8x - %.8x %s overflow\n", ia, ib, TSubOk(ia, ib) ? "doesn't" : "");
  std::printf("%.8x - %.8x %s overflow\n", ic, id, TSubOk(ic, id) ? "doesn't" : "");
  std::printf("%.8x - %.8x %s overflow\n", ib, ic, TSubOk(ib, ic) ? "doesn't" : "");
}

// 判断补码乘法是否溢出
bool TMulOk(int x, int y) {
  int t = x * y;
  return !x || t / x == y;
}

// 判断补码乘法是否溢出 拓宽位数
bool TMulOk64(int32_t x, int32_t y) {
  int64_t t1 = (int64_t) x * y;  // 默认转换为 int64_t
  return int32_t(t1) == t1;
}

void TestTMulOk() {
  int ia = 0X7FFFFFFF;
  int ib = 0X00000001;
  int ic = 0X80000000;
  int id = 0X80000000;

  printf("------signed int mul test------\n");
  std::printf("%.8x * %.8x %s overflow\n", ia, ib, TMulOk(ia, ib) ? "doesn't" : "");
  std::printf("%.8x * %.8x %s overflow\n", ic, id, TMulOk(ic, id) ? "doesn't" : "");
  std::printf("%.8x * %.8x %s overflow\n", ib, ic, TMulOk(ib, ic) ? "doesn't" : "");

  printf("------signed int mul64 test------\n");
  std::printf("%.8x * %.8x %s overflow\n", ia, ib, TMulOk64(ia, ib) ? "doesn't" : "");
  std::printf("%.8x * %.8x %s overflow\n", ic, id, TMulOk64(ic, id) ? "doesn't" : "");
  std::printf("%.8x * %.8x %s overflow\n", ib, ic, TMulOk64(ib, ic) ? "doesn't" : "");
}

int main() {
  TestUAddOk();
  TestTAddOk();
  TestTSubOk();
  TestTMulOk();
}