#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <stack>
#include <queue>
 
using namespace std;
using pii = pair<int, int>;
using tiii = tuple<int, int, int>;

int n, R, C;
pii rowFlowers[1505][5], colFlowers[1505][5];
int rowSize[1505], colSize[1505];
tiii flowers[2265025];
int flower[1505][1505];
 
void input(){
    cin >> n >> R >> C;
    R--; C--;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> flower[i][j];
        }
    }
}

void update_set(pii * st, int & sz, pii data){
    int idx;
    for(idx=0; idx < sz && *(st+idx) >= data; ++idx){}
 
    for(int i=sz; idx < i; i--) *(st+i) = *(st+i-1);
    *(st+idx) = data;
 
    sz = min(sz+1, 4);
}

void update_cnt(int r, int c, int cnt){
    update_set(rowFlowers[r], rowSize[r], {cnt, c});
    update_set(colFlowers[c], colSize[c], {cnt, r});
}

int get_set_cnt(pii * arr, int sz, int idx){
    int res = 0;
    for(int i = 0; i < sz; ++i){
        if(abs(arr[i].second - idx) > 1){
            res = max(res, arr[i].first);
            break;
        }
    }
    return res;
}

int get_cnt(int r, int c){
    if(r == R && c == C) return 1;
    int res = 0;
    if(0 <= r-1) res = max(res, get_set_cnt(rowFlowers[r-1], rowSize[r-1], c));
    if(n > r+1) res = max(res, get_set_cnt(rowFlowers[r+1], rowSize[r+1], c));
    if(0 <= c-1) res = max(res, get_set_cnt(colFlowers[c-1], colSize[c-1], r));
    if(n > c+1) res = max(res, get_set_cnt(colFlowers[c+1], colSize[c+1], r));
    return res;
}

int solve(){
    int k = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(flower[i][j] <= flower[R][C] && !(i==R && j==C)) continue;
            flowers[k++] = {flower[i][j], i, j};
        }
    }

    sort(flowers, flowers+k);

    int ans = 0, last_val = flower[R][C];
    stack<tiii> update_stk;
    for(int i=0; i<k; i++){ /// how to ???????????
        int val = get<0>(flowers[i]), r = get<1>(flowers[i]), c = get<2>(flowers[i]);

        if(val != last_val){
            last_val = val;
            while(!update_stk.empty()){
                auto now = update_stk.top(); update_stk.pop();
                update_cnt(get<0>(now), get<1>(now), get<2>(now));
            }
        }

        int cnt = get_cnt(r, c);
        if(cnt == 0) continue;
        if(ans < cnt) ans = cnt;
        update_stk.push({r, c, cnt+1});
    }
    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
 
    input();
    cout << solve();
    return 0;
}