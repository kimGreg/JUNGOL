#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;

int arr[30][30];
int pos[2][4] = {{0,0,1,-1},{1, -1, 0,0}};
set<int> history[30][30];
int ans, r, c;

void dfs(int x, int y, int status, int cnt){
	if(cnt > ans) ans = cnt;
	for(int i=0; i<4; i++){
		int nextX = x+pos[0][i], nextY = y+pos[1][i];
		if(nextX < 0 || nextY < 0 || nextX >= r || nextY >= c)
			continue;
		int nextStatus = status + (1<<arr[nextX][nextY]);
		if(!(status&(1<<arr[nextX][nextY]))  && history[nextX][nextY].find(nextStatus) == history[nextX][nextY].end()){
			history[nextX][nextY].insert(nextStatus);
			dfs(nextX, nextY, nextStatus, cnt+1);
		}
	}
}

int main(){
	scanf("%d %d", &r, &c);
	for(int i=0; i<r; i++){
		for(int j=0; j<c; j++){
			char ch;
			scanf(" %c", &ch);
			arr[i][j] = ch-'A';
		}
	}
	dfs(0, 0, 1<<arr[0][0], 1);
	printf("%d", ans);
	return 0;
}
