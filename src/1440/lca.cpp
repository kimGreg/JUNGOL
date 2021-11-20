#include <cstdio>
#include <vector>
using namespace std;

vector<int> adj[10100];
int par[10100];
int dp[10100][20];
int level[10100];

void fill_table(int node, int depth){
    dp[node][0] = par[node];
    
    level[node] = depth;
    for(int k=1; dp[node][k-1]; k++)
        dp[node][k] = dp[dp[node][k-1]][k-1];
    
    for(auto it : adj[node])
        fill_table(it, depth+1);
}

int lca(int a, int b){
    if(level[a] < level[b]){
        int temp = a;
        a = b;
        b = temp;
    }
    int diff = level[a] - level[b];
    
    for(int i=0; diff; i++){
        if(diff&1) a = dp[a][i];
        diff >>= 1;
    }

    //printf("%d %d \n %d %d\n\n", a, b, level[a], level[b]);
    
    while(a != b){
        if(par[a] == par[b]){
            a = par[a];
            b = par[b];
            break;
        }

        int t;
        for(t = 0; dp[a][t] != dp[b][t]; t++);
        a = dp[a][t-1];
        b = dp[b][t-1];
    }
    return a;
}

int main(){
    int n;
    scanf("%d", &n);

    for(int i=0; i<n-1; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a].push_back(b);
        par[b] = a;
    }
    
    int root = 0;
    for(int i=1; i<=n; i++){
        if(par[i] == 0){
            root = i;
            break;
        }
    }

    fill_table(root, 0);
    int x, y;
    scanf("%d %d", &x, &y);
    printf("%d", lca(x, y));


    return 0;    
}
