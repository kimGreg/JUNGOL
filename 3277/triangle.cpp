#include <cstdio>
using namespace std;

int main(){
	for(int t=0; t<5; t++){
		long long n;
		scanf("%lld", &n);
        if(n%2) n += 3;
		long long ans = 0;
        ans = ((n/6)*(n+4) - 3*(n/6)*(n/6 + 1) - 2*((n/12) + ((n/6)%2 && (n%4 == 0)))) / 4;
		printf("%lld\n", ans);
	}
	return 0;
}
