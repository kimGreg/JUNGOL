#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
int tree[300100], lazy[300300];//tree == 켜져있는 수

void func(int now, int s, int e){
	tree[now] = e-s+1-tree[now];
	if(s!=e){
		lazy[now*2] = 1 - lazy[now*2];
		lazy[now*2+1] = 1 - lazy[now*2+1];
	}
	lazy[now] = 0;
}

void update(int now, int s, int e, int l, int r){
	if(lazy[now]) func(now, s, e);
	if(r < s || e < l) return;
	if(l <= s && e <= r){
		func(now, s, e);
		return;
	}
	update(now*2, s, (s+e)/2, l, r);
	update(now*2+1, (s+e)/2+1, e, l, r);
	tree[now] = tree[now*2] + tree[now*2+1];
}

int getsum(int now, int s, int e, int l, int r){
	if(lazy[now]) func(now, s, e);
	if(r < s || e < l) return 0;
	if(l <= s && e <= r) return tree[now];
	return getsum(now*2, s, (s+e)/2, l, r) + getsum(now*2+1, (s+e)/2+1, e, l, r);
}

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i=0; i<m; i++){
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		if(a == 0) update(1, 1, n, b, c);
		else printf("%d\n", getsum(1, 1, n, b, c));
	}
	return 0;
}
