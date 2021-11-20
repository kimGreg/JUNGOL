#include <cstdio>
#include <cmath>
using namespace std;
using ll = long long;

int main(){
	ll n;
	bool i = 0;
	scanf("%lld", &n);
	while(n > 1){
		ll t;
		t = i ? 2 : 9;
		n = n/t + (n%t != 0);
		i = !i;
	}
	printf("%s wins.", i?"Stan":"Ollie");
	return 0;
}
