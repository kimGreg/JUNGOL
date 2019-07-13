#include <cstdio>
#include <vector>
#include <algorithm>
#include <stack>
#include <set>
using namespace std;
typedef pair<int, int> pii;
vector<pii> edge;
vector<int> adj[10010];
set<int> st;
int par[10010], cnt[10010], visit[10010];
int n, m;

void init(){
    edge.clear();
	st.clear();
    for(int i=0; i<=n; i++){
        visit[i] = cnt[i] = 0;
        par[i] = i;
        adj[i].clear();
    }
}

int getPar(int now){
    if(par[now] == now) return now;
    else return par[now] = getPar(par[now]);
}

pii dfs(int now, int k){
    visit[now] = k;
    pii ans(0,0);
    if(k+1) ans.first += cnt[now];
    else ans.second += cnt[now];
    for(auto it : adj[now]){
        if(visit[it] == k) return {-1, -1};
        else if(visit[it] == -k) continue;
        pii temp = dfs(it, -k);
        if(temp.first == -1) return {-1, -1};
        ans.first += temp.first;
        ans.second += temp.second;
    }
    return ans;
}

void solve(){
    scanf("%d %d", &n, &m);
    init();
    for(int i=0; i<m; i++){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        if(a+1)
            par[getPar(b)] = getPar(c);
        else
            edge.push_back({b, c});
    }
    for(int i=1; i<=n; i++) cnt[getPar(i)]++;
    for(auto it : edge){
        int a = par[it.first], b = par[it.second];
        if(a == b){
            printf("-1\n");
            return;
        }
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> Aans;
    for(int i=1; i<=n; i++){
        if(visit[i]) continue;
        pii k = dfs(i, 1);
        if(k.first == -1){
            printf("-1\n");
            return;
        }
        if(k.first != k.second)
            Aans.push_back(abs(k.first - k.second));
    }
	stack<int> stk;
	st.insert(0);
    for(auto it : Aans){
    	while(!st.empty()){
			stk.push(abs(*st.begin()-it));
			stk.push(abs(*st.begin()+it));
			st.erase(st.begin());
		}
		while(!stk.empty()){
			st.insert(stk.top());
			stk.pop();
		}
	}
    printf("%d\n", *st.begin());
}

int main(){
    for(int i=0; i<5; i++)
        solve();
    return 0;
}
