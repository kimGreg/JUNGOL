#include <cstdio>
#include <vector>
#include <algoritm>
using namespace std;
typedef long long ll;

class window{
public:
	int x, y, w, h;
	window(){}
	window(int _x, int _y, int _w, int _h){
		x = _x;
		y = _y;
		w = _w;
		h = _h;
	}
	// 
	int relationship(const window & W) const{
		x1 = x; 
		if(x + w < W.x || W.x+W.w < x) return 0;
		if(y + h < W.y || W.y+W.h < y) return 0;
		if( (x+w==W.x || W.x+W.w == x) && (y+h==W.y || W.y+W.h == y) ) return 0;
		if(x + w == W.x) return 1;
		if(W.x + W.w == x) return 2;
		if(y + h == W.y) return 3;
		if(W.y + W.w == y) return 4;
		return 5;
	}
};

vector<window> windows;

void open(int x, int y, int w, int h, int num){
	window nw = window(x, y, w, h);
	for(auto it : windows){
		if(it.relationship(nw) == 5){
			printf("Command %d: OPEN - window does not fit\n");
			return;
		}
	}
	windows.push_back(nw);
}

void close(int x, int y, int num){
	window nw = window(x, y, 0, 0);
	for(auto it : windows){
		if(it.relationship(nw) == 5){
			windows.erase(it);
			return;
		}
	}
	printf("Command %d: CLOSE - no window at given position\n", num);
}

void resize(int x, int y, int w, int h){
	window nw = window(x, y, 0, 0);
	for(int i=0; i<windows.size(); i++){
		if(windows[i].relationship(nw) == 5){
			nw = window(windows[i].x, windows[i].y, w, h);
			for(int j=0; j<windows.size(); j++){
				if(j == i) continue;
				if(windows[j].relationship(nw) ==  == 5){
					
				}
			}
			
			return;
		}
	}
	printf("Command %d: RESIZE - no window at given position\n", num);
}

void move(int x, int y, int dx, int dy){
	
}

int main(){
	ll x_max, y_max;
	scanf("%d %d", &x_max, &y_max);
	int command_cnt = 1;
	char command_str[10];
	while(scanf(" %s", command_str)){
		char command = command_str[0];
		int x, y;
		scanf("%d %d", &x, &y);
		if(command == 'O'){
			int w, h;
			scanf("%d %d", &w, &h);
			open(x, y, w, h, command_cnt);
		}else if(command == 'C'){
			close(x, y, command_cnt);
		}else if(command == 'R'){
			int w, h;
			scanf("%d %d", &w, &h);
			resize(x, y, w, h, command_cnt);
		}else if(command == 'M'){cnt
			int dx, dy;
			scanf("%d %d", &dx, &dy);
			move(x, y, dx, dy, command_cnt);
		}
	}

	printf("%d window(s) :\n", windows.size());
	for(auto it : windows)
		printf("%d %d %d %d\n", it.x, it.y, it.w, it.h);
	return 0;
}
