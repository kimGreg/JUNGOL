#include <cstdio>
#include <map>
#include <vector>
using namespace std;
const int MOD = 1000000007;

int prime[44], isP[220];
int inverse[2000], n;
map<long long, int> mp;
long long maxK = 0;

int dfs(long long K){
	if(mp.find(K) != mp.end())
		return mp[K];
    
	vector<int> vec(n);
	vec[0] = n;
	for(int i=1; i<n; i++){
		while(K%prime[i] == 0){
			K /= prime[i];
			vec[i]++;
			vec[0] -= i+1;
		}
	}
    
	int ans = 0;
	for(int i=0; i<n; i++){
		for(int j=i; j<n; j++){
			vector<int> temp = vec;
			temp[i]--; temp[j]--;
			if(temp[i] < 0 || temp[j] < 0) continue;
			temp[i+j+1]++;
			
			long long next = 1;
			for(int i=1; i<n; i++)
				for(int j=0; j<temp[i]; j++)
					next *= prime[i];
                    
			int T = dfs(next) + 1;
			int val = (inverse[n*n]*vec[i]*(i+1))%MOD;
			if(i == j){
				val = (val*(vec[j]-1)*(j+1))%MOD;
				val = (val*inverse[2])%MOD;
			}else val = (val*vec[j]*(j+1)*inverse[2])%MOD;
			val = (val+T)%MOD;
			ans = (ans+val)%MOD;
		}
	}
	return mp[K] = ans;
}

int pow(int n, int k){
	if(k == 0) return 1;
	int temp = pow(n, k/2);
	int a = (temp*temp)%MOD;
	if(k % 2) a =(a*n)%MOD;
	return a;
}

int main(){
	scanf("%d", &n);
	int Pcnt = 1;
	prime[0] = 1;
	for(int i=2; i<=200; i++){
		if(isP[i]) continue;
		prime[Pcnt++] = i;
		for(int j=i*i; j<=200; j += i)
			isP[j] = 1;
	}

	for(int i=1; i<=n*n; i++)
		inverse[i] = pow(i, MOD-2);
	
	printf("%d", dfs(1));
	
	return 0;
}
