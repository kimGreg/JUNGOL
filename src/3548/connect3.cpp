#include <cstdio>
using namespace std;

int map[10][10];
int pos[2][4][2] = {
	{{-1,0,1}, {0,0,0}, {-1,0,1}, {-1,0,1}}, 
	{{0,0,0}, {-1,0,1}, {-1,0,1}, {1,0,-1}}
};

int top[5], cnt[5][5][5];
int lasti, lastj, lastk;

bool isEnd(void){
	int cnt = 0;
	for(int i=1; i<=4; i++){
		for(int j=1; j<=4; j++){
			int k = map[i][j];
			if(k == 0) continue;
			for(int k=0; k<4; k++){
				int flag = 1;
				for(int t=0; t<3; t++){
					if(k != map[i+pos[0][k][t]][j+pos[1][k][t]]){
						flag = 0;
						break;
					}
				}
				if(flag){
					lasti = i;
					lastj = j;
					lastk = k;
				}
				cnt += flag;
			}
		}
	}
	return cnt == 1;
}

bool isCorr(void){
	for(int i=1; i<=4; i++){
		top[i] = 0;
		for(int j=4; j>0; j--){
			if(map[i][j]){
				if(top[i]) return 0;
				top[i] = j;
			}
		}
	}
	return 1;
}

void dfs(int a, int b){
	if(a > 4){
		if(!iscorr()) return;
		if(!isEnd())  return;
		for(int t=0; t<3; t++){
			int nowx = lasti+pos[0][lastk][t];
			int nowy = lastj+pos[1][lastk][t];
			if(top[nowx] != nowy) continue;
			for(int i=1; i<=4; i++){
				if(map[i][1] == 1) cnt[i][nowx][nowy]++;
			}
		}
	}
	for(int i=0; i<
}

int main(){
	for(int i=1; i<=4; i++){
		dfs(1, x);
	}
	return 0;
}
