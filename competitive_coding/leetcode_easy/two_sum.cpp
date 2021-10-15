#include <bits/stdc++.h>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target){
    /**
     * two pointer solution O(nlogn)
     * sort takes O(nlogn)
     */
    sort(nums.begin(), nums.end());
    int front=0, rear = nums.size()-1;
    while(front<rear){
        int sum = nums[front] + nums[rear];
        if(sum == target){
            break;
        }
        else if (sum > target)
            rear--;
        else
            front++;
    }
    return {front, rear};
}

vector<int> twoSumHashMap(vector<int>& nums, int target){
    /**
     * O(n) time complexity
     * O(n) space complexity
     */ 
    map<int, int> map;
    vector<int> pairs;
    for(int i=0; i<nums.size(); i++){
        int complement = target - nums[i];
        if(map.find(complement) != map.end()){
            pairs.push_back(map.find(complement)->second);
            pairs.push_back(i);
            break;
        }
        map.insert(pair<int, int>(nums[i], i));
    }
    return pairs;
}

void print_vec(vector<int> &a){
    for(int i:a)
        cout<<i<<" ";
    cout<<"\n";
}

void test(vector<int> a, int target){
    vector<int> copy1(a);
    vector<int> copy2(a);
    print_vec(copy1);
    vector<int> result = twoSumHashMap(copy1, target);
    print_vec(copy2);
    vector<int> result2 = twoSum(copy2, target);
    print_vec(result);
    print_vec(result2);
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    vector<int> vect1{2, 7, 11, 15};
    test(vect1,9);
    vector<int> vect2{1, 2, 3, 9};
    test(vect2,10);
    vector<int> vect3{11, 1, 5, 12};
    test(vect3,12);
    
    return 0;
}