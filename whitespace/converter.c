#include<iostream>
#include<cstdio>

using namespace std;
int main(){
	char code;
	bool flag = false;
	while((code = getchar()) != EOF){
		if( code == 'S'){
			if( flag == true){
				putchar('\n');
				flag = false;
			}
			putchar(' ');
		}else if(code == 'T'){
			if( flag == true){
				putchar('\n');
				flag = false;
			}
			putchar('\t');
		}else if(code == 'L'){
			if( flag == true){
				putchar('\n');
				flag = false;
			}
			flag = true;
		}
	}
}