#include <stdio.h>
#include <string.h>
typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len){
	size_t i=0;
	for(; i<len; ++i)
		printf("%.2x ", start[i]);
	printf("\n");
}

void show_int(int x){
	show_bytes((byte_pointer)&x, sizeof(int));
}

void show_long(long x){
	show_bytes((byte_pointer)&x, sizeof(long));
}

void show_double(double x){
	show_bytes((byte_pointer)&x, sizeof(double));
}

_Bool isLitteEndian(){
	int a=1;
	return *((char*)&a);
}

int main(){
	if(isLitteEndian()) printf("little endian\n");
	else printf("little endian\n");
	const char *p="abcdef";
	show_int(10);
	show_long(20);
	show_double(-123.1);
	show_bytes((byte_pointer)(p), strlen(p)+1);
	return 0;
}
