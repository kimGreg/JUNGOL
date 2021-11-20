#include <cstido>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> arr;

void func(){
	int n, m;
	scanf("%d %d", &n, &m);
	arr.resize(m, 0);
	for(int i=0; i<m; i++) scanf("%d", arr+i);

}

int main(){
	for(int t=0; t<4; t++) func();
	return 0;
}
