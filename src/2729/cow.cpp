#include <cstdio>
using namespace std;

int d[2][1<<13];
int MOD = 100000000;

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	d[0][0] = 1;

	for(int i=0; i<n*m; i++){
		int now;
		scanf("%d", &now);
		for(int k=0; k<(1<<(m+1)); k++)
			d[1][k] = 0;

		for(int j=0; j<(1<<(m+1)); j++){
			if(d[0][j]){
				int k = j >> 1;
				d[1][k] = (d[1][k] + d[0][j])%MOD;
				if(now){
					if((k&1) || ((k & (1<<(m-1))) && (i%m != 0)))
						continue;
					d[1][k + (1 << m)] = (d[1][k + (1 << m)] +  d[0][j])%MOD;
				}
			}
		}
		
		for(int k=0; k<(1<<(m+1)); k++)
			d[0][k] = d[1][k];

	}

	int ans = 0;
	for(int k=0; k<(1<<(m+1)); k++){
		ans = (ans + d[0][k])%MOD;
	}

	printf("%d", ans);
	return 0;
}
