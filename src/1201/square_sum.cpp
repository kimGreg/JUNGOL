#include <cstdio>
using namespace std;
const int MAX = 1000000;
int d[MAX+10], sq[1100];
 
int main(){
    for(int i=1; i<=MAX; i++) d[i] = 4;
    for(int i=1; i<=1010; i++) sq[i] = i*i;
    for(int i=1; sq[i] <= MAX; i++){
        d[sq[i]] = 1;
        for(int j=i; sq[j] + sq[i] <= MAX; j++) 
            d[sq[i]+sq[j]] = 2;
    }
    for(int i=1; i<=MAX; i++){
        if(d[i] != 4) continue;
        for(int j=1; sq[j]<=i; j++){
            if(d[i-sq[j]] == 2){
                d[i] = 3;
                break;
            }
        }
    }
    int n;
    scanf("%d", &n);
    printf("%d\n", d[n]);
    return 0;
}