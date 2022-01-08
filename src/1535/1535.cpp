#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    string str, word;
    vector<string> words;

    while(getline(cin, str) && str != "END"){
        for(stringstream sts(str); (sts>>word);){
            if(find(words.begin(), words.end(), word) == words.end()) 
                words.push_back(word);
        }
        for(auto it : words) cout << it << " ";
        cout << "\n";
    }
    return 0;
}