#include <iostream>
#include <vector>
#include <set>
#include <climits>
using namespace std;

#define rep(i,n) for(int i=0;i<n;i++)

int n;				//number of elements
vector <int> a;		//array of elements
int MOD;			//modulo

int solve(){
	set <int> pre;
	pre.insert(0);
	int preSum = 0,bestSum = 0;	
	//in this case modulo ensures bestSum ∈ [0,MOD-1]∩ℕ

	rep(i,n){
		preSum = (preSum+a[i])%MOD;

	   	bestSum = max(bestSum,preSum);
		//case 1: pre[j] <= pre[i] 
		//in this case max is achieved for j=0

		auto it = pre.lower_bound(preSum+1); 
		//case 2: pre[j] >  pre[i]
		//in this case max is achieved for
		//pre[j] just greater than preSum

		if(it!=pre.end())
			bestSum = max(bestSum,preSum-*it+MOD);

		pre.insert(preSum);
	}

	return bestSum;
}
//Θ(n*㏒n)

int main(){
	cin>>n>>MOD;
	a.resize(n);

	rep(i,n)
		cin>>a[i];

	cout<<solve()<<endl;
}
