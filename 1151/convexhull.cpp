#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
class vector2{
public;
	ll x, y;
	vector2(ll _x=0, ll _y=0):x(_x),y(_y){}
	vector2 operator-(const vector2 & V)const{
		return vector2(x-V.x, y-V.y);
	}
	ll cross(vector2 A, vector2 B)const{
		return A.x*B.y - B.x*A.y;
	}
};

vector<vector2> point, convHull;

void getconvexhull(){
	swap(point[0], min_element(point.begin(), point.end(), [](vector2 & V

int main(){
	int n;
	scanf("%d", &n);
	point.resize(n);
	for(int i=0; i<n; i++) scanf("%d %d", point[i].x, point[i].y);
	getconvexhull();
	return 0;
}
