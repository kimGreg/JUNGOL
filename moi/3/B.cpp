#include <cstdio>
#include <algorithm>
using namespace std;
int visit[300][300], map[300][300];
pair<int, int> path[300][300];
int dir[2][4] = {{0, 0, 1, -1},{1, -1, 0, 0}};
int a, b, n, m, sx, sy;

void dfs(int x, int y, int cnt = 0){
    //printf("%d %d : %d\n", x, y, cnt);
    if(x == a && y == b) return;
    cnt++;
    for(int i=0; i<4; i++){
        //check
        int nx = x+dir[0][i]*2, ny = y+dir[1][i]*2;
        //printf("haha %d %d\n", nx, ny);
        if(0<=nx && nx<n && 0<=ny && ny<m){
            if(map[x+dir[0][i]][y+dir[1][i]] != map[nx][ny])
                continue;
        }else{
            //printf("!!ha\n");
            continue;
        }
        if(visit[nx][ny] == -1 || visit[nx][ny] > cnt){
            visit[nx][ny] = cnt;
            path[nx][ny] = {x, y};
            swap(map[nx][ny], map[x][y]);
            dfs(nx, ny, cnt);
            swap(map[nx][ny], map[x][y]);
        }
    }
}

void print(int a, int b){
    if(a == sx && b == sy) return;
    print(path[a][b].first, path[a][b].second);
    printf("%d ", map[a][b]);
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            visit[i][j] = -1;
            scanf("%d", map[i]+j);
            if(map[i][j] == -1) sx = i, sy = j;
        }
    }
    scanf("%d %d", &a, &b); a--; b--;
    dfs(sx, sy);
    if(visit[a][b] == -1) printf("impossible");
    else print(a, b);
    return 0;
}
