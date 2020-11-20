#include<stdio.h>
#include<stdlib.h>

#ifndef COMMON_H_
#define COMMON_H_


void ctr_flow(int *call_stack_number);
void set_label();
void jump_label();
void jze();
void jmi();
void set_call_stack(int *call_stack_number);
void jump_call_stack();

void ctr_calc();

void ctr_io();

void ctr_heap();

void ctr_stack();
void push_stack();
int get_integer();
void del_stack();
void copy_n_stack();

#endif