#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
class robot{
public:
	int s, e;
	robot(int _s=0, int _e=0):s(_s),e(_e){}
};
const ll mod = 20070713;
vector<robot> arr;
vector<int> arrP, temp;
int n;
ll d[100100][2];

int main(){
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		arr.push_back({a, b});
		arrP.push_back(a), arrP.push_back(b);
	}
	sort(arrP.begin(), arrP.end());
	for(int i=0; i<n; i++) arr[i] = {(int)(lower_bound(arrP.begin(), arrP.end(), arr[i].s)-arrP.begin())+1, (int)(lower_bound(arrP.begin(), arrP.end(), arr[i].e)-arrP.begin())+1};
	sort(arr.begin(), arr.end(), [](robot & A, robot & B)->bool{return A.e!= B.e?A.e<B.e:A.s<B.s;});
	d[0][0] = d[0][1] = 1;
	temp.push_back(arr[0].e);
	for(int i=1; i<n; i++){
		d[i][1] = (d[i-1][0] + d[i-1][1])%mod;
		int k = lower_bound(temp.begin(), temp.end(), arr[i].s)-temp.begin(); 
		d[i][0] = d[k][1];
		temp.push_back(arr[i].e);
	}
	printf("%lld", (d[n-1][0] + d[n-1][1])%mod);
	return 0;
}
