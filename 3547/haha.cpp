#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

class Data{
public:
	int cost[4][4];
	char color[4][4];
	Data(){}
	
	void input(){
		for(int i=0; i<4; i++)
			for(int j=0; j<4; j++)
				scanf(" %d", cost[i] + j);
		for(int i=0; i<4; i++)
			for(int j=0; j<4; j++)
				scanf(" %c", color[i]+j);
	}

	void rotate(){
		int tempMap[4][4];
		char tempColor[4][4];
		memcpy(tempMap, cost, sizeof(cost));
		memcpy(tempColor, color, sizeof(color));
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				color[i][j] = tempColor[3-j][i];
				cost[i][j] = tempMap[3-j][i];
			}
		}
	}
};

Data arr[10];
int L[3], map[5][5], ans;
char mapColor[5][5];

int calculate(char b){
	if(b == 'R') return 7;
	if(b == 'B') return 5;
	if(b == 'G') return 3;
	if(b == 'Y') return 2;
	return 0;
}

void solve(int n){
	if(n == 3){
		int temp = 0;
		for(int i=0; i<5; i++)
			for(int j=0; j<5; j++)
				temp += calculate(mapColor[i][j])*map[i][j];
		ans = max(ans, temp);
		return;
	}
	int tempMap[5][5];
	char tempMapColor[5][5];
	memcpy(tempMap, map, sizeof(map));
	memcpy(tempMapColor, mapColor, sizeof(mapColor));
    
    Data D = arr[L[n]];
    for(int k=0; k<4; k++){
        D.rotate();
        for(int i=0; i<2; i++){
            for(int j=0; j<2; j++){
				
                for(int I=0; I<4; I++){
					for(int J=0; J<4; J++){
						map[I+i][J+j] += D.cost[I][J];
						map[I+i][J+j] = min(9, max(map[I+i][J+j], 0));
						if(D.color[I][J] == 'W') continue;
						mapColor[I+i][J+j] = D.color[I][J];
					}
				}
				solve(n+1);
				memcpy(map, tempMap, sizeof(map));
				memcpy(mapColor, tempMapColor, sizeof(mapColor));
			}
		}
	}
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++) arr[i].input();
	
	for(int i=0; i<5; i++)
		for(int j=0; j<5; j++)
			mapColor[i][j] = 'W';

	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(i == j) continue;
			for(int k=0; k<n; k++){
				if(i == k || j == k) continue;
				L[0] = i;
				L[1] = j;
				L[2] = k;
				solve(0);
			}
		}
	}
	printf("%d", ans);
	return 0;
}
