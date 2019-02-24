#include <cstdio>
#include <vector>
using namespace std;
int arr1[1010], arr2[1010], K, sz1, sz2;
int d1[1010][1010][33], d2[1010][1010][33];
vector<int> path1[1010][1010][33], path2[1010][1010][33];

void check(int & a, int & b, vector<int> & A, vector<int> & B){
    if(a > b || b == -2e9) return;
    if(a == b){
        for(int i=0; i<A.size(); i++){
            if(A[i] < B[i]) return;
            else if(A[i] > B[i]) break;
        }
    }
    a = b;
    A = B;
}

int main(){
	char temp;
	scanf("%d %d", &K, &sz1);
	for(int i=1; i<=sz1; i++){
		scanf(" %c", &temp);
		arr1[i] = temp - 'A';
	}
	scanf("%d", &sz2);
	for(int i=1; i<=sz2; i++){
		scanf(" %c", &temp);
		arr2[i] = temp - 'A' + 1;
	}

	for(int i=0; i<=sz1; i++){
        for(int j=0; j<=sz2; j++){
            for(int k=0; k<=K; k++)
                d1[i][j][k] = d2[i][j][k] = -2e9;
        }
	}
	d1[0][0][0] = d2[0][0][0] = 0;
	for(int i=0;i<=sz1; i++){
        for(int j=0; j<=sz2; j++){
            for(int k=1; k<=K && j != 0; k++)
                check(d1[i][j][k], d1[i][j-1][k-1], path1[i][j][k], path1[i][j-1][k-1]);
            for(int k=1; k<=K && i != 0; k++)
                check(d2[i][j][k], d2[i-1][j][k-1], path2[i][j][k], path2[i-1][j][k-1]);

            if(arr1[i] == arr2[j] && i != 0 && j != 0){
                check(d1[i][j][0], d1[i-1][j-1][0], path1[i][j][0], path1[i-1][j-1][0]);
                for(int k=1; k<=K && i != 0 && j != 0; k++)
                    check(d1[i][j][0], d1[i-1][j-1][k], path1[i][j][0], path1[i-1][j-1][k]);
                d1[i][j][0]++;
                path1[i][j][0].push_back(arr1[i]);
                d2[i][j][0] = d1[i][j][0];
                path2[i][j][0] = path1[i][j][0];
            }
        }
	}
	int a=-2e9;
	vector<int> ans;
	for(int k=0; k<=K; k++){
        check(a, d1[sz1][sz2][k], ans, path1[sz1][sz2][k]);
        check(a, d2[sz1][sz2][k], ans, path2[sz1][sz2][k]);
	}
	printf("!! %d\n", a);
	for(auto i : ans) printf("%c", i+'A'-1);
	return 0;
}
