#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

class line{
public:
    int x, s, e, m;
    line(){}
    line(int _x, int _s, int _e, int _m){
        x=_x; s=_s; e=_e; m=_m;
    }
    bool operator<(const line & D)const{
        if(x != D.x) return x < D.x;
        return m < D.m;
    }
};

vector<line> lines, lines2;
vector<int> Xpos, Ypos;
int tree[40000], cnt[40000], mode[40000];

void update(int now, int l, int r, int s, int e, int diff, int x){
    if(e < l || r < s) return;
    if(s <= l && r <= e) cnt[now] += diff;
    else{
        update(now*2, l, (l+r)/2, s, e, diff, x);
        update(now*2+1, (l+r)/2+1, r, s, e, diff, x);
    }
    if(cnt[now]){
        tree[now] = 0;
        mode[now] = 3;
    }else if(l == r){
        tree[now] = 0;
        mode[now] = 0;
    }else{
        tree[now] = tree[now*2] + tree[now*2+1];
        if(mode[now*2]%2 != mode[now*2+1]/2) tree[now]++;
        mode[now] = (mode[now*2]/2)*2 + mode[now*2+1]%2;
    }
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        if(x1 > x2) swap(x1, x2);
        if(y1 > y2) swap(y1, y2);
        Xpos.push_back(x1); Xpos.push_back(x2);
        Ypos.push_back(y1); Ypos.push_back(y2);
        lines.push_back({x1, y1, y2, 1});
        lines.push_back({x2, y1, y2, -1});
        lines2.push_back({y1, x1, x2, 1});
        lines2.push_back({y2, x1, x2, -1});
    }
    sort(Xpos.begin(), Xpos.end()); sort(Ypos.begin(), Ypos.end());
    sort(lines.begin(), lines.end()); sort(lines2.begin(), lines2.end());
    Xpos.erase(unique(Xpos.begin(), Xpos.end()), Xpos.end());
    Ypos.erase(unique(Ypos.begin(), Ypos.end()), Ypos.end());
    for(auto & i: lines){
        i.x = lower_bound(Xpos.begin(), Xpos.end(), i.x)-Xpos.begin();
        i.s = lower_bound(Ypos.begin(), Ypos.end(), i.s)-Ypos.begin();
        i.e = lower_bound(Ypos.begin(), Ypos.end(), i.e)-Ypos.begin();
    }
    for(auto & i: lines2){
        i.x = lower_bound(Ypos.begin(), Ypos.end(), i.x)-Ypos.begin();
        i.s = lower_bound(Xpos.begin(), Xpos.end(), i.s)-Xpos.begin();
        i.e = lower_bound(Xpos.begin(), Xpos.end(), i.e)-Xpos.begin();
    }
    int lastX = 0, ans = 0;
    for(auto i : lines){
        if(i.x != lastX) ans += (Xpos[i.x]-Xpos[lastX])*tree[1], lastX = i.x;
        update(1, 1, Ypos.size()+2, i.s+2, i.e+1, i.m, i.x);
    }
    for(int i=0; i<30300; i++) tree[i] = cnt[i] = mode[i] = 0;
    lastX = 0;
    for(auto i : lines2){
        if(i.x != lastX) ans += (Ypos[i.x]-Ypos[lastX])*tree[1], lastX = i.x;
        update(1, 1, Xpos.size()+2, i.s+2, i.e+1, i.m, i.x);
    }
    printf("%d", ans);
    return 0;
}
