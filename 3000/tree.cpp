#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

vector<int> adj[200200];
int par[200200];
int group[200200], visit[200200], groupCnt = 1, vcnt = 1;

void seperate(int now){
	if(par[now] == 0) return;
	int a = now, b = par[now];
    while(par[b] == 0) b = par[b];
    
	// delete edge
    adj[b].erase(find(adj[b].begin(), adj[b].end(), a));
	par[a] = 0;

	//find less rank group
    stack<pair<int, int>> A, B;
    A.push({a, 0});
    B.push({b, 0});
    
    vcnt++;
	int change;
    if(A.empty()) change = a;
    else change = b;
    
    
    //update group
	vcnt++;
	groupCnt++;
	queue<int> que;
	visit[change] = vcnt;
	que.push(change);

	while(!que.empty()){
		int now = que.front();
		que.pop();
		group[now] = groupCnt;
		for(auto it : adj[now]){
			if(visit[it] != vcnt){
				visit[it] = vcnt;
				que.push(it);
			}
		}
	}
}

int main(){
	int n, q;
	scanf("%d %d", &n, &q);
	for(int i=1; i<=n; i++) group[i] = 1;
	for(int i=2; i<=n; i++){
		int temp;
		scanf("%d", &temp);
		adj[temp].push_back(i);
		par[i]=temp;
	}
	while(q--){
		int b, c, d;
		scanf("%d %d %d", &b, &c, &d);
		printf("%s\n", group[b]==group[c]?"YES":"NO");
		if(d){//delete
			if(group[b] == group[c])
				seperate(b);
			else
				seperate(c);
		}
	}
	return 0;
}
