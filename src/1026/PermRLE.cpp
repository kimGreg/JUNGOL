#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

char str[50050];
int d[66000][17][17];
int sameCnt[17][18];
vector<int> perm;

void update(int i, int j, int k, int val){
	if(d[i][j][k] == -1 || d[i][j][k] > val)
		d[i][j][k] = val;
}

int main(){
	int k, len;
	scanf("%d %s", &k, str);
	len = strlen(str);


	for(int i=0; i<k; i++){
		for(int j=0; j<k; j++){
			int cnt = 0;
			for(int ind = 0; ind<len; ind+=k){
				cnt += str[ind+i] == str[ind+j];
			}
			sameCnt[i][j] = cnt;
		}
	}

	memset(d, -1, sizeof(d));
	//초기치
	for(int i=0; i<k; i++)
		update(1<<i, i, i, len/k);
	// dp 채우기
	for(int i=1; i<(1<<k); i++){
		for(int j=0; j<k; j++){
			if(i & (1<<j)) continue;

			//d[i + (1<<j)][t][j] = d[i][t][?] + diff
			for(int t=0; t<k; t++){// t찾기
				if(!(i & (1<<t))) continue;
				
				for(int q=0; q<k; q++){
					if(d[i][t][q] == -1) continue;
					update(i+(1<<j), t, j, d[i][t][q] + len/k - sameCnt[q][j]);
				}
			}	
		}
	}
	//답 구하기
	int ans = len;
	for(int i=0; i<k; i++){
		for(int j=0; j<k; j++){
			if(i == j) continue;
			int sameCnt = 0;
			for(int ind = k; ind<len; ind+=k){
				sameCnt += str[ind-k+j] == str[ind+i];
			}
			ans = min(ans, d[(1<<k)-1][i][j]-sameCnt);  
		}
	}

	printf("%d", ans);
	return 0;
}
