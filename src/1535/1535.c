#include <stdio.h>
#include <string.h>
 
int word_cnt;
char words[1000][100];
 
void push(char * str){
    for(int i=0; i<word_cnt; i++){
        if(strcmp(words[i], str) == 0) return;
    }
    strcpy(words[word_cnt++], str);
}
 
void print(){
    for(int i=0; i<word_cnt; i++){
        printf("%s ", words[i]);
    }
    printf("\n");
}
 
int main(){
    char str[100];
 
    while(1){
        fgets(str, 100, stdin);
        int len = strlen(str);
        while(str[len-1] == '\n') str[--len] = 0;
        if(strcmp(str, "END") == 0) break;
 
        char *word = str;
 
        for(char * temp = str; *temp != 0; temp++){
            if(*temp == ' '){
                *temp = 0;
                push(word);
                word = temp+1;
            }
        }
        push(word);

        print();
    }
    return 0;
}