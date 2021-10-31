#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 300100;

int N;
vector<int> adj[MAXN];
long long subTreeSize[MAXN], level[MAXN];

void input(){
    cin >> N;
    for(int i=1; i<N; i++){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
}

int dfs(int now, int par){
    level[now] = level[par]+1;
    subTreeSize[now] = 1;
    for(auto next : adj[now]){
        if(next == par) continue;
        subTreeSize[now] += dfs(next, now);
    }
    return subTreeSize[now];
}

long long solve(){
    dfs(1, 0);
    long long ans = 0;
    for(int i=1; i<=N; i++)
        ans += (level[i]-1)*(N-1);

    for(int i=2; i<=N; i++)
        ans -= (subTreeSize[i]-1)*(subTreeSize[i])/2;

    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    input();
    cout << solve() << "\n";

    return 0;
}