#include <iostream>
using namespace std;
using ll = long long;

ll s=1, c=0, tot=0, n = 0;
ll cnt=0;

int arr[20];

void addAns(){
  cnt++;
  if(cnt <= 20){
    for(int i=1; i<=n; i++){
      cout << i << " ";
      if(i < n){
        if(arr[i] == 1) cout << "+ ";
        else if(arr[i] == 2) cout << "- ";
        else cout << ". ";
      }
    }
    cout << "\n";
  }
}

void solve(int now, ll s, ll c, ll tot){
  c = c*(now>=10?100:10) + now;
  
  if(now == n){
    if(tot+s*c == 0) addAns();
    return;
  }
  arr[now] = 1;
  solve(now+1, 1, 0, tot+s*c);
  arr[now] = 2;
  solve(now+1, -1, 0, tot+s*c);
  arr[now] = 3;
  solve(now+1, s, c, tot);
}

int main(){
  cin >> n;
  
  solve(1, 1, 0, 0);
  cout << cnt << "\n";
  
  return 0;
}