#include <cstdio>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

class Person{
public:
    int w, count, id;

    bool operator<(const Person & P)const{
        if(w != P.w) return w > P.w;
        return count < P.count;
    }

    Person(){}
    Person(int W, int C, int I){
        w = W;
        count = C;
        id = I;
    }
};

priority_queue<Person> pq;
stack<Person> stk;

long long ans = 0, cnt = 0;


int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    
    int now_time = 0;

    for(int i=k; i>0; i--){
        stk.push({0, i, 0});
    }

    while(!pq.empty() || n){
        while(n && !stk.empty()){
            Person temp = stk.top();
            stk.pop();
            
            int id, w;
            scanf("%d %d", &id, &w);
            pq.push({temp.w + w, temp.count, id});
            n--;
        }

        now_time = pq.top().w;
        
        while(!pq.empty() && now_time == pq.top().w){
            stk.push(pq.top());
            ans += pq.top().id * (++cnt);
            pq.pop();
        }
    }

    printf("%lld", ans);
    return 0;
}
