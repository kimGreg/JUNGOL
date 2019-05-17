#include <cstdio>
using namespace std;
int arr[1001000];
int main(){
	int n, m, k, ans = 0, flag = 1;
	scanf("%d %d %d", &n, &m, &k);
	for(int i=2; i<=m; i++){
		if(arr[i]) continue;
		if((i-1)%n == k) ans++;
		if(flag && i*i > m) flag = 0;
		for(int j = i*i; flag && j<=m; j+=i) arr[j] = 1;
	}
	printf("%d", ans);
	return 0;
}
