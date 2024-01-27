# 3.1 程序编码
## 基础命令
- `gcc -Og -S` 生成符合原始 C 代码的汇编  `-c` 生成目标代码 `-o` 生成可执行程序
    - `-O1/-O2` 表示不同优化等级
    - `-masm=intel` 使用 intel 格式, gcc 和 objdump 默认为 AT&T 格式
- `objdump -d xxx.o` 对目标的代码反汇编
- `(gdb) x/14xb multstore` multstore的地址开始 打印(x/) 14个十六进制的字节(14xb)

## 机器代码抽象
- ISA : 指令集架构, 定义了机器级程序的格式和行为, 定义了处理器状态及程序行为对状态的影响
- 虚拟内存 : 可以把内存, 硬判等存储器看作一个非常大的字节数组 
> 一般 64位机器的高16位一般设置为0, 总体为 2^48字节

## 寄存器
- 程序计数器 (PC) : %rip 存放下一条指令地址
- 16个 通用寄存器 : 存放整数或地址, 一般用于保存实参, 局部变量和返回值等
- 条件码寄存器 (PSW) : 保存算术或逻辑指令状态信息, 保存控制流信息
- 向量寄存器 : 保存多个整数 或 浮点数

## 程序内存
- 机器代码
- 操作系统信息 和 运行时栈
- 堆

> 举了个 汇编 比 C 更高效的例子, 快速获取 ParityFlag 信息

# 3.2 数据格式

| 类型   | 汇编后缀 | 大小(x86-64) |
| ------ | -------- | ------------ |
| char   | b        | 1B           |
| short  | w        | 2B           |
| int    | l        | 4B           |
| long   | q        | 8B           |
| char * | q        | 8B           |
| float  | s        | 4B           |
| double | l(不产生歧义整数和浮点数指令不一样)| 8B |

# 3.3 访问信息
## 整数寄存器
### 寄存器类型

| 用途       | 寄存器名字       |
| --------- | --------------- |
| 返回值     | ax               |
| 栈指针     | sp              |
| 参数1-6    | di si dx cx 8 9   |
| 调用者保存  | 10 11           |
| 被调用者保存1-6 | bx bp 12 13 14 15 |

### 两个寄存器命名规则

| 64位 | 32位 | 16位 | 8位  |
| ---- | ---- | ---- | ---- |
| rax  | eax  | ax   | al   |
| r8   | r8d  | r8w  | r8b  |

### 三个 x86-64 下指令通用规则
- 在寄存器中产生 32 位结果的指令会默认将高 32 位置零 (如 movl, movzbl, movsbl 等等)
- 在寄存器中产生 16 位 或 8 位 结果的指令不对高位进行任何修正
- 16 位 或 8 位 寄存器在用于地址计算时或符号扩展为64位 如 `jmp *(ax)`
> 高 32 位置零解决寄存器依赖问题, 方便寄存器重命名解决并发执行问题

## 操作数指示符

| 格式           | 操作数值             | 类型         |
| -------------- | -------------------- | ------------ |
| $ num          | num                  | 立即数寻址   |
| ra             | R[ra]                | 寄存器寻址   |
| num            | M[num]               | 绝对寻址     |
| (ra)           | M[R[ra]]             | 间接寻址     |
| num(ra, rb)    | M[num+R[ra]+R[rb]]   | 变址寻址     |
| num(ra, rb, s) | M[num+R[ra]+R[rb]\*s] | 比例变址寻址 |

> 比例因子 s = (1,2,4,8)

## 数据传送指令
- 传送 S -> D 中, S 可以是立即数, 内存和寄存器, D 可以是内存和寄存器  ( 注意 一定以64位寄存器表示内存 )
- 传送过程中不可以内存 -> 内存, 必须有寄存器进行中间过渡

| 移动指令        | mov S D (S->D) |
| ------------- | -------------- |
| movb/w/l/q    | 传送 字节/字/双字/四字 |
| movabsq I R  | 传送 绝对四字立即数 到 寄存器(只能是寄存器)|

> movq 如果源是立即数, 只能为32位补码然后符号扩充到高位 

- 传送 S -> R 中 源可以是 内存和寄存器, 目标必须是寄存器

| 移动零拓展指令  | movz S R (S->R) |
| ------------- | -------------- |
| movzb<w/l/q>        | 字节 零拓展到 字/双字/四字 |
| movzw<l/q>          | 字 零拓展到 双字/四字  |

> movzlq 被 movl 取代

| 移动符号拓展指令        | movs S R (S->R) |
| ------------- | -------------- |
| movsb<w/l/q>  | 字节 符号拓展到 字/双字/四字  |
| movsw<l/q>    | 字 符号拓展到 双字 |
| movslq		| 双字 符号拓展到 四字|
| cltq		  	| %eax 符号拓展到 %rax|

- 无符号类型拓展为有符号类型 则先符号拓展为 int (提升为大整型) 再进行下一次拓展 (C 规定)
- 类型转换如果发生截取则 先转存原类型再截取
- 注意某些生成双字的命令可以取代生成四字的命令 如 movzbq => movzbl 
- 注意 char 在 gcc 实现层面为有符号数

## 压栈弹栈

| 指令    | 效果                           |
| ------- | ------------------------------ |
| pushq S | %rsp = %rsp - 8<br>M[%rsp] = S |
| popq D  | D = M[%rsp]<br>%rsp = %rsp + 8 |

- 一般栈底在高位地址, 可以通过 %rsp + n * 8 读取栈内任意元素

# 3.4 算术与逻辑运算

> 只有算数右移区分无符号和有符号，其他运算符有相同的位级等价性

## 加载有效地址
- `leaq S, D` : &S -> D   将源的地址赋予目标
- 一般作用于加法和优化乘法

## 一元和二元操作
> 一元二元, 移位和逻辑操作都有 b w l q四个版本

- 一元 : `inc, dec, neg, not D` : op D -> D  
- 二元 : `add, sub, imul, xor, or, and S, D` : S op D -> D

> xor D, D : 是指令长度较小的清零 

## 移位操作
- `sal(shl), sar(算术右移), shr(逻辑右移) k, D` : k op D  -> D
- k 是立即数 或 存放在 %cl 
    - %cl 有效位数m :  2^m=w(D)  (确保移位k<数据位数) 
- D 可存放在寄存器和内存

## 特殊算术操作

| 指令 S 等价为64位操作数 | 效果 |
| --- | --- |
| imulq S 有符号全乘法 | S \* %rax -> %rdx : %rax |
| mulq S 无符号全乘法 | S \* %rax -> %rdx : %rax |
| clto 符号拓展为8字   | %rax -> %rdx : %rax |
| idivq S 有符号全除法 | %rdx : %rax mod S -> %rdx<br/>%rdx : %rax div S ->  %rax |
| divp S 无符号全除法  | %rdx : %rax mod S -> %rdx<br/>%rdx : %rax div S -> %rax |
| cqto(att) / cqo(intel) | 有符号 除法通过 cqto 将 rax 的符号位拓展到rdx中|
> imulq 单操作数全乘法 与 双操作数乘法 在位级上一致， 会根据操作数数目选择调用

# 3.5 控制

## 条件码
- CF : 进位标志 检测无符号溢出
- ZF : 判断结果是否为零
- SF : 判断结果是否为负数
- OF : 是否产生补码溢出
> leaq 不改变任何条件码, 其余上述指令根据类别改变不同的条件码

- `cmp S1, S2` 根据 S2-S1 结果设定条件码 , 有bwlq四个版本
- `test S1, S2`根据S1&S2 结果设定条件码, 有bwlq四个版本, 一般用 `testq rax, rax` 判断 rax 与 0 的关系, 或用掩码判断某些位

## 访问条件码

| 指令 ( D是 1字节寄存器 或 1字节内存地址 ) | 效果         |
| --------------------------- | ---------------------- |
| sete/setz D 相等 / setne/setnz D 不相等 | D <-- ZF / D <-- ~ZF   |
| sets D 负数 / setns D 非负数   | D <-- SF / D <-- ~SF   |
| setg/setnle D 大于(有符号)  | D <-- ~( OF^SF ) & ~ZF |
| setge/setnl D 大于等于      | D <-- ~( OF^SF )       |
| setl/setnge D 小于          | D <-- OF^SF            |
| setle/setng D 小于等于      | D <-- ( OF^SF \| ZF )  |
| seta/setnbe D 大于 (无符号) | ~CF & ~ZF              |
| setae/setnb D 大于等于      | ~CF                    |
| setb/setnae D 小于          | CF                     |
| setbe/setna D 小于等于      | CF \| ZF               |

-  由于是1字节寄存器, 获得多字节结果时要将寄存器高位清零

## 跳转指令
- `jmp .Label` : 直接跳转到 Label 处 ( 运行时 Label 变成相应地址 )
- `jmp *Operand` : 间接跳转, 以 Operand 结果为目标跳转
- `j<e/ne/g/ge...> Label` : 条件跳转, 通配 set 指令后的相关判断
- 跳转规则 : 实际编码时, 跳转目标指令地址与紧跟跳转指令后的指令地址之差为编码(补码表示), 原因在于 rip 的自增
- AMD 中 以 rep ret 为组合防止问题 :  ret 以跳转指令到达时 CPU不能正确预测 ret 指令的目的

## 条件
- 通过条件控制实现分支
```c
	t = expr;
	if (!t) goto false; // 先对 false条件跳转 可实现 短路求值
	then-statement;
	goto done;
false:
	else-statement;
	goto done;
done:
	rep; ret;
```

- 通过条件传送实现分支有助于处理器流水线处理指令
```c
// 1. 一般运行时间期望为 Tavg(p) = Tok + pTmp, 
// 2. 使用条件跳转实现分支要考虑到 额外计算成本 和 额外计算的合法性
// 3. 一般 gcc 只会对简单的分支语句进行优化
v = then-expr;
ve = else-expr;
t = test-expr;
if(!t) v = ve;
```

## 循环
### do-while 循环
```c
loop:
	body-statement;
	t = test-expr;
	if (t) goto loop;
```

### while 循环
- for 循环可等价为 while 循环 body-statement 增加更新语句
```c
//  1. jump to middle
	goto test;
loop:
	body-statement;
test:
	t = test-expr;
	if(t) goto loop;
	rep; ret;
	
//  2. guarded-do
	t = test-expr;
	if(!t) goto done;
loop:
	body-statement;
	t = test-expr;
	if(t) goto loop;
done;
```

### switch 语句 
- 将标签转换为跳转表, 跳转表一般存放在 `.rodata` 只读数据中
```c
// 跳转表,  && 取标签的指令地址
// 一般跳转表存储在 .rodata 只读数据段中, 每组存放机器字长的地址
static void *jt[] = {
	&&loc_A, &&loc_def, &&loc_B, 
	&&loc_C, &&loc_D, &&loc_def,
	&&loc_D
};

//  BASE 因标签而异, 标签可以为任意整数
//  但最终会被映射为无符号数
unsigned long index = n - BASE; 
if (index > INDEX_MAX) goto loc_def;
else goto *jt[index];

loc_A:
	...
loc_B:
	...
loc_C:
	...
loc_D:
	...
loc_def:
	...
done:
	...
```

# 3.6 过程
## 转移控制
- `call Label` : 将本指令后的指令地址压入栈中(返回地址), pc 置为 `&&Label`
- `call *Operand` : 将本指令后的指令地址压入栈中(返回地址), pc 置为 `*Operand`
- `ret` : 将 PC 置为返回地址

## 局部存储
- 在栈上分配局部变量的情况
    - 寄存器不够用
    - 产生左值
    - 产生数组或者结构等复杂数据结构
- 局部存储的变量与在栈上传参不同, 会存在对齐压缩的情况

## 栈上传递参数
- di, si, dx, cx, r8w, r9w : 1-6 参数
- 其中超出6个则在栈上分配
- 通过栈传递参数, 每个参数的地址都与机器字长对齐

## 寄存器传递参数
- 被调用者保存寄存器 : rbx, rbp, r13 - r15, 调用者调用其他过程后需要再次用到的寄存器, 由被调用者在过程开始存放在栈上, 结束前弹栈恢复
- 调用者保存寄存器 : 可被任何过程修改的寄存器, 调用者前由调用者额外暂存, 非前者的寄存器均可视作调用者保存寄存器

## 内存分布
- 过程需要创建超出寄存器个数的变量时会在运行时栈上保存相应的栈帧, P 调用 Q ( Q中会调用 Z ) 则创建如下部分 : 
    - push 被调用者保存寄存器
    - 创建局部变量
    - 创建超出6个调用参数之外的调用参数 ( 假设 Q 调用了Z )
    - 创建 Q 的返回地址 ( 调用 Z 后的指令地址 )
- 栈上构建的对象内存位置需要对齐机器字长





# 3.7 数组
```c
T a[N];  // S = sizeof(T)
T temp_a = a[n];  //  M[a+ S * n]
T temp_b = *(a+n);  // M[a + S * n]
T b[L][M][N];
T temp_c = b[i][j][k];  // M[a + 1 * S * k + N * S * j + M * N * S * i]
```

- 在优化遍历数组代码情况下会参考 `for (iterator it = begin; it != end; ++it)`的模式

# 3.10 习题

3.18 注意条件分支 先处理条件失败跳转
3.26 & 3.28
```c
// 1. 判断 1 个数的奇偶性
long val = 0;
while(x > 0) {
    val ^= x;
	x>>=1;
}
long parity_is_odd = val & 0x1;

// 2. 转置一个无符号数
unsigend long val = 111;
while(int i = 64; i > 0; --i) {
	int low_bit = x & 0x01;
	val <<= 1;
	val |= low_bit;
	x >>= 1;
}
```
3.31 注意跳转表的默认情况