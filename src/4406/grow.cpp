#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class Data{
public:
  int n, s, p;
  Data(){}
  Data(int N, int P, int S){
    n = N; s = S; p = P;
  }
};

int n;
int Cap[1010];
double dp[1010];
vector<Data> adj[1010];

void input(){
  cin >> n;
  for(int i=1; i<n; i++){
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    adj[a].push_back({b, c, d});
    adj[b].push_back({a, c, d});
  }
  for(int i=1; i<=n; i++) cin >> Cap[i];
}

void dfs(int now, int par = -1){
  if(par != -1 && adj[now].size() == 1){
    dp[now] = max(Cap[now], 0);
    return;
  }
  for(auto next : adj[now]){
    if(next.n == par) continue;
    dfs(next.n, now);
  }
  dp[now] = max(Cap[now], 0);
  for(auto next : adj[now]){
    if(next.n == par) continue;
    double temp = dp[next.n];
    if(next.s) temp = min(temp, sqrt(dp[next.n]));
    dp[now] = max(dp[now], temp*100/next.p);
  }
}

double solve(){
  dfs(1);
  return dp[1];
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  input();
  cout << solve() << "\n";
  return 0;
}