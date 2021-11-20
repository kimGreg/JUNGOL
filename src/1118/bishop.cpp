#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

int arr[110][110], A[110][110], b[6000], visit[6000], vcnt;
vector<vector<int>> adj;

int dfs(int now){
	if(visit[now] == vcnt) return 0;
	visit[now] = vcnt;
	for(int i=0; i<adj[now].size(); i++){
		int next = adj[now][i];
		if(!b[next] || dfs(b[next])){
			b[next] = now;
			return 1;
		}
	}
	return 0;
}

int getAns(){
	int ans = 0;
	
	for(int i=0; i < adj.size(); i++){
		vcnt++;
		if(dfs(i)) ans++;
	}

	return ans;
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i=0; i<m; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		arr[a][b] = 1;
	}
	int cnt = 1;
	for(int i=1; i<n+n; i++){
		int x, y;
		if(i <= n){
			x = 1;
			y = n-i+1;
		}else{
			y = 1;
			x = i-n+1;
		}

		while(x <= n && y <= n){
			if(arr[x][y] == 1) cnt++;
			else A[x][y] = cnt;
			x++; 
			y++;
		}
		cnt++;
	}
	
	cnt = 1;
	for(int i=1; i<n+n; i++){
		int x, y;
		if(i <= n){
			y = 1;
			x = i;
		}else{
			x = n;
			y = i-n+1;
		}

		while(1 <= x && x <= n && 1<= y &&  y <= n){
			if(arr[x][y] == 1) cnt++;
			else{
				adj.resize(cnt+1);
				adj[cnt].push_back(A[x][y]);
			}
			x--;
			y++;
		}
		cnt++;
	}
	printf("%d", getAns());

	return 0;
}
