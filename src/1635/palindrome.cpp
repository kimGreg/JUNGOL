#include <cstdio>
#include <cstring>
int d[40][40][60], len[60], n, l;
char str[60][40], temp[40];

bool check(int a, int b, int k, int t){
	for(int i=0; i<l; i++) temp[i] = 0;
	if(a > b){
		for(int i=0; i<len[k]; i++) temp[a-len[k]+i] = str[k][i];
		for(int i=0; i<len[t]; i++) temp[l-b-len[t]+i] = str[t][i];
	}else{
		for(int i=0; i<len[k]; i++) temp[l-b+i] = str[k][i];
		for(int i=0; i<len[t]; i++) temp[a+i] = str[t][i];
	}
	for(int i=0; i<l; i++) if(temp[i] != 0 && temp[l-i-1] != 0 && temp[i] != temp[l-i-1]) return false; 
	return true;
}

int main(){
	scanf("%d %d", &n, &l);
	for(int i=0; i<n; i++){
		scanf("%s", str[i]);
		len[i] = strlen(str[i]);
		if(check(0, 0, n, i)) d[len[i]][0][i]++;
	}
	for(int i=0; i<=l; i++){
		for(int j=0; j+i<=l; j++){
			for(int k=0; k<n; k++){
				if(d[i][j][k] == 0) continue;
				for(int t=0; t<n; t++){
					if(i + j + len[t] > l || !check(i, j, k, t)) continue;
					int I = i, J = j, T;
					if(i > j){
						if(i > j+len[t]) d[i][j+len[t]][k] += d[i][j][k];
						else d[i][j+len[t]][t] += d[i][j][k];
					}else{
						if(i+len[t] > j) d[i+len[t]][j][t] += d[i][j][k];
						else d[i+len[t]][j][k] += d[i][j][k];
					}
				}
			}
		}
	}
	int sum = 0;
	for(int i=0; i<=l; i++) for(int j=0; j<n; j++) sum += d[i][l-i][j];
	printf("%d", sum);
	return 0;
}
