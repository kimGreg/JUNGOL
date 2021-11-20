#include <cstdio>
int n, a[10010], b[10010], visit[10010][10], dir[10010][10], C[10010][10], d[10010][10];

int f(int now, int turn){
	if(now > n) return 0;
	if(visit[now][turn]) return d[now][turn];
	visit[now][turn] = 1;
	int cur = (a[now]+turn)%10;
	int lt = (b[now]-cur+10) % 10, ls = f(now+1, (turn+lt)%10) + lt;
	int rt = (cur-b[now]+10)%10, rs = f(now+1, turn) + rt;
	if(ls > rs){
		d[now][turn] = rs;
		dir[now][turn] = -1;
		C[now][turn] = rt;
	}else{
		d[now][turn] = ls;
		dir[now][turn] = 1;
		C[now][turn] = lt;
	}
	return d[now][turn];
}

int main(){
	scanf("%d", &n);
	for(int i=1; i<=n; i++) scanf("%1d", a+i);
	for(int i=1; i<=n; i++) scanf("%1d", b+i);
	printf("%d\n", f(1, 0));
	int t = 0;
	for(int i=1; i<=n; i++){
		printf("%d %d\n", i, dir[i][t]*C[i][t]);
		if(dir[i][t] == 1) t = (t+C[i][t])%10;
	}
	return 0;
}
