#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
class point{
public:
	int x, y, ind;
	point(int _x=0, int _y=0, int _ind=0):x(_x),y(_y),ind(_ind){}
};
vector<int> adj[100100];
vector<point> arr;
vector<int> arrX, arrY;
int tree[600100], visit[200100];
int n, r, d;

void initT(int now, int s, int e){
	tree[now] = -1;
	if(s >= e) return;
	initT(now*2, s, (s+e)/2);
	initT(now*2+1, (s+e)/2+1, e);
}

void update(int now, int l, int r, int t, int diff){
	if(l > t || r < t) return;
	tree[now] = max(tree[now], diff);
	if(l >= r) return;
	update(now*2, l, (l+r)/2, t, diff);
	update(now*2+1, (l+r)/2+1, r, t, diff);
}

int query(int now, int l, int r, int s, int e){
	if(l > e || r < s ) return -1;
	if(s <= l && r <= e) return tree[now];
	int k = query(now*2, l, (l+r)/2, s, e);
	int t = query(now*2+1, (l+r)/2+1, r, s, e);
	return max(k, t);
}

void mkG(){
	int s, e, t;
	initT(1, 1, n);
    sort(arr.begin(), arr.end(), [](point A, point B)->bool{return A.x<B.x;});
	for(int i=0; i<n; i++){
		s = lower_bound(arrY.begin(), arrY.end(), arrY[arr[i].y]-r)-arrY.begin();
		e = lower_bound(arrY.begin(), arrY.end(), arrY[arr[i].y])-arrY.begin();
		t = query(1, 1, n, s+1, e);
		if(t!=-1 && arrX[arr[t].x] >= arrX[arr[i].x] - r - d){
			adj[arr[t].ind].push_back(arr[i].ind);
			adj[arr[i].ind].push_back(arr[t].ind);
		}
		s = lower_bound(arrY.begin(), arrY.end(), arrY[arr[i].y])-arrY.begin();
		e = lower_bound(arrY.begin(), arrY.end(), arrY[arr[i].y]+r+1)-arrY.begin();
		t = query(1, 1, n, s+1, e);
		if(t!=-1 && arrX[arr[t].x] >= arrX[arr[i].x] - r - d){
			adj[arr[t].ind].push_back(arr[i].ind);
			adj[arr[i].ind].push_back(arr[t].ind);
		}
		update(1, 1, n, arr[i].y+1, i);
	}
	initT(1, 1, n);
	sort(arr.begin(), arr.end(), [](point A, point B)->bool{return A.y<B.y;});
	for(int i=0; i<n; i++){
		s = lower_bound(arrX.begin(), arrX.end(), arrX[arr[i].x]-r)-arrX.begin();
		e = lower_bound(arrX.begin(), arrX.end(), arrX[arr[i].x])-arrX.begin();
		t = query(1, 1, n, s+1, e);
		if(t!=-1 && arrY[arr[t].y] >= arrY[arr[i].y] - r - d){
			adj[arr[t].ind].push_back(arr[i].ind);
			adj[arr[i].ind].push_back(arr[t].ind);
		}
		s = lower_bound(arrX.begin(), arrX.end(), arrX[arr[i].x])-arrX.begin();
		e = lower_bound(arrX.begin(), arrX.end(), arrX[arr[i].x]+r+1)-arrX.begin();
		t = query(1, 1, n, s+1, e);
		if(t!=-1 && arrY[arr[t].y] >= arrY[arr[i].y] - r - d){
			adj[arr[t].ind].push_back(arr[i].ind);
			adj[arr[i].ind].push_back(arr[t].ind);
		}
		update(1, 1, n, arr[i].x+1, i);
	}
}

int main(){
	scanf("%d %d", &n, &r);
	arrX.resize(n); arrY.resize(n); arr.resize(n);
	for(int i=0; i<n; i++){
		scanf("%d %d", &arr[i].x, &arr[i].y);
		arr[i].ind = i;
		arrX.push_back(arr[i].x);
		arrY.push_back(arr[i].y);
	}
	sort(arrX.begin(), arrX.end()); sort(arrY.begin(), arrY.end());
	arrX.erase(unique(arrX.begin(), arrX.end()), arrX.end());
	arrY.erase(unique(arrY.begin(), arrY.end()), arrY.end());
	for(int i=0; i<n; i++){
		arr[i].x = lower_bound(arrX.begin(), arrX.end(), arr[i].x)-arrX.begin();
		arr[i].y = lower_bound(arrY.begin(), arrY.end(), arr[i].y)-arrY.begin();
	}	
	scanf("%d", &d);
	mkG();
	sort(arr.begin(), arr.end(), [](point A, point B)->bool{return A.ind < B.ind;});
	queue<int> que;
	for(int i=0; i<n; i++){
		if(arr[i].x == 0 &&  arr[i].y == 0){
			que.push(i);
			visit[i] = 1;
			break;
		}
	}
	int ans = 0;
	while(!que.empty()){
		int now = que.front(); que.pop();
		ans = max(ans, arrX[arr[now].x] + arrY[arr[now].y]);
		for(auto it : adj[now]){
			if(visit[it]) continue;
			visit[it] = 1;
			que.push(it);
		}
	}
	printf("%d", ans + 2*r);
	return 0;
}
