#include <cstdio>
using namespace std;

class seg_tree{
public:
	
};
int R, C;
int row_wombat[5050][220], col_wombat[220][5050];

void input(){
	scanf("%d %d", &R, &C);
	
	for(int i=0; i<R; i++){
		for(int j=1; j<C; j++){
			scanf("%d", row_wombat[i]+j);
		}
	}
	for(int j=0; j<R-1; j++){
		for(int i=0; i<C; i++){
			scanf("%d", col_wombat[i]+j);
		}
	}
}



void solve(){
	int E;
	scanf("%d", &E);
	while(E--){
		char str[10];
		int type;
		scanf(" %s %d", str, &type);
		if(str[0] == 'c'){
			int p, q, w;
			scanf("%d %d %d", &p, &q, &w);
			if(type == 1){
				
			}else{

			}

		}else{
			int v1, v2;
			scanf("%d %d", &v1, &v2);


		}
	}

}
int main(){
	input();
	solve();
	
	return 0;
}
