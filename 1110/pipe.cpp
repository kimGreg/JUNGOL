#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int capa[220][220], flow[220][220], path[220];

int main(){
	int m, n;
	scanf("%d %d", &m, &n);
	for(int i=0; i<m; i++){
		int a, b, f;
		scanf("%d %d %d", &a, &b, &f);
		capa[a][b] += f;
	}
	int ans = 0;

	while(1){
		fill(path, path+n+1, 0);

		queue<int> que;
		que.push(1);
		while(!que.empty()){
			int now = que.front();
			que.pop();
			for(int i=1; i<=n; i++){
				if(capa[now][i]-flow[now][i] > 0 && path[i] == 0){
					path[i] = now;
					que.push(i);
				}
			}
		}
		if(!path[n]) break;
		int mn = 2e9;
		for(int i=n; i != 1; i = path[i]){
			mn = min(mn, capa[path[i]][i] - flow[path[i]][i]);
		}
		for(int i=n; i != 1; i = path[i]){
			flow[path[i]][i] += mn;
			flow[i][path[i]] -= mn;
		}
		ans += mn;
	}

	printf("%d", ans);
	
	return 0;
}
