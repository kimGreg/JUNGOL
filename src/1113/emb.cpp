#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

class data{
public:
	int x, y, dir, cnt;
	data(){}
	data(int _x, int _y, int _d, int _cnt = 0):x(_x),y(_y),dir(_d),cnt(_cnt){}
	bool operator < (const data & D)const{
		return cnt > D.cnt;
	}
};

priority_queue<data> pq;

int pos[2][4] = {{0, -1, 0, 1}, {1, 0, -1, 0}};
int visit[110][110][4], arr[110][110];

int main(){
	int n, m, ex, ey;
	scanf("%d %d %d %d", &n, &m, &ex, &ey);
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			scanf("%d", arr[i] + j);
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			for(int k=0; k<4; k++)
				visit[i][j][k] = 2e9;
		}
	}
	pq.push({0, 0, 0, 0});
	visit[0][0][0] = 1;
	pq.push({0, 0, 3, 0});
	visit[0][0][3] = 1;
	int ans = 2e9;
	while(!pq.empty()){
		int x = pq.top().x, y = pq.top().y;
		int cnt = pq.top().cnt, dir = pq.top().dir;
		pq.pop();
		if(x == ex && y == ey){
			ans = min(ans, cnt);
		}
		for(int i=0; i<4; i++){
			int nx = x+pos[0][i], ny = y+pos[1][i], nc = cnt + !(i == dir);
			if(nx<0 || ny < 0 || nx >= n || ny >= m) continue;
			if(!arr[nx][ny]) continue;
			if(visit[nx][ny][i] <= nc) continue;
			visit[nx][ny][i] = nc;
			pq.push({nx, ny, i, nc});
		}
	}
	printf("%d", ans);;
	return 0;
}
