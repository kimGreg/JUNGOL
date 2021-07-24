#include <cstdio>
#include <stack>
#include <algorithm>
using namespace std;
using pii = pair<int, int>;

int arr[1100][1100];
char str[2000010];
int n;
stack<pii> history;

void fill(int pos, int depth, int val){
    int posx = 0, posy = 0;
    for(int i=0; i<depth; i++){
        if(pos & 1)
            posx += 1<<(n-depth+i);
        if(pos & 2)
            posy += 1<<(n-depth+i);
        pos >>= 2;
    }
    for(int i=0; i< (1<<(n-depth)); i++){
        for(int j=0; j<(1<<(n-depth)); j++){
            arr[posy+i][posx+j] = val;
        }
    }
}

int main(){
    int temp;
    scanf("%d %s", &temp, str);
    for(n = -1; temp; n++, temp>>=1);
    
    history.push({0,0});    
    for(int i=0; str[i]; i++){
        int now_pos = history.top().first;
        int depth = history.top().second;
        history.pop();
        if(str[i] == 'X'){
            for(int i=3; i>=0; i--){
                history.push({(now_pos<<2) + i, depth+1});
            }
        }else{
            fill(now_pos, depth, str[i]-'0');
        }
    }
    printf("%d\n", (1<<n));
    for(int i=0; i < (1<<n); i++){
        for(int j=0; j < (1<<n); j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    return 0;
}