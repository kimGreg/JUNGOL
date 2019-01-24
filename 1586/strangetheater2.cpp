#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
pii tree[600000];
const ll MAX = 100000, MOD = 987654313;
pii getAns(int node, int l, int r, int s, int e){
	if(l > e || r < s) return {0,0};
	if(s <= l && r <= e) return tree[node];
	pii A1 = getAns(node*2, l, (l+r)/2, s, e);
	pii A2 = getAns(node*2+1, (l+r)/2+1, r, s, e);
	if(A1.first != A2.first)
		return A1.first>A2.first?A1:A2;
	else
		return {A1.first, (A1.second + A2.second)%MOD};
}

void update(int node, int l, int r, int t, pii diff){
	if(l > t || t > r) return;
	if(l == r){
		tree[node] = diff;
		return;
	}
	int lc = node*2, rc = node*2+1, m = (l+r)/2;
	update(lc, l, m, t, diff);
	update(rc, m+1, r, t, diff);
	if(tree[lc].first != tree[rc].first)
		tree[node] = tree[lc].first>tree[rc].first?tree[lc]:tree[rc];
	else
		tree[node] = {tree[lc].first, (tree[lc].second + tree[rc].second)%MOD};
}

int main(){
	ll n, a;
	scanf("%lld", &n);
	for(int i=0; i<n; i++){
		scanf("%lld", &a);
		pii temp = getAns(1, 1, MAX, 1, a);
		if(temp.first == 0 && temp.second == 0) temp = {1, 1};
		else temp.first++;
		update(1, 1, MAX, a, temp); 
	}
	pii Ans = getAns(1, 1, MAX, 1, MAX);
	printf("%lld\n%lld", Ans.first, Ans.second);
	return 0;
}
