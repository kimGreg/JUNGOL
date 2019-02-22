#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int MAX = 1000000;
int d[MAX+10];

int main(){
    for(int i=1; i<=MAX; i++) d[i] = 4;
    for(int i=1; i*i<=MAX; i++){
        d[i*i] = 1;
        for(int j=i; j*j + i*i <= MAX; i++) d[i*i+j*j] = min(d[i*i+j*j], 2);
    }
    for(int i=1; i<=MAX; i++){
        if(d[i]==1 || d[i]==2) continue;
        for(int j=1; j*j<=i; j++){
            d[i] = min(d[i], d[i-j*j]+1);
            if(d[i] == 3) break;
        }
    }
    int t, n;
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        printf("%d\n", d[n]);
    }
    return 0;
}
