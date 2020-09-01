#include <iostream>
#include <climits>
#include <vector>
using namespace std;

int MAX_VALUE = 1e5+10; //Maximum value we can get from items without restriction
int W;					//Capacity of knapsack
int N;					//Number of items
int w;					//weight of item
int v;					//value of item
vector <long long> ks;	//minimum weight for knapsack of given value
/*
 * this time we have very big capacity knapsack so 
 * we will try to minimize weight for given value
 */

int main(){
	cin>>N>>W;
	
	ks.resize(MAX_VALUE+1,INT_MAX);
	ks[0]=0;

	for(int i=1;i<=N;i++){
		cin>>w>>v;
		
		for(int j=MAX_VALUE;j>=v;j--){
			if(ks[j-v]!=INT_MAX)
				ks[j] = min( ks[j], ks[j-v]+w );
		}

	}

	//taking biggest value whose weight is still under W
	for(int j=MAX_VALUE;j>=0;j--){
		if(ks[j]<=W){
			cout<<j<<endl;
			break;
		}
	}
}
