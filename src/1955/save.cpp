#include <cstdio>
int r, c, sr, sc, ra[1001], ca[1001];
int main(){
	scanf("%d %d", &r, &c);
	sr=r;sc=c;
	for(int i=0; i<r; i++) for(int j=0; j<c; j++){
		char t; scanf(" %c", &t);
		if(t == '.') continue;
		if(!ra[i]) ra[i]=1, sr--;
		if(!ca[j]) ca[j]=1, sc--;
	}
	printf("%d", sr<sc?sc:sr);
	return 0;
}

