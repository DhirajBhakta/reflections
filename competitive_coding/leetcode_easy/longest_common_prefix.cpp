#include<bits/stdc++.h>

using namespace std;

string longestCommonPrefix(vector<string>& strs){
    int pointer = 0;
    string prefix = "";
    char pointerChar='\0'; 

    while(true){
        pointerChar = strs[0][pointer];
        for(string str: strs){
            if(str[pointer] == '\0')
                return prefix;
            if(str[pointer]!=pointerChar)
                return prefix;
        }
        prefix+=pointerChar;
        pointer++;
    }
    return prefix;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    vector<string> strs = {
        "flower",
        "flow",
        "flight"
    };
    cout<<longestCommonPrefix(strs);
    vector<string> strs2 = {
        "dog",
        "racecar",
        "car"
    };
    cout<<longestCommonPrefix(strs2);

    return 0;
}