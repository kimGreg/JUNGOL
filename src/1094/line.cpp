#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
class data{
public:
	int dx, dy;
	data(){}
	data(int X, int Y){dx = X; dy = Y;}
	bool operator <(const data & D) const{
		if(dx != D.dx) return dx < D.dx;
		return dy < D.dy;
	}
};

int xarr[500], yarr[500];

int gcd(int a, int b){
	if(a == 0) return b;
	return gcd(b%a, a);
}

set<data> st;

int main(){
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++)
		scanf("%d %d", xarr+i, yarr+i);
	for(int i=0; i<n; i++){
		for(int j=i+1; j<n; j++){
			int dx = xarr[i] - xarr[j], dy = yarr[i] - yarr[j];
			if(dx == 0)
				st.insert({-1, -1});
			else{
				if(dx < 0) dx = -dx, dy = -dy;
				int k = gcd(dx, dy);
				st.insert({dx/k, dy/k});
			}
		}
	}
	printf("%d", st.size());
	return 0;
}
