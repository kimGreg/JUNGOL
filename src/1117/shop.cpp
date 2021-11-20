#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

int capa[500][500], flow[500][500], path[500]; 

// 0 : Source , 1~n : student, n+1~n+m : gift, n+m+1 : Sink 
int main(){
	int n, m;
	scanf("%d %d", &n, &m);;
	for(int i=1; i<=n; i++){
		int k;
		scanf("%d", &k);
		capa[0][i] = 1;
		capa[i+n][n+m+1] = 1;
		for(int j=1; j<=k; j++){
			int temp;
			scanf("%d", &temp);
			capa[i][temp+n] = 1;
		}
	}
	// 0->n+n+1 flow 찾기
	int ans = 0;
	while(1){
		fill(path, path+n+m+2, -1);
		queue<int> que;
		que.push(0);
		while(!que.empty()){
			int now = que.front();
			que.pop();
			for(int i=0; i<=n+m+1; i++){
				if(path[i] == -1 && capa[now][i] - flow[now][i] > 0){
					path[i] = now;
					que.push(i);
				}
			}
		}
		if(path[n+m+1] == -1) break;
		
		for(int i=n+m+1; i != 0; i = path[i]){
			flow[path[i]][i]++;
			flow[i][path[i]]--;
		}
		ans++;
	}
	printf("%d", ans);
	return 0;
}
