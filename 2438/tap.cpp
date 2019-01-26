#include <cstdio>
#include <algorithm>
using namespace std;
class data{
public:
	int mode, max_l, lc, rc, ll, rl;
	data(){}
	data(int _mode, int _max_l, int _lc, int _rc, int _ll, int _rl):mode(_mode),max_l(_max_l),lc(_lc),rc(_rc),ll(_ll),rl(_rl){}
};

data segTree[800000];

void init(int now, int l, int r){
	if(l == r){
		segTree[now] = data(1, 1, 0, 0, 1, 1);
		return;
	}
	init(now*2, l, (l+r)/2);
	init(now*2+1, (l+r)/2+1, r);
	segTree[now] = data(0, 1, 0, 0, 1, 1);
}

void update(int now, int l, int r, int target){
	if(l > target || r < target) return;
	if(l == r){
		segTree[now].lc = segTree[now].rc = 1-segTree[now].lc;
		return;
	}
	int lcil = now*2, rcil = now*2+1;
	update(now*2, l, (l+r)/2, target);
	update(now*2+1, (l+r)/2+1, r, target);
	if(segTree[lcil].rc == segTree[rcil].lc) segTree[now] = {0, max(segTree[lcil].max_l, segTree[rcil].max_l),segTree[lcil].lc, segTree[rcil].rc, segTree[lcil].ll, segTree[rcil].rl};
	else{
		int sz = max(segTree[lcil].rl + segTree[rcil].ll, max(segTree[lcil].max_l, segTree[rcil].max_l));
		if(segTree[lcil].mode){
			if(segTree[rcil].mode) segTree[now] = {1, sz, segTree[lcil].lc, segTree[rcil].rc, sz, sz};
			else segTree[now] = {0, sz, segTree[lcil].lc, segTree[rcil].rc, segTree[lcil].rl + segTree[rcil].ll, segTree[rcil].rl};
		}else{
			if(segTree[rcil].mode) segTree[now] = {0, sz, segTree[lcil].lc, segTree[rcil].rc, segTree[lcil].ll, segTree[lcil].rl + segTree[rcil].ll};
			else segTree[now] = {0, sz, segTree[lcil].lc, segTree[rcil].rc, segTree[lcil].ll, segTree[rcil].rl};
		}
	}
}


int main(){
	int n, q, a;
	scanf("%d %d", &n, &q);
	init(1, 1, n);
	while(q--){
		scanf("%d", &a);
		update(1, 1, n, a);
		printf("%d\n", segTree[1].max_l);
	}
	return 0;
}
