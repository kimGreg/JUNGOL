#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
 
int adj[7][7], tempAdj[7][7], visit[7], checkArr[7], deg[7], ans;
 
void update(int a, int b, int diff){
    adj[a][b] += diff;
    if(a != b)
        adj[b][a] += diff;
}

void change(int a, int b, int diff){
    adj[a][b] = diff;
    adj[b][a] = diff;
}

bool check(){
    fill(deg, deg+7, 0);
    for(int i=0; i<=6; i++){
        for(int j=i; j<=6; j++){
            deg[i] += adj[i][j];
            deg[j] += adj[i][j];
        }
    }
    
    int k = 0;
    for(int i=0; i<=6; i++){
        k += deg[i]%2;
    }
    
    return (k == 0 || k == 2);
}

int dfs2(int now){
    visit[now] = 1;
    checkArr[now] = 0;
    int res = 1;
    for(int i=0; i<=6; i++){
        if(adj[i][now] && !visit[i]){
            res += dfs2(i);
        }
    }
    return res;
}

void dfs(int a, int b, int cnt, bool flag = 1){
    if(a == 7){
        if(check())
            ans = max(ans, cnt);
        return;
    }
    
    int nextA = a, nextB = b+1;
    if(nextB == 7)
        nextB = nextA = a+1;
    
    dfs(nextA, nextB, cnt);
    
    if(adj[a][b] > 0){
        update(a, b, -1);
        dfs(nextA, nextB, cnt-1);
        update(a, b, 1);
        
        int temp = adj[a][b];
        if(temp != 1){
            update(a, b, -temp);
            dfs(nextA, nextB, cnt - temp);
            update(a, b, temp);
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        update(a, b, 1);
    }
    dfs(0, 0, n);
    printf("%d", ans);
    return 0;
}
