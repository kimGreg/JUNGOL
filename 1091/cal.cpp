#include <cstdio>
#include <cstring>
using namespace std;
char str[110];
int arr[5];

int main(){
	scanf("%s", str);
	int sz = strlen(str), buff = 0, buff2 = 0;
	for(int i=0; i<sz; i++){
		if('0' <= str[i] && str[i] <= '9'){
			buff2 = buff2*10 + str[i] - '0';
		}else{
			if(!buff2) buff2 = 1;
			arr[buff] += buff2;

			buff2 = 0;
			if(str[i] == 'C') buff = 1;
			if(str[i] == 'H') buff = 2;
			if(str[i] == 'O') buff = 3;
			if(str[i] == 'N') buff = 4;
		}
	}
	if(!buff2) buff2 = 1;
	arr[buff] += buff2;
	printf("%.3lf", (double)arr[1]*12.01 + (double)arr[2]*1.008 + (double)arr[3]*16.00 + (double)arr[4]*14.01); 
	return 0;
}
