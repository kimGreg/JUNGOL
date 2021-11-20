#include <cstdio>
#include <algorithm>
using namespace std;
using ll = long long;

const ll INF = 1e9;

ll d[1000][1000];
ll person[1000];

int main(){
    int n, p, c;
    scanf("%d %d %d", &n, &p, &c);
    
    for(int i=1; i<=p; i++){
        for(int j=1; j<=p; j++){
            if(i != j){
                d[i][j] = INF;
                d[j][i] = INF;
            }else{
                d[i][j] = 0;
            }
        }
    }
    
    for(int i=0; i<c; i++){
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        d[x][y] = z;
        d[y][x] = z;
    }
    
    for(int i=0; i<n; i++){
        int temp;
        scanf("%d", &temp);
        person[temp]++;
    }
    
    // 플로이드 워셜
    for(int k=1; k<=p; k++){
        for(int i=1; i<=p; i++){
            for(int j=1; j<=p; j++){
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);  
            }
        }
    }
    
    ll ans = INF;
    
    for(int i=1; i<=p; i++){
        ll temp = 0;
        for(int j=1; j<=p; j++){
            temp += person[j]*d[i][j];
        }
        ans = min(ans, temp);
    }
    
    printf("%lld", ans);
    
    return 0;
}