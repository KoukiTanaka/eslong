#include "common.h"


void ctr_flow(int *call_stack_number){
	char code = my_getc();
	if( code == ' '){
		code = my_getc();
		if(code == ' '){
			set_label();
		}else if( code == '\t'){
			set_call_stack(call_stack_number);
			jump_label();
		}else if( code == '\n'){
			jump_label();
		}
	}else if(code == '\t'){
		code = my_getc();
		if(code == ' '){
			jze();
		}else if( code == '\t'){
			jmi();
		}else if( code == '\n'){
			jump_call_stack();
		}
	}else if(code == '\n'){
		code = getchar();
		if( code == EOF || code == '\n'){
			printf("}\n");
			exit(0);
		}
	}
}

void set_label(){
	int label_number = get_number();
	printf("NOMAL_LABEL%d:\n",label_number);
}
void jump_label(){
	int label_number = get_number();
	printf("\tgoto NOMAL_LABEL%d;\n",label_number);
}
void jze(){
	print("if( pop_stack() == 0 ){");
	printf("\t");
	jump_label();
	print("}");
}
void jmi(){
	print("if( pop_stack() < 0 ){");
	printf("\n\t");
	jump_label();
	print("\n}");
}
void set_call_stack(int *call_stack_number){
	int num;
	printf("CALL_LABEL%d:\n",*call_stack_number);
	printf("push_call_stack(&&CALL_LABEL%d);",*call_stack_number);
	(*call_stack_number)++;
}
void jump_call_stack(){
	printf("goto pop_call_stack();");
}