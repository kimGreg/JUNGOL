#include <iostream>
using namespace std;

int arr[9][9];
bool row[9][10];
bool col[9][10];
bool box[3][3][10];
 
void input(){
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            int n;
            cin >> n;
            arr[i][j] = n;
            row[i][n] = true;
            col[j][n] = true;
            box[i/3][j/3][n] = true;
        }
    }
}

bool solve(int r=0, int c=0){
    if(r>=9) return true;
    if(c>=9) return solve(r+1, 0);
    if(arr[r][c] != 0) return solve(r, c+1);
    else{
        for(int n=1; n<=9; n++){
            if(!(row[r][n]||col[c][n]||box[r/3][c/3][n])){
                row[r][n] = true;
                col[c][n] = true;
                box[r/3][c/3][n] = true;
                arr[r][c] = n;
                 
                if(solve(r, c+1)) return true;

                row[r][n] = false;
                col[c][n] = false;
                box[r/3][c/3][n] = false;
                arr[r][c] = 0;
            }
        }
    }
    return false;
}

void print(){
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++) cout << arr[i][j] << " ";
        cout << "\n";
    }
}

int main(){
    input();
    solve();
    print();
    return 0;
}