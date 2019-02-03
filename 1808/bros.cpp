#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
int n, sum, arr[50][50], d[30][400010], path[30][400010];

void print(int now, int h){
	if(now == 0) return;
	print(now-1, path[now][h]);
	printf("%d ", n-d[now][h]);
}

int main(){
	scanf("%d", &n);
	for(int i=1; i<=n; i++) for(int j=1; j<=n; j++){
		scanf("%d", arr[i] + j);
		sum += arr[i][j];
		arr[i][j] += arr[i-1][j];
	}
	for(int i=0; i<=n; i++) for(int j=0; j<=sum; j++) d[i][j] = -1;
	for(int i=1; i<=n; i++) d[1][arr[i][1]] = i;
	for(int i=1; i<n; i++){
		for(int j=0; j <= sum; j++){
			if(d[i][j] == -1) continue;
			for(int k=0; k<=d[i][j]; k++){
				if(d[i+1][j+arr[k][i+1]] < k){
					d[i+1][j+arr[k][i+1]] = k;
					path[i+1][j+arr[k][i+1]] = j;
				}
			}
		}
	}
	int ans = 0;
	for(int i=0; i<=sum; i++) if(d[n][i]!=-1 && abs(sum - ans*2) > abs(sum - i*2)) ans = i;
	printf("%d\n", abs(sum-ans*2));
	print(n, ans);
	return 0;
}
