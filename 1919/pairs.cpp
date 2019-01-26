#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
int b, n, d, m;
long long tree2[3000][3000];
int arr[100100];

long long query2Y(int now, int l, int r, int x, int y){
    if(r < y-d || l > y+d) return 0;
    if(y-d <= l && r <= y+d) return tree2[x][now];
    return query2Y(now*2, l, (l+r)/2, x, y) + query2Y(now*2+1, (l+r)/2+1, r, x, y);
}
long long query2(int now, int l, int r, int x, int y){
    if(r < x-d || l > x+d) return 0;
    if(x-d <= l && r <= x+d) return query2Y(1, 1, 2*m-1, now, y);
    return query2(now*2, l, (l+r)/2, x, y) + query2(now*2+1, (l+r)/2+1, r, x, y);
}
int update2Y(int now, int l, int r, int x, int y){
    if(r < y || l > y) return 0;
    if(l == r){
        tree2[x][now]++;
        return now;
    }
    int k = update2Y(now*2, l, (l+r)/2, x, y);
    int t = update2Y(now*2+1, (l+r)/2+1, r, x, y);
    tree2[x][now] = tree2[x][now*2] + tree2[x][now*2+1];
    return max(k, t);
}
int update2(int now, int l, int r, int x, int y){
    if(r < x|| l > x) return 0;
    if(l == r) return update2Y(1, 1, 2*m-1, now, y);
    int k = update2(now*2, l, (l+r)/2, x, y);
    int t = update2(now*2+1, (l+r)/2+1, r, x, y);
    k = max(k, t);
    for(int i=1; i<=k; i++) tree2[now][i] = tree2[now*2][i] + tree2[now*2+1][i];
    return k;
}

void solve1(){
    for(int i=0; i<n; i++) scanf("%d", arr+i);
    sort(arr, arr+n);
    queue<int> que;
    que.push(arr[0]);
    long long ans = 0;
    for(int i=1; i<n; i++){
        while(!que.empty() && que.front() < arr[i]-d) que.pop();
        ans += que.size();
        que.push(arr[i]);
    }
    printf("%lld", ans);
}

void solve2(){
    long long ans = 0;
    for(int i=0; i<n; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        int x = a+b-1, y = a-b+m;
        ans += query2(1, 1, 2*m-1, x, y);
        update2(1, 1, 2*m-1, x, y);
    }
    printf("%lld", ans);
}

int main(){
    scanf("%d %d %d %d", &b, &n, &d, &m);
    if(b==1) solve1();
    else solve2();
    return 0;
}
