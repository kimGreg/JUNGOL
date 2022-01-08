#include <iostream>
#include <algorithm>
#define MAX_N 100001

using namespace std;

int N;
int tree[MAX_N*3], lazy[MAX_N*3];

void update_lazy(int now, int l, int r, int s, int e){
    tree[now] = (r-l+1)-tree[now];
    if(l < r){
        lazy[now*2] = 1-lazy[now*2];
        lazy[now*2+1] = 1-lazy[now*2+1];
    }
}

void toggle(int now, int l, int r, int s, int e){
    if(lazy[now]){
        update_lazy(now, l, r, s, e);
        lazy[now] = 0;
    }

    if(l > e || r < s) return;
    if(s <= l && r <= e){
        update_lazy(now, l, r, s, e);
        return;
    }

    int m = (l+r)/2;
    toggle(now*2, l, m, s, e);
    toggle(now*2+1, m+1, r, s, e);
    tree[now] = tree[now*2] + tree[now*2+1];
}

int get_ans(int now, int l, int r, int s, int e){
    if(lazy[now]){
        update_lazy(now, l, r, s, e);
        lazy[now] = 0;
    }
    if(e < l || r < s) return 0;
    if(s <= l && r <= e) return tree[now];
    int m = (l+r)/2;
    return get_ans(now*2, l, m, s, e) + get_ans(now*2+1, m+1, r, s, e);
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int m;
    cin >> N >> m; 
    while(m--){
        int q, s, e;
        cin >> q >> s >> e;
        if(q == 0) toggle(1, 1, N, s, e);
        if(q == 1) cout << get_ans(1, 1, N, s, e) << "\n";
    }
    return 0;   
}