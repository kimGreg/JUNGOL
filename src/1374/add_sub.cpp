#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

class number{
public:
	int arr[300], len;
	void input(){
		char str[300];
		scanf(" %s", str);
		len = strlen(str);
		fill(arr, arr+300, 0);
		for(int i=len-1; i>=0; i--) arr[i] = str[len-i-1]-'0'; 
	}
	number(){
		fill(arr, arr+300, 0);
		len = 0;
	}
	number(int n){
		fill(arr, arr+300, 0);
		for(int i=0; n != 0; i++){
			len = i+1;
			arr[i] = n%10;
			n /= 10;
		}
	}
	void print(){
		for(int i=len-1; i>=0; i--) printf("%d", arr[i]);
		printf("\n");
	}
	bool isZero(){
		return (len == 1) && (arr[0] == 0);
	}
	number complement() const {
		number New;
		for(int i=0; i<300; i++) New.arr[i] = 9-arr[i];
		New.len = 300;
		return New + number(1);
	}
	number operator + (const number & N) const{
		int carry = 0;
		number New;
		New.len = 1;
		for(int i=0; (i<N.len || i<len || carry != 0) && i < 300; i++){
			carry = arr[i] + N.arr[i] + carry;
			New.arr[i] = carry%10;
			if(carry%10) New.len = i+1;
			carry = carry/10;
		}
		return New;
	}
	number operator - (const number & N) const{
		int carry = 0;
		return *this + N.complement();
	}
	number operator *  (const number & N) const{
		
	}
	bool operator < (const number & N) const{
		if(N.len != len) return len <  N.len;
		for(int i=len-1; i>=0; i--){
			if(arr[i] != N.arr[i]) 
				return arr[i] < N.arr[i];
		}
		return false;
	}
};

int main(){
	while(1){
		number A, B;
		A.input();
		B.input();
		if(A.isZero() && B.isZero()) break;
		if(A < B) swap(A, B);  
		number C = A+B;
		number D = A-B;
		C.print();
		D.print();
	}
	return 0;
}
