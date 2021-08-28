	.file	"test.c"
	.text
	.globl	_test
	.def	_test;	.scl	2;	.type	32;	.endef
_test:
LFB0:
	.cfi_startproc
	movl	4(%esp), %eax
	movsbl	(%eax), %edx
	movl	8(%esp), %eax
	movl	%edx, (%eax)
	ret
	.cfi_endproc
LFE0:
	.ident	"GCC: (i686-posix-dwarf-rev2, Built by MinGW-W64 project) 7.1.0"
