#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
class data{
public:
	ll x, y, c;
	data(ll _x=0, ll _y=0, ll _c=0):x(_x),y(_y),c(_c){}
};
class data2{
public:
	ll sum, maxsum, lsum, rsum;
	data2(){}
	data2(ll S, ll MS, ll LS, ll RS):sum(S),maxsum(MS),lsum(LS),rsum(RS){}
};

vector<data> arr;
vector<int> Xidx, Yidx;
ll n, sum[10000], maxsum[10000], lsum[10000], rsum[10000];

void update(int now, int l, int r, int t, int c){
	if(l > t || r < t) return;
	if(l == r){
		sum[now] += c;
		maxsum[now] += c;
		lsum[now] += c;
		rsum[now] += c;
		return;
	}
	update(now*2, l, (l+r)/2, t, c);
	update(now*2+1, (l+r)/2+1, r, t, c);
	sum[now] = sum[now*2] + sum[now*2+1];
	lsum[now] = max(lsum[now*2], sum[now*2] + lsum[now*2+1]);
	rsum[now] = max(rsum[now*2+1], rsum[now*2] + sum[now*2+1]);
	maxsum[now] = max(max(maxsum[now*2], maxsum[now*2+1]), max(sum[now], rsum[now*2]+lsum[now*2+1]));
}

int main(){
	scanf("%lld", &n);
	arr.resize(n);
	for(int i=0; i<n; i++){
		scanf("%lld %lld %lld", &arr[i].x, &arr[i].y, &arr[i].c);
		Xidx.push_back(arr[i].x);
		Yidx.push_back(arr[i].y);
	}
	sort(Xidx.begin(), Xidx.end()); sort(Yidx.begin(), Yidx.end());
	Xidx.erase(unique(Xidx.begin(), Xidx.end()), Xidx.end());
	Yidx.erase(unique(Yidx.begin(), Yidx.end()), Yidx.end());
	for(int i=0; i<n; i++){
		arr[i].x = lower_bound(Xidx.begin(), Xidx.end(), arr[i].x) - Xidx.begin() + 1;
		arr[i].y = lower_bound(Yidx.begin(), Yidx.end(), arr[i].y) - Yidx.begin() + 1;
	}
	sort(arr.begin(), arr.end(), [](data & A, data & B)->bool{return A.x!=B.x?A.x<B.x:A.y<B.y;});
	ll ans = 0;
	for(int i=0; i<n; i++){
		if(i > 0 && arr[i].x == arr[i-1].x) continue;
		for(int i=0; i<10000; i++) sum[i]=maxsum[i]=lsum[i]=rsum[i]=0;
		for(int j=i; j<n; j++){
			if(j > 0 && arr[j].x != arr[j-1].x) ans = max(ans, maxsum[1]);
			update(1, 1, Yidx.size(), arr[j].y, arr[j].c);
		}
		ans = max(ans, maxsum[1]);
	}
	printf("%lld", ans);
	return 0;
}
