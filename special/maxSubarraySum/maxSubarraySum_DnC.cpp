#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct range{
	int L,R,value;
};

#define rep(i,n) for(int i=0;i<n;i++)

vector <int> a;
int n;

range maxCrossingSubarraySum(int start,int end){
    int leftSum,rightSum,sum,leftIndex,rightIndex;
    int mid = start+(end-start)/2;

    leftSum = INT_MIN,sum=0;
    for(int i=mid;i>=0;i--){
        sum += a[i];
        if(sum>leftSum){
            leftIndex=i;
            leftSum=sum;
        }   
    }

    rightSum = INT_MIN,sum=0;
    for(int i=mid+1;i<=end;i++){
        sum += a[i];
        if(sum>rightSum){
            rightIndex=i;
            rightSum=sum;
        }
    }   

    return {leftIndex,rightIndex,rightSum+leftSum};
}
//Θ(n)

range maxSubarraySum(int start,int end){
	if(start==end)
		return {start,end,a[start]};
	int mid = start+(end-start)/2;

	range l = maxSubarraySum(start,mid);		//in Left Subarray
	range r = maxSubarraySum(mid+1,end);		//in Right Subarray
	range m = maxCrossingSubarray(start,end);	//in Crossing Subarray 

	if(l.value>=r.value && l.value>=m.value)
		return l;
	if(r.value>=m.value && r.value>=m.value)
		return r;
	return m;
}
//Θ(n*㏒n)

int main(){
	cin>>n;
	a.resize(n);

	rep(i,n)
		cin>>a[i];

	cout<< maxSubarraySum(0,n-1).value <<endl;
	
}
