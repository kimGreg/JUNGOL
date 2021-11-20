#include <cstdio>
#include <set>
using namespace std;
int arr[550], v[550];
set<int> st;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i=0; i<n; i++) scanf("%d", arr+i);
    for(int i=0; i<m; i++) st.insert(arr[i]);
    for(int i=0; i<n-m+1; i++){
        
        scanf("%d", v+i);
    }
    return 0;
}
