#include <cstdio>
using namespace std;

class SegTree{
public:
	int R, C;
	int row_wombat[5050][220], col_wombat[5050][220];	
	int tree[20020][220][220];

	void init(int now, int r, int l){

	}

	void update(int now, int r, int l, int s, int e){
		if(r > e || l < s)
			return;
		if(r == l){
			// caculate r == l
			return;
		}
		int m = (r+l)/2;
		update(now*2, r, m, s, e);
		update(now*2+1, m, l, s, e);
		// caculate r, m, l

	}

	int get_ans(int a, int b){
		return tree[1][a][b];
	}
};

SegTree tree;


void input(SegTree & tree){
	scanf("%d %d", &tree.R, &tree.C);
	
	for(int i=1; i<= tree.R; i++){
		for(int j=1; j<tree.C; j++){
			scanf("%d", tree.row_wombat[i]+j);
		}
	}
	for(int j=1; j<= tree.R-1; j++){
		for(int i=1; i<=tree.C; i++){
			scanf("%d", tree.col_wombat[i]+j);
		}
	}

	tree.init(1, 1, tree.R);
}

void solve(SegTree & tree){
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
				tree.row_wombat[p][q] = w;				
			}else{
				tree.col_wombat[p][q] = w;
			}
		}else{
			int v1, v2;
			scanf("%d %d", &v1, &v2);
			printf("%d\n", tree.get_ans(v1, v2));
		}
	}

}

int main(){
	input(tree);
	solve(tree);
	
	return 0;
}
