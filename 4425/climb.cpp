#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

class Data{
public:
  ll val, s, e;
  Data(){}
  Data(ll V, ll S, ll E){
    val = V; s = S; e = E;
  }
  bool operator<(const Data & D)const{
    return val < D.val;
  }
};

vector<Data> E;
int par[400000], size[400000], h[550][550];
int N; 

ll get_par(int s){
  if(par[s] == s) return s;
  return par[s] = get_par(par[s]);
}

ll attach(ll s, ll e){
  s = get_par(s); e = get_par(e);
  if(s == e){
    return size[s];
  }
  par[s] = e;
  size[e] += size[s];
  return size[e];
}

int main(){
  cin >> N;
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      cin >> h[i][j];
      if(i != 0)
        E.push_back({abs(h[i][j]-h[i-1][j]), i*N+j+1, i*N+j-N+1});
      if(j != 0)
        E.push_back({abs(h[i][j]- h[i][j-1]), i*N+j+1, i*N+j});
    }
  }
  for(int i=1; i<=N*N; i++){
    par[i] = i;
    size[i] = 1;
  }
  sort(E.begin(), E.end());
  ll ans = 0;
  for(auto it : E){
    ans = it.val;
    if(attach(it.s, it.e) >= N*N*3/4) break;
  }
  cout << ans;
  return 0;
}