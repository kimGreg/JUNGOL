#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

class Obs{
public:
	int x, yl, yh, n;
	Obs(){}
	Obs(int _x, int _y1, int _y2, int _n):x(_x),yl(_y1),yh(_y2),n(_n){
		if(yl>yh) swap(yl, yh);
	}
	bool operator<(const Obs & O)const{
		if(O.x != x) return x > O.x;
		return yh > O.yh;
	}
	void input(){
		scanf("%d %d %d", &x, &yl, &yh);
	}
};

vector<Obs> obss;
vector<int> Yans;
int ans[100100][2], path[100100][2];


Obs getObs(int x, int y){
	Obs res = obss[0];
	for(int i=1; i<obss.size(); i++){
		if((obss[i].yh > y) && (y > obss[i].yl) && (obss[i].x >= x) && (res.x > obss[i].x)){
			res = obss[i];
		}
	}
	return res;
}


void getAns(int now, int k){
	if(path[now][k] == 0){
		if(k == 0)
			Yans.push_back(obss[now].yh);
		else
			Yans.push_back(obss[now].yl);
        
		return;
	}

	Obs nextObs;
	if(k == 0) nextObs = getObs(obss[now].x, obss[now].yh);
	else nextObs = getObs(obss[now].x, obss[now].yl);

	if(path[now][k]&1)
		getAns(nextObs.n, 0);
    
	if(path[now][k]&2)
		getAns(nextObs.n, 1);
}

int main(){
	int n;
	int start, end;
	scanf("%d %d %d", &n, &start, &end);
	obss.resize(n);
	for(int i=0; i<n; i++){
		obss[i].input();
	}
	obss.push_back({0, start, start, 0});
	obss.push_back({end, 0, 0, 0});
	sort(obss.begin(), obss.end());
	for(int i=n+1; i>=0; i--) obss[1+n-i].n = i;
    for(int i=0; i<obss.size(); i++) printf("%d : %d %d %d\n", obss[i].n, obss[i].x, obss[i].yl, obss[i].yh);
	for(auto it : obss){
		if(it.x == end) continue;
		Obs NextObs = getObs(it.x, it.yl);
        printf("in the for loop %d %d %d\n", it.n, it.yl, NextObs.n);
		if(NextObs.x == end){//끝일떄
			ans[it.n][0] = NextObs.x - it.x;
			path[it.n][0] = 0;
		}else{
			int a = NextObs.x - it.x + NextObs.yh - it.yl + ans[NextObs.n][0]; // 0 -> h
			int b = NextObs.x - it.x + it.yl - NextObs.yl + ans[NextObs.n][1]; // 1 -> l
			ans[it.n][0] = min(a, b);
			if(a < b)
				path[it.n][0] = 1;
			else if(a > b)
				path[it.n][0] = 2;
			else
				path[it.n][0] = 3;
		}
        printf("next :  %d\n", path[it.n][0]);
        
		NextObs = getObs(it.x, it.yh);
        printf("in the for loop %d %d %d\n", it.n, it.yh, NextObs.n);
		if(NextObs.x == end){
			ans[it.n][1] = NextObs.x = it.x;
			path[it.n][1] = 0;
		}else{
			int a = NextObs.x - it.x + NextObs.yh - it.yh + ans[NextObs.n][0];
			int b = NextObs.x - it.x + it.yh - NextObs.yl + ans[NextObs.n][1];
			ans[it.n][1] = min(a, b);
			if(a < b)
				path[it.n][1] = 1;
			else if(a > b)
				path[it.n][1] = 2;
			else
				path[it.n][1] = 3;
		}
        printf("next :  %d\n", path[it.n][1]);
	}
	
	getAns(0, 1);
	sort(Yans.begin(), Yans.end());
	Yans.erase(unique(Yans.begin(), Yans.end()), Yans.end());
	printf("%d\n%d ", ans[0][1], Yans.size());
	for(auto it : Yans) printf("%d ", it);
	return 0;
}
