#include <iostream>
#include <vector>
#include <set>
#include <climits>
using namespace std;

#define rep(i,n) for(int i=0;i<n;i++)

int n;				//number of elements
vector <int> a;		//array of elements

int solve(){
	int sum=0,bestSum=0;
	//if null subarray is allowed bestSum=0
	//if not bestSum=INT_MIN
	//this will choose minimum element
	//
	rep(i,n){
		sum = max(a[i],sum+a[i]);	
		//sum is maximum subarray sum ending on i
		bestSum = max(bestSum,sum); 
		//maxSubarraySum in a[0...i]
	}
	return bestSum;	
}
//Θ(n)

int Solve(){
	set <int> pre;
	pre.insert(0);
	int preSum = 0,bestSum = INT_MIN;	
	//if null subarray is allowed bestSum=0
    //if not bestSum=INT_MIN
    //this will choose minimum element

	rep(i,n){
		preSum += a[i];
		auto it = pre.upper_bound(INT_MIN);	
		//finding smallest prefix sum before i
		if(it!=pre.end())
			bestSum = max(bestSum,preSum-*it);
		pre.insert(preSum);
	}

	return bestSum;
}
//Θ(n*㏒n)

int main(){
	cin>>n;
	a.resize(n);

	rep(i,n)
		cin>>a[i];

	cout<<solve()<<end;
}
