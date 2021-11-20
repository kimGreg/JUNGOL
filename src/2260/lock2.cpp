#include <stdio.h>
#include <algorithm>
  
using namespace std;
  
int arr[1010];
int tmp[1010];
int input[1010];
int u[2010];
int st = -1, ed = -1;
int N;
  
int find_1(){
  for(int i = 0; i < N; i++){      
    if(input[i] == 1) return i;
  }
  return -1;
}
  
int main(void){
  int i, k, p, j, l, e;
  scanf("%d", &N);
  for(i = 0; i < N; i++) scanf("%d", &input[i]);
 
  for(i = 0; i < 2 * N; i++) u[i] = input[i % N];
  int firstZero = 0;
  for(i = 0; i < N-1; i++){
    if(!(u[i] == u[i + 1] + 1 || (u[i] == 1 && u[i + 1] == N))){
      firstZero = i;
      break;
    }
  }
  for(i = firstZero; i < 2 * N - 1; i++){
    if((u[i] == u[i + 1] + 1 || (u[i] == 1 && u[i + 1] == N)) && st == -1) st = i;
    if(st != -1 && !((u[i] == u[i + 1] + 1 || (u[i] == 1 && u[i + 1] == N)))){
      ed = i;
      break;
    }
  }
  
  if(ed == -1){
    int x = find_1();
    if(x != 0){
      printf("1\n1 %d\n%d\n", N, N-x);
    }
    else{
      printf("%d\n1 %d\n%d\n", N - 1, N, N-2);
    }
    return 0;
  }
  
  int first = find_1();
  for(int i=st; i<=ed; i++) if(u[i] == 1) first = i;
  if(st <= first && first <= ed) 
    first = ((st + ed) - first + 10 * N) % N;
   
  for(int now = 1; now < N; now++){
    int s = (3*N+st-now)%N;
    int e = (3*N+ed-now)%N;
    int id = (2*N+first-now)%N;
    if(s > e || id == 0) continue;
    printf("%d\n%d %d\n%d\n", N-id, s+1, e+1, N-now);
    break;
  }
  return 0;
}