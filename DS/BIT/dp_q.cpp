//https://atcoder.jp/contests/dp/tasks/dp_q

#include <iostream>
#include <climits>
#include <vector>

using namespace std;

#define lsb(i) ((i)&(-i))

int N;
vector <long long> h;	//heights
vector <long long> a;	//beauties
vector <long long> bit; //Binary Indexed Tree/Fenwick Tree

void update(int j,long long value){
	for(int i=j;i<=N;i+=lsb(i)){
		 bit[i] = max(value,bit[i]);
	}
}

long long getMax(int j){
	long long Max = 0;
	for(int i=j;i>0;i-=lsb(i)){
		Max = max(Max,bit[i]);
	}
	return Max;
}

int main(){
	cin>>N;

	h.resize(N+1);
	a.resize(N+1);
	bit.resize(N+1,0);

	for(int i=1;i<=N;i++)
		cin>>h[i];

	for(int i=1;i<=N;i++){
		cin>>a[i];
	}

	/*
	vector <long long> BestTill(N+1);
	long long best = 0;
	for(int i=2;i<=N;i++){
		best = a[i];
		for(int j=1;j<i;j++)
			if(h[j]<h[i])
				best = max(best,BestTill[j]);
		BestTill[i] = best + a[i];
	}
	This aproach is O(n²)
	TLE
	*/

	for(int i=1;i<=N;i++){
		update(h[i],getMax(h[i]-1)+a[i]);
	}
	// O(n*logn) 
	// From previous flowers we are getting
	// Max-beauty from flowers which have h[j]<h[i]
	// And Update Corresponding beauty h[i]
	// For Stricty increasing?
	// update(h[i], max(getMax(h[i]-1),a[i]) );

	cout<<getMax(N)<<endl;
}
