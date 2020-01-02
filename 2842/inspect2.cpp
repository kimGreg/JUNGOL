#include <cstdio>
#include <cstring>
#include <list>
using namespace std;

char str[1000100], patt[1000100];// 1번부터 저장
int fail[1000100], fail2[1000100];
int pattN, strN;
list<char> strL;

void input(){
	scanf("%s %s", str+1, patt+1);
	strN = strlen(str+1), pattN = strlen(patt+1);
	for(int i=1; i<=strN; i++) strL.push_back(str[i]);	
}

void preKMP(){
	for(int i=2, k=0; i<=pattN; i++){
		while(k && patt[k+1] != patt[i])
			k = fail[k];
		if(patt[k+1] == patt[i])
			fail[i] = ++k;
	}
}

void solve(){
	auto it = strL.begin();
	for(int i=1, k=0; it != strL.end(); it++, i++){
		while(k && patt[k+1] != *it)
			k = fail[k];	
		if(patt[k+1] == *it){
			k++;
			if(k == pattN){ // 매칭이 됨
				for(int j=0; j<pattN; j++){
					fail2[i] = 0;
					strL.erase(it--);
					i--;
				}
				k = fail2[i];
				continue;
			}
		}

		fail2[i] = k;
	}

	for(auto it = strL.begin(); it != strL.end(); it++){
		printf("%c", *it);
	}
}

int main(){
	input();
	preKMP();
	solve();
	return 0;
}
