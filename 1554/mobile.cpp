#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
int tree[4000][4000];
int s;

int updateY(int now, int l, int r, int x, int y, int d){
	if(l > y || r < y) return 0;
	if(l == r){
		tree[x][now] += d;
		return now;
	}
	int m = (l+r)/2;
	int k = updateY(now*2, l, m, x, y, d), t = updateY(now*2+1, m+1, r, x, y, d);
	tree[x][now] = tree[x][now*2] + tree[x][now*2+1];
	return max(k, t);
}

int update(int now, int l, int r, int x, int y, int d){
	if(l > x || r < x) return 0;
	if(l == r){
		return updateY(1, 1, s, now, y, d);
	}
	int m = (l+r)/2;
	int k = update(now*2, l, m, x, y, d), t = update(now*2+1, m+1, r, x, y, d);
	k = max(k, t);
	for(int i=0; i<=k; i++) tree[now][i] = tree[now*2][i] + tree[now*2+1][i];
	return k;
}

int queryY(int now, int l, int r, int x, int y1, int y2){
	if(l > y2 || r < y1) return 0;
	if(l >= y1 && r <= y2) return tree[x][now];
	return queryY(now*2, l, (l+r)/2, x, y1, y2) + queryY(now*2+1, (l+r)/2+1, r, x, y1, y2);
}

int query(int now, int l, int r, int x1, int x2, int y1, int y2){
	if(l > x2 || r < x1) return 0;
	if(l >= x1 && r <= x2) return queryY(1, 1, s, now, y1, y2);
	return query(now*2, l, (l+r)/2, x1, x2, y1, y2) + query(now*2+1, (l+r)/2+1, r, x1, x2, y1, y2);
}

int main(){
	bool flag = true;
	while(flag){
		int m; 
		scanf("%d", &m);
		switch(m){
		case 0:
			scanf("%d", &s);
			break;
		case 1:
			int x, y, val;
			scanf("%d %d %d", &x, &y, &val);
			update(1, 1, s, x+1, y+1, val);
			break;
		case 2:
			int l, b, r, t;
			scanf("%d %d %d %d", &l, &b, &r, &t);
			printf("%d\n", query(1, 1, s, l+1, r+1, b+1, t+1));
			break;
		case 3:
			flag = 0;
		}
	}
	return 0;
}
