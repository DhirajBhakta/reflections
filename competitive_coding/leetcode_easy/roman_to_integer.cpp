#include<bits/stdc++.h>

using namespace std;

int romanToInt(string s){
    map<char, int> mp;
    mp['I'] = 1;
    mp['V'] = 5;
    mp['X'] = 10;
    mp['L'] = 50;
    mp['C'] = 100;
    mp['D'] = 500;
    mp['M'] = 1000;
    int sum=0;
    for(int i=0; s[i]!='\0'; i++){
        if(mp[s[i]] < mp[s[i+1]]){
            sum += mp[s[i+1]] - mp[s[i]];
            i++;
        }
        else{
            sum+= mp[s[i]];
        }
    }
    return sum;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    return 0;
}