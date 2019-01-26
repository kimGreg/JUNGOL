#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
int b, n, d, m;
long long tree2[3000][3000];
int arr[100100];

void update(int x, int y){
	while(y <= 2*m-1){
		tree2[x][y]++;
		y += (y & -y);
	}
}
long long Sum(int x, int y){
	long long ans = 0;
	while(y > 0){
		ans += tree2[x][y];
		y -= (y & -y);
	}
	return ans;
}

void solve1(){
	for(int i=0; i<n; i++) scanf("%d", arr+i);
	sort(arr, arr+n);
	queue<int> que;
	que.push(arr[0]);
	long long ans = 0;
	for(int i=1; i<n; i++){
		while(!que.empty() && que.front() < arr[i]-d) que.pop();
		ans += que.size();
		que.push(arr[i]);
	}
	printf("%lld", ans);
}

void solve2(){
	long long ans = 0;
	for(int i=0; i<n; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		int x = a+b-1, y = a-b+m;
		int x1 = max(0, x-d-1), x2 = min(m*2-1, x+d);
		int y1 = max(0, y-d-1), y2 = min(m*2-1, y+d);
		while(x2 > 0){
			ans += Sum(x2, y2) - Sum(x2, y1);
			x2 -= (x2 & -x2);
		}
		while(x1 > 0){
			ans -= Sum(x1, y2) - Sum(x1, y1);
			x1 -= (x1 & -x1);
		}
		while(x <= 2*m-1){
			update(x, y);
			x += (x&-x);
		}
	}
	printf("%lld", ans);
}

int main(){
	scanf("%d %d %d %d", &b, &n, &d, &m);
	if(b==1) solve1();
	else solve2();
	return 0;
}
