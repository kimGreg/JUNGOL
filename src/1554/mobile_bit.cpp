#include <cstdio>
#include <algorithm>
using namespace std;
int tree[4000][4000], s; 

void update(int x, int y, int a){
	while(y <= s){
		tree[x][y] += a;
		y += (y & -y);
	}
}

int Sum(int x, int y){
	int ans = 0;
	while(y > 0){
		ans += tree[x][y];
		y -= (y & -y);
	}
	return ans;
}

int main(){
	bool flag = true;
	while(flag){
		int m, ans = 0;
		scanf("%d", &m);
		switch(m){
		case 0:
			scanf("%d", &s);
			break;
		case 1:
			int x, y, a;
			scanf("%d %d %d", &x, &y, &a);
			x++; y++;
			while(x <= s){
				update(x, y, a);
				x += (x & -x);
			}
			break;
		case 2:
			int x1, y1, x2, y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			x2++; y2++;
			while(x2 > 0){
				ans += Sum(x2, y2) - Sum(x2, y1);
				x2 -= (x2 & -x2);
			}
			while(x1 > 0){
				ans -= Sum(x1, y2) - Sum(x1, y1);
				x1 -= (x1 & -x1);
			}
			printf("%d\n", ans);
			break;
		case 3:
			flag = false;
		}
	}
	return 0;
}
