#include <cstdio>

unsigned long long d[1600];

int main(){
    d[0] = 0;
    unsigned long long a = 1, b = 1, c = 0;
    for(int i=1; i<=1500; i++, c++){
        if(c == b) a*=2, b++, c=0;
        d[i] = d[i-1]+a;
    }
    int t;
    scanf("%d", &t);
    while(t--){
        int temp;
        scanf("%d", &temp);
        printf("%llu\n", d[temp]);
    }
    return 0;
}
