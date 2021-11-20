#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

ll phi(ll n){
	//get Prime factor
	ll res = n;

	if(!(n%2)){
		res -= res/2;
		while (n % 2 == 0)
	        n = n/2;
	}
    for (ll i = 3; i*i <= n; i = i + 2){  
        if(!(n%i)){
        	res -= res/i;
        	while (n % i == 0)  
            	n = n/i;
        }
         
    }   
    if (n > 2)  
        res -= res/n;

	return res;
}

int main(){
	while(1){
		ll n;
		scanf("%lld", &n);
		if(n == 0) break;	
		printf("%lld\n", phi(n));
	}
	return 0;
}
