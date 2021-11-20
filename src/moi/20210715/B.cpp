#include <cstdio>
#include <algorithm>
using namespace std;
using ll = long long;
  
ll n, arr[100100], check[100100], s1[100100], s2[100100];
  
int check_seq(ll s, ll d){
    for(int i=0; i<100100; i++){
        check[i] = 0;
        s1[i] = 0;
        s2[i] = 0;
    }
     
    ll s1_size = 0, s2_size = 0;
     
    s1[s1_size++] = arr[s];
    check[s] = 1;
     
    for(int i=s+1; i<n; i++){
        if(arr[i] - s1[s1_size-1] == d){
            s1[s1_size++] = arr[i];
            check[i] = 1;
        }
    }
     
    for(int i=0; i<n; i++){
        if(!check[i])
            s2[s2_size++] = arr[i];
    }
    
    bool flag = 0;
    for(int i=1; i<s2_size; i++){
        if(s2[i] - s2[i-1] != s2[1] - s2[0]){
            flag = 1;
            break;
        }
    }
    
    if(flag|| s2_size == 0){
        s2[s2_size++] = s1[s1_size-1];
        s1_size--;
        sort(s2, s2+s2_size);
    }
    
    for(int i=1; i<s2_size; i++){
        if(s2[i] - s2[i-1] != s2[1] - s2[0]){
            return 0;
        }
    }
    
    printf("%lld\n", s1_size);
    for(int i=0; i<s1_size; i++) printf("%lld ", s1[i]);
    printf("\n");
     
    printf("%lld\n", s2_size);
    for(int i=0; i<s2_size; i++) printf("%lld ", s2[i]);
    printf("\n");
     
    return 1;
}
  
int main(){
    scanf("%lld", &n);
    for(int i=0; i<n; i++) scanf("%lld", arr+i);
    sort(arr, arr+n);
      
    int tmp = check_seq(0, arr[1]-arr[0]);
    if(!tmp) tmp = check_seq(0, arr[2]-arr[0]);
    if(!tmp) tmp = check_seq(1, arr[2]-arr[1]);
    if(!tmp) printf("-1");
     
    return 0;
}
