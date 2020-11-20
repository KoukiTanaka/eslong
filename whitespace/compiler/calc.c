#include"common.h"

void ctr_calc(){
	char code = my_getc();

	if( code == ' '){
		code = my_getc();
		if( code == ' '){
			print("add_();");
		}else if(code == '\t'){
			print("sub_();");
		}else if( code == '\n'){
			print("mul_();");
		}
	}else if(code == '\t'){
		code = my_getc();
		if( code == ' '){
			print("div_();");
		}else if(code == '\t'){
			print("mod_();");
		}else if( code == '\n'){
			error();
		}
	}else if(code == '\n'){
		error();
	}
}