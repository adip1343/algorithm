#include <iostream>
#include <vector>
using namespace std;

int N;					//Number of items
int W;					//Capacity of Knapsack
int w;					//weights of item
int v;					//values of item
vector <long long> ks;	

// ks[w]=maximum value of knapsack containing exact weight w

int main(){
	cin>>N>>W;
	ks.resize(W+1,0);

	for(int i=1;i<=N;i++){
		cin>>w>>v;
		//we will update all relavent knapsacks for taking this item or not
		for(int j=W;j>=w;j--){
			ks[j] = max( ks[j] , ks[j-w]+v );
		} 
		//this is from W to w because it will take care 
		//that are not considering same item twice
	}

	//But we should consider all the knapsacks to get max value 
	
	long long MaxValue = 0;
	for(int i=1;i<=W;i++)
		MaxValue = max( MaxValue , ks[i] );

	cout<<MaxValue<<endl;
}
