#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using pii = pair<int, int>;

int group[100100];
vector<pii> logs;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n, q;
    cin >> n >> q;

    for(int i=1; i<=n; i++){
        int a, b, c;
        cin >> a >> b >> c;
        logs.push_back({a,-i});
        logs.push_back({b, i});
    }
    
    sort(logs.begin(), logs.end());
    
    int gn = 1, h = 0;

    for(auto it : logs){
        if(it.second < 0) group[-it.second] = gn, h++;
        else h--;
        if(h == 0) gn++;
    }

    for(int i=0; i<q; i++){
        int a, b;
        cin >> a >> b;
        cout << (int)(group[a] == group[b]) << "\n";
    }

    return 0;
}