#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
class Data{
public:
  ll s, e, c;
  Data(ll _s=0, ll _e=0, ll _c=0):s(_s),e(_e),c(_c){}
};
vector<ll> Tree;
vector<Data> arr;

int main(){
  ll n, l, m;
  scanf("%lld %lld %lld", &n, &l, &m);
  for(int i=0; i<m; i++){
    ll a, b, c;
    scanf("%lld %lld %lld", &a, &b, &c);
    arr.push_back({a, b, c});
  }
  sort(arr.begin(), arr.end(), [&](Data &a, Data &b)->bool{return a.s<b.s;});
  return 0;
}
