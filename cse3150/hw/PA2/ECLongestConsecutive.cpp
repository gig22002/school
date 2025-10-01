#include <iostream>
#include <vector>
#include <set>

using namespace std;

int ECLongestConsecutive(vector<int>& nums) {
    // return the longest length of consecutive numbers in nums
    // Implement function here
	set<int> s;
	for(int i=0; i<nums.size(); i++){
		s.insert(nums[i]);
	}

	int sum=1;
	int greatestSum=s.empty() ? 0 : 1;
	int last;
	for(set<int>::iterator k = s.begin(); k != s.end(); k++){
		if(last == *k-1){
			sum++;
			if(sum>greatestSum) { greatestSum = sum; }
		}
		else { sum=1; }
		last = *k;
		//cout << *k << endl;
	}
	return greatestSum;
}
