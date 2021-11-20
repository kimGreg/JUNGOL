 
#include <iostream>
#include <algorithm>
using namespace std;
int n, k, arr[100010], maxi[100010];

int sol(){
    int e = 0, c = 0, t = 0;
    for(int i=1; i<=n; i++){
        if(arr[i]) t = i;
        if(i == e + k){
            if(t+k-1 <= e) return -1;
            e = t+k-1;
            c++;
        }
    }
    if(e < n){
      if(t+k-1 < n) return -1;
      c++;
    }
    return c;
}
 
void fill_maxi(){
  int t = -k+1;
  for(int i=1; i<=n; i++){
    if(arr[i]) t = i;
    maxi[i] = t;
  }
}

int sol2(){
  fill_maxi();
  int now = -k+1, cnt = 0;
  while(now+k-1 < n){
    int next = maxi[min(now+2*k-1, n)];
    if(next == now) return -1;
    now = next;
    cnt++;
  }
  return cnt;
}

int main(){
  cin >> n >> k;
  for(int i=1; i<=n; i++) cin >> arr[i];
  cout << sol2();
  return 0;
}