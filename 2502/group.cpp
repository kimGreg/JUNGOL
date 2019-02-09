#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
int line[3030][3030], arr[3030][3030], d[3030], path[3030], n;
void print(int now, int d){
    if(now == 0){
        printf("%d ", d);
        return;
    }
	print(path[now], d+1);
	printf("%d ", now-path[now]);
}

int main(){
	scanf("%d", &n);
	for(int i=1; i<=n; i++){
		while(1){
			int a;
			scanf("%d", &a);
			if(a == 0) break;
			if(a>i) line[i][a] = arr[i][a]  = 1;
		}
	}
    for(int i=1; i<=n; i++) for(int j=1; j<=n; j++) arr[i][j] += arr[i][j-1];
    for(int i=n; i>=1; i--) for(int j=1; j<=n; j++) arr[i][j] += arr[i+1][j];
	for(int i=1; i<=n; i++){
		d[i] = i*(i-1)/2 - arr[1][i];
		for(int j=1; j<i; j++){
			int sz = i-j, Ttotal = sz*(sz-1)/2;
			int val = d[j] +  (Ttotal - arr[j+1][i]) + arr[1][i] - arr[1][j] - arr[j+1][i];
			if(d[i] > val){
				d[i] = val;
				path[i] = j;
			}
		}
	}
	printf("%d\n", d[n]);
	print(n, 0);
	return 0;
}
