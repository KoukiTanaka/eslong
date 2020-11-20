#include "./include/whitespace.h"

int main(){
	push_stack(3);
	push_stack(0);
	push_heap();
NOMAL_LABEL1:
	push_stack(3);
	get_heap();
	push_stack(1);
	add_();
	push_stack(3);
	swap_stack();
	push_heap();
	push_stack(1);
	input_char();
	push_stack(2);
	input_char();
	push_stack(48);
	push_stack(1);
	get_heap();
	sub_();
	if( pop_stack() == 0 ){
		goto NOMAL_LABEL2;
	}
	goto NOMAL_LABEL1;
NOMAL_LABEL2:
	push_stack(3);
	get_heap();
	output_num();
}
