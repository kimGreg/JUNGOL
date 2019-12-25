#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

int capa[300][300], flow[300][300], path[300];

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		int n;
		scanf("%d", &n);
        for(int i=0; i<=n+n+1; i++){
            for(int j=0; j<=n+n+1; j++){
                capa[i][j] = 0;
                flow[i][j] = 0;
            }
        }
		for(int i=1; i<=n; i++){
			capa[0][i] = 1;
			capa[i+n][n+n+1] = 1;
			for(int j=1; j<=n; j++){
				char ch;
				scanf(" %c", &ch);
				if(ch == 'W') capa[i][j+n] = 1;
				else capa[i][j+n] = 0;
			}
		}
		
		int ans = 0;
		while(1){
			fill(path, path+n+n+2, 0);
			queue<int> que;
			que.push(0);
			while(!que.empty()){
				int now = que.front();
				que.pop();
				for(int i=0; i<=n+n+1; i++){
					if(capa[now][i] - flow[now][i] > 0 && path[i] == 0){
						path[i] = now;
						que.push(i);
					}
				}
			}
			if(!path[n+n+1]) break;
            for(int i=n+n+1; i != 0; i = path[i]){
                flow[path[i]][i] += 1;
                flow[i][path[i]] -= 1;
            }
            ans += 1;
		}
        if(ans == n) printf("YES\n");
        else printf("NO\n");
	}
	return 0;
}
