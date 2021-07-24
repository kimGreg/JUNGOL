#include <cstdio>

using namespace std;

int dice_chage[4][6] = {
    {4,1,0,3,5,2},
    {2,1,5,3,0,4},
    {3,0,2,5,4,1},
    {1,5,2,0,4,3}
};
int pos_chagne[4][2] = {
    {0,-1}, {0,1}, {-1,0}, {1,0}
};

int status[6] = {0,1,2,3,4,5};
int temp[6];
int dice[6], arr[10][10], visit[10][10];


void dfs(int r, int c){
    if(arr[r][c] == 0) return;
    
    dice[status[0]] = arr[r][c];
    arr[r][c] = 0;
    for(int i=0; i<4; i++){
        int nr = r+pos_chagne[i][0];
        int nc = c+pos_chagne[i][1];
        for(int j=0; j<6; j++){
            temp[j] = status[dice_chage[i][j]];
        }
        for(int j=0; j<6; j++){
            status[j] = temp[j];
        }
        dfs(nr, nc);
        for(int j=0; j<6; j++){
            temp[dice_chage[i][j]] = status[j];
        }
        for(int j=0; j<6; j++){
            status[j] = temp[j];
        }
    }    
}

int main(){
    int r, c;
    for(int i=1; i<=6; i++){
        for(int j=1; j<=6; j++){
            scanf("%d", arr[i]+j);
            if(arr[i][j] == 1){
                r = i; c = j;
            }
        }
    }
    
    dfs(r,c);
    
    int flag = 1;
    for(int i=0; i<6; i++){
        if(dice[i] == 0) flag = 0;
    }
    
    if(flag) printf("%d", dice[5]);
    else printf("0");
    
    return 0;
}