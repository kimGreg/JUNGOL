#include <cstdio>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;
using ll = long long;

ll MAXE = 3001ll;
ll total, k;

const int possible_act[12][3] = {
{0,1,2}, {0,1,3}, {0,2,1}, {0,2,3}, {0,3,1}, {0,3,2},
{1,2,0}, {1,2,3}, {1,3,0}, {1,3,2}, {2,3,0}, {2,3,1}};

queue<pair<ll, ll>> que;
unordered_map<ll, ll> history;

ll hashing(ll a, ll b, ll c){
    return a+(b*MAXE)+(c*MAXE*MAXE);
}

void dehashing(ll key, ll & a, ll & b, ll & c, ll & d){
    a = key%MAXE;
    key /= MAXE;
    b = key%MAXE;
    key /= MAXE;
    c = key%MAXE;
    d = total - a - b - c;
}


void inque(ll key, ll depth = 1, ll before = -1){
    if(!history.count(key)){
        que.push({key,depth});
        history[key] = before;
    }
}

void print_ans(ll key){
    if(key == -1) return;
    print_ans(history[key]);
    ll a, b, c, d;
    dehashing(key, a, b, c, d);
    printf("%lld %lld %lld %lld\n", a, b, c, d);
}

int main(){
    ll a, b, c, d;
    scanf("%lld %lld %lld %lld %lld", &k, &a, &b, &c, &d);
    total = a+b+c+d;
    MAXE = total+1;

    inque(hashing(a, b, c));
    
    ll ans = -1;

    while(!que.empty()){
        ll now = que.front().first, depth = que.front().second;
        que.pop();
        
        ll arr[4];
        dehashing(now, arr[0], arr[1], arr[2], arr[3]);
        //printf("!! %lld %lld %lld %lld\n", arr[0], arr[1], arr[2], arr[3]); 
        if(!((arr[0]-total)*(arr[1]-total)*(arr[2]-total)*(arr[3]-total))){
            ans = now;
            break;
        }

        if(depth >= k)
            continue;
        
        for(int i=0; i<12; i++){
            int x = possible_act[i][0];
            int y = possible_act[i][1];
            int z = possible_act[i][2];
            
            if(arr[x]>=1 && arr[y]>=1){
                arr[x] -= 1, arr[y] -= 1, arr[z] += 2;
                inque(hashing(arr[0], arr[1], arr[2]), depth+1, now);
                arr[x] += 1, arr[y] += 1, arr[z] -= 2;
            }
        }
    }
    
    print_ans(ans);
    return 0;
}
