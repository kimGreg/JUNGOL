#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

using pii = pair<int, int>;

vector<pii> adj[200100];
int edgeTree[400100], edgeData[400100], nodeNum[200100];
int par[200100];
int edge_cnt, node_cnt;

void EulerTour(int now){
    nodeNum[now] = ++node_cnt;
    
    int parIdx = 0;
    for(int i=0; i<adj[now].size(); i++){
        if(adj[now][i].first == par[now]){
            parIdx = i;
            continue;
        }
        adj[now][i].second = ++edge_cnt;
        EulerTour(adj[now][i].first);
    }
    adj[now][parIdx].second = ++edge_cnt;
}

void update(int x){
    if(edgeData[x]) return;
    edgeData[x] = 1;
    while(x <= edge_cnt){
        edgeTree[x]++;
        x += x&-x;
    }
}

int get_sum(int x){
    int sum = 0;
    while(x){
        sum += edgeTree[x];
        x -= x&-x;
    }
    return sum;
}

int get_sum(int x, int y){
    return get_sum(y) - get_sum(x-1);
}

int get_edge(int node, int mode){// 0: in, 1: out
    int node1 = node, node2 = par[node];
    if(!mode){
        node1 = par[node];
        node2 = node;
    }
    
    pii find = {node2, -1};
    int idx = upper_bound(adj[node1].begin(), adj[node1].end(), find) - adj[node1].begin();
    int ret = adj[node1][idx].second;
    
    printf("!!! get_edge(%d %d), %d %d\n", node, mode, idx, ret);
    return ret;
}

int is_connected(int a, int b){
    if(nodeNum[a] > nodeNum[b]){
        int temp = a;
        a = b;
        b = temp;
    }
    
    int e1 = get_edge(a, 1), e2 = get_edge(b, 0);
    return get_sum(a, b) == 0;
    
}

void cut_edge(int node){
    if(node == 1) return;
    int e1 = get_edge(node, 0), e2 = get_edge(node, 1);
    printf("!!! %d %d\n", e1, e2);
    update(e1);
    update(e2);
}

int main(){
    int n, q;
    scanf("%d %d", &n, &q);
    for(int i=2; i<=n; i++){
        scanf("%d", par+i);
        adj[i].push_back({par[i],0});
        adj[par[i]].push_back({0, par[i]});
    }
    for(int i=1; i<=n; i++) sort(adj[i].begin(), adj[i].end());
    EulerTour(1);
    
    while(q--){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
                
        int exist = is_connected(a, b);
        
        printf("%s\n", exist?"YES":"NO");
        
        if(c){
            if(exist){
                cut_edge(a);
            }else{
                cut_edge(b);
            }
        }
        printf("!!!\n");
    }
    
    return 0;
}