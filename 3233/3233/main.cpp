#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
int n;
class data{
public:
    int x, y;
    double degree;
    data(){}
    data(int X, int Y){x=X; y=Y;}
    void set_degree(int X, int Y){
        degree = atan2((double)y - Y, (double)x - X);
    }
    bool operator<(const data & b) const {
        return degree < b.degree;
    }
};
data arr[3333];

int d1[3333][3333], d2[3333][3333], path1[3333][3333], path2[3333][3333];

inline long long check(int a, int b, int c){
    return (long long)((long long)arr[b].x - (long long)arr[a].x)*((long long)arr[c].y - (long long)arr[a].y) - (long long)((long long)arr[b].y - arr[a].y) * ((long long)arr[c].x - arr[a].x);
}

void print(int x, int y, int mode){
    if(x != 0){
        if(mode == 0){
            print(y, path1[x][y], 1);
        }else{
            print(y, path2[x][y], 0);
        }
    }
    printf("%d %d\n", arr[x].x, arr[x].y);
}

int main(){
    int sx, sy = 2e9;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("%d %d", &arr[i].x, &arr[i].y);
        if(arr[i].y < sy){
            sy = arr[i].y; sx = arr[i].x;
        }
    }
    for(int i=0; i<n; i++){
        arr[i].set_degree(sx, sy);
    }
    sort(arr, arr+n);
    int lasti=-1, lastj=-1, last = 0;
    for(int i=1; i<n; i++){
        d1[i][0] = 2;
        d2[i][0] = -2e9;
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<i; j++){
            if(arr[i].degree == arr[j].degree) continue;
            for(int k=0; k<j; k++){
                if(check(i, j, k) > 0 && d1[i][j] <= d2[j][k] + 1){
                    d1[i][j] = d2[j][k] + 1;
                    if(d1[i][j] > last){
                        lasti = i;
                        lastj= j;
                        last = d1[i][j];
                    }
                    path1[i][j] = k;
                }
                if(check(i, j, k) < 0 && d2[i][j] <= d1[j][k] + 1){
                    d2[i][j] = d1[j][k] + 1;
                    path2[i][j] = k;
                }
            }
        }
    }
    if(lasti == -1){
        printf("%d", 0);
    }else{
        printf("%d\n", d1[lasti][lastj]);
        print(lasti, lastj, 0);
    }
    return 0;
}
