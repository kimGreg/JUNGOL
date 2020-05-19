#include <cstdio>
using namespace std;

int size[3], pile[3][100100], last[3];
const long long MOD = 1000000007;
const long long MAXCNT = 65536;
long long ans = 0;
bool flag = 0;

long long pow(int k){
	if(k == 0) return 1;
	if(k > 16) flag = 1;

	long long temp = pow(k/2);
	
	temp = (temp*temp)%MOD;

	if(k & 1)
		temp = (temp*2)%MOD;

	return temp;
}



void add_ans(long long k){
	ans += k;
	if(ans > 65536)  flag = 1;
	ans %= MOD;
}

void print_move(int a, int b, int c){
	printf("%d : %d -> %d\n", a, b+1, c+1);
}

void print_hanoi(int n, int f, int t, int r){
	if(n == 0)
		return;
	print_hanoi(n-1, f, r, t);
	print_move(n, f, t);
	print_hanoi(n-1, r, t, f);
}

void hanoi(int t, bool IsPrint = 0){ //max plate to t
	if(last[0] == size[0] &&  last[1] == size[1] && last[2] == size[2])
		return;
	
	int maxi = 0;
	if(pile[1][last[1]] > pile[maxi][last[maxi]])
		maxi = 1;
	if(pile[2][last[2]] > pile[maxi][last[maxi]])
		maxi = 2;
	
	if(t == maxi){
		last[maxi]++;
		hanoi(t, IsPrint);
		last[maxi]--;
	}else{
		int next_t = 0;
		while(next_t == t || next_t == maxi) next_t++;
		last[maxi]++;
		hanoi(next_t, IsPrint);
		last[maxi]--;
		if(IsPrint){
			print_move(pile[maxi][last[maxi]], maxi, t);
			print_hanoi(pile[maxi][last[maxi]]-1, next_t, t, maxi);
		}else{
			add_ans(pow(pile[maxi][last[maxi]]-1));
		}
	}
}

int main(){
	int n, k;
	scanf("%d %d", &n, &k);
	k--;

	for(int i=0; i<3; i++){
		scanf("%d", size+i);
		for(int j=size[i]-1; j>=0; j--)
			scanf("%d", pile[i]+j);
	}

	hanoi(k);
	printf("%lld\n", ans);

	if(!flag) hanoi(k, 1);	

	return 0;
}
