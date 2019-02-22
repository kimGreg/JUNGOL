#include <cstdio>
const int mod = 42043;
int cnt[1010], d[1010][2], temp[1010], n, k, t;

void dp(int now, int a, int b){
	if(now == 1){
		for(int i=0; i<=k; i++) d[i][a] = cnt[i], d[i][b] = 0;
		return;
	}
	dp(now/2, b, a);
	for(int i=0; i<=k; i++) d[i][a] = temp[i] = 0;
	for(int i=0; i<=k; i++)
		for(int j=0; j<=i; j++)
			d[i][a] = (d[i][a] + (d[j][b]*d[i-j][b])%mod)%mod;
	if(now%2){
		for(int i=0; i<=k; i++) 
			for(int j=0; j<=i; j++) 
				temp[i] = (temp[i] + (d[j][a]*cnt[i-j])%mod)%mod;
		for(int i=0; i<=k; i++) d[i][a] = temp[i];
	}
}

int main(){
	scanf("%d %d %d", &n, &k, &t);
	for(int i=0; i<t; i++){
		int temp;
		scanf("%d", &temp);
		if(temp <= k) cnt[temp]++;
	}
	dp(n, 0, 1);
	int ans = 0;
	for(int i=0; i<=k; i++) ans = (ans + d[i][0])%mod;	
	printf("%d", ans);
	return 0;
}
