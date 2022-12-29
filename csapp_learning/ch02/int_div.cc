#include <cstdio>
#include <cassert>
#include <cstdint>

// 右移实现 div 16
int32_t Div16(int32_t x){
  // 正常版本
  // return ( (x > 0) ? ( x >> 4 ) : ((x + ((1 << 4) - 1))  >> 4 ));
  // 稍微简化
  // return ( (x > 0) ? ( x >> 4 ) : (x + 15 >> 4 );
  // 通过第三变量消除分支, x>0, bias=0, x<0, bias=0xF
  int32_t bias = (x >> 31) & 0xF;
  return (bias + x) >> 4;
}

int main() {
  int a = -3 / 2;
  // 机器级已经对负数的补码除法是向下取整做出了调整
  // 变成正常的向零取整
  assert(a==-1);

  int32_t aa = -77;
  int32_t bb = 77;
  printf("%d / 16 = %d\n", aa, Div16(aa));
  printf("%d / 16 = %d\n", bb, Div16(bb));
  return 0;
}