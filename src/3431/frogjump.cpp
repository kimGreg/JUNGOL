#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
class Log{
public:
    int s, e, idx;
    Log(){}
    Log(int S, int E, int I){
        s = S; e = E; idx = I;
    }
    bool operator<(const Log & l)const{
        if(s != l.s) return s < l.s;
        return e < l.e;
    }
    void input(int I){
        scanf("%d %d %*d", &s, &e);
        idx = I;
    }
};

Log logs[100100];
int group[100100];

int main(){
    int n, q;
    scanf("%d %d", &n, &q);

    for(int i=0; i<n; i++)
        logs[i].input(i+1);
    
    sort(logs, logs+n);
    
    int last = 0, gnum = 1;
    for(int i=0; i<n; i++){
        if(logs[i].s > last) gnum++;

        last = max(last, logs[i].e);
        group[logs[i].idx] = gnum;
    }

    for(int i=0; i<q; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d\n", group[a] == group[b]);
    }

    return 0;
}
