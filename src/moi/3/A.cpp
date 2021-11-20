#include <cstdio>
#include <algorithm>
using namespace std;

class data{
public:
	int x1, y1, x2, y2;
	data(){}
	data(int a, int b, int c, int d){
		x1 = a; y1 = b; x2 = c; y2 = d;
	}
	void input(){
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
	}
};

int n, x, y;

int ccw(double x1, double y1, double x2, double y2, double x3, double y3) {
    double temp = x1*y2 - y1*x2 + x2*y3 - y2*x3 + x3*y1 - y3*x1;
    if (temp > 0) return 1;
    else if (temp < 0) return -1;
    else return 0;
}

bool comp(data E1, data E2){
	double s=0, e=1000000, nx, ny;
    
    while(1){
        double m = (s+e)/2;
		if(x != 0){
            nx = m;
			ny = (double)((m*y)/(double)x);
		}else{
			ny = m;
			nx = 0;
		}
        int a = ccw(nx, ny, E1.x1, E1.y1, E1.x2, E1.y2), b = ccw(0, 0, E1.x1, E1.y1, E1.x2, E1.y2);
        int c = ccw(nx, ny, E2.x1, E2.y1, E2.x2, E2.y2), d = ccw(0, 0, E2.x1, E2.y1, E2.x2, E2.y2);
		int p1 = a*b;
        if(a == 0 && b == 0){
            if(nx >= min(E1.x1, E1.x2) && ny >= min(E1.y1, E1.y2)) p1 = -1;
            else p1 = 1;
        }
        int p2 = c*d;
        if(c == 0 && d == 0){
            if(nx >= min(E2.x1, E2.x2) && ny >= min(E2.y1, E2.y2)) p1 = -1;
            else p1 = 1;
        }
        if(p1 <= 0 && p2 <= 0) // 두개 다 교차
            e = m;
        else if(p1 > 0 && p2 > 0) // 둘다 교차X
            s = m;
        else
            return p2 <= 0;
	}
    return 1;
}

int main(){
	scanf("%d %d %d", &x, &y, &n);
	data ans;
	int ansI = -1;
	for(int i=1; i<=n; i++){
		data temp;
		temp.input();
		if(ccw(0, 0, x, y, temp.x1, temp.y1) * ccw(0, 0, x, y, temp.x2, temp.y2) > 0) continue;
        if(ansI == -1 || comp(ans, temp)){
            ans = temp;
            ansI = i;
        }
	}
	printf("%d\n", ansI);
	return 0;
}
