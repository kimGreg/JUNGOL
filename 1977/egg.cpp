#include <cstdio>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;
using ll = long long;

ll MAXE = 755ll;
ll total, k;

const int pAct[12][3] = {
{0,1,2}, {0,1,3}, {0,2,1}, {0,2,3}, {0,3,1}, {0,3,2},
{1,2,0}, {1,2,3}, {1,3,0}, {1,3,2}, {2,3,0}, {2,3,1}};

queue<ll> que;
map<ll, ll> history;

inline ll hashing(ll * arr){
    ll a=arr[0], b=arr[1], c=arr[2], d=arr[3];
    if(a >= MAXE) swap(a, d);
    if(b >= MAXE) swap(b, d);
    if(c >= MAXE) swap(c, d);
    return a+(b*MAXE)+(c*MAXE*MAXE);
}

void dehashing(ll key, ll * arr){
    arr[0] = key%MAXE;
    key /= MAXE;
    arr[1] = key%MAXE;
    key /= MAXE;
    arr[2] = key%MAXE;
    arr[3] = total - arr[0] - arr[1] - arr[2];
}

void inque(ll key, ll before = -1){
    if(!history.count(key)){
        que.push(key);
        history[key] = before;
    }
}


void print(ll * arr){
    for(int i=0; i<4; i++) printf("%lld ", arr[i]);
    printf("\n");
}

inline int check(ll * arr){
    return !((arr[0]-total)*(arr[1]-total)*(arr[2]-total)*(arr[3]-total));
}

ll prt_arr[4];

void print_ans(ll key){
    if(history[key] == -1){
        print(prt_arr);
        return;
    }
    
    print_ans(history[key]);
    
    for(int i=0; i<12; i++){
        int x = pAct[i][0], y = pAct[i][1], z = pAct[i][2];
        if(prt_arr[x]>=1 && prt_arr[y]>=1){
            prt_arr[x] -= 1, prt_arr[y] -= 1, prt_arr[z] += 2;
            if(hashing(prt_arr) == key){
                print(prt_arr);
                return;
            }
            prt_arr[x] += 1, prt_arr[y] += 1, prt_arr[z] -= 2;
        }
    }
}

int main(){
    scanf("%lld", &k);
    for(int i=0; i<4; i++){
        scanf("%lld", prt_arr+i);
        total += prt_arr[i];
    }

    inque(hashing(prt_arr));
    
    ll ans = -1;

    while(!que.empty()){
        ll now = que.front();
        que.pop();
        
        ll arr[4];
        dehashing(now, arr);
        
        if(check(arr)){
            ans = now;
            break;
        }
        
        for(int i=0; i<12; i++){
            int x = pAct[i][0], y = pAct[i][1], z = pAct[i][2];
            if(arr[x]>=1 && arr[y]>=1){
                arr[x] -= 1, arr[y] -= 1, arr[z] += 2;
                inque(hashing(arr), now);
                arr[x] += 1, arr[y] += 1, arr[z] -= 2;
            }
        }
    }
    
    print_ans(ans);
    return 0;
}
