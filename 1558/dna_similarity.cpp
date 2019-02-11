#include <iostream>
#include <vector>

int arr1[1010], arr2[1010];


int main(){
	int n, sz1, sz2;
	scanf("%d %d", &n, &sz1);
	for(int i=1; i<=sz1; i++){
		char temp; scanf(" %c", temp);
		arr1[i] = temp - 'A';
	}
	scanf("%d", &sz2);
	for(int i=1; i<=sz2; i++){
		char temp; scanf(" %c", temp);
		arr2[i] = temp - 'A';
	}
	for(int i=0; i<n; i++){
			
	}
	return 0;
}
