#include<iostream>

typedef unsigned long long ULL;
using namespace std;
int main(){
	char code;
	ULL ans = 0;
	bool carry = false;
	bool first5 = false;
	while((code = getchar()) != '\n'){
		code -= '0';
		if( code >= 5){
			first5 = true;
			if(code != 5){
				first5 = false;
			}
			if( carry == true){
				code++;
			}
			carry = true;
			ans += 10 - code;
		}else{
			if(carry == true){
				if( first5 == false){
					ans++;
				}
			}
			carry = false;
			first5 = false;
			ans += code;
		}
	}
	cout << ans << endl;
}