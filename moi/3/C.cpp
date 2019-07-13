#include <cstdio>
#include <cmath>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

class Point{
public:
    int x, y;
    Point(){}
    Point(int _x, int _y){
        x = _x; y = _y;
    }
};

long long SZ(Point A, Point B, Point C){
    return abs((long long)A.x*B.y + (long long)B.x*C.y + (long long)C.x*A.y - (long long)B.x*A.y - (long long)C.x*B.y - (long long)A.x*C.y);
}

int ccw(Point A, Point B, Point C){
    int t = A.x*B.y - A.y*B.x + B.x*C.y - B.y*C.x + C.x*A.y - C.y*A.x;
    if(t > 0) return 1;
    else if(t == 0) return 0;
    return -1;
}

int ccw(int ax, int ay, int bx, int by, int cx, int cy){
    long long k = (long long)(bx-ax)*(cy-ay) - (long long)(cx-ax)*(by-ay);
    if(k > 0) return 1;
    else if(k == 0) return 0;
    else return -1;
}

int n;
vector<Point> arr;
vector<Point> ch;
stack<int> stk;

void convex_hull(){
    stk.push(0); stk.push(1);
    for(int i=2; i<n;i++){
        while(stk.size() >= 2){
            int b = stk.top(); stk.pop();
            int a = stk.top();
            if(ccw(arr[a], arr[b], arr[i]) == 1){
                stk.push(b);
                break;
            }
        }
        stk.push(i);
    }
    while(!stk.empty()){
        ch.push_back(arr[stk.top()]);
        stk.pop();
    }
    reverse(ch.begin(), ch.end());
}

long long dist(Point A, Point B){
    return pow(A.x-B.x, 2) + pow(A.y-B.y, 2);
}

int main(){
    scanf("%d", &n);
    arr.resize(n);
    for(int i=0; i<n; i++){
        scanf("%d %d", &arr[i].x, &arr[i].y);
        if((arr[0].y > arr[i].y)||(arr[0].y == arr[i].y && arr[0].x < arr[i].x))
            swap(arr[0], arr[i]);
    }
    
    sort(arr.begin() + 1, arr.end(), [&](Point & A, Point & C)->bool{
        Point B = arr[0];
        int t = A.x*B.y - A.y*B.x + B.x*C.y - B.y*C.x + C.x*A.y - C.y*A.x;
        if(t == 0)
            return pow(A.x-B.x, 2) + pow(A.y-B.y, 2) < pow(C.x-B.x, 2) + pow(C.y-B.y, 2);
        return t < 0;
    });
    convex_hull();
    
    int j=1;
    long long ans = 0;
    for(int i=0; i<ch.size(); i++){
        int ni = (i+1) % ch.size();
        while(1){
            int nj = (j+1) % ch.size();
            int v = ccw({0, 0}, {ch[ni].x-ch[i].x, ch[ni].y-ch[i].y}, {ch[nj].x-ch[j].x, ch[nj].y-ch[j].y});
            if(v > 0) j = nj;
            else break;
        }
        if(i == j) continue;
        long long ans1 = 0, ans2 = 0;
        int k = (i+1)%ch.size();
        while(k != j){
            ans1 = max(ans1, SZ(ch[i], ch[j], ch[k]));
            k = (k+1)%ch.size();
        }
        k = (j+1)%ch.size();
        while(k != i){
            ans2 = max(ans2, SZ(ch[i], ch[j], ch[k]));
            k = (k+1)%ch.size();
        }
        ans = max(ans, ans1+ans2);
    }
    printf("%lld", ans/2);
    if(ans%2) printf(".5");
    else printf(".0");
    return 0;
}
