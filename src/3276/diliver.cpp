#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
class data{
public:
	ll s, e, val;
	data(ll _s=0, ll _e=0, ll _val=0):s(_s),e(_e),val(_val){}
};

vector<data> arr;
vector<ll> tree(5000000);
vector<ll> lazy(5000000);

ll getMx(int now, int l, int r, int s, int e){
	if(l > e || r < s) return 0;
	if(lazy[now] != 0){
		tree[now] += lazy[now];
		if(l != r){
			lazy[now*2] += lazy[now];
			lazy[now*2+1] += lazy[now];
		}
		lazy[now] = 0;
	}
	if(s <= l && r <= e) return tree[now];
	int m = (l+r)/2;
	return max(getMx(now*2, l, m, s, e), getMx(now*2+1, m+1, r, s, e));
}

void update(int now, int l, int r, int s, int e, ll val){
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
	int m = (l+r)/2;
	update(now*2, l, m, s, e, val);
	update(now*2+1, m+1, r, s, e, val);
	tree[now] = max(tree[now*2], tree[now*2+1]);
}

int main(){
	ll n, c, m;
	scanf("%lld %lld %lld", &n, &c, &m);
	for(int i=0; i<m; i++){
		ll a, b, c;
		scanf("%lld %lld %lld", &a, &b, &c);
		arr.push_back({a,b,c});
	}
	sort(arr.begin(), arr.end(), [&](data & a, data & b)->bool{return a.e!=b.e?a.e<b.e:a.s<b.s;});
	ll ans = 0;
	for(auto it : arr){
		int s = it.s, e = it.e-1, val = it.val;
		ll mx = getMx(1, 1, n, s, e);
		if(mx + val > c) val = c - mx;
		update(1, 1, n, s, e, val);
		ans += val;
	}
	printf("%lld", ans);
	return 0;
}
