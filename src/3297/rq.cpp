#include <cstdio>
using namespace std;
using ll = long long;

int n;
ll data[1000100];
ll tree[1000100];

void update_tree(int i, int val){
    ll delta = val - data[i];
    data[i] = val;
    while(i <= n){
        tree[i] += delta;
        i += i&-i;
    }
}

ll sum(int x){
    ll sum = 0;
    while(x){
        sum += tree[x];
        x -= x&-x;
    }
    return sum;
}

ll sum(int x, int y){
    return sum(y) - sum(x-1);
}

int main(){
    scanf("%d", &n);
    for(int i=1; i<=n; i++){
        ll temp;
        scanf("%lld", &temp);
        update_tree(i, temp);
    }
    int q;
    scanf("%d", &q);
    
    while(q--){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        if(a == 1) update_tree(b, c);
        else printf("%lld\n", sum(b, c));
    }
    
    return 0;
}