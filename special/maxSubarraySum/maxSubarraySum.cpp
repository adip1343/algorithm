#include <iostream>
#include <vector>
using namespace std;

#define rep(i,n) for(int i=0;i<n;i++)

int n;				//number of elements
vector <int> a;		//array of elements

int solve(){
	int sum=0,bestSum=0;			//if null subarray is allowed bestSum=0
									//if not bestSum=INT_MIN
									//this will choose minimum element
	rep(i,n){
		sum = max(a[i],sum+a[i]);	//sum is maximum subarray sum ending on i
		bestSum = max(bestSum,sum); //maxSubarraySum in a[0...i]
	}
	return bestSum;	
}

int main(){
	cin>>n;
	a.resize(n);

	rep(i,n)
		cin>>a[i];

	cout<<solve()<<end;
}
