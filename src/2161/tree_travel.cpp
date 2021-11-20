#include <cstdio>
#include <cstring>
using namespace std;

char P[30], I[30];

void postorder(int a, int b, int c, int d){
	if(b < a) return;
	int k=c;
	while(I[k] != P[a]) k++;
	postorder(a+1, a+k-c, c, k-1);
	postorder(a+k-c+1, b, k+1, d);
	printf("%c", P[a]);
}

int main(){
	scanf("%s %s", P, I);
	int len = strlen(P);
	postorder(0, len-1, 0, len-1);
	return 0;
}
