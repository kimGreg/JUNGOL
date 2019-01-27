#include <cstdio>
#include <algorithm>
using namespace std;
int tree[200000], lazy[200000];

int getMax(int now, int l, int r, int s, int e){
	if(lazy[now] != 0){
		tree[now] += lazy[now];
		if(l != r){
			lazy[now*2] += lazy[now];
			lazy[now*2+1] += lazy[now];
		}
		lazy[now] = 0;
	}
	if(l > e || r < s) return 0;
	if(s <= l && r <= e) return tree[now];
	return max(getMax(now*2, l, (l+r)/2, s, e), getMax(now*2+1, (l+r)/2+1, r, s, e));
}

void update(int now, int l, int r, int s, int e, int val){
	if(lazy[now] != 0){
		tree[now] += lazy[now];
		if(l != r){
			lazy[now*2] += lazy[now];
			lazy[now*2+1] += lazy[now];
		}
		lazy[now] = 0;
	}
	if(l > e || r < s) return;
	if(s <= l && r <= e){
		tree[now] += val;
		if(l != r){
			lazy[now*2] += val;
			lazy[now*2+1] += val;
		}
		return;
	}
	update(now*2, l, (l+r)/2, s, e, val);
	update(now*2+1, (l+r)/2+1, r, s, e, val);
	tree[now] = max(tree[now*2], tree[now*2+1]);
}

int main(){
	int n, s, r;
	scanf("%d %d %d", &n, &s, &r);
	while(r--){
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		if(getMax(1, 1, n, a, b-1) + c <= s){
			printf("T\n");
			update(1, 1, n, a, b-1, c);
		}else printf("N\n");
	}
	return 0;
}
