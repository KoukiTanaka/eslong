#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MAX 10000
#define CAPACITY 126
int stack[MAX];
int stack_point = 0;
int heap[MAX];
int *call_stack[MAX];
int call_stack_point = 0;

void error(char *str);

//スタック操作
void push_stack(int n);
int pop_stack();
void copy_stack();
void swap_stack();
void copy_stack_n(int n);
void del_stack(int n);

//計算
void add_();
void sub_();
void mul_();
void div_();
void mod_();

//ヒープ操作
void push_heap();
void set_heap(int address,int value);
void get_heap();

//入出力操作
void input_char();
void input_num();
void output_num();
void output_char();

//コールスタック操作
void push_call_stack(int *p);
int *pop_call_stack();

void error(char *str){
	fprintf(stderr,str);
	exit(1);
}
//スタック操作
//スタックに詰む
void push_stack(int n){
	stack[stack_point++] = n;
}

int pop_stack(){
	if( stack_point <= 0){
		error("stack point overflow\n");
	}
	return stack[--stack_point];
}
void copy_stack(){
	int temp = pop_stack();
	pop_stack(temp);
	pop_stack(temp);
}
void swap_stack(){
	int temp1,temp2;
	temp1 = pop_stack();
	temp2 = pop_stack();
	push_stack(temp1);
	push_stack(temp2);
}

void copy_stack_n(int n){
	if( n < 0 || n >= stack_point){
		error("stack point overflow\n");
	}
	push_stack(stack[n]);
}

void del_stack(int n){
	if( stack_point-1-n < 0){
		error("stack point overflow\n");
	}
	stack[stack_point-1-n] = stack[stack_point-1];
	stack_point = stack_point-1-n;
}

void add_(){
	int a,b;
	a = pop_stack();
	b = pop_stack();
	push_stack(a+b);
}
void sub_(){
	int a,b;
	a = pop_stack();
	b = pop_stack();
	push_stack(b-a);
}
void mul_(){
	int a,b;
	a = pop_stack();
	b = pop_stack();
	push_stack(a*b);
}
void div_(){
	int a,b;
	a = pop_stack();
	b = pop_stack();
	push_stack(b/a);
}
void mod_(){
	int a,b;
	a = pop_stack();
	b = pop_stack();
	push_stack(b%a);
}

//ヒープ操作
void push_heap(){
	int value = pop_stack();
	int address = pop_stack();
	set_heap(address,value);
}
void set_heap(int address,int value){
	heap[address] = value;
}
void get_heap(){
	int address = pop_stack();
	push_stack(heap[address]);
}

//入出力操作
void input_char(){
	int address = pop_stack();
	char code = getchar();

	set_heap(address,code);
}
void input_num(){
	int address = pop_stack();
	char str[CAPACITY];
	fgets(str,CAPACITY,stdin);
	set_heap(address,atoi(str));
}
void output_num(){
	int value = pop_stack();
	printf("%d",value);
}
void output_char(){
	char code = pop_stack();
	putchar(code);
}

//コールスタック操作
void push_call_stack(int *p){
	call_stack[call_stack_point++] = p;
}
int *pop_call_stack(){
	if(call_stack_point <= 0 ){
		error("call stack overflow\n");
	}
	return call_stack[call_stack_point--];
}