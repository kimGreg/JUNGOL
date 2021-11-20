#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
class data{
public:
    int x, y;
    data(){}
    data(int _x, int _y):x(_x),y(_y){}
};
class data2{
public:
	int x, y, rk;
	data2(){}
	data2(int _x, int _y, int _r):x(_x),y(_y),rk(_r){}
	bool operator < (const data2 & D)const{
		return rk > D.rk;
	}
};
int arr[2005][2005], rarr[2005][2005], par[100010], psz[100010], pos[2][4] = {{0, 0, 1, -1}, {1, -1, 0, 0}};
queue<data> que;
priority_queue<data2> ans;

int getPar(int x){
    if(par[x] == x) return x;
    return par[x] = getPar(par[x]);
}

int main(){
    int n, k, a, b;
    scanf("%d %d", &n, &k);
    for(int i=1; i<=k; i++){
        scanf("%d %d", &a, &b);
        par[i] = i;
        psz[i] = 1;
        arr[a][b] = i;
        rarr[a][b] = 1;
        que.push({a, b});
    }
    int lastrk = 1;
    while(!que.empty()){
        int x = que.front().x, y = que.front().y, rk = rarr[x][y];
        while(lastrk != rk && !ans.empty() && ans.top().rk < rk-1){
            int x=ans.top().x, y=ans.top().y, rk = ans.top().rk;
            ans.pop();
            x = getPar(x); y = getPar(y);
            if(x != y){
                par[y] = x;
                psz[x] += psz[y];
                if(k == psz[x]){
                    printf("%d", rk);
                    return 0;
                }
            }
		}
        lastrk = rk;
		que.pop();
        for(int i=0; i<4; i++){
            int X = x+pos[0][i], Y = y+pos[1][i];
            if(X < 1 || X > n || Y < 1 || Y > n) continue;
            if(rarr[X][Y] == 0){
                arr[X][Y] = arr[x][y];
                rarr[X][Y] = rk+1;
                que.push({X, Y});
            }else{
                int t = getPar(arr[X][Y]), p = getPar(arr[x][y]);
                if(t!=p && arr[X][Y] <= arr[x][y]) ans.push({t, p, rarr[X][Y] - 1});
            }
        }
    }
    printf("%d", lastrk-1);
    return 0;
}

