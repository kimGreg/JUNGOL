#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char str[400100];
int fail[400100];

void make_failure_function(char *str, int * fail, int len){
	for(int i=2, k=0; i<=len; ++i){
		while(k && str[k+1] != str[i])
			k = fail[k];
		if(str[k+1] == str[i])
			fail[i] = ++k;
	}
}

void print(int len){
	if(len == 0)
		return;
	print(fail[len]);
	printf("%d ", len);
}

int main(){
	int len;
	scanf("%s", str+1);
	len = strlen(str+1);
	make_failure_function(str, fail, len);
	
	print(len);

	return 0;
}
