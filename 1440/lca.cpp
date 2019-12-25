#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

vector<int> adj[200200];
int par[200200];
int table[200200][20];

int log2(int a){
	int k = 0;
	while(a > 1<<k) k++;
	return k;
}

int dfs(int now, int dep=0){
	
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		par[b] = a;
	}
	int root = 0;
	for(int i=1; i<=n; i++){
		if(!par[i]){
			root = i;
			break;
		}
	}
	dfs(root);
	return 0;
}
