#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, vcnt;
int visit[550];
vector<int> adj[2][550];

void input(){
  int a, b, k;
  cin >> n >> k;
  for(int i=0; i<k; i++){
    cin >> a >> b;
    adj[0][a].push_back(b);
    adj[1][b].push_back(a);
  }
}

int dfs(int now, int M){
  int ret = 1;
  for(auto next : adj[M][now]){
    if(visit[next] == vcnt) continue;
    visit[next] = vcnt;
    ret += dfs(next, M);
  }
  return ret;
}

int can_know(int now){
  vcnt++;
  visit[now] = vcnt;
  int res = dfs(now, 0);
  vcnt++;
  visit[now] = vcnt;
  res += dfs(now, 1);
  return res-1 == n;
}

int solve(){
  int ans = 0;
  for(int i=1; i<=n; i++){
    if(can_know(i)) ans++;
  }
  return ans;
}


int main(){
  input();
  cout << solve() << "\n";
  return 0;
}