#include <cstdio>
#include <algorithm>
using namespace std;
int Mxt[2000000], Mnt[200000];
int arr[200000];

void init(int now, int l, int r){
	if(l == r){
		Mxt[now] = arr[l];
		Mnt[now] = arr[l];
		return;
	}
	int m = (l+r)/2;
	init(now*2, l, m);
	init(now*2+1, m+1, r);
	Mxt[now] = max(Mxt[now*2], Mxt[now*2+1]);
	Mnt[now] = min(Mnt[now*2], Mnt[now*2+1]);
}

pair<int, int> query(int now, int l, int r, int s, int e){
	if(l > e || r < s) return {-2e9, 2e9};
	if(l >= s && r <= e) return {Mxt[now], Mnt[now]};
	int m = (l+r)/2;
	pair<int, int> A1 = query(now*2, l, m, s, e), A2 = query(now*2+1, m+1, r, s, e);
	return {max(A1.first, A2.first), min(A1.second, A2.second)};
}

int main(){	
	int n, q;
	scanf("%d %d", &n, &q);
	for(int i=1; i<=n; i++) scanf("%d", arr+i);
	init(1, 1, n);
	while(q--){
		int s, e;
		scanf("%d %d", &s, &e);
		pair<int, int> A = query(1, 1, n, s, e);
		printf("%d\n", A.first - A.second);
	}
	return 0;
}
