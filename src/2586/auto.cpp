#include <cstdio>

using namespace std;

int arr[10][10];
int rcnt[10], ccnt[10];

int main(){
    int base_production;
    scanf("%d", &base_production);

    int tot = 0;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            scanf("%d", arr[i] + j);
            arr[i][j] -= base_production;
            tot += arr[i][j];
            ccnt[j] += arr[i][j];
            rcnt[i] += arr[i][j];
        }
    }
    tot /= 15;
    
    for(int i=0; i<8; i++){
        ccnt[i] = (ccnt[i]-tot)/7;
        rcnt[i] = (rcnt[i]-tot)/7;
        printf("!! %d %d\n", ccnt[i], rcnt[i]);
    }

    

    return 0;
}
