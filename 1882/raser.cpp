#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int n, k, vcnt = 1, visit[1000], b[1000];
vector<int> adj[1000];

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
	for(int i=1; i<=n; i++){
		vcnt++;
		if(dfs(i)) ans++;
	}
	return ans;
}

int main(){
	scanf("%d %d", &n, &k);
	for(int i=0; i<k; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
	}
	
	printf("%d", getAns());
	return 0;
}
