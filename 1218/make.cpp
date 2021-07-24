#include <cstdio>

using namespace std;

inline CtoI(char ch){
    if(ch == 'R') return 0;
    else if(ch == 'G') return 1;
    else if(ch == 'B') return 2;
    return 3;
}

char str[4][7];




int main(){
    for(int i=0; i<4; i++)
        scanf("%s", str[i]);
    
    
    
    return 0;
}