#include <cstdio>
#include <algorithm>
using namespace std;

int tree[10100], able[10100], cnt[10100][2];

int update(int now, int a, int b, int temp, int bias){
	if(cnt[now*2][a] == -1) return temp;
	if(cnt[now*2+1][b] == -1) return temp;
	int newAns = cnt[now*2][a] + cnt[now*2+1][b] + bias;
	if(temp == -1) return newAns;
	else return min(temp, newAns);
}

int main(){
	int m, v;
	scanf("%d %d", &m, &v);
	for(int i=1; i<=m; i++){
		scanf("%d", tree+i);
		if(i <= (m-1)/2) scanf("%d", able+i);
		else{
			cnt[i][tree[i]] = 0;
			cnt[i][1-tree[i]] = -1;
		}
	}
	for(int i=(m-1)/2; i>0; i--){
		// case of 0
		// 0, 0 -> and, or
		// 0, 1 | 1, 0 -> and 
		int temp = -1;
		if(tree[i] == 1){// and
			temp = update(i, 0, 0, temp, 0);
			temp = update(i, 0, 1, temp, 0);
			temp = update(i, 1, 0, temp, 0);
		}else{
			if(able[i]){
				temp = update(i, 0, 0, temp, 1);
				temp = update(i, 0, 1, temp, 1);
				temp = update(i, 1, 0, temp, 1);
			}
			temp = update(i, 0, 0, temp, 0); 
		}
		cnt[i][0] = temp;

		// case of 1
		// 0, 1 | 1, 0 -> or
		// 1, 1 -> and, or
		temp = -1;
		if(tree[i] == 0){
			temp = update(i, 0, 1, temp, 0);
			temp = update(i, 1, 0, temp, 0);
			temp = update(i, 1, 1, temp, 0);
		}else{
			if(able[i]){
				temp = update(i, 0, 1, temp, 1);
				temp = update(i, 1, 0, temp, 1);
				temp = update(i, 1, 1, temp, 1);
			}
			temp = update(i, 1, 1, temp, 0);
		}
		cnt[i][1] = temp;
	}
	if(cnt[1][v] == -1) printf("IMPOSSIBLE");
	else printf("%d", cnt[1][v]);
	return 0;
}
