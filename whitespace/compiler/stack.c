#include "common.h"

void ctr_stack(){
	char code;
	code = my_getc();
	if( code == ' '){
		push_stack();
	}else if(code == '\n'){
		code = my_getc();
		if( code == ' '){
			print("copy_stack();");
		}else if(code == '\t'){
			print("swap_stack();");
		}else if(code == '\n'){
			print("pop_stack();");
		}
	}else if(code == '\t'){
		code = my_getc();
		if( code == ' '){
			 copy_n_stack();
		}else if(code == '\n'){
			del_stack();
		}else if( code == '\t'){
			error();
		}
	}
}
int get_integer(){
	int sign;
	int value;
	char code;
	code = my_getc();
	if( code == ' '){
		sign = 1;
	}else if(code == '\t'){
		sign = -1;
	}
	value = get_number();
	return sign * value;
}
void push_stack(){
	int value = get_integer();
	printf("\tpush_stack(%d);\n",value);
}
void del_stack(){
	int value = get_integer();
	printf("\tdel_stack(%d);\n",value);
}
void copy_n_stack(){
	int value = get_integer();
	printf("\tcopy_n_stack(%d);\n",value);
}