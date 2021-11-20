#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
using pii = pair<int, int>;

int k, len1, len2;
char str1[1010], str2[1010];

int dp_table[1001][1001];
int max_row[1001];

queue<pii> que1, que2;
char ans[1001];

inline int get_val(const pii a){
    return dp_table[a.first][a.second];
}

inline char get_chr(const pii a){
    if(a.first == 0) return 'X'; 
    return str1[a.first];
}

pii get_max(const pii a, const pii b){
    if(get_val(a) != get_val(b))
        return get_val(a) > get_val(b) ? a : b;
    
    return a.first+a.second > b.first+b.second ? a : b;
}


int main(){
    // input
    scanf("%d %d %s %d %s", &k, &len1, str1+1, &len2, str2+1);
    
    // reverse_string
    for(int i=1; i<=len1/2; i++){
        char temp = str1[i];
        str1[i] = str1[len1-i+1];
        str1[len1-i+1] = temp;
    }
    
    for(int i=1; i<=len2/2; i++){
        char temp = str2[i];
        str2[i] = str2[len2-i+1];
        str2[len2-i+1] = temp;
    }
    
    // fill dp_table
    int max_len = 0;
    for(int i=1; i<=len1; i++){
        for(int j=1; j<=len2; j++){
            int temp = 0;
            max_row[j] = 0;
            
            for(int t=1; t<=k+1; t++){
                if(i-t > 0) max_row[j] = max(max_row[j], dp_table[i-t][j]);
                if(j-t > 0) temp = max(temp, max_row[j-t]);
            }
            if(str1[i] == str2[j]){
                dp_table[i][j] = temp + 1;
                max_len = max(max_len, temp+1);
            }
        }
    }
    
    
    
    char min_chr = 'X';
    for(int i=1; i<=len1; i++){
        for(int j=1; j<=len2; j++){
            pii now = {i,j};
            if(get_val(now) == max_len){
                que1.push(now);
                min_chr = min(min_chr, get_chr(now));
            }
        }
    }
    
    for(int t=0; t<max_len; t++){
        ans[t] = min_chr;
        
        while(!que1.empty()){
            if(get_chr(que1.front()) == min_chr){
                que2.push(que1.front());
            }
            que1.pop();
        }
        
        min_chr = 'X';
        while(!que2.empty()){
            int a = que2.front().first, b = que2.front().second;
            que2.pop();
            
            for(int i=max(1, a-k-1); i<a; i++){
                for(int j=max(1, b-k-1); j<b; j++){
                    pii now = {i,j};
                    if(get_val(now) == max_len-t-1){
                        que1.push(now);
                        min_chr = min(min_chr, get_chr(now));
                        dp_table[i][j] = 0;
                    }
                }
            }
        }
    }
        
    ans[max_len] = '\0';
    
    printf("%s", ans);
    
    return 0;
}