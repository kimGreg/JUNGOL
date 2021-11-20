#include <cstdio>
#include <algorithm>
using namespace std;
int d[33][33][33], l[33][33][33], r[33][33][33];
int arr[33], n, g;

int print(int s, int e, int val, int sift){
	if(s == e) return 0;
	int sum = 0;
	sum += print(s, d[s][e][val], l[s][e][val], sift);
	sift += sum;
	sum += print(d[s][e][val]+1, e, r[s][e][val], sift);
	printf("%d\n", d[s][e][val] - sift);
	return sum+1;
}

int main(){
	scanf("%d %d", &n, &g);
	for(int i=1; i<=n; i++) scanf("%d", arr+i), d[i][i][arr[i]] = i;
	for(int i=1; i<n; i++){
		for(int j=1; j+i<=n; j++){
			int s = j, e = j+i;
			for(int k=s; k<e; k++){
				for(int a=0; a<=30; a++) for(int b=0; b<=30; b++){
					if(d[s][e][abs(a-b)] != 0 || d[s][k][a] == 0 || d[k+1][e][b] == 0) continue;
					d[s][e][abs(a-b)] = k;
					l[s][e][abs(a-b)] = a;
					r[s][e][abs(a-b)] = b;
				}
			}
		}
	}
	if(d[1][n][g] != 0) print(1, n, g, 0);
	else printf("0");
	return 0;
}
