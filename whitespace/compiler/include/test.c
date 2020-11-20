#include<stdio.h>

int main(){
	int a=0;
	int *s = &&LOOP1;
LOOP1:
	a++;
	if( a > 100){
		goto LOOP2;
	}
 goto *s;
LOOP2:
 printf("a = %d\n",a);
 return 0;
}