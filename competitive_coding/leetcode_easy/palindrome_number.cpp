#include <bits/stdc++.h>
#include <math.h>
using namespace std;

int reverse(int x)
{
    long reversed = 0;
    while (x != 0)
    {
        reversed = reversed * 10 + x % 10;
        x = x / 10;
    }
    return reversed;
}

bool isPalindrome(int x)
{
    /**
     * with reversal, sucks with long numbers
     */
    if (x < 0)
        return false;
    if (x == 0)
        return true;
    return x == reverse(x);
}
bool isPalindromeWithoutReversal(int x)
{
    int copy = x;
    if (x < 0)
        return false;
    if (x == 0)
        return true;
    vector<int> vect;
    while(x){
        vect.push_back(x%10);
        x=x/10;
    }
    int front=0;
    int rear = vect.size()-1;
    while(front<rear){
        // cout<<front<<"->"<<vect[front]<<" "<<rear<<"->"<<vect[rear]<<" ";
        if(vect[front]!=vect[rear])
            return false;
        front++;
        rear--;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout << 200 << " " << isPalindrome(200) << " " << isPalindromeWithoutReversal(200) << "\n";
    cout << 201 << " " << isPalindrome(201) << " " << isPalindromeWithoutReversal(201) << "\n";
    cout << -100 << "  " << isPalindrome(-100) << " " << isPalindromeWithoutReversal(-100) << "\n";
    cout << 001 << "  " << isPalindrome(001) << " " << isPalindromeWithoutReversal(001) << "\n";
    cout << 121 << "  " << isPalindrome(121) << " " << isPalindromeWithoutReversal(121) << "\n";
    cout << 1000021 << "  " << isPalindrome(1000021) << " " << isPalindromeWithoutReversal(1000021) << "\n";
    cout << 11 << "  " << isPalindrome(11) << " " << isPalindromeWithoutReversal(11) << "\n";
}