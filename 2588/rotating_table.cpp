#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> arr[3];
int sz[3], d[100][100][100][3], n;

int func(int a, int b){
	return min((n+a-b)%n, (n-a+b)%n);
}

int main(){
	scanf("%d", &n);
	for(int i=0; i<3; i++){
		scanf("%d", sz+i);
		arr[i].resize(sz[i]+1);
		for(int j=1; j<=sz[i]; j++){
			scanf("%d", &arr[i][j]);
			arr[i][j] = (2*n+arr[i][j]-1-(n/3)*i)%n;
		}
	}
	for(int i=0; i<=sz[0]; i++){
		for(int j=0; j<=sz[1]; j++){
			for(int k=0; k<=sz[2]; k++){
				for(int t=0; t<3; t++){
					int A[3] = {i, j, k}, f;
					A[t]--;
					if(A[0]<0||A[1]<0||A[2]<0){
						if(i != 0 || j != 0 || k != 0) d[i][j][k][t] = 2e9;
						continue;
					}
					d[i][j][k][t] = 2e9;
					for(int p=0; p<3; p++){
						int temp;
						if(t == 0) temp = func(arr[0][i], arr[p][A[p]]);
						else if(t == 1) temp = func(arr[1][j], arr[p][A[p]]);	
						else temp = func(arr[2][k], arr[p][A[p]]);
						d[i][j][k][t] = min(d[i][j][k][t], d[A[0]][A[1]][A[2]][p] + temp);
					}
				}
			}
		}
	}
	int ans = 2e9;
	for(int i=0; i<3; i++) ans = min(ans, d[sz[0]][sz[1]][sz[2]][i]);
	printf("%d", ans);
	return 0;
}
