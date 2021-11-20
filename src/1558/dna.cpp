#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
using pii = pair<int, int>;

int k, len1, len2;
char str1[1010], str2[1010];

pii trace_table[1001][1001];
int dp_table[1001][1001];
pii tree[3001][3001];

inline int get_val(const pii a){
    return dp_table[a.first][a.second];
}

inline char get_chr(const pii a){
    if(a.first == 0) return 'X'; 
    return str1[a.first];
}

inline pii get_par(const pii a){
    return trace_table[a.first][a.second];
}

pii get_max(const pii a, const pii b){
    if(get_val(a) != get_val(b))
        return get_val(a) > get_val(b) ? a : b;
    
    pii ta = a, tb = b;
    
    for(int i=0; i<4; i++){
        if(get_chr(ta) != get_chr(tb))
            return get_chr(ta) < get_chr(tb) ? a : b;
        ta = get_par(ta);
        tb = get_par(tb);
    }
    
    
    return a.first+a.second > b.first+b.second ? a : b;
}

pii deep_get_max(const pii a, const pii b){
    if(get_val(a) != get_val(b))
        return get_val(a) > get_val(b) ? a : b;
    
    pii temp_a = a, temp_b = b;
    while(get_chr(temp_a) == get_chr(temp_b) && get_chr(temp_a) != 'X' && get_chr(temp_b) != 'X'){
        temp_a = get_par(temp_a);
        temp_b = get_par(temp_b);
    }
    return get_chr(temp_a) < get_chr(temp_b) ? a : b;
}

void update_col(int node, int rnode, int col, int l, int r, pii diff){
    if(col < l || r < col) return;
    if(l == r){
        tree[rnode][node] = get_max(tree[rnode][node], diff);
        return;
    }
    
    int m = (l+r)/2;
    update_col(node*2, rnode, col, l, m, diff);
    update_col(node*2+1, rnode, col, m+1, r, diff);
    
    tree[rnode][node] = get_max(tree[rnode][node*2], tree[rnode][node*2+1]);
}

void update(int node, int row, int col, int l, int r, pii diff){
    if(row < l || r < row) return;
    if(l == r){
        update_col(1, node, col, 1, len2, diff);
        return;
    }
    
    int m = (l+r)/2;
    update(node*2, row, col, l, m, diff);
    update(node*2+1, row, col, m+1, r, diff);
    
    update_col(1, node, col, 1, len2, diff);
}

pii query_col(int node, int rnode, int sc, int ec, int l, int r){
    if(r < sc || ec < l) return {0,0};
    if(sc <= l && r <= ec) return tree[rnode][node];
    
    int m = (l+r)/2;
    pii temp1 = query_col(node * 2, rnode, sc, ec, l, m);
    pii temp2 = query_col(node * 2 + 1, rnode, sc, ec, m+1, r);
    return get_max(temp1, temp2);
}

pii query(int node, int sr, int er, int sc, int ec, int l, int r){
    if(r < sr || er < l) return {0,0};
    if(sr <= l && r <= er) return query_col(1, node, sc, ec, 1, len2);
    
    int m = (l+r)/2;
    pii temp1 = query(node*2, sr, er, sc, ec, l, m);
    pii temp2 = query(node*2+1, sr, er, sc, ec, m+1, r);
    return get_max(temp1, temp2);
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
    pii ans = {0,0};
    
    for(int i=1; i<=len1; i++){
        for(int j=1; j<=len2; j++){
            if(str1[i] == str2[j]){
                pii temp;
                pii now = {i,j};
                
                if(i != 1 && j != 1){
                    temp = query(1, max(1, i-k-1), i-1, max(1, j-k-1), j-1, 1, len1);
                }
                
                dp_table[i][j] = get_val(temp)+1;
                trace_table[i][j] = temp;
                ans = deep_get_max(ans, now);
                
                update(1, i, j, 1, len1, now);
            }
        }
    }
    
    
    // print answer
    while(ans.first != 0 && ans.second != 0){
        printf("%c", get_chr(ans));
        ans = get_par(ans);
    }
    
    
    return 0;
}