#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int t1[62505][250], t2[62505][250];
int a[250], b[250];

int main(){
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++)
		scanf("%d %d", a+i, b+i);

	memset(t1, -1, sizeof(t1));
	memset(t2, -1, sizeof(t2));

	t1[a[0]][0] = 0;
	t2[b[0]][0] = 0;
	int t = 0;
	bool flag = 1;
	while(flag){
		t++;
		for(int i=0; i<n; i++){
			if(t1[t][i] != -1){
				if(i == n-1){
					flag = 0;
					break;
				}
				t1[t+a[i+1]][i+1] = t1[t][i];
				if(t1[t][i] + b[i+1] > t){
					t2[t1[t][i] + b[i+1]][i+1] = t;
				}else{
					t1[t][i+1] = t1[t][i] + b[i+1];
				}
			}
			if(t2[t][i] != -1){
				if(i == n-1){
					flag = 0;
					break;
				}
				t2[t+b[i+1]][i+1] = t2[t][i];
				if(t2[t][i] + a[i+1] > t){
					t1[t2[t][i] + a[i+1]][i+1] = t;
				}else{
					t2[t][i+1] = t2[t][i] + a[i+1]; 
				}
			}
		}
	}
	printf("%d", t);
	return 0;
}
