#include <iostream>

using namespace std;
using ll = long long;

int main(){
  ll N, S;
  cin >> N >> S;
  ll ans = N, a = N-S, b = S;
  while(a){
    ans += a*(b/a)*2;
    if(b%a == 0) ans -= a;
    ll temp = b;
    b = a;
    a = temp%a;
  }
  cout << ans << "\n";
  return 0;
}