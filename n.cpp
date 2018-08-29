#include <stdio.h>
#include <stdlib.h>
#include <new>
class A{};

int main(){
char *buff = (char*)malloc(sizeof(A));
A* pA = new (buff)A();
	return 0;
}
