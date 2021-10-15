#include<bits/stdc++.h>
using namespace std;

int removeDuplicates(vector<int>& nums){
    int count=0;
    for(int i=0; i<nums.size();i++){
        int a = nums[i];
        while(nums[i]==a)
            i++;
        i--;
        nums[count]=a;
        count++;
    }
    return count;

}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    vector<int> vect= vector{1};
    int result = removeDuplicates(vect);
    cout<<result;
    return 0;
}