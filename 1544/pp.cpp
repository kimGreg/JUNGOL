#include <cstdio>
#include <algorithm>
using namespace std;

int d[100][100];
int max_dis[100];

int main(){
    int n;
    scanf("%d", &n);
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(i != j){
                d[i][j] = n+1;
                d[j][i] = n+1;
            }else{
                d[i][j] = 0;
            }
        }
    }
    while(true){
        int a, b;
        scanf("%d %d", &a, &b);
        if(a == -1 && b == -1) break;
        d[a][b] = 1;
        d[b][a] = 1;
    }
    for(int k=1; k<=n; k++){
        for(int i=1; i<=n; i++){
            for(int j=1; j<=n; j++){
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    
    int ans_dis = 1000, ans_cnt = 0;
    for(int i=1; i<=n; i++){
        max_dis[i] = 0;
        for(int j=1; j<=n; j++)
            max_dis[i] = max(d[i][j], max_dis[i]);
        ans_dis = min(ans_dis, max_dis[i]);
    }
    
    for(int i=1; i<=n; i++){
        if(max_dis[i] == ans_dis) ans_cnt++;
    }
    
    printf("%d %d\n", ans_dis, ans_cnt);
    for(int i=1; i<=n; i++){
        if(max_dis[i] == ans_dis) printf("%d ", i);
    }
    
    return 0;
}