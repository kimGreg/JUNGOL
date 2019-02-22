#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
typedef pair<int, int> pii;
vector<pii> adj[200100];
vector<pii> temp;
int sz[200100], ans = 2e9, vcnt;
bool wasCen[200100];
int visit[200100], vMin[1000100], Min[1000100];
int n, k;

void getSize(int now){
    visit[now] = vcnt;
    sz[now] = 1;
    for(auto it : adj[now]){
        if(visit[it.first] == vcnt || wasCen[it.first]) continue;
        getSize(it.first);
        sz[now] += sz[it.first];
    }
}

int getCen(int now, int SizeT){
    visit[now] = vcnt;
    for(auto it : adj[now]){
        if(visit[it.first] == vcnt || wasCen[it.first]) continue;
        if(sz[it.first] >= SizeT/2) return getCen(it.first, SizeT);
    }
    return now;
}

void dfs(int now, int cost, int len){
    visit[now] = vcnt;
    if(cost > k) return;
    temp.push_back({cost, len});
    for(auto it : adj[now]){
        if(visit[it.first] == vcnt || wasCen[it.first]) continue;
        dfs(it.first, cost+it.second, len+1);
    }
}

void func(int now){
    vcnt++;
    getSize(now);
    vcnt++;
    int cen = getCen(now, sz[now]);
    vcnt++;
    wasCen[cen]=1;
    vMin[0] = vcnt;
    Min[0] = 0;
    for(auto it : adj[cen]){
        if(!wasCen[it.first]) dfs(it.first, it.second, 1);
        for(auto j : temp){
            int nowC = j.first, nowL = j.second;
            if(vMin[k-nowC] == vcnt) ans = min(ans, Min[k-nowC]+j.second);
        }
        for(auto j : temp){
            int nowC = j.first, nowL = j.second;
            if(vMin[nowC] == vcnt) nowL = min(Min[nowC], nowL);
            vMin[nowC] = vcnt;
            Min[nowC] = nowL;
        }
        temp.clear();
    }
    for(auto it : adj[cen])
        if(!wasCen[it.first]) func(it.first);
}

int main(){
    scanf("%d %d", &n, &k);
    for(int i=1; i<n; i++){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    func(0);
    printf("%d", ans!=2e9?ans:-1);
    return 0;
}
