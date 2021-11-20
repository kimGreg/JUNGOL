#include <cstdio>
#include <algorithm>
using namespace std;
 
int adj[7][7];
 
inline void update(int a, int b, int diff){
    adj[a][b] += diff;
    adj[b][a] += diff;
}
 
int dfs(int now){
    int ans = 0;
    for(int i=0; i<=6; i++){
        if(!adj[now][i]) continue;
        update(now, i, -1);
        ans = max(ans, 1+dfs(i));
        update(now, i, 1);;
    }
    return ans;
}
 
int main(){
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        update(a, b, 1);
    }
    int ans = 0;
    for(int i=0; i<=6; i++){
        ans = max(dfs(i), ans);
    }
    printf("%d", ans);
    return 0;
}
