#include <iostream>
 
using namespace std;
 
int n, arr[1010];
 
 
int check(int S, int E){
  int s = S, e = E, d = ((n+E-S+1)%n)/2;
  for(int i=0; i<d; i++){
    swap(arr[s], arr[e]);
    s = (s+1)%n;
    e = (n+e-1)%n;
  }
   
  int cnt = 0, idx = 0;
  for(int i=1; i<n; i++){
    if(arr[i]-arr[i-1] != 1){
      cnt++;
      idx = i;
    }
  }
   
  if(cnt <= 1){
    for(int now = 1; now < n; now++){
      int s = (2*n+S-now)%n, e = (2*n+E-now)%n, id = (2*n+idx-now)%n;
      if(s > e || id == 0) continue;
      cout << (2*n-id)%n <<"\n"<< s+1 << " " << e+1 << "\n" << (2*n-now)%n << "\n";
      return 1;
    }
  }
   
  s = S; e = E;
  for(int i=0; i<d; i++){
    swap(arr[s], arr[e]);
    s = (s+1)%n;
    e = (n+e-1)%n;
  }
  return 0;
}
 
void solve(){
  for(int s=0; s<n; s++){
    for(int e=0; e<n; e++){
      if(s == 0 && e == n-1) continue;
      if(check(s, e)) return;
    }
  }
}
 
int main(){
  cin >> n;
  for(int i=0; i<n; i++) cin >> arr[i];
   
  solve();
   
  return 0;
}