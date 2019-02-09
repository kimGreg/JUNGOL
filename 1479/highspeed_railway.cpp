#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
class robot{
public:
	int s, e;
	robot(int _s=0, int _e=0):s(_s),e(_e){}
};
const ll mod = 20070713;
vector<robot> arr;
vector<int> arrP;
int n, tree[400400];
ll d[100100][2];

void init(int now, int l, int r){
	tree[now] = 2e9;
	if(l == r) return;
	init(now*2, l, (l+r)/2);
	init(now*2+1, (l+r)/2+1, r);
}

void update(int now, int l, int r, int t, int diff){
	if(l > t) return;
	if(l == r){
		tree[now] = min(tree[now], diff);
		return;
	}
	update(now*2, l, (l+r)/2, t, diff);
	update(now*2+1, (l+r)/2+1, r, t, diff);
	tree[now] = min(tree[now*2], tree[now*2+1]);
}

int getMin(int now, int l, int r, int t){
	if(r < t) return 2e9;
	if(l >= t) return tree[now];
	return min(getMin(now*2, l, (l+r)/2, t), getMin(now*2+1, (l+r)/2+1, r, t));
}

int main(){
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		arr.push_back({a, b});
		arrP.push_back(a), arrP.push_back(b);
	}
	sort(arrP.begin(), arrP.end());
	for(int i=0; i<n; i++) arr[i] = {(int)(lower_bound(arrP.begin(), arrP.end(), arr[i].s)-arrP.begin())+1, (int)(lower_bound(arrP.begin(), arrP.end(), arr[i].e)-arrP.begin())+1};
	sort(arr.begin(), arr.end(), [](robot & A, robot & B)->bool{return A.s!= B.s?A.s<B.s:A.e<B.e;});
	for(int i=0; i<n; i++) printf("%d %d\n", arr[i].s, arr[i].e);
	printf("\n");
	d[0][0] = d[0][1] = 1;
	int lastM = 0;
	init(1, 1, 2*n);
	update(1, 1, 2*n, arr[0].e, 0);
	for(int i=1; i<n; i++){
		d[i][1] = (d[i-1][0] + d[i-1][1])%mod;
		int mn = getMin(1, 1, 2*n, arr[i].s);
		if(mn == 2e9) d[i][0] = (d[i-1][0] + d[i-1][1])%mod;
		else d[i][0] = d[mn][1];
		
		printf("%lld %lld %d\n", d[i][0], d[i][1], mn);
		if(arr[lastM].e < arr[i].e) lastM = i;
		update(1, 1, 2*n, arr[i].e, i);
	}
	printf("%lld", (d[n-1][0] + d[n-1][1])%mod);
	return 0;
}
