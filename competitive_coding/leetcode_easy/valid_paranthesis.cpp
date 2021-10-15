#include <bits/stdc++.h>
using namespace std;

bool isValid(string s){
    vector<char> stack;
    if(s.length()==1)
        return false;
    for(char c: s){
        if(c=='{' || c=='[' || c=='(')
            stack.push_back(c);
        else{
            if(stack.empty())
                return false;
            char top = stack.back(); stack.pop_back();
            if(c=='}' && top != '{')
                return false;
            if(c==']' && top != '[')
                return false;
            if(c==')' && top != '(')
                return false;
        }
    }
    if(stack.size() > 0)
        return false;
    return true;
}


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout<<isValid("{[]}");
    cout<<isValid("()");
    cout<<isValid("()[]{}");
    cout<<isValid("(]");
    cout<<isValid("([)]");
    cout<<isValid("(");
    cout<<isValid("((");
    cout<<isValid(")[");
    return 0;
}