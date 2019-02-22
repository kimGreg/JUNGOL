#include <iostream>
#include <vector>

<<<<<<< HEAD
int arr1[1010], arr2[1010];
=======
int arr1[1010], arr2[1010], k, sz1, sz2;
>>>>>>> 457f8de4132511f017557f0ee8efeddee3d283f8

int main(){
	char temp;
	scanf("%d %d", &n, &sz1);
	for(int i=1; i<=sz1; i++){
		scanf(" %c", &temp);
		arr1[i] = temp - 'A';
	}
	scanf("%d", &sz2);
	for(int i=1; i<=sz2; i++){
		scanf(" %c", &temp);
		arr2[i] = temp - 'A';
	}
	for(int i=0; i<n; i++){
		
	}
	return 0;
}
