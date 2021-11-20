#include <iostream>
using namespace std;
const int INF = 100100;
int d[510][60100];
int n, m, k, maxK;

int getd(int i, int j){
  if(j < 0 || j > maxK) return -INF;
  return d[i][j];
}

int main(){
  cin >> n >> m >> k;
  maxK = n*m + k;
  
  int ans = 0;
  for(int j=0; j<=maxK; j++) d[0][j] = -INF;
  d[0][k] = 0;
  for(int i=1; i<=n; i++){
    int c;
    cin >> c;
    for(int j=0; j<=maxK; j++){
      d[i][j] = max(getd(i-1, j-m), getd(i-1, j+c)+c);
      if(d[i][j] < 0) d[i][j] = -INF;
      ans = max(ans, d[i][j]);
    }
  }
  
  cout << ans << "\n";
  return 0;
}