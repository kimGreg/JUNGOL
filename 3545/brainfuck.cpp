#include <cstdio>
#include <stack>
#include <cstring>
#include <algorithm>
using namespace std;

const int Msize = 327618, Vmax = 256;
int connected[2000000], arr[327618], commands[2000000], len;
char com[7] = {'>', '<', '+', '-', '.', '[', ']'};


void run(){
	int Mptr = 0, Cptr = 0;
	while(Cptr < len){
		int now = commands[Cptr]+1;
		switch(now){
		case 1:
			Mptr = (Mptr+1)%Msize;
			break;
		case 2:
			Mptr = (Mptr+Msize-1)%Msize;
			break;
		case 3:
			arr[Mptr] = (arr[Mptr]+1)%256;
			break;
		case 4:
			arr[Mptr] = (arr[Mptr]+255)%256;
			break;
		case 5:
			printf("%c", (char)arr[Mptr]);
			break;
		case 6:
			if(!arr[Mptr]) 
				Cptr = connected[Cptr];
			break;
		case 7:
			if(arr[Mptr])
				Cptr = connected[Cptr];
			break;
		}
		Cptr++;
	}
}

int main(){
	bool flag = 0, flag2 = 1;
	char ch;
	stack<int> stk;
	while(scanf("%c", &ch) != -1 && flag2){
		if(ch == '\n') flag = 0;
		else if(flag)  continue;
		else if(ch == '%') flag = 1;
		else{
			for(int i = 0; i<7; i++){
				if(ch == com[i]){
					commands[len] = i;
					if(i == 5) stk.push(len);
					else if(i == 6){
						if(stk.empty())
							flag2 = 0;
						else{
							int before = stk.top(); stk.pop();
							connected[before] = len;
							connected[len] = before;
						}
					}
					len++;
					break;
				}
			}
		}
	}
	if(flag2 && stk.empty())
		run();
	else
		printf("COMPILE ERROR");
	return 0;
}
