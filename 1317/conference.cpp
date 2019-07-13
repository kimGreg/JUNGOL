#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<int> adj[110];
bool Achk[110];
int vcnt, gcnt, visit[110], Aans[110], Acnt[110], G[110];

int bfs(int now){
	queue<pair<int, int>> que;
	visit[now] = vcnt;
	que.push({now, 0});
	int res = 0;
	while(!que.empty()){
		int N = que.front().first, dep = que.front().second;
		res = max(res, dep);
		que.pop();
		for(auto it : adj[N]){
			if(visit[it] == vcnt) continue;
			visit[it] = vcnt;
			G[it] = G[N];
			que.push({it, dep+1});
		}
	}
	return res;
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i=0; i<m; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for(int i=1; i<=n; i++){
		vcnt++;
		if(G[i] == 0) G[i] = ++gcnt, Acnt[G[i]] = 2e9;
		int dep = bfs(i);
		if(Acnt[G[i]] > dep){
			Achk[Aans[G[i]]] = 0;
			Achk[i] = 1;
			Aans[G[i]] = i;
			Acnt[G[i]] = dep;
		}
	}
	printf("%d\n", gcnt);
	for(int i=1; i<=n; i++)
		if(Achk[i])
			printf("%d\n", i);
	return 0;
}
