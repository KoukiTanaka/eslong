#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define max_file_size 100000 /*100K*/
#define mem_size 10000000 /*10M (40 megs of ram)*/

typedef struct {
	unsigned from;
	unsigned to;
	char case1;
} bytecode;

int *mem, vars[26], fs;
char *file;
unsigned char *input = 0;

int geti() {
	int i=0;
	if(input) {
		sscanf(input, "%d", &i);
		while(*input >= '0' && *input <= '9') input++;
	} else scanf("%d", &i);
	return i;
}

int getic() {
	if(input) {
		if(*input) return *(input++);
		else return -1;
	} else {
		return (unsigned)getchar();
	}
}

int debugi(int c, int *mp) {
	int i=0;
	printf("\n[ ");
	for(i=0; i<26; i++) printf("%c:%d ",i+'a', i==2?c:vars[i]);
	printf("\n");
	for(i=0; i<26; i++) printf("%c:%d ",i+'A', mp[i]);
	printf("]\n");
	return 0;
}

void get_input_source() {
	char *f;
	for(f=file; *f; f++) {
		if(!input && *f=='!') {
			input = f + 1;
			*f = '\0';
		}
	}
}

void clean_code() {
	char goods[256];
	int i;
	char *from, *to;
	from = to = file;
	
	for(i=0;i<256;i++) goods[i] = 0;
	for(i=65;i<91;i++) goods[i] = 1;
	for(i=97;i<123;i++) goods[i] = 1;
	for(i=48;i<58;i++) goods[i] = 1;
	goods[95] = goods[123] = goods[125] = goods[35] = goods[10] = 1;
	
	while(*from) {
		if(goods[(int)*from]) *(to++) = *from;
		from++;
	}
	*to = 0;
	fs = to - file;
}

void remove_pound_comments() {
	char *from, *to;
	from = to = file;
	while(*from) {
		if(*from == '#') while(*(++from) != '\n' && *from != '\0');
		else if(*from != '\n') *(to++) = *from;
		if(!*from) break;
		from++;
	}
	*to = 0;
	fs = to - file;
}

void remove_bracket_comments() {
	char *from, *to;
	from = to = file;
	int count = 0;
	while(*from) {
		if(*from == '}') {
			if(count) count--;
			else to = file;
		} else if(*from == '{') {
			count++;
		}
		else if(!count) {
			*(to++) = *from;
		}
		from++;
	}
	*to = 0;
	fs = to - file;
}

bytecode *compile(char *filename) {
	char *fp;
	FILE *f = fopen(filename, "r");
	if(!f) {fprintf(stderr,"file not found: %s\n", filename); exit(1); }
	file = malloc(max_file_size);
	file[fread(file, 1, max_file_size, f)]=0;
	fclose(f);
	fs=strlen(file);
	
	get_input_source();
	clean_code();
	remove_pound_comments();
	remove_bracket_comments();
	
	bytecode *rp, *ret = malloc((fs+10) / 2 * sizeof(bytecode));
	for(fp = file, rp = ret; *fp; fp++, rp++) {
		char i = *fp;
		if(i == 'o') { rp->case1 = 2; }
		else if(i == 'q') { rp->case1 = 3; }
		else if(i == 'p') { rp->case1 = 4; }
		else if(i == 'c') { rp->case1 = 5; }
		else if(i<='Z' && i>='A') { rp->case1 = 0; rp->to = i - 'A'; }
		else if(i<='z' && i>='a') { rp->case1 = 1; rp->to = i - 'a'; }
		else if(i == '_') { rp->case1 = -1; }
		else if(i<='9' && i>='0') {
			do { i=*(++fp); } while (i<='9' && i>='0');
			fp--;
			rp->case1 = -1;
		}
		else printf("shouldn't get here 1\n");
		rp->case1 *= 8;
		
		i=*(++fp);
		if(!i) { fprintf(stderr, "parse error: odd number of operands\n"); exit(1); }
		if(i == 'i') { rp->case1 += 3; }
		else if(i == 'j') { rp->case1 += 4; }
		else if(i == 'r') { rp->case1 += 5; }
		else if(i == 'c') { rp->case1 += 6; }
		else if(i == '_') { rp->case1 += 7; }
		else if(i<='Z' && i>='A') { rp->from = i - 'A'; }
		else if(i<='z' && i>='a') { rp->case1 += 1; rp->from = i - 'a'; }
		else if(i<='9' && i>='0') {
			int num = 0;
			do {
				num*=10;
				num+=i-'0';
				i=*(++fp);
			} while (i<='9' && i>='0');
			fp--;
			rp->case1 += 2; rp->from = num;
		}
		else printf("shouldn't get here 2\n");
	}
	rp->case1 = -1;
	fs = rp - ret;

	return ret;
}

int main(int argc, char **argv) {
	if(argc != 2) { fprintf(stderr, "usuage: iminus <filename>\n"); return 1; }
	bytecode *code = compile(argv[1]);
	srand(time(0));
	
	mem=calloc(mem_size+50, sizeof(int));
	int maxp = mem_size / 2;
	int minp = -maxp;
	int *maxmp = mem + mem_size;
	int *minmp = mem;
	int *memp = mem + maxp;
	
	/* z -> -1, y -> -2, x -> -10, w -> -32, v -> -mem_size, last Z -> -1 */
	vars[25]-=1; vars[24]-=2; vars[23]-=10; vars[22]-=32; vars[21] -= maxp;
	maxmp[25]-=1;
	
	
	int temp, *p = vars + 'p' - 'a', *r = vars + 'r' - 'a';
	bytecode *cp = code;
	
	top:
	switch (cp->case1) {
case 0: memp[cp->to] -= memp[cp->from]; cp++; goto top;
case 1: memp[cp->to] -= vars[cp->from]; cp++; goto top;
case 2: memp[cp->to] -= cp->from; cp++; goto top;
case 3: memp[cp->to] -= getic(); cp++; goto top;
case 4: memp[cp->to] -= geti(); cp++; goto top;
case 5: memp[cp->to] -= (rand()%(*r+!(*r))*(1-2*(((*r)>>31)&1))); cp++; goto top;
case 6: memp[cp->to] -= (cp-code); cp++; goto top;
case 7: memp[cp->to] -= debugi(cp-code,memp); cp++; goto top;
case 8: vars[cp->to] -= memp[cp->from]; cp++; goto top;
case 9: vars[cp->to] -= vars[cp->from]; cp++; goto top;
case 10: vars[cp->to] -= cp->from; cp++; goto top;
case 11: vars[cp->to] -= getic(); cp++; goto top;
case 12: vars[cp->to] -= geti(); cp++; goto top;
case 13: vars[cp->to] -= (rand()%(*r+!(*r))*(1-2*(((*r)>>31)&1))); cp++; goto top;
case 14: vars[cp->to] -= (cp-code); cp++; goto top;
case 15: vars[cp->to] -= debugi(cp-code,memp); cp++; goto top;
case 16: putchar(-memp[cp->from]); cp++; goto top;
case 17: putchar(-vars[cp->from]); cp++; goto top;
case 18: putchar(-cp->from); cp++; goto top;
case 19: putchar(-getic()); cp++; goto top;
case 20: putchar(-geti()); cp++; goto top;
case 21: putchar(-(rand()%(*r+!(*r))*(1-2*(((*r)>>31)&1)))); cp++; goto top;
case 22: putchar(-(cp-code)); cp++; goto top;
case 23: putchar(-debugi(cp-code,memp)); cp++; goto top;
case 24: printf("%d", -memp[cp->from]); cp++; goto top;
case 25: printf("%d", -vars[cp->from]); cp++; goto top;
case 26: printf("%d", -cp->from); cp++; goto top;
case 27: printf("%d", -getic()); cp++; goto top;
case 28: printf("%d", -geti()); cp++; goto top;
case 29: printf("%d", -(rand()%(*r+!(*r))*(1-2*(((*r)>>31)&1)))); cp++; goto top;
case 30: printf("%d", -(cp-code)); cp++; goto top;
case 31: printf("%d", -debugi(cp-code,memp)); cp++; goto top;
case 32: temp = memp[cp->from]; (*p) -= temp; memp -= temp; if(memp < minmp) { memp = minmp; (*p) = minp; } else if(memp > maxmp) { memp = maxmp; (*p) = maxp; }; cp++; goto top;
case 33: temp = vars[cp->from]; (*p) -= temp; memp -= temp; if(memp < minmp) { memp = minmp; (*p) = minp; } else if(memp > maxmp) { memp = maxmp; (*p) = maxp; }; cp++; goto top;
case 34: temp = cp->from; (*p) -= temp; memp -= temp; if(memp < minmp) { memp = minmp; (*p) = minp; } else if(memp > maxmp) { memp = maxmp; (*p) = maxp; }; cp++; goto top;
case 35: temp = getic(); (*p) -= temp; memp -= temp; if(memp < minmp) { memp = minmp; (*p) = minp; } else if(memp > maxmp) { memp = maxmp; (*p) = maxp; }; cp++; goto top;
case 36: temp = geti(); (*p) -= temp; memp -= temp; if(memp < minmp) { memp = minmp; (*p) = minp; } else if(memp > maxmp) { memp = maxmp; (*p) = maxp; }; cp++; goto top;
case 37: temp = (rand()%(*r+!(*r))*(1-2*(((*r)>>31)&1))); (*p) -= temp; memp -= temp; if(memp < minmp) { memp = minmp; (*p) = minp; } else if(memp > maxmp) { memp = maxmp; (*p) = maxp; }; cp++; goto top;
case 38: temp = (cp-code); (*p) -= temp; memp -= temp; if(memp < minmp) { memp = minmp; (*p) = minp; } else if(memp > maxmp) { memp = maxmp; (*p) = maxp; }; cp++; goto top;
case 39: temp = debugi(cp-code,memp); (*p) -= temp; memp -= temp; if(memp < minmp) { memp = minmp; (*p) = minp; } else if(memp > maxmp) { memp = maxmp; (*p) = maxp; }; cp++; goto top;
case 40: cp-=memp[cp->from]; if((unsigned)(++cp - code)>=fs) goto done; goto top;
case 41: cp-=vars[cp->from]; if((unsigned)(++cp - code)>=fs) goto done; goto top;
case 42: cp-=cp->from; if((unsigned)(++cp - code)>=fs) goto done; goto top;
case 43: cp-=getic(); if((unsigned)(++cp - code)>=fs) goto done; goto top;
case 44: cp-=geti(); if((unsigned)(++cp - code)>=fs) goto done; goto top;
case 45: cp-=(rand()%(*r+!(*r))*(1-2*(((*r)>>31)&1))); if((unsigned)(++cp - code)>=fs) goto done; goto top;
case 46: cp-=(cp-code); if((unsigned)(++cp - code)>=fs) goto done; goto top;
case 47: cp-=debugi(cp-code,memp); if((unsigned)(++cp - code)>=fs) goto done; goto top;
	}
	
	done:
	free(file);
	free(code);
	free(mem);
	return 0;
}

/* generated from (ruby)
from=['memp[cp->from]',
'vars[cp->from]',
'cp->from',
'getic()',
'geti()',
'(rand()%(*r+!(*r))*(1-2*(((*r)>>31)&1)))',
'(cp-code)',
'debugi(cp-code,memp)']

to=['memp[cp->to] -= from; cp++',
'vars[cp->to] -= from; cp++',
'putchar(-from); cp++',
'printf("%d", -from); cp++',
'temp = from; (*p) -= temp; memp -= temp; if(memp < minmp) { memp = minmp; (*p) = minp; } else if(memp > maxmp) { memp = maxmp; (*p) = maxp; }; cp++',
'cp-=from; if((unsigned)(++cp - code)>=fs) goto done']

48.times{|i|puts "case #{i}: #{to[i/8].sub('from',from[i%8])}; goto top;"}
*/