#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
int arr[300000], minT[800000], maxT[800000];
int table[5][5] = {{0,3,2,3,2},{1,-1,-1,-1,-1},{3,3,-1,-1,2},{3,-1,-1,-1,-1},{1,1,-1,-1,4}};

void init(int now, int l, int r){
	if(l == r){
		minT[now] = maxT[now] = arr[l];
		return;
	}
	init(now*2, l, (l+r)/2);
	init(now*2+1, (l+r)/2+1, r);
	minT[now] = min(minT[now*2], minT[now*2+1]);
	maxT[now] = max(maxT[now*2], maxT[now*2+1]);
}

void update(int now, int l, int r, int t, int val){	
	if(l > t || r < t) return;
	if(l == r){
		minT[now] = maxT[now] = val;
		return;
	}
	update(now*2, l, (l+r)/2, t, val);
	update(now*2+1, (l+r)/2+1, r, t, val);
	minT[now] = min(minT[now*2], minT[now*2+1]);
	maxT[now] = max(maxT[now*2], maxT[now*2+1]);
}

int getAns(int now, int l, int r, int s, int e){
	if(l == r){
		if(s <= arr[l] && arr[l] <= e) return 4;
		else return 0;
	}
	if(minT[now] > e || maxT[now] < s) return 0;
	if(minT[now] >= s && maxT[now] <= e) return 4;
	int lA = getAns(now*2, l, (l+r)/2, s, e);
	int rA = getAns(now*2+1, (l+r)/2+1, r, s, e);
	if(lA == -1 || rA == -1) return -1;
	return table[lA][rA];
}

int main(){
	int n, t;
	scanf("%d %d", &n, &t);
	for(int i=1; i<=n; i++) scanf("%d", arr+i);
	init(1, 1, n);
	while(t--){
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		if(a == 1){
			swap(arr[b], arr[c]);
			update(1, 1, n, b, arr[b]);
			update(1, 1, n, c, arr[c]);
		}else{
			int k = getAns(1, 1, n, b, c);
			if(k != -1) printf("YES\n");
			else printf("NO\n");
		}
	}
	return 0;
}
