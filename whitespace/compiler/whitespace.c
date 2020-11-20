#include "common.h"

int main(){
	char code;
	int call_stack_number = 0;
	printf("#include \"./include/whitespace.h\"\n");
	printf("\nint main(){\n");
	while(1){
		code = my_getc();
		if( code == ' '){
			ctr_stack();
		}else if( code == '\t'){
			code = my_getc();
			if(code == ' '){
				ctr_calc();
			}else if(code == '\t'){
				ctr_heap();
			}else if( code == '\n'){
				ctr_io();
			}
		}else if(code == '\n'){
			ctr_flow(&call_stack_number);
		}
	}
}
