#include"common.h"

void error(){
	fprintf(stderr,"syntax error\n");
	exit(1);
}
char my_getc(){
	char code;
	while(1){
		code = getchar();
		if( code == EOF){
			error();
		}
		if( code == '\n' || code == '\t' || code == ' '){
			break;
		}
	}
	
	return code;
}
int get_number(){
	char code;
	int num = 0;
	while((code = my_getc()) != '\n'){
		num *= 2;
		if( code == '\t'){
			num += 1;
		}else if(code == ' '){
			num += 0;
		}
	}
	return num;
}

void print(char *s){
	printf("\t%s\n",s);
}
