#include <iostream>
 
using namespace std;
 
int main(){
    int n, p;
    cin >> n >> p;
    auto f = [=](int & a){a = (a*n)%p;};
    int a = n, b = n, ans = 0;
    do{f(a); f(b); f(b);}while(a != b);
    do{f(a); f(b); f(b); ans++;}while(a != b);
    cout << ans;
    return 0;
}