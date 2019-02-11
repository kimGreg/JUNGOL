#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
vector<int> arr1, arr2;
int d[404][404][2];
int main(){
	int n, temp, cnt1 = 0, cnt2 = 0;
	scanf("%d", &n);
	arr1.push_back(0); arr2.push_back(0);
	for(int i=0; i<n; i++){
		scanf("%d", &temp);
		if(temp != 0) arr1.push_back(temp);
		else cnt1++;
	}
	for(int i=0; i<n; i++){
		scanf("%d", &temp);
		if(temp != 0) arr2.push_back(temp);
		else cnt2++;
	}
    int prev = 0, now = 1;
    for(int i=0; i<=n-cnt1; i++) for(int j=0; j<=n-cnt2; j++) d[i][j][0] = d[i][j][1] = -2e9;
    for(int k = 1; k <= n; k++){
        for(int i = 0; i <= n; i++){
            d[i][0][prev] = (i>cnt2 || i>k-1)?-2e9:0;
            d[0][i][prev] = (i>cnt1 || i>k-1)?-2e9:0;
        }
        for(int i=1; i<=n-cnt1 && i <= k; i++){
            for(int j=1; j<=n-cnt2 && j <= k; j++){
				d[i][j][now] = max({d[i-1][j-1][prev] + arr1[i]*arr2[j], d[i-1][j][prev], d[i][j-1][prev], d[i][j][prev]});
			}
		}
        prev = 1-prev; now = 1-now;
	}
	printf("%d", d[n-cnt1][n-cnt2][prev]);
	return 0;
}
