#include"common.h"

void ctr_heap(){
	char code = my_getc();
	if( code == ' '){
		print("push_heap();");
	}else if(code == '\t'){
		print("get_heap();");
	}else if(code == '\n'){
		error();
	}
}