#include <cstdio>
#include <algorithm>
using namespace std;

bool d1[2][1010], d2[2][1010];

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	d1[1][0] = d2[1][0] = 1;
    
	int ans = 0;
	for(int i=1; i<=n; i++){
		int a;
		scanf("%d", &a);
		for(int j=0; j<m; j++){
			if(d1[i%2][j] + d2[i%2][j]){
				ans = max(ans, j);
				d2[1-i%2][j] = 1;
				d1[1-i%2][j] = 1;
			}
			if(d2[i%2][j]){
				d1[1-i%2][(j+a)%m] = 1;
				ans = max(ans, (j+a)%m);
			}
		}
	}
	printf("%d", ans);
	return 0;
}
