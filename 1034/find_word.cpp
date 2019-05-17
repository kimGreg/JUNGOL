#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char str[110];
int arr[110];

int main(){
	scanf("%s", str);
	int sz = strlen(str);
	for(int i=0; i<sz; i++) arr[i] = str[i];
	int k = next_permutation(arr, arr+sz);
	for(int i=0; k && i<sz; i++) str[i] = arr[i];
	printf("%s", str);
	return 0;
}	
