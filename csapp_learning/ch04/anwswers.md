# 4.2
```assembly
# A :
0x100 : irmovq $-4, rbx
0x10A : rmmovq rsi, 0x800(rbx)
# B :
0x200 : pushq rsi
0x202 : call 0x020C
0x20B : halt
0x20C : irmovq $10, rbx
0x216 : ret
# C :
0x300 : mrmovq 7(rsp), rbp 
0x30A : nop
0x30B : f0b01f -> instruction error !
# D :
0x400 : subq rcx, rbx
0x402 : je 0x400
0x40B : halt
# E : 
0x500 : xorq rsi, rdx
0x502 : pushq f0 -> instruction error !
```

# 4.4

```assembly
# long *start in rdi, long count in rsi
rsum:
    testq rsi, rsi
    jle done
    push rbx
    movq rdi, rbx # 只需保留局部的 start 变量
    leaq 8(rdi), rdi
    subq $1, rsi
    call rsum
    addq (rbx), rax
    pop rbx
    ret
done:
    movq $0, rax
    ret
```

# 4.5 
```assembly
# long absSum(long *start, long count)
# start in %rdi, count in %rsi
# 条件分支做法
sum: 
	irmovq $8, r8 # start 增加的步长
	irmovq $1, r9 # count 减少的步长
	xorq rax, rax # 清零
	andq rsi, rsi
	jle test # jump middle 做法
loop:
	mrmovq (rdi), rdx
	andq rdx, rdx
	jge refresh
# <0 求相反数
	irmovq 0xFFFF FFFF FFFF FFFF, rcx #  求反
	xorq rcx, rdx
	irmovq $1, rcx
	addq rcx, rdx  # +1 
refresh:
	addq rdx, rax
	addq r8, rdi
	subq r9, rsi
test :
	jne loop;
	ret
```

# 4.6 
```assembly
# long absSum(long *start, long count)
# start in %rdi, count in %rsi
# 条件传送做法
sum : 
	irmovq $8, r8 # start 增加的步长
	irmovq $1, r9 # count 减少的步长
	xorq rax, rax # 清零
	andq rsi, rsi
	jle test # jump middle 做法
loop:
	mrmovq (rdi), rdx
	mrmovq (rdi), r10
	
	xorq rcx, rcx   # 0
	subq r10, rcx	# - r10 求相反数
	andq rdx, rdx
	cmovl rcx, rdx

	addq rdx, rax
	addq r8, rdi
	subq r9, rsi
test :
	jne loop;
	ret
```

# 4.11
```verilog
word Mid3 = [
    (B <= A && A <= C) || (C <= A && A <= B) : A;
    (A <= B && B <= C) || (C <= B && B <= A) : B;
    1 : C;
];
```

# 4.32
```assembly
pop rsp             F D E M W
bubble                    E M W
rrmovq rsp, rax       F D D E M W
#                         m_valM = M[rsp] 
#                         M_valE = rsp+8
# m_valM 转发优先级大于  M_valE
```

# 4.33
```assembly
pop rsp             F D E M W
nop                   F D E M W
nop                     F D E M W
rrmovq rsp, rax           F D E M W
#                           W_valM = M[rsp] 
#                           W_valE = rsp+8
# W_valM 转发优先级大于  W_valE
```