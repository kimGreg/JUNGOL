#include <cstdio>
#include <vector>
using namespace std;
 
int number[90][90], visit[10010], matched[10010], vcnt;
vector<int> adj[10010];
int n, m, odd_col_N, even_col_N;
int pos[2][6] = {{-1, 0, 1, -1, 0, 1},{1, 1, 1, -1, -1, -1}};
 
inline bool is_able(int x, int y){
    return (0<=x && x<m && 0<=y && y<n && number[x][y]);
}
 
bool dfs(int now){
    if(visit[now] == vcnt)
        return 0;
    visit[now] = vcnt;
 
    for(auto it : adj[now]){
        if(!matched[it] || dfs(matched[it])){
            matched[it] = now;
            return 1;
        }
    }
    return 0;
}
 
int bi_match(){
    int res = 0;
    for(int i=1; i<=even_col_N; i++){
        vcnt++;
        if(dfs(i)){
            res++;
        }
    }
    return res;
}
 
 
int main(){
    scanf("%d %d", &m, &n);
     
    int ans = 0;
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            char ch;
            scanf(" %c", &ch);
            if(ch == '.'){
                if(j%2) number[i][j] = ++odd_col_N;
                else number[i][j] = ++even_col_N;
                ans++;
            }
        }
    }
 
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(!number[i][j] || j%2)
                continue;
            for(int k=0; k<6; k++){
                int adj_I = i + pos[0][k], adj_J = j + pos[1][k];
                if(is_able(adj_I, adj_J))
                    adj[number[i][j]].push_back(number[adj_I][adj_J]);
            }
        }
    }
     
    ans -= bi_match();
 
    printf("%d", ans);
 
    return 0;
}
