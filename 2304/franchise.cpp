#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int,int> pii;
class data{
public:
    int arr[3], node;
    bool operator<(const data & D)const{
        return arr[0] < D.arr[0];
    }
};
vector<pii> adj[100100];
vector<int> Bx;
priority_queue<pii, vector<pii>, greater<pii>> que;
queue<pii> que2;
int n, m, A, B, C;
data dist[100100];
int tree[100100];
bool isN[100100];

void dij(int S, int ind){
    for(int i=0; i<n; i++) dist[i].arr[ind] = 2e9;
    dist[S].arr[ind] = 0;
    que.push({0, S});
    while(!que.empty()){
        int now = que.top().second, cost = que.top().first;
        que.pop();
        for(auto i : adj[now]){
            if(dist[i.second].arr[ind] > cost + i.first){
                dist[i.second].arr[ind] = cost + i.first;
                que.push({dist[i.second].arr[ind], i.second});
            }
        }
    }
}

void comp(){
    for(int i=0; i<n; i++)
        Bx.push_back(dist[i].arr[1]);
    sort(Bx.begin(),Bx.end());
    Bx.erase(unique(Bx.begin(), Bx.end()), Bx.end());
    for(int i=0; i<n; i++)
        dist[i].arr[1] = lower_bound(Bx.begin(), Bx.end(), dist[i].arr[1]) - Bx.begin()+1;
}

void update(int now, int diff){
    while(now <= n){
        tree[now] = min(tree[now], diff);
        now += (now & -now);
    }
}

int getMn(int now){
    int Mn = 2e9;
    while(now > 0){
        Mn = min(Mn, tree[now]);
        now -= (now & -now);
    }
    return Mn;
}

void prepro(){
    for(int i=0; i<n; i++) dist[i].node = i;
    dij(A-1, 0);
    dij(B-1, 1);
    dij(C-1, 2);
    comp();
    sort(dist, dist+n);
    for(int i=0; i<=n; i++) tree[i] = 2e9;
    que2.push({dist[0].arr[1], dist[0].arr[2]});
    for(int i=1; i<n; i++){
        while(dist[i].arr[0] != dist[i-1].arr[0] && !que2.empty()){
            update(que2.front().first, que2.front().second); que2.pop();
        }
        int Mn = getMn(dist[i].arr[1]-1);
        if(Mn < dist[i].arr[2]) isN[dist[i].node] = 1;
        que2.push({dist[i].arr[1], dist[i].arr[2]});
    }
}

void query(){
    int q;
    scanf("%d", &q);
    while(q--){
        int temp;
        scanf("%d", &temp);
        temp--;
        printf("%s\n", isN[temp]?"NO":"YES");
    }
}

int main(){
    scanf("%d %d %d %d %d", &n, &A, &B, &C, &m);
    for(int i=0; i<m; i++){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        a--; b--;
        adj[a].push_back({c, b});
        adj[b].push_back({c, a});
    }
    prepro();
    query();
    return 0;
}
