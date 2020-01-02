#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

vector<pair<int, int>> finish;
char map[20][20], input[60];
int pos[2][4] = {{0, -1, 0, 1},{1, 0, -1, 0}};
int r, c;

void moveBox(int x, int y, int dir){
	int nextX = x+pos[0][dir], nextY = y+pos[1][dir];
	char & nextM = map[nextX][nextY];
	if(nextM == '+' || nextM == '.'){
		map[x][y] = map[x][y] == 'b' ? '.' : '+';
		nextM = (nextM == '.') ? 'b' : 'B';
	}
}

bool moveChar(int x, int y, int dir){
	int nextX = x + pos[0][dir], nextY = y + pos[1][dir];
	char & nextM = map[nextX][nextY];
	
	if(nextM == 'b' || nextM == 'B')
		moveBox(nextX, nextY, dir);

	if(nextM == '.' || nextM == '+'){
		map[x][y] = map[x][y] == 'w' ?  '.' : '+';
		nextM = nextM == '.' ? 'w' : 'W';
		return 1;
	}
	return 0;
}

bool isEnd(){
	for(int i=1; i<=r; i++){
		for(int j=1; j<c; j++){
			if(map[i][j] == 'b') 
				return 0;
		}
	}
	return 1;
}

int main(){
	int x, y;
	scanf("%d %d", &r, &c);
	for(int i=1; i<=r; i++){
		for(int j=1; j<=c; j++){
			scanf(" %c", map[i] + j);
			if(map[i][j] == 'w' || map[i][j] == 'W'){
				x = i;
				y = j;
			}
		}
	}
	scanf(" %s", input);
	int len = strlen(input);
	for(int i=0; i<len; i++){
		int dir;
		if(input[i] == 'U') dir = 1;
		else if(input[i] == 'D') dir = 3;
		else if(input[i] == 'L') dir = 2;
		else dir = 0;
		if(moveChar(x, y, dir)){
			x = x+pos[0][dir];
			y = y+pos[1][dir];
		}
		if(isEnd()) break;
	}
	if(isEnd()) printf("complete\n");
	else printf("incomplete\n");
	for(int i=1; i<=r; i++){
		for(int j=1; j<=c; j++){
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
	return 0;
}
