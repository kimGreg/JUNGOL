#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

vector<pll> adj[100100];
int visit[100100];
int n, s, e;

ll dfs(int now, ll mx, ll sm){
  if(visit[now]) return -1;
  visit[now] = 1;
  
  if(now == e) return sm - mx;
  for(auto it : adj[now]){
    ll next = it.first, w = it.second;     
    ll res = dfs(next, max(mx, w), sm + w);
    if(res != -1) return res;
  }
  return -1;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  
  cin >> n >> s >> e;
  for(int i=1; i<n; i++){
    int a, b, c;
    cin >> a >> b >> c;
    adj[a].push_back({b, c});
    adj[b].push_back({a, c});
  }
  cout << dfs(s, 0, 0) << "\n";
  return 0;
}