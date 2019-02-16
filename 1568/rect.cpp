#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
class line{
public:
    int x, sy, ey, mode;
    line(int _x=0, int _sy=0, int _ey=0, int _mode=0){
        x = _x; sy = _sy; ey = _ey; mode = _mode;
    }
    bool operator<(const line & L)const{
        return x < L.x;
    }
};
vector<int> Xarr, Yarr;
vector<line> lines;
long long tree[1200000];
int cnt[1200000];

void update(int now, int s, int e, int l, int r, int mode){
    if(r < s || e < l) return;
    if(l <= s && e <= r) cnt[now] += mode;
    else{
        update(now*2, s, (s+e)/2, l, r, mode);
        update(now*2+1, (s+e)/2+1, e, l, r, mode);
    }
    if(cnt[now]) tree[now] = Yarr[e] - Yarr[s-1];
    else if(s == e) tree[now] = 0;
    else tree[now] = tree[now*2] + tree[now*2+1];
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        int x1, x2, y1, y2;
        scanf("%d %d %d %d", &x1, &x2, &y1, &y2);
        Xarr.push_back(x1); Xarr.push_back(x2);
        Yarr.push_back(y1); Yarr.push_back(y2);
        lines.push_back({x1, y1, y2, 1});
        lines.push_back({x2, y1, y2, -1});
    }
    sort(Xarr.begin(), Xarr.end()); sort(Yarr.begin(), Yarr.end());
    Xarr.erase(unique(Xarr.begin(), Xarr.end()), Xarr.end());
    Yarr.erase(unique(Yarr.begin(), Yarr.end()), Yarr.end());
    for(int i=0; i<lines.size(); i++){
        lines[i].x = lower_bound(Xarr.begin(), Xarr.end(), lines[i].x)-Xarr.begin();
        lines[i].sy = lower_bound(Yarr.begin(), Yarr.end(), lines[i].sy)-Yarr.begin();
        lines[i].ey = lower_bound(Yarr.begin(), Yarr.end(), lines[i].ey)-Yarr.begin();
    }
    sort(lines.begin(), lines.end());
    long long ans = 0, beforeX = 0;
    for(int i=0; i<lines.size(); i++){
        if(lines[i].x != beforeX){
            ans += (Xarr[lines[i].x] - Xarr[beforeX])*tree[1];
            beforeX = lines[i].x;
        }
        update(1, 1, Yarr.size()-1, lines[i].sy+1, lines[i].ey, lines[i].mode);
    }
    printf("%lld", ans);
    return 0;
}
