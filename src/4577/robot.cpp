#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int arr[500100];
long long minPos[500100];
long long maxPos[500100];
vector<int> pos;

int main(){
    int n;
    scanf("%d", &n);
    pos.reserve(n);
    for(int i=0; i<n; i++){
        scanf("%d", arr+i);
        pos.push_back(arr[i]);
    }
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
    
    for(int i=0; i<n; i++){
        arr[i] = (lower_bound(pos.begin(), pos.end(), arr[i]) - pos.begin());
        if(minPos[arr[i]] == 0) minPos[arr[i]] = i+1;
        maxPos[arr[i]] = i+1;
    }
    int num_cnt = pos.size();
    long long a = maxPos[0] - 1, b = 2*maxPos[0] - minPos[0] -1;
    for(int i=1; i < num_cnt; i++){
        long long temp_a = min(a+abs(minPos[i]-maxPos[i-1]), b+abs(minPos[i]-minPos[i-1])) + maxPos[i] - minPos[i]; // maxPos[i] 에서 끝;
        long long temp_b = min(a+abs(maxPos[i]-maxPos[i-1]), b+abs(maxPos[i]-minPos[i-1])) + maxPos[i] - minPos[i]; // minPos[i] 에서 끝;
        a = temp_a;
        b = temp_b;
    }
    printf("%lld", min(a, b));
    return 0;
}