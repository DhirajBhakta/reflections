TIME : O(N)
SPACE : O(1)

Finds the Majority element in a given array.

Majority Element: an element that occurs **more than half of the time (>N/2)**

```c++
int candidate=0, votes=0;

for(int n: nums){
 if(votes == 0){
	 candidate = n;
 }
 if (n == candidate){
	 votes++;
 }else{
	 votes--;
 }
}
```
