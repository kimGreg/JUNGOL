/*
https://www.crocus.co.kr/613
*/

#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int lenA, lenB, lent;
string A, B, tot;
int t, SA[1000100], g[1000100], tg[1000100], RANK[1000100], LCP[1000100], L[1000100];
vector<int> H[1000100];

void init(){
  for(int i=0; i<=2*lenA+2; i++) H[i].clear();
  for(int i=0; i<=lent; i++){
    L[i] = 0;
  }
}

void input(){
  cin >> A >> B;
  tot = A + B + " ";
  lenA = A.size(); 
  lenB = B.size();
  lent = tot.size();
  init();

  int h = lenA+1;
  for(int i=0; i<lenA; i++){
    H[h].push_back(i);
    if(A[i] == '(') h++;
    else h--;
  }
  H[h].push_back(lenA);
}

bool cmp(int x, int y){
  if(g[x] == g[y])
    return g[x+t] < g[y+t];
  return g[x] < g[y];
}

void get_SA(){
  t = 1;
  for(int i=0; i<lent; i++){
    SA[i] = i;
    g[i] = tot[i]-'a';
  }

  while(t <= lent){
    g[lent] = -1;
    sort(SA, SA+lent, cmp);
    tg[SA[0]] = 0;
    for(int i=1; i<lent; i++){
      if(cmp(SA[i-1], SA[i]))
        tg[SA[i]] = tg[SA[i-1]] + 1;
      else
        tg[SA[i]] = tg[SA[i-1]];
    }
    for(int i=0; i<lent; i++) g[i] = tg[i];
    t <<= 1;
  }
}

void get_LCP(){
  for(int i=0; i<lent; i++) RANK[SA[i]] = i;
  int len = 0;
  for(int i=0; i<lent; i++){
    int k = RANK[i];
    if(k){
      int j = SA[k-1];
      while(tot[j+len] == tot[i+len]){
        len++;
      }
      LCP[k] = len;
      if(len) len--;
    }else LCP[k] = 0;
  }
}

void get_L(){
  int mn = 0;

  for(int i=0; i<lent; i++){
    if(SA[i] >= lenA){
      if(i+1 < lent) mn = LCP[i+1];
    }else{
      L[SA[i]] = max(L[SA[i]], mn);
      if(i+1 < lent) mn = min(mn, LCP[i+1]);
    }
  }
  
  for(int i=lent-1; i>=0; i--){
    if(SA[i] >= lenA){
      mn = LCP[i];
    }else{
      L[SA[i]] = max(L[SA[i]], mn);
      mn = min(mn, LCP[i]);
    }
  }
}

int get_ans(){
  int h = lenA+1, ans = 0;
  for(int i=0; i<lenA; i++){
    int R = upper_bound(H[h-1].begin(), H[h-1].end(), i)-H[h-1].begin();
    if(R == H[h-1].size()) R = lenA;
    else R = H[h-1][R]-1;
    R = min(R, i+L[i]);
    int Rend = upper_bound(H[h].begin(), H[h].end(), R)-H[h].begin();
    int res = H[h][Rend-1] - i;
    ans = max(ans, res);

    if(A[i] == '(') h++;
    else h--;
  }
  return ans;
}

int solve(){
  init();
  input();
  get_SA();
  get_LCP();
  get_L();
  int k = get_ans();
  return k;
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  int T;
  cin >> T;
  for(int Cs = 1; Cs <= T; Cs++){
    
    cout << solve() << "\n";
  }
  return 0;
}