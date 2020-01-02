#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

char map[110][110];
int pos[2][2] = {{0, 1}, {1, 0}};
int d[110][110][220];
int w, h;

inline bool isOkay(int x, int y){
	return (1<=x) && (x<=h) && (1<=y) && (y<=w);
}

void update(int x1, int x2, int step, int k){
	int & target = d[x1][x2][step];
	if(target == -1) target = k;
	else target = max(target, k);
}

int main(){
	scanf("%d %d", &w, &h);
	for(int i=1; i<=h; i++){
		for(int j=1; j<=w; j++){
			scanf(" %c", map[i]+j);
		}
	}

	memset(d, -1, sizeof(d));
	d[1][1][1] = (map[1][1] == '*');
	for(int step = 1; step < h+w-1; step++){
		int x1 = step, y1 = 1;
		if(x1 > h){
			y1 = step+1-h;
			x1 = h;
		}

		while(isOkay(x1, y1)){
			int x2 = x1, y2 = step + 1 - x1;
			
			while(isOkay(x2, y2)){
				if(d[x1][x2][step] != -1){

					for(int i=0; i<2; i++){
						for(int j=0; j<2; j++){
							int nx1 = x1+pos[0][i], ny1 = y1+pos[1][i];
							int nx2 = x2+pos[0][j], ny2 = y2+pos[1][j];
							if(!isOkay(nx1, ny1) || !isOkay(nx2, ny2))
								continue;
							if(map[nx1][ny1] == '#' || map[nx2][ny2] == '#')
								continue;
							if(nx1 < nx2)
								continue;

							int nextVal = d[x1][x2][step];

							if(map[nx1][ny1] == '*') nextVal++;
							if(map[nx2][ny2] == '*' && nx1 != nx2) nextVal++;
							
							update(nx1, nx2, step+1, nextVal);
						}
					}
				}
				x2--; y2++;
			}
			x1--; y1++;
		}
	}

	printf("%d", d[h][h][h+w-1]);
	
	return 0;
}
