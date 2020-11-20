#include "common.h"

void ctr_io(){
	char code = my_getc();
	if( code == ' '){
		code = my_getc();
		if(code == ' '){
			print("output_char();");
		}else if(code == '\t'){
			print("output_num();");
		}else if(code == '\n'){
			error();
		}
	}else if(code == '\t'){
		code = my_getc();
		if(code == ' '){
			print("input_char();");
		}else if(code == '\t'){
			print("input_num();");
		}else if(code == '\n'){
			error();
		}
	}else if(code == '\n'){
		error();
	}
}