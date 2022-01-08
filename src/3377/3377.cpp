#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using pii = pair<int, int>;
using ll = long long;

const ll MAX_N = 100010;

class Line{
public:
    int s, e, x;
    Line(){}
    Line(int s, int e, int x):s(s),e(e),x(x){}
    bool operator < (const Line & l) const{
        return x < l.x;
    }
};

int N;
ll tree[MAX_N*6], lazy[MAX_N*6];
ll X[MAX_N*2], Y[MAX_N*2], lenx, leny, lenl;
Line lines[2*MAX_N];

ll get_length(int l, int r){
    return (Y[r]-Y[l-1]);
}

void update_lazy(int now, int l, int r, int s, int e){
    tree[now] = get_length(l, r)-tree[now];
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

ll get_tot(int now, int l, int r, int s, int e){
    if(lazy[now]){
        update_lazy(now, l, r, s, e);
        lazy[now] = 0;
    }
    if(e < l || r < s) return 0;
    if(s <= l && r <= e) return tree[now];
    int m = (l+r)/2;
    return get_tot(now*2, l, m, s, e) + get_tot(now*2+1, m+1, r, s, e);
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> N; 
    for(int i=0; i<N; i++){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        lines[lenl++] = Line(y1, y2, x1); lines[lenl++] = Line(y1, y2, x2);
        Y[leny++] = y1; Y[leny++] = y2;
    }
   sort(Y, Y+leny); leny = unique(Y, Y+leny)-Y;
    


    sort(lines, lines+lenl);
    int lastX = lines[0].x;

    ll ans = 0;
    for(int i=0; i<lenl; i++){
        int s = lower_bound(Y, Y+leny, lines[i].s)-Y+1;
        int e = lower_bound(Y, Y+leny, lines[i].e)-Y+1;
        int x = lines[i].x;

        if(lastX != x){
            ans += (ll) (x-lastX) * get_tot(1, 1, leny, 1, leny);
            //cout << x << " " << lastX << " " << get_tot(1, 1, leny, 1, leny) << "\n";
            lastX = x;
        }
        toggle(1, 1, leny, s, e-1);
    }

    cout << ans;

    return 0;   
}