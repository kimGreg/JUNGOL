#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 1010;
int N, degree[MAXN];
vector<int> adj[MAXN];

void input(){
    int M, cnt, prev, now;
    cin >> N >> M;
    while(M--){
        cin >> cnt >> now; cnt--;
        while(cnt--){
            prev = now;
            cin >> now;
            adj[prev].push_back(now);
            degree[now]++;
        }
    }
}

void solve(){
    queue<int> que;
    vector<int> ans;
    for(int i=1; i<=N; i++) 
        if(!degree[i]) que.push(i);
    while(!que.empty()){
        int now = que.front(); que.pop();
        ans.push_back(now);
        for(int next : adj[now]) 
            if(!(--degree[next])) que.push(next);
    }
    if(ans.size() < N) cout << "0\n";
    else for(auto it : ans) cout << it << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    input();
    solve();
    return 0;
}