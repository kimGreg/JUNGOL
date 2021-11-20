#include <cstdio>
int main(){
    long long n;
    scanf("%lld", &n);

    if(n%2) n += 3;
    printf("%lld\n", ((n/6)*(n+4) - 3*(n/6)*(n/6 + 1) - 2*((n/12) + ((n/6)%2 && (n%4 == 0)))) / 4);
	return 0;
}
