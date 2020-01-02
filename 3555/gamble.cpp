#include <cstdio>
#include <algorithm>
using namespace std;

inline double cost(int a, int b, int c){
	if(a == b && b == c){
		return 10000+a*1000;
	}else if(a == b || a == c){
		return 1000+a*100;
	}else if(b == c){
		return 1000+b*100;
	}else{
		return max({a, b, c})*100;
	}
}

double d[1010][7][7][7];

int main(){
	int n;
	scanf("%d", &n);

	for(int k=n; k>=3; k--){
		for(int a = 1; a<=6; a++){
			for(int b=1; b<=6; b++){
				for(int c=1; c<=6; c++){
					d[k][a][b][c] = cost(a, b, c);
					if(k != n){
						double temp = 0;
						for(int i=1; i<=6; i++)
							temp += d[k+1][i][a][b];
						d[k][a][b][c] = max(d[k][a][b][c], temp/6);
					}
				}
			}
		}
	}
	
	double ans = 0;
	for(int a=1; a<=6; a++){
		for(int b=1; b<=6; b++){
			for(int c=1; c<=6; c++){
				ans += d[3][a][b][c];
			}
		}
	}
	printf("%.12f", ans/(6*6*6));
	return 0;
}
