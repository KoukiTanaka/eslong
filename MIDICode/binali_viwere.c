#include<stdio.h>
#include<stdlib.h>

#define SIZE 10

int main(int args, char **argc){
	FILE *fp;
	int n;
	int i,size;
	int count;
	unsigned char code[SIZE];
	if( (fp = fopen(argc[1],"rb")) == NULL ){
		fprintf(stderr,"File Can't Open");
		exit(1);
	}
	count = 0;
	while(!feof(fp)){
		size = fread(code,sizeof(char),SIZE,fp);
		printf("%04X: ",count);
		for(i=0;i<size;i++){
			count++;
			printf("%02X ", code[i]);
		}
		printf("\n");
	}

	return 0;
}