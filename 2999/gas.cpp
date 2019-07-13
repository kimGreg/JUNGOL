#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;

class data{
public:
	ll now, fule, last_GS;
	data(){}
	data(ll N, ll F, ll L){
		now = N;
		fule = F;
		last_GS = L;
	}
	bool operator<(const data & D)const{
		return fule > D.fule;
	}
};

vector<pair<ll, ll>> adj[2250];
priority_queue<data> que;
ll visit[2550][2550], arr[2550];

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i=1; i<=n; i++) scanf("%lld", arr+i);
	for(int i=0; i<m; i++){
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		adj[a].push_back({b, c});
		adj[b].push_back({a, c});
	}
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			visit[i][j] = -1;
	visit[1][1] = 0;
	que.push({1, 0, 1});
	while(!que.empty()){
		ll now = que.top().now;
		ll fule = que.top().fule, GS = que.top().last_GS;
		que.pop();
		if(now == n){
			printf("%lld", fule);
			break;
		}
		if(visit[now][GS] < fule) continue;
		if(arr[GS] > arr[now]) GS = now;
		for(auto it : adj[now]){
			ll next = it.first, dist = it.second;
			if(visit[next][GS] != -1 && visit[next][GS] <= fule + arr[GS]*dist)
				continue;
			visit[next][GS] = fule + arr[GS]*dist;
			que.push({next, visit[next][GS], GS});
		}
	}
	return 0;
}
