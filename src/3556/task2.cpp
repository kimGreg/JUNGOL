#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int a[255], b[255];
vector<pair<int, int>> d;
int arr[63000];

inline void update(int a, int b){
	if(arr[a] == -1) arr[a] = b;
	else arr[a] = min(arr[a], b);
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++)
		scanf("%d %d", a+i, b+i);
	
	d.push_back({a[0], 0});
	d.push_back({0, b[0]});

	for(int i=0; i<n-1; i++){
		memset(arr, -1, sizeof(arr));
		int mx = 0;
		for(auto it : d){
			update(it.first+a[i+1], it.second);
			update(it.first, it.second+b[i+1]);
			mx = max(mx, it.first+a[i+1]);
		}
		d.clear();
		for(int i=0; i<=mx; i++){
			if(arr[i] != -1)
				d.push_back({i, arr[i]});
		}
	}
	int ans = 2e9;
	for(auto it : d){
		ans = min(ans, max(it.first, it.second));
	}
	printf("%d", ans);
	return 0;
}
